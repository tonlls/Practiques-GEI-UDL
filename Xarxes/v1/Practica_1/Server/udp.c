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
	servaddr->sin_addr.s_addr = htons(INADDR_ANY); 
	servaddr->sin_port = htons(cfg.udp_port);  

	// Bind the socket with the server address 
	if (bind(*sockfd,(const struct sockaddr *)servaddr,sizeof(*servaddr))<0) {
		debug("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	debug("udp server created");
}

//TODO check for errors while calling functions
int udp_send(int sock,struct sockaddr_in *cli,pdu msg){
	int len = sizeof(*cli);  
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
	int len = sizeof(*cli);
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
    exit(0);
}

void udp_accept(config cfg,shared_mem *sh_mem,int n_cl){
	pdu p;
	char data[UDP_DATA_LEN];
	client cli=sh_mem->clis[n_cl];
	sprintf(data,"%d",cfg.tcp_port);
	create_pdu(&p,REGISTER_ACK,cfg.id,cfg.mac,atoi(cli.num),data);
    udp_send(cli.sock,cli.cliaddr,p);
	
	reset_timer(sh_mem,n_cl);
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
	char str[20];
	// int e;
	if(p.type==REGISTER_REQ){
		// e=check_pdu_ip()
		if(s==DISCONNECTED){
			reset_timer(shm,c);
			shm->clis[c].actual_state=WAIT_REG;
			get_state(shm->clis[c].actual_state,str);
			debug("client with id=%s state => %s",cl.id,str);
			udp_accept(cfg,shm,c);
			shm->clis[c].actual_state=REGISTERED;
			get_state(shm->clis[c].actual_state,str);
			debug("client with id=%s state => %s",cl.id,str);
		}else if(s==REGISTERED||s==ALIVE)
			udp_accept_conected(cfg,shm,c);
	}else if(p.type==ALIVE_INF){
		if(s==DISCONNECTED){
			reject_alive(shm,c);
			exit(0);
		}
		if(s==REGISTERED){
			shm->clis[c].actual_state=ALIVE;
			get_state(shm->clis[c].actual_state,str);
			debug("client with id=%s stat => %s",cl.id,str);
		}
		reply_alive(cfg,shm,c);
		reset_timer(shm,c);
	}
}
void udp_server(config cfg,shared_mem *sh_mem){//function for runing on udp proces
	int sockfd;
	pdu pdu;
	struct sockaddr_in servaddr, cliaddr; 
	int cli;
	udp_create_server(&sockfd,&servaddr,&cliaddr,cfg);
	while(1){
		udp_recive(sockfd,&cliaddr,&pdu);
		
		cli=check_client(*sh_mem,pdu.mac,pdu.id);
		if(cli==-1){
			udp_refuse(sockfd,&cliaddr,pdu);
		}else{
			// debug("client can be accepted");
        	if(sh_mem->clis[cli].actual_state==DISCONNECTED)
				set_client(sh_mem,cli,sockfd,get_rand(),&cliaddr);
	        udp_attend_client(cfg,pdu,sh_mem,cli);
		}
		memset(&cliaddr, 0, sizeof(cliaddr)); 
	}
	udp_close(sockfd);
	exit(EXIT_SUCCESS);
}