
#include "common.h"
#ifndef foo_c__
#define foo_c__
 
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
	// strcpy(msg->num,data[2]);
	sprintf(msg->num,"%06d",atoi(data[2]));
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


void create_pdu(pdu *pdu,PDU_TYPE type,char id[ID_LEN],char mac[MAC_LEN],int num,char data[DATA_LEN]){
	pdu->type=type;
	strcpy(pdu->id,id);
	strcpy(pdu->mac,mac);
	sprintf(pdu->num,"%06d",num);
	// strcpy(pdu->num,"000000\0");
	strcpy(pdu->data,data);
}
int check_pdu(client cli,pdu msg){
	return strcmp(cli.id,msg.id)==0&&strcmp(cli.mac,msg.mac)==0&&strcmp(cli.num,msg.num)==0;
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
		fread(id,1,1,fd);
		// read(fd,id,1);
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
		fread(value,1,1,config);
		// read(config,value,1);
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
int get_rand(){
	return rand()%999999;
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
void list(shared_mem sh_mem){
	//acces shared mem and loop through then connected clients to show them
	client c;
	for(int i=0;i<sh_mem.n_clis;i++){
		c=sh_mem.clis[sh_mem.n_clis];
		if(c.actual_state==ALIVE)
			printf("%s",c.mac);//TODO: print all
	}
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

#endif  // foo_h__