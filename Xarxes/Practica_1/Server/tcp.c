#include "common.c"
#define W 3
/* TCP */
void tcp_create_server(int *sockfd,struct sockaddr_in *servaddr,struct sockaddr_in *cliaddr,config cfg){
	if ( (*sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) { 
		debug("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	memset(servaddr, 0, sizeof(*servaddr)); 
	memset(cliaddr, 0, sizeof(*cliaddr)); 
	servaddr->sin_family = AF_INET; 
	servaddr->sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr->sin_port = htons(cfg.tcp_port);//TODO add port parameter
	//if (bind(*sockfd,(const struct sockaddr *)servaddr,sizeof(*servaddr))<0) {
	if ((bind(*sockfd, (const struct sockaddr *)servaddr, sizeof(*servaddr))) != 0) { 
		debug("TCP socket bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	else
		debug("TCP socket successfully binded"); 
  
	// Now server is ready to listen and verification 
	if ((listen(*sockfd, TCP_MAX_CONN)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
   
}
void tcp_send(int sock,pdu msg,struct sockaddr_in *cli){
	char buff[TCP_PDU_LEN+1];
	int len=sizeof(*cli);
	pdu2str(msg,buff);
	// write(sock, buff, TCP_PDU_LEN+1); 
	sendto(sock, buff, TCP_PDU_LEN, 0, (struct sockaddr *)cli,len);
	debug("TCP message sent");
}
void tcp_recive(int sock,pdu *msg,struct sockaddr_in *cli){
	char buff[TCP_PDU_LEN+1];
	int len=sizeof(*cli);
	// int n=read(sock, buff, sizeof(buff));
	int n = recvfrom(sock,(char *)buff,TCP_PDU_LEN,MSG_WAITALL,(struct sockaddr *)cli,(unsigned int * restrict)&len); 
	buff[n]='\0';
	debug("TCP message recived");
	str2pdu(buff,msg,TCP);
}
void tcp_close(int socketfd){
	close(socketfd);
	exit(0);
}



void tcp_error(){

}
void tcp_reject(){

}
/* ACTIONS */
void wait_file(int sock,client cli,config cfg,char file[],struct sockaddr_in *cl){/////////////////////////////////////////////////////////////////////////
	// char buff[TCP_PDU_LEN];
	pdu p;
	// int ret,i=0;
	// fd_set rfds;
	// struct timeval tv;
	//TODO: track file creation error
	FILE *f=fopen(file,"w");
	// tv.tv_sec = W; 
	// tv.tv_usec = 0;
	// FD_ZERO(&rfds);
	// FD_SET(sock, &rfds);
	do{
		//TODO:add timing
		// ret=select(sock+1, &rfds, NULL, NULL, &tv);
		debug("waiting for client to send file");
		// if(ret==-1){
		// TODO: check errors
		// printf("tens un putu error joder\n");
		// }else{
			tcp_recive(sock,&p,cl);
			// printf("paquete bro %d\n",i++);
			//TODO: add/test timeout
			if(check_pdu(cli,p)){
				tcp_reject(sock);
			}
			//TODO: check_pdu()
			if(p.type==PUT_DATA){
				fprintf(f,"%s",p.data);
			}
		// }
	}while(p.type==PUT_DATA);
	if(p.type!=PUT_END){
		//TODO: ERRRRRRRRRRRRRROOOOOOOOOOOOOOOOOOR
	}
	fclose(f);
	// fclose(sock);
}
void send_file(int sock,client cli,config cfg,char file[],struct sockaddr_in *c){///////////////////////////////////////////////////////////////////////////////////////////////
	pdu p;
	// int i=0;
	char *buff;//TODO:ADD LINE LEN
	// char *buff[200];//TODO:ADD LINE LEN
	// char st[TCP_PDU_LEN];//TODO:ADD LINE LEN
	size_t len=0;
	FILE *f=fopen(file,"r");
	if(f<(FILE*)0){
		//error
		printf("error\n");
	}
	// printf("%s\n",file);
	create_pdu(&p,GET_DATA,cfg.id,cfg.mac,atoi(cli.num),"");
	while (getline(&buff, &len, f)!=-1) {
		strcpy(p.data,buff);
		tcp_send(sock,p,c);
	}
	p.type=GET_END;
	free(buff);
	strcpy(p.data,"");
	tcp_send(sock,p,c);
	// fclose(tt);
	fclose(f);
}
//send file to client
void put_file(int sock,pdu msg,client cli,config cfg,struct sockaddr_in *c){
	pdu p;
	int e;
	char buff[TCP_PDU_LEN];
	// FILE *f;
	create_pdu(&p,GET_ACK,cfg.id,cfg.mac,atoi(cli.num),buff);
	e=check_pdu(cli,msg);
	// printf("%d\n",e);
	if(e){
		// printf("vaig a enviar file\n");
		sprintf(buff,"%s.cfg",cli.id);
		tcp_send(sock,p,c);
		send_file(sock,cli,cfg,buff,c);
		// printf("----------------vaig a enviar file\n");
	}
	//TODO: tancar canal tcp;
}
//get file from client
void get_file(int sock,pdu recived,client cli,config cfg,struct sockaddr_in *c){
	pdu p;
	// int e;
	char buff[TCP_DATA_LEN];
	//check client
	create_pdu(&p,PUT_ACK,cfg.id,cfg.mac,atoi(cli.num),buff);
	if(check_pdu(cli,recived)){
		sprintf(buff,"%s.cfg",cli.id);
		tcp_send(sock,p,c);
		wait_file(sock,cli,cfg,buff,c);
	}else{
		//TODO: add reject if data isn't correct
		create_pdu(&p,PUT_REJ,cfg.id,cfg.mac,atoi(cli.num),"");
		tcp_send(sock,p,c);
	}
	//close client()
	//TODO: tancar canal tcp;
}
void choose_act(int sock,client cli,pdu p,config cfg,struct sockaddr_in *cl){
	switch(p.type){
		case PUT_FILE:
			get_file(sock,p,cli,cfg,cl);
			break;
		case GET_FILE:
			put_file(sock,p,cli,cfg,cl);
			break;
		default:
			break;
	}
}
void tcp_attend_client(int sock,config cfg,shared_mem *shm,struct sockaddr_in *cli){////////////////////////////////////////////////////////////////////////
	pdu p;
	//read()
	// while(){
	// printf("hola he fet tcp");
	tcp_recive(sock,&p,cli);
	int cl=check_client(*shm,p.mac,p.id);
	choose_act(sock,shm->clis[cl],p,cfg,cli);
	tcp_close(sock);
	// }
}
void tcp_server(config cfg,shared_mem *shm){
	int sockfd,len,pid,client;
	// pdu pdu;
	struct sockaddr_in servaddr, cliaddr;
	tcp_create_server(&sockfd,&servaddr,&cliaddr,cfg);
	len = sizeof(cliaddr);
	//TODO get signal to end proces
	while(1){
		client = accept(sockfd, (struct sockaddr*)&cliaddr, (socklen_t *restrict)&len); 
		if (client < 0) { 
			debug("server acccept failed...\n"); 
		}
		else{
			pid=fork();
			if(pid!=0)
				tcp_attend_client(client,cfg,shm,&cliaddr);
		}
			printf("server acccept the client...\n"); 
  
	}
  
	//TODO: on each accept make a fork to talk to each client
	// int pid=fork();
	// if(pid==0)trate_client(connfd);
	/*while(1){
		udp_recive(sockfd,&cliaddr,&pdu);
		//TODO:check another time pls
		int pid=fork();
		if(pid==0)
			udp_attend_client(&cliaddr,pdu);
		else
			memset(cliaddr, 0, sizeof(*cliaddr)); 
	}*/
	exit(0);
}