#include "common.c"
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
	if ((listen(sockfd, TCP_MAX_CONN)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
   
}
void tcp_send(int sock,pdu msg){
	char buff[TCP_PDU_LEN+1];
	pdu2str(msg,buff);
	write(sock, buff, sizeof(buff)); 
	debug("TCP message sent");
}
void tcp_recive(int sock,pdu *msg){
	char buff[TCP_PDU_LEN+1];
	int n=read(sock, buff, sizeof(buff));
	debug("TCP message recived");
	str2pdu(buff,msg);
}
void tcp_close(int *socketfd){
	close(socketfd);
	exit(0);
}
/* ACTIONS */
void wait_file(int sock,char file[]){/////////////////////////////////////////////////////////////////////////
	char buff[TCP_PDU_LEN];
	pdu p;
	int ret,rfds;
	//TODO: track file creation error
	FILE *f=fopen(file,"w");
	FD_ZERO(&rfds);
    FD_SET(sock, &rfds);
	do{
		//TODO:add timing
		ret=select(sock+1, &rfds, NULL, NULL, NULL);
		debug("waiting for client to send file");
		if(ret==-1){
		//TODO: check errors
		}else{
			tcp_recive(sock,buff);
			str2pdu(buff,&p);
			//TODO: check_pdu()
			if(p.type==PUT_DATA){
				fprintf(f,"%s\n",p.data);
			}
		}
	}while(p.type==PUT_DATA);
	if(p.type!=PUT_END){
		//TODO: ERRRRRRRRRRRRRROOOOOOOOOOOOOOOOOOR
	}
	fclose(f);
	// fclose(sock);
}
void send_file(int sock,client cli,config cfg,char file[]){///////////////////////////////////////////////////////////////////////////////////////////////
	pdu p;
	char buff[200];//TODO:ADD LINE LEN
	size_t len=0;
	FILE *f=fopen(file,"r");
	if(f<0){
		//error
	}
	create_pdu(&p,GET_DATA,cfg.id,cfg.mac,atoi(cli.num),"");
	while (getline(&buff, &len, f)!=-1) {
		strcpy(p.data,buff);
		tcp_send(sock,&p);
        // printf("Retrieved line of length %zu:\n", read);
        printf("%s", line);
    }
	p.type=GET_END;
	strcpy(p.data,"");
	tcp_send(sock,&p);
}
//send file to client
void put_file(int sock,pdu msg,client cli,config cfg){
	pdu p;
	int e;
	char buff[TCP_PDU_LEN];
	FILE *f;
	if(check_pdu(cli,msg)){
		sprintf(buff,"%s.cfg",cli.id);
		create_pdu(&p,GET_ACK,cfg.id,cfg.mac,atoi(cli.num),buff);
		tcp_send(sock,p);
		send_file(sock,cli,cfg,buff);
	}
	//TODO: tancar canal tcp;
}
//get file from client
void get_file(int sock,pdu recived,client cli,client me){
	pdu p;
	int e;
	char buff[DATA_LEN];
	//check client
	if(check_pdu(cli,recived)){
		sprintf(buff,"%s.cfg",cli.id);
		create_pdu(&p,PUT_ACK,cfg.id,cfg.mac,atoi(cli.num),buff);
		tcp_send(sock,p);
		wait_file(sock,buff);
	}else{
		//TODO: add reject if data isn't correct
		create_pdu(&p,PUT_REJ,cfg.id,cfg.mac,atoi(cli.num),"");
		tcp_send(sock,p);
	}
	//close client()
	//TODO: tancar canal tcp;
}
void choose_act(int sock,client cli,pdu p,client me){
	switch(p.type){
		case PUT_FILE:
			get_file(sock,cli,me);
			break;
		case GET_FILE:
			put_file(sock,cli,me);
			break;
		case ALIVE_INF:
			break;
		case default:
			break;
	}
}
void tcp_attend_client(int sock,config cfg){////////////////////////////////////////////////////////////////////////
	pdu p;
	//read()
	tcp_recive();
	choose_act(p);
}
void tcp_server(config cfg){
	int sockfd,len,pid,client;
	pdu pdu;
	struct sockaddr_in servaddr, cliaddr;
	tcp_create_server(&sockfd,&servaddr,&cliaddr,cfg);
	len = sizeof(cliaddr);
	//TODO get signal to end proces
	while(1){
		client = accept(sockfd, (struct sockaddr_in*)&cliaddr, &len); 
		if (client < 0) { 
			debug("server acccept failed...\n"); 
		}
		else{
			pid=fork();
			if(pid!=0)
				tcp_attend_client(client,cfg);
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