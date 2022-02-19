#include "common.c"
#include "udp.c"
#include "tcp.c"
/* MAIN */
int main(int argc,char *argv[]) {
    srand(time(NULL));
	char config_file[MAX_FILENAME]="server.cfg";
	char computer_file[MAX_FILENAME]="equips.dat";
	int pids[3];
	//shared
	shared_mem *sh_mem;
	config cfg;
	int shmid;
	if((shmid=shmget(IPC_PRIVATE,sizeof(shared_mem),0666|IPC_CREAT))<0){
		printf("shmget\n");
		exit(EXIT_FAILURE);
	}
	if((sh_mem=shmat(shmid,NULL,0))<(shared_mem*)0)
		printf("error\n");
	sh_mem->n_clis=0;

	parse_parameters(argc,argv,config_file,computer_file);
	read_config(config_file,&cfg);
	read_clients(computer_file,sh_mem);
	

	pids[0]=fork();
	if(pids[0]==0){
		signal(SIGUSR1, end_udp);
		debug("Creating UDP server proces: %d",getpid());
		udp_server(cfg,sh_mem);
		exit(0);
	}
	pids[1]=fork();
	if(pids[1]==0){
		signal(SIGUSR1, end_timing);
		debug("Creating UDP alive timeout proces: %d",getpid());
		time_controller(sh_mem);
		exit(0);
	}
	pids[2]=fork();
	if(pids[2]==0){
		signal(SIGUSR1, end_tcp);
		debug("Creating TCP server proces: %d",getpid());
		tcp_server(cfg,sh_mem);
		exit(0);
	}
	debug("Creating console proces: %d",getpid());
	console(sh_mem,pids,3);
	exit(0);
	while(wait(NULL)<0);
	return 0; 
}