#include "common.c"
/* UDP */
void udp_create_server(int *sockfd,struct sockaddr_in *servaddr, struct sockaddr_in *cliaddr,config cfg){
	// Creating socket file descriptor 
	if ( (*sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		debug("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	memset(servaddr, 0, sizeof(*servaddr)); 
	memset(cliaddr, 0, sizeof(*cliaddr)); 
	// Filling server information 
	servaddr->sin_family = AF_INET; // IPv4 
	// servaddr->sin_addr.s_addr = INADDR_ANY; 
	servaddr->sin_addr.s_addr = htons(INADDR_ANY); 
	servaddr->sin_port = htons(cfg.udp_port);  

	// Bind the socket with the server address 
	//TODO: bind in a loop and cerate a proc for each bind
	if (bind(*sockfd,(const struct sockaddr *)servaddr,sizeof(*servaddr))<0) {
		debug("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	debug("udp server created");
}

//TODO check for errors while calling functions
int udp_send(int sock,struct sockaddr_in *cli,pdu msg){
	int len = sizeof(*cli);  //len is value/resuslt
	char buff[UDP_PDU_LEN+1];
	pdu2str(msg,buff);
	if(sendto(sock,(const char *)buff,UDP_PDU_LEN+1,0,(const struct sockaddr *)cli,len)<0){
		debug("error on sending UDP message");
		return -1;
	}
	return 0;
	debug("udp message sent");
}

int udp_recive(int sock,struct sockaddr_in *cli,pdu *msg){
	char buff[UDP_PDU_LEN+1];
	int len = sizeof(*cli);  //len is value/resuslt 
	debug("listening for udp messages");
	int n = recvfrom(sock,(char *)buff,UDP_PDU_LEN+1,MSG_WAITALL,(struct sockaddr *)cli,(unsigned int * restrict)&len); 
	buff[n] = '\0';
	if(n<0||n>UDP_PDU_LEN){
		debug("error while reciving an UDP message");
		return -1;
	}
	debug("udp message recived");
	str2pdu(buff,msg,UDP);
	return 0;
}
void udp_close(int sock){
	close(sock);
	debug("UDP server cloosed");
}
void udp_refuse(int sock,struct sockaddr_in *cli,pdu pd){
	pdu p;
	create_pdu(&p,REGISTER_REJ,"000000","000000000000",0,"client dosen't have permisions");
    udp_send(sock,cli,p);
    exit(0);//TODO: add fork wait
}

void udp_accept(config cfg,shared_mem *sh_mem,int n_cl){
	pdu p;
	char data[UDP_DATA_LEN];
	client cli=sh_mem->clis[n_cl];
    // strcpy(sh_mem->clis[n_cl].id,c.id);
    // strcpy(sh_mem->clis[n_cl].mac,c.mac);
    // sprintf(cli.num,"%06d",n);

    // sh_mem->clis[n_cl].cliaddr=*cli;
    // sh_mem->clis[n_cl].actual_state=REGISTERED;//TODO: tocheck
    // memcpy((void *)&sh_mem->clis[cl].cliaddr, (void *)cli, sizeof() );
	sprintf(data,"%d",cfg.tcp_port);
	create_pdu(&p,REGISTER_ACK,cfg.id,cfg.mac,atoi(cli.num),data);
	// printf("sending brhu");
    udp_send(cli.sock,cli.cliaddr,p);
	sh_mem->clis[n_cl].actual_state=WAIT_REG;
	reset_timer(sh_mem,n_cl);
	debug("client registered");
}
void udp_accept_conected(config cfg,shared_mem *sh_mem,int n_cli){
	pdu p;
	client cli=sh_mem->clis[n_cli];
	create_pdu(&p,REGISTER_ACK,cfg.id,cfg.mac,atoi(cli.num),cli.num);
    udp_send(cli.sock,cli.cliaddr,p);
}
void udp_naccept(int sock,struct sockaddr_in *cli){
	pdu p;
	create_pdu(&p,REGISTER_NACK,"000000","000000000000",0,"client dosen't have permisions");
    udp_send(sock,cli,p);
    //exit(0);//TODO: add fork wait
}

void reply_alive(config cfg,shared_mem *shm,int c){
	pdu p;
	client cl=shm->clis[c];
	create_pdu(&p,ALIVE_ACK,cfg.id,cfg.mac,atoi(cl.num),"");
	udp_send(cl.sock,cl.cliaddr,p);
}
void reject_alive(shared_mem *shm,int c){
	pdu p;
	client cl=shm->clis[c];
	create_pdu(&p,ALIVE_REJ,"000000","000000000000",0,"client dosen't have permisions");
	udp_send(cl.sock,cl.cliaddr,p);
}
void udp_timeout(int sockfd){
	struct timeval tv;
	tv.tv_sec = 4;
	tv.tv_usec = 0;
	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
}
// void reply_reject(int sock)
/*void udp_wait_alives(int sock,client c,struct sockaddr_in *cli,shared_mem *sh_mem,config cfg){
	pdu p;
	while (1){
		udp_recive(sock,cli,&p);
		if(p.type==ALIVE_INF){
			debug("alive recived id: %s",p.id);
			reply_alive(cfg,sh_mem);
		}else{
			// reply_reject(sock,cfg,cli)
			// tcp_reject;
		}
	}
	
}*/
/*void udp_attend_client(int sock,struct sockaddr_in *cli,client c,shared_mem *sh_mem,config cfg,int e){
	if(sh_mem->clis[e].actual_state==WAIT_REG||sh_mem->clis[e].actual_state==REGISTERED)//client alredy connected but neeed random number
        udp_accept_conected(sock,cfg,sh_mem,e);
	else if(sh_mem->clis[e].actual_state!=DISCONNECTED)//client alredy connected
		udp_naccept(sock,cli);
	else{//cli ok
		// sh_mem->clis[e].actual_state==DISCONNECTED
		debug("sent acceptaTION");
		udp_accept(sock,cli,cfg,sh_mem,e);
	}
	udp_wait_alives(sock,c,cli,sh_mem,cfg);
}*/
void disconnect_cli(shared_mem *shm,int i){
	debug("client disconnected for timeout id: %s",shm->clis[i].id);
	shm->clis[i].actual_state=DISCONNECTED;
}
void time_controller(shared_mem *shm){
	clock_t t;
	client c;
	while(1){
		for(int i=0;i<shm->n_clis;i++){
			c=shm->clis[i];
			if(c.actual_state!=DISCONNECTED){
				// printf("%s\n",c.id);
				t=time(NULL);
				if(c.timer<t-4)
					disconnect_cli(shm,i);
			}
		}
		
	}
}
void udp_attend_client(config cfg,pdu p,shared_mem *shm,int c){
	client cl=shm->clis[c];
	STATE s=cl.actual_state;
	if(p.type==REGISTER_REQ){
		if(s==DISCONNECTED){
			reset_timer(shm,c);
			shm->clis[c].actual_state=REGISTERED;
			udp_accept(cfg,shm,c);
		}else if(s==REGISTERED||s==ALIVE)
			udp_accept_conected(cfg,shm,c);
	}else if(p.type==ALIVE_INF){
		if(s==DISCONNECTED){
			reject_alive(shm,c);
			exit(0);
		}
		if(s==REGISTERED)
			shm->clis[c].actual_state=ALIVE;
		reply_alive(cfg,shm,c);
		reset_timer(shm,c);
	}
}
void udp_server(config cfg,shared_mem *sh_mem){//function for runing on udp proces
	int sockfd;
	pdu pdu;
	struct sockaddr_in servaddr, cliaddr; 
    // client c;
	int cli;
	// signal(SIGINT, handle_sigint);
	udp_create_server(&sockfd,&servaddr,&cliaddr,cfg);////////////////////////////////////////
	// time_contr
	while(1){
		udp_recive(sockfd,&cliaddr,&pdu);
		
		cli=check_client(*sh_mem,pdu.mac,pdu.id);
		// printf("%d %d %d\n",cli,strcmp(pdu.id,(*sh_mem).clis[2].id),strcmp(pdu.mac,(*sh_mem).clis[2].mac));
		// printf("%s %s\n",(*sh_mem).clis[2].id,(*sh_mem).clis[2].mac);
		if(cli==-1){
			udp_refuse(sockfd,&cliaddr,pdu);
		}else{
			debug("client can be accepted");
        	if(sh_mem->clis[cli].actual_state==DISCONNECTED)
				set_client(sh_mem,cli,sockfd,get_rand(),&cliaddr);
			//TODO:check another time pls
			// int pid=fork();
	        udp_attend_client(cfg,pdu,sh_mem,cli);
			// exit(0);
			// }
		}
		memset(&cliaddr, 0, sizeof(cliaddr)); 
	}
	// create_pdu(&pdu,REGISTER_REQ,"000001","111111111111","hola puta");
	// udp_send(sockfd,&cliaddr,pdu);
	udp_close(sockfd);
	exit(0);
}