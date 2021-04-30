#include "common.c"
#include "udp.c"
#include "tcp.c"
/* MAIN */
int main(int argc,char *argv[]) {
    srand(time(NULL));
	char config_file[MAX_FILENAME]="server.cfg";
	char computer_file[MAX_FILENAME]="equips.dat";

	// char id[ID_LEN],mac[MAC_LEN];
	// int tcp_port,udp_port;
	
	//shared
	shared_mem *sh_mem;
	config cfg;
	// int n_cli;
	
	int pid;
	int shmid;
	// init_shared_mem(sh_mem);
	// if((shmid=shmget(IPC_PRIVATE,sizeof(shared_mem),0666 | IPC_CREAT))<0){
	if((shmid=shmget(IPC_PRIVATE,sizeof(shared_mem),0666|IPC_CREAT))<0){
		printf("shmget\n");
		exit(EXIT_FAILURE);
	}
	if((sh_mem=shmat(shmid,NULL,0))<(shared_mem*)0)
		printf("error\n");
	sh_mem->n_clis=0;

	// printf("%d\n", sh_mem->n_clis);
	// printf("hola puta de merda\n");
	read_config(config_file,&cfg);
	parse_parameters(argc,argv,config_file,computer_file);
	read_clients(computer_file,sh_mem);
	// printf("%d\n",sh_mem->n_clis);
	

	pid=fork();
	if(pid==0){
		udp_server(cfg,sh_mem);
		exit(0);
	}
	pid=fork();
	if(pid==0){
		time_controller(sh_mem);
		exit(0);
	}

	pid=fork();
	if(pid==0)
		tcp_server(cfg,sh_mem);
	pid=fork();
	if(pid==0)
		console(sh_mem);
	//udp_server();
	wait(NULL);
	wait(NULL);
	wait(NULL);
	return 0; 
}