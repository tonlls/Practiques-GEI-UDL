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
	char buff[PDU_LEN+1];
	int size=pdu2str(msg,buff);
	// printf("(%d) -> %s",size,buff);
	if(sendto(sock,(const char *)buff,PDU_LEN+1,0,(const struct sockaddr *)cli,len)<0){
		debug("error on sending UDP message");
		//TODO return error from enum if needed
		return -1;
	}
	debug("udp message sent");
	// printf("\nerror: %d\n",x);
	// printf("Oh dear, %s\n", strerror(errno));

}

int udp_recive(int sock,struct sockaddr_in *cli,pdu *msg){
	char buff[PDU_LEN+1];
	int len = sizeof(*cli);  //len is value/resuslt 
	debug("listening for udp messages");
	int n = recvfrom(sock,(char *)buff,PDU_LEN+1,MSG_WAITALL,(struct sockaddr *)cli,(unsigned int * restrict)&len); 
	buff[n] = '\0';
	if(n<0){
		debug("error while reciving an UDP message");
		return -1;
	}
	debug("udp message recived");
	str2pdu(buff,msg);
	return 0;
}
void udp_close(int sock){
	close(sock);
	debug("UDP server cloosed");
}
void udp_refuse(int sock,struct sockaddr_in *cli){
	pdu p;
	create_pdu(&p,REGISTER_REJ,"000000","000000000000",0,"client dosen't have permisions");
    udp_send(sock,cli,p);
    exit(0);//TODO: add fork wait
}
void udp_accept(int sock,struct sockaddr_in *cli,config cfg,shared_mem *sh_mem,int n_cl){
	pdu p;
    int n=get_rand();
	char data[DATA_LEN];
    // strcpy(sh_mem->clis[n_cl].id,c.id);
    // strcpy(sh_mem->clis[n_cl].mac,c.mac);
    sprintf(sh_mem->clis[n_cl].num,"%06d",n);
    sh_mem->clis[n_cl].cliaddr=*cli;
    sh_mem->clis[n_cl].actual_state=REGISTERED;//TODO: tocheck
    // memcpy((void *)&sh_mem->clis[cl].cliaddr, (void *)cli, sizeof() );
	sprintf(data,"%d",cfg.tcp_port);
	create_pdu(&p,REGISTER_ACK,cfg.id,cfg.mac,n,data);
    udp_send(sock,cli,p);
}
void udp_accept_conected(int sock,config cfg,shared_mem *sh_mem,int n_cli){
	pdu p;
	create_pdu(&p,REGISTER_ACK,cfg.id,cfg.mac,atoi(sh_mem->clis[n_cli].num),sh_mem->clis[n_cli].num);
    udp_send(sock,&sh_mem->clis[n_cli].cliaddr,p);
}
void udp_naccept(int sock,struct sockaddr_in *cli){
	pdu p;
	create_pdu(&p,REGISTER_NACK,"000000","000000000000",0,"client dosen't have permisions");
    udp_send(sock,cli,p);
    //exit(0);//TODO: add fork wait
}
void set_client(client *c,pdu p){
    strcpy(c->id,p.id);
    strcpy(c->mac,p.mac);
}
void udp_attend_client(int sock,struct sockaddr_in *cli,client c,shared_mem *sh_mem,config cfg){
	int e=check_client(c,*sh_mem);
	if(e==-1)//error el client no te permis
		udp_refuse(sock,cli);
	else if(sh_mem->clis[e].actual_state==ALIVE||sh_mem->clis[e].actual_state==REGISTERED)//client alredy connected but neeed random number
        udp_accept_conected(sock,cfg,sh_mem,e);
	else if(sh_mem->clis[e].actual_state!=DISCONNECTED)//client alredy connected
		udp_naccept(sock,cli);
	else{//cli ok
		udp_accept(sock,cli,cfg,sh_mem,e);
	}

}
void udp_server(config cfg,shared_mem *sh_mem){//function for runing on udp proces
	int sockfd;
	pdu pdu;
	struct sockaddr_in servaddr, cliaddr; 
    client c;
	udp_create_server(&sockfd,&servaddr,&cliaddr,cfg);////////////////////////////////////////
	// while(1){
		udp_recive(sockfd,&cliaddr,&pdu);
        set_client(&c,pdu);
		//TODO:check another time pls
		int pid=fork();
		if(pid==0)
	        udp_attend_client(sockfd,&cliaddr,c,sh_mem,cfg);
		else
			memset(&cliaddr, 0, sizeof(cliaddr)); 
	//}
	// printf("%s\n",pdu.data);
	// create_pdu(&pdu,REGISTER_REQ,"000001","111111111111","hola puta");
	udp_send(sockfd,&cliaddr,pdu);
	udp_close(sockfd);
	exit(0);
}