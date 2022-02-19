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
	servaddr->sin_port = htons(cfg.tcp_port);
	if ((bind(*sockfd, (const struct sockaddr *)servaddr, sizeof(*servaddr))) < 0) { 
		debug("TCP socket bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	else
		debug("TCP socket successfully binded"); 
  
	// Now server is ready to listen and verification 
	if ((listen(*sockfd, TCP_MAX_CONN)) != 0) { 
		debug("Listen failed..."); 
		exit(EXIT_FAILURE); 
	} 
	else
		debug("Server listening..."); 
   
}
void tcp_send(int sock,pdu msg,struct sockaddr_in *cli){
	char buff[TCP_PDU_LEN+1];
	int len=sizeof(*cli);
	pdu2str(msg,buff);
	sendto(sock, buff, TCP_PDU_LEN, 0, (struct sockaddr *)cli,len);
	debug("TCP message sent");
}
void tcp_recive(int sock,pdu *msg,struct sockaddr_in *cli){
	char buff[TCP_PDU_LEN+1];
	int len=sizeof(*cli);
	int n = recvfrom(sock,(char *)buff,TCP_PDU_LEN,MSG_WAITALL,(struct sockaddr *)cli,(unsigned int * restrict)&len); 
	buff[n]='\0';
	debug("TCP message recived");
	str2pdu(buff,msg,TCP);
}
void tcp_close(int socketfd){
	debug("closing TCP socket");
	close(socketfd);
}
void tcp_reject(int sock,struct sockaddr_in *addr,ERROR e,PDU_TYPE pt){
	pdu p;
	char buf[50];
	get_err(e,buf);
	create_pdu(&p,pt,"000000","000000000000",0,buf);
	tcp_send(sock,p,addr);
}
/* ACTIONS */
void wait_file(int sock,client cli,config cfg,char file[],struct sockaddr_in *cl,int n,shared_mem shm){
	pdu p;
	int e;
	FILE *f=fopen(file,"w");
	do{
		debug("waiting for client to send file");
		tcp_recive(sock,&p,cl);
		e=check_pdu_ip(p,*cl,shm,n);
		if(e!=0){
			tcp_reject(sock,cl,e,PUT_REJ);
			fclose(f);
			exit(EXIT_FAILURE);
		}
		if(p.type==PUT_DATA){
			fprintf(f,"%s",p.data);
		}
	}while(p.type==PUT_DATA);
	if(p.type!=PUT_END){
		debug("error");
	}
	fclose(f);
}
void send_file(int sock,client cli,config cfg,char file[],struct sockaddr_in *c,int n,shared_mem shm){
	pdu p;
	char *buff;
	size_t len=0;
	FILE *f=fopen(file,"r");
	if(f<(FILE*)0){
		debug("error on file opening");
		exit(EXIT_FAILURE);
	}
	create_pdu(&p,GET_DATA,cfg.id,cfg.mac,atoi(cli.num),"");
	while (getline(&buff, &len, f)!=-1) {
		strcpy(p.data,buff);
		tcp_send(sock,p,c);
	}
	p.type=GET_END;
	free(buff);
	strcpy(p.data,"");
	tcp_send(sock,p,c);
	fclose(f);
}
//send file to client
void put_file(int sock,pdu msg,client cli,config cfg,struct sockaddr_in *c,shared_mem *shm,int n){
	pdu p;
	char buff[TCP_PDU_LEN];
	int e=check_pdu_ip(msg,*c,*shm,n);
	create_pdu(&p,GET_ACK,cfg.id,cfg.mac,atoi(cli.num),buff);
	if(e==0){
		sprintf(buff,"%s.cfg",cli.id);
		tcp_send(sock,p,c);
		send_file(sock,cli,cfg,buff,c,n,*shm);
	}else{
		tcp_reject(sock,c,e,PUT_REJ);
	}
}
//get file from client
void get_file(int sock,pdu recived,client cli,config cfg,struct sockaddr_in *c,shared_mem *shm,int n){
	pdu p;
	char buff[TCP_DATA_LEN];
	int e1=check_pdu_ip(recived,*c,*shm,n);
	create_pdu(&p,PUT_ACK,cfg.id,cfg.mac,atoi(cli.num),buff);
	if(e1==0){
		sprintf(buff,"%s.cfg",cli.id);
		tcp_send(sock,p,c);
		wait_file(sock,cli,cfg,buff,c,n,*shm);
		debug("saved file %s",cli.id); 
	}else{
		tcp_reject(sock,c,e1,PUT_REJ);
	}
}
void choose_act(int sock,client cli,pdu p,config cfg,struct sockaddr_in *cl,shared_mem *shm,int n){
	switch(p.type){
		case PUT_FILE:
			get_file(sock,p,cli,cfg,cl,shm,n);
			break;
		case GET_FILE:
			put_file(sock,p,cli,cfg,cl,shm,n);
			break;
		default:
			break;
	}
}
void tcp_attend_client(int sock,config cfg,shared_mem *shm,struct sockaddr_in *cli){
	pdu p;
	tcp_recive(sock,&p,cli);
	int cl=check_client(*shm,p.mac,p.id);
	int e1=check_pdu_ip(p,*cli,*shm,cl);
	
	PDU_TYPE t;
	if(p.type==GET_FILE)t=GET_REJ;
	else if(p.type==PUT_FILE)t=PUT_REJ;
	else{
		tcp_close(sock);
		exit(EXIT_FAILURE);
	}
	if(e1==0){
		choose_act(sock,shm->clis[cl],p,cfg,cli,shm,cl);
	}else{
		tcp_reject(sock,cli,e1,t);
	}
	tcp_close(sock);
}
void tcp_server(config cfg,shared_mem *shm){
	int sockfd,len,pid,client;
	struct sockaddr_in servaddr, cliaddr;
	tcp_create_server(&sockfd,&servaddr,&cliaddr,cfg);
	len = sizeof(cliaddr);
	while(1){
		client = accept(sockfd, (struct sockaddr*)&cliaddr, (socklen_t *restrict)&len); 
		if (client < 0) { 
			debug("server acccept failed..."); 
		}
		else{
			pid=fork();
			if(pid!=0){
				tcp_attend_client(client,cfg,shm,&cliaddr);
				close(client);
				exit(EXIT_SUCCESS);
			}
		}
		debug("server acccept the client"); 
  
	}
	exit(0);
}