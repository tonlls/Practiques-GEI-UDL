
#include "common.h"
#ifndef common_c__
#define common_c__



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
	return -1;
}

char *itoa(int value, char *result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) {
        *result = '\0';
        return result;
    }
    char *ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;
    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 +(tmp_value - value * base)];
    } while (value);
    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

void udp_str2pdu(char buff[],pdu *msg){
	char data[4][UDP_DATA_LEN];
	char str[UDP_DATA_LEN];
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
void tcp_str2pdu(char buff[],pdu *msg){
	char data[4][TCP_DATA_LEN];
	char str[TCP_DATA_LEN];
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
/* transforms to string a pdu struct variable */

void str2pdu(char buff[],pdu *msg,pdu_type type){
	if(type==UDP)
		 udp_str2pdu(buff,msg);
	else 
		tcp_str2pdu(buff,msg);
}
void concat(char dest[],char source[],int start){
	int l=strlen(source);
	int i;
	int j=start;
	for(i=0;i<=l;i++){
		dest[i+j]=source[i];
	}
	dest[i+j+1]='\0';
}
void fill(char dest[],char c,int len){
	int i;
	for(i=strlen(dest);i<len-1;i++){
		dest[i]=c;
	}
	dest[i]=c;
}
int pdu2str(pdu pdu,char str[]){
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
	// int l=strlen(str);
	// for(int i=0;i<l;i++){
	// 	if(str[i]=='?')
	// 		str[i]='\0';
	// }
	// return s;
	return 1+strlen(pdu.id)+strlen(pdu.mac)+strlen(pdu.num)+strlen(pdu.data);

}


void create_pdu(pdu *pdu,PDU_TYPE type,char id[ID_LEN],char mac[MAC_LEN],int num,char data[]){
	pdu->type=type;
	strcpy(pdu->id,id);
	// if(type==GET_DATA)printf("%s\n",data);
	strcpy(pdu->mac,mac);
	sprintf(pdu->num,"%06d",num);
	// strcpy(pdu->num,"000000\0");
	strcpy(pdu->data,data);
	// if(type==GET_DATA)printf("sending basura\n");
}
int check_pdu(client cli,pdu msg){
	return strcmp(cli.id,msg.id)==0&&strcmp(cli.mac,msg.mac)==0&&strcmp(cli.num,msg.num)==0;
}
void reset_timer(shared_mem *shm,int cli){
	shm->clis[cli].timer = time(NULL);
}
void set_client(shared_mem *shm,int c,int sock,int rand,struct sockaddr_in *cl){
	char tmp[20];
	char *ip = inet_ntoa(cl->sin_addr);
	itoa(rand,tmp,10);
	strcpy(shm->clis[c].num,tmp);
	strcpy(shm->clis[c].ip,ip);
	shm->clis[c].sock=sock;
	shm->clis[c].cliaddr=cl;
}
void read_clients(char file[],shared_mem *sh_mem){
	int e;
	FILE *fd=fopen(file,"r");
	char id[ID_LEN],mac[MAC_LEN];
	// client cli;
	do{
		e=fscanf(fd,"%s %s",id,mac);
		// printf("%d\n",sh_mem->n_clis);
		if(e==2){
			strcpy(sh_mem->clis[sh_mem->n_clis].id,id);
			strcpy(sh_mem->clis[sh_mem->n_clis].mac,mac);

			sh_mem->clis[sh_mem->n_clis].actual_state=DISCONNECTED;
			sh_mem->n_clis++;
		}
		fread(id,1,1,fd);
		// read(fd,id,1);
	}while(!feof(fd));
	fclose(fd);
}
//TODO: repair function to use shared memory
int check_client(shared_mem sh_mem,char mac[MAC_LEN],char id[ID_LEN]){
	//TODO: check ips
	// char str[INET_ADDRSTRLEN];
	// inet_ntop( AF_INET, &ipAddr, str, INET_ADDRSTRLEN );
	for(int i=0;i<sh_mem.n_clis;i++){
		if(strcmp(id,sh_mem.clis[i].id)==0&&strcmp(mac,sh_mem.clis[i].mac)==0)
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
				cfg->udp_port=atoi(value);
			else if(strcmp(name,"TCP-port")==0)
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
				// printf("config filename: %s\n", optarg);
				strcpy(config,optarg);
				break;  
			case 'u':  
				// printf("data filename %s\n",optarg);
				strcpy(computers,optarg);
				break;  
		}
	}

}
int get_rand(){
	return rand()%999999;
}
/* COMANDS */
void list(shared_mem *sh_mem){
	//acces shared mem and loop through then connected clients to show them
	client c;
	printf("holahola%d\n",sh_mem->n_clis);
	for(int i=0;i<sh_mem->n_clis;i++){
		c=sh_mem->clis[i];
		// if(c.actual_state==ALIVE)
			printf("%s\n",c.id);//TODO: print all
	}
}
void quit(){
	//kill(getppid(),SIGUSR1);
	//send signal to the main proces to kill all proces and close all sockets and end the program
}
int check_command(char str[],shared_mem *sh_mem){
    if(strcmp(str,"list")==0)
        list(sh_mem);
    else if(strcmp(str,"quit")==0){
		quit();
        return 1;
	}
    else 
        debug("Comand '%s' dosen't exist.\n",str);
    return 0;
}

/* CONSOLE */
void console(shared_mem *sh_mem){
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
            end=check_command(buff,sh_mem);
		}
	}
}


#endif  // foo_h__