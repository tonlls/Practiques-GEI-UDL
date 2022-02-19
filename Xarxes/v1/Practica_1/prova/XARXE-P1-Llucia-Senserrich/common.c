
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
	return 1+strlen(pdu.id)+strlen(pdu.mac)+strlen(pdu.num)+strlen(pdu.data);

}


void create_pdu(pdu *pdu,PDU_TYPE type,char id[ID_LEN],char mac[MAC_LEN],int num,char data[]){
	pdu->type=type;
	strcpy(pdu->id,id);
	strcpy(pdu->mac,mac);
	sprintf(pdu->num,"%06d",num);
	strcpy(pdu->data,data);
}
int check_pdu(client cli,pdu msg){
	if(strcmp(cli.id,msg.id)!=0)return ID_ERR;
	if(strcmp(cli.mac,msg.mac)!=0)return MAC_ERR;
	if(strcmp(cli.num,msg.num)!=0)return NUM_ERR;
	return 0;
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
	do{
		e=fscanf(fd,"%s %s",id,mac);
		if(e==2){
			strcpy(sh_mem->clis[sh_mem->n_clis].id,id);
			strcpy(sh_mem->clis[sh_mem->n_clis].mac,mac);
			strcpy(sh_mem->clis[sh_mem->n_clis].ip,"               ");

			sh_mem->clis[sh_mem->n_clis].actual_state=DISCONNECTED;
			sh_mem->n_clis++;
		}
		fread(id,1,1,fd);
	}while(!feof(fd));
	fclose(fd);
}
void get_err(ERROR e,char str[]){
	switch(e){
		case ID_ERR:strcpy(str,"Id value isn't correct");break;
		case MAC_ERR:strcpy(str,"MAC value isn't correct");break;
		case NUM_ERR:strcpy(str,"random number value isn't correct");break;
		case IP_ERR:strcpy(str,"ip value isn't correct");break;
		case CONN_ERR:strcpy(str,"connection error");break;
		default:strcpy(str,"unknown");break;
	}
}
int check_client(shared_mem sh_mem,char mac[MAC_LEN],char id[ID_LEN]){
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
		i--;
	}while(e==2&&i>0);
}
void parse_parameters(int argc, char *argv[],char config[],char computers[]){
	int opt;
	while((opt = getopt(argc, argv,"dc:u:"))!=-1){
		switch(opt){  
			case 'd':
				DEBUG=1;
				debug("debug mode enabled");
				break;  
			case 'c':  
				strcpy(config,optarg);
				break;  
			case 'u':  
				strcpy(computers,optarg);
				break;  
		}
	}

}
int get_rand(){
	return rand()%999999;
}
void get_state(STATE s,char str[]){
	switch(s){
		case DISCONNECTED:strcpy(str,"DISCONECTED");break;
		case WAIT_REG:strcpy(str," WAIT_REG  ");break;
		case REGISTERED:strcpy(str,"REGISTERED ");break;
		case ALIVE:strcpy(str,"   ALIVE   ");break;
		default:strcpy(str,"  UNKNOWN  ");break;
	}
}
/* COMANDS */
void list(shared_mem *sh_mem){
	//acces shared mem and loop through then connected clients to show them
	char str[20];
	client c;
	printf("│   ID   │     MAC      │    STATE    │        IP       │\n");
	printf("│────────│──────────────│─────────────│─────────────────│\n");
	for(int i=0;i<sh_mem->n_clis;i++){
		c=sh_mem->clis[i];
		get_state(c.actual_state,str);
		printf("│ %s │ %s │ %s │ %s │\n",c.id,c.mac,str,c.ip);
	}
}
void end_udp(int sig){
	debug("Ending udp server proces(pid=%d)",getpid());
	exit(EXIT_SUCCESS);
}
void end_tcp(int sig){
	while(wait(NULL)<0);
	debug("Ending tcp server proces(pid=%d)",getpid());
	exit(EXIT_SUCCESS);
}
void end_timing(int sig){
	debug("Ending timing server proces(pid=%d)",getpid());
	exit(EXIT_SUCCESS);
}
void quit(int pids[],int len){
	int i;
	for(i=0;i<len-1;i++)
		kill(pids[i],SIGUSR1);
	kill(pids[i],SIGINT);
}
int check_pdu_ip(pdu p,struct sockaddr_in adr,shared_mem shm,int n){
	client c=shm.clis[n];
	char *ip = inet_ntoa(adr.sin_addr);
	if(strcmp(c.id,p.id)!=0)return ID_ERR;
	if(strcmp(c.mac,p.mac)!=0)return MAC_ERR;
	if(strcmp(c.num,p.num)!=0)return NUM_ERR;
	if(strcmp(c.ip,ip)!=0)return IP_ERR;
	return 0;
}
int check_command(char str[],shared_mem *sh_mem,int pids[],int len){
    if(strcmp(str,"list")==0)
        list(sh_mem);
    else if(strcmp(str,"quit")==0){
		quit(pids,len);
        return 1;
	}
    else 
        debug("Comand '%s' dosen't exist.\n",str);
    return 0;
}

/* CONSOLE */
void console(shared_mem *sh_mem,int pids[],int l){
	fd_set rfds;
    int ret, len;
    char buff[255] = {0};
	int end=0;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    while(!end){
		ret=select(1, &rfds, NULL, NULL, NULL);
		if(ret==-1){
            debug("comand-line error");
		}
		else{
			fgets(buff, sizeof(buff), stdin);
            len = strlen(buff)-1;
            if (buff[len] == '\n')
                buff[len] = '\0';
            end=check_command(buff,sh_mem,pids,l);
		}
	}
}


#endif  // foo_h__