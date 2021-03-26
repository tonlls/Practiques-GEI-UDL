#include "common.c"
#include "udp.c"
#include "tcp.c"
/* MAIN */
int main(int argc,char *argv[]) {
    srand(time(NULL));
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
		udp_server(cfg,sh_mem);
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