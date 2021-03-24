// Server side implementation of UDP client-server model 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdarg.h>
#include <string.h> 
#include <ctype.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <sys/select.h>
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <sys/ipc.h>
#include <sys/shm.h>

#include <errno.h>

 
#define MAX_MSG_SIZE 10000

#define MAX_CLI 10

#define TCP_MAX_CONN 5

#define MAX_FILENAME 100

#define ID_LEN 7
#define MAC_LEN 13
#define RAND_LEN 7
#define DATA_LEN 50
#define PDU_LEN (ID_LEN+MAC_LEN+RAND_LEN+DATA_LEN+1)


int DEBUG=0;

typedef enum t_STATE{
	DISCONNECTED=0,
	WAIT_REG=1,
	REGISTERED=2,
	ALIVE=3
}STATE;
typedef enum t_ERROR{
	UDP_CREATION_ERR,
	UDP_MSG_SEND_ERR
}ERROR_;
typedef enum t_PDU_TYPE{
	REGISTER_REQ=0x10,
	REGISTER_ACK=0x11,
	REGISTER_NACK=0x12,
	REGISTER_REJ=0x13,
	ERROR=0x19,
	ALIVE_INF=0x20,
	ALIVE_ACK=0x21,
	ALIVE_NACK=0x22,
	ALIVE_REJ=0x23,
	PUT_FILE=0x30,
	PUT_DATA=0x31,
	PUT_ACK=0x32,
	PUT_NACK=0x33,
	PUT_REJ=0x34,
	PUT_END=0x35,
	GET_FILE=0x40,
	GET_DATA=0x41,
	GET_ACK=0x42,
	GET_NACK=0x43,
	GET_REJ=0x44,
	GET_END=0x45
}PDU_TYPE;

typedef struct t_pdu{
	PDU_TYPE type;
	char id[ID_LEN];
	char mac[MAC_LEN];
	char num[RAND_LEN];
	char data[DATA_LEN];
}pdu;
typedef struct t_client{
	STATE actual_state;
	char id[ID_LEN];
	char mac[MAC_LEN];
	char num[RAND_LEN];
	struct sockaddr_in cliaddr;
	int sock;
}client;
typedef struct t_shared_mem{
	client clis[MAX_CLI];
	int n_clis;
}shared_mem;
typedef struct t_config{
	char id[ID_LEN];
	char mac[MAC_LEN];
	int udp_port;
	int tcp_port;
}config;
/* SHARED MEMORY */

/*  UTILS  */
void error(char str[]){
	if(DEBUG)
		printf("ERROR: %s",strerror(errno));
}
int debug(const char *format, ...){
	if(DEBUG){
		printf("%s", "DEBUG: ");
		va_list ptr;
		va_start(ptr, format);
		int done=vprintf(format, ptr);
		va_end(ptr);
		printf("\n");
		return done;
	}
}
/* checks if string is ip or not */
int itsip(char str[]){
	int i=0;
	char c;
	while(i<4){
		if(c=='.')
			i++;
		else 
			if(!isdigit(c))
				return 0;
	}
	return 1;
}
/*void ddebug(char msg[]){
	if(DEBUG)
		printf("DEBUG: %s\n",msg);
}*/

/* transforms to string a pdu struct variable */
void str2pdu(char buff[],pdu *msg){
	char data[4][DATA_LEN];
	char str[DATA_LEN];
	int j=1,k=0;
	for(int i=0;i<4;i++){
		k=0;
		while(buff[j]!='\0'){
			str[k++]=(char)buff[j++];
		}
		str[k]='\0';
		j++;
		strcpy(data[i],str);
	}
	msg->type=buff[0];
	strcpy(msg->id,data[0]);
	strcpy(msg->mac,data[1]);
	strcpy(msg->num,data[2]);
	strcpy(msg->data,data[3]);

}
void concat(char dest[],char source[],int start){
	int l=strlen(source);
	int i;
	int j=start;
	for(i=0;i<=l;i++){
		dest[i+j]=source[i];
	}
}
int pdu2str(pdu pdu,char str[]){
	//str[0]='\0';
	// sprintf(str,"%s\0%s\0","hola","puta");
	// sprintf(str,"%c%s?%s?%s?%s?",pdu.type,pdu.id,pdu.mac,pdu.num,pdu.data);
	int s=0;
	str[0]=pdu.type;
	s=1;
	concat(str,pdu.id,s);
	s+=strlen(pdu.id)+1;
	concat(str,pdu.mac,s);
	s+=strlen(pdu.mac)+1;
	concat(str,pdu.num,s);
	s+=strlen(pdu.num)+1;
	concat(str,pdu.data,s);

	/*int l=strlen(str);
	for(int i=0;i<l;i++){
		if(str[i]=='?')
			str[i]='\0';
	}*/
	// return s;
	return 1+strlen(pdu.id)+strlen(pdu.mac)+strlen(pdu.num)+strlen(pdu.data);

}


void create_pdu(pdu *pdu,PDU_TYPE type,char id[ID_LEN],char mac[MAC_LEN],char data[DATA_LEN]){
	pdu->type=type;
	strcpy(pdu->id,id);
	strcpy(pdu->mac,mac);
	strcpy(pdu->num,"00000\0");
	strcpy(pdu->data,data);
}


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
	char buff[PDU_LEN+1];
	pdu2str(msg,buff);
	write(sock, buff, sizeof(buff)); 
	debug("TCP message sent");
}
void tcp_recive(int sock,pdu *msg){
	char buff[PDU_LEN+1];
	read(sock, buff, sizeof(buff));
	debug("TCP message recived");
	str2pdu(buff,msg);
}
void tcp_close(int *socketfd){
	close(socketfd);
}
/* ACTIONS */
void wait_file(int sock,char file[]){/////////////////////////////////////////////////////////////////////////
	char buff[PDU_LEN];
	pdu p;
	int ret;
	//TODO: track file creation error
	FILE *f=fopen(file,"w");
	FD_ZERO(&rfds);
    FD_SET(sock, &rfds);
	do{
		//TODO:add timing
		ret=select(sock+1, &rfds, NULL, NULL, NULL);
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
	close(f);
	// close(sock);
}
void send_file(int sock,char file[]){///////////////////////////////////////////////////////////////////////////////////////////////
	pdu p;
	do{
		tcp_send(sock,&p);

	}while();
}
//send file to client
void get_file(int sock,pdu msg,client cli,client me){
	pdu p;
	int e;
	char buff[PDU_LEN];
	FILE *f;
	if(check_pdu(cli,msg)){
		sprintf(buff,"%s.cfg",cli.id);
		create_pdu(&p,GET_DATA,me.id,me.mac,buff);
		tcp_send(sock,p);
		send_file(sock,buff);
	}
}
//get file from client
void put_file(int sock,pdu recived,client cli,client me){
	pdu p;
	int e;
	char buff[DATA_LEN];
	//check client
	if(check_pdu(cli,recived)){
		sprintf(buff,"%s.cfg",cli.id);
		create_pdu(&p,PUT_ACK,me.id,me.mac,buff);
		tcp_send(sock,p);
		wait_file(sock,buff);
	}else{
		//TODO: add reject if data isn't correct
		create_pdu(&p,PUT_REJ,me.id,me.mac,me)
		tcp_send(sock,p);
	}
	//close client()
}
int check_pdu(client cli,pdu msg){
	return strcmp(cli.id,msg.id)==0&&strcmp(cli.mac,msg.mac)==0&&strcmp(cli.num,msg.num)==0&&
}
void choose_act(int sock,client cli,pdu p,client me){
	switch(p.type){
		case PUT_FILE:
			put_file(sock,cli,me);
			break;
		case GET_FILE:
			get_file(sock,cli,me);
			break;
	}
}
/////////////////////////

void tcp_attend_client(config cfg){////////////////////////////////////////////////////////////////////////
	pdu p;
	//read()
	//tcp_recive();
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
				tcp_attend_client(cfg);
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

void udp_recive(int sock,struct sockaddr_in *cli,pdu *msg){
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
}
void udp_close(int sock){
	close(sock);
	debug("UDP server cloosed");
}
void read_clients(char file[],shared_mem *sh_mem){
	int e;
	FILE *fd=fopen(file,"r");
	char id[ID_LEN],mac[MAC_LEN],c[2];
	client cli;
	do{
		e=fscanf(fd,"%s %s",id,mac);
		if(e==2){
			strcpy(sh_mem->clis[sh_mem->n_clis].id,id);
			strcpy(sh_mem->clis[sh_mem->n_clis].mac,mac);
			sh_mem->clis[sh_mem->n_clis].actual_state=DISCONNECTED;
			sh_mem->n_clis++;
		}
		read(fd,id,1);
	}while(feof(fd));
	fclose(fd);
}
//TODO: repair function to use shared memory
int check_client(client c,shared_mem sh_mem){
	//TODO: check ips
	// char str[INET_ADDRSTRLEN];
	// inet_ntop( AF_INET, &ipAddr, str, INET_ADDRSTRLEN );
	for(int i=0;i<sh_mem.n_clis;i++){
		if(strcmp(c.id,sh_mem.clis[i].id)==0&&strcmp(c.mac,sh_mem.clis[i].mac)==0)
			return i;
	}
	return -1;
}
void udp_refuse(){
	pdu p;
	create_pdu(&p,REGISTER_ACK,)
}
void udp_accept(){
	pdu p;
	create_pdu(&p,)

}
void udp_attend_client(client c,shared_mem sh_mem){
	//check client
	int e=check_client(c,sh_mem);
	if(e==-1)//error el client no te permis
		udp_refuse();
	else if(sh_mem.clis[e].actual_state!=0)//client alredy connected
		udp_refuse();
	else{//cli ok
		udp_accept();
	}

}
void udp_server(config cfg){//function for runing on udp proces
	int sockfd;
	pdu pdu;
	struct sockaddr_in servaddr, cliaddr; 
	udp_create_server(&sockfd,&servaddr,&cliaddr,cfg);////////////////////////////////////////
	// while(1){
		udp_recive(sockfd,&cliaddr,&pdu);
		//TODO:check another time pls
		// int pid=fork();
		// if(pid==0)
			// udp_attend_client(&cliaddr,pdu);
		// else
			// memset(cliaddr, 0, sizeof(*cliaddr)); 
	//}
	// printf("%s\n",pdu.data);
	// create_pdu(&pdu,REGISTER_REQ,"000001","111111111111","hola puta");
	udp_send(sockfd,&cliaddr,pdu);
	udp_close(sockfd);
	exit(0);
}
/* CONFIG */
void read_config(char file[],config *cfg){
	char name[100],value[100];
	FILE *config=fopen(file,"r");
	int i=4,e;
	do{
		e=fscanf(config,"%s %s",name,value);
		// printf("%d\n",e);
		if(e==2){
			if(strcmp(name,"Id")==0)
				strcpy(cfg->id,value);
			else if(strcmp(name,"MAC")==0)
				strcpy(cfg->mac,value);
			else if(strcmp(name,"UDP-port")==0)
				// printf("%d\n",atoi(value));
				cfg->udp_port=atoi(value);
			else if(strcmp(name,"TCP-port")==0)
				// printf("%d\n",atoi(value));
				cfg->tcp_port=atoi(value);
		}
		read(config,value,1);
		i--;
	}while(e==2&&i>0);
}
void parse_parameters(int argc, char *argv[],char config[],char computers[]){
	int opt;
	//: at the end of a parameter if it has content like a file name
	while((opt = getopt(argc, argv,"dc:u:"))!=-1){
		switch(opt){  
			case 'd':
				DEBUG=1;
				debug("debug mode enabled");
				break;  
			case 'c':  
				printf("config filename: %s\n", optarg);
				strcpy(config,optarg);
				break;  
			case 'u':  
				printf("data filename %s\n",optarg);
				strcpy(computers,optarg);
				break;  
		}
	}

}

/* COMANDS */
int check_command(char str[]){
    if(strcmp(str,"list")==0)
        list();
    else if(strcmp(str,"quit")==0){
		quit();
        return 1;
	}
    else 
        printf("Comand '%s' dosen't exist.\n",str);
    return 0;
}
void list(){
	//acces shared mem and loop through then connected clients to show them
}
void quit(){
	//kill(getppid(),SIGUSR1);
	//send signal to the main proces to kill all proces and close all sockets and end the program
}

/* CONSOLE */
void console(){
	fd_set rfds;
    int ret, len;
    char buff[255] = {0};
	int end=0;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    while(!end){
		ret=select(1, &rfds, NULL, NULL, NULL);
		if(ret==-1){
            //TODO tractar error
		}
		else{
			fgets(buff, sizeof(buff), stdin);
            len = strlen(buff)-1;
            if (buff[len] == '\n')
                buff[len] = '\0';
            end=check_command(buff);
		}
	}
}

/* shared memory */
void init_shared_mem(int *shmid,shared_mem *sh_mem){
	if(((*shmid)=shmget(IPC_PRIVATE,sizeof(shared_mem),IPC_CREAT))<0){
		perror("shmget"),
		exit -1;
	}
	sh_mem=(shared_mem *)shmat((*shmid),0,0);
	sh_mem->n_clis=0;
	/**mem=0;
	if(mem==0){
		perror("shmat");
		exit -1;
	}*/
}


/* MAIN */
int main(int argc,char *argv[]) {
	char config_file[MAX_FILENAME]="server.cfg";
	char computer_file[MAX_FILENAME]="equips.dat";

	char id[ID_LEN],mac[MAC_LEN];
	int tcp_port,udp_port;
	
	//shared
	int shmid;
	shared_mem *sh_mem;
	config cfg;
	int n_cli;
	
	int pid;
	
	init_shared_mem(&shmid,sh_mem);

	parse_parameters(argc,argv,config_file,computer_file);
	read_config(config_file,&cfg);
	read_clients(computer_file,sh_mem);
	

	pid=fork();
	if(pid==0)
		udp_server(cfg);
	pid=fork();
	if(pid==0)
		tcp_server(cfg);
	pid=fork();
	if(pid==0)
		console();
	//udp_server();
	wait();
	wait();
	return 0; 
}