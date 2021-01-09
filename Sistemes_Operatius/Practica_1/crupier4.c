/* -----------------------------------------------------------------------
 PRA1. Processos, pipes i senyals: El 7,5
 Codi font : crupier4.c

 Ton Llucià Senserrich 
 ---------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include<fcntl.h>

#define MAX_PLAYERS 10
#define NUM_CARTES 10

char *color_blue = "\033[01;34m";
char *color_end = "\033[00m";

//we declare a struct to use with the pipes ant the childs
typedef struct{
	int alive;
	int pipe[2];
}my_pipe;

//a reference to the proc we are trating in the moment
my_pipe *actual_pipe;

void init(){
	/* Inicialització nombres aleatoris */
	srand(getpid());
}
/* Retorna una carta (enter entre 0 i NUM_CARTES -1) */
int obtenir_carta(){
	return (rand() % NUM_CARTES);
}

void error(char *m){
	write(2, m, strlen(m));
	write(2, "\n", 1);
	exit(0);
}

void read_pipe(int fd, int *wpid,int * wpoints,int n){
	char s[16*n];
	char str1[16];
	char str2[16];
	int points=0,pid=0;
	int j=0,k=0;
	//we read the whole pipe
	int bytes=read(fd,s,16*n);
	while(j<bytes&&bytes>0){
		k=0;
		//we get the pid
		while(s[j]!='-'&&j<bytes)
			str1[k++]=s[j++];	
		str1[k]='\0';
		k=0;
		j++;
		//we get the points
		while(s[j]!='.'&&j<bytes)
			str2[k++]=s[j++];	
		str2[k]='\0';
		//we transform the pid ant the points from string to int
		pid=atoi(str1);
		points=atoi(str2);
		//we check the winners
		if((points==*wpoints&&pid<*wpid)||(points>*wpoints)){
			*wpid=pid;
			*wpoints=points;
		}
		j++;
	}
}
void give_card(int sig){
	int card=obtenir_carta();
	char str[5];
	//sends a card to the actual child
	sprintf(str,"%d",card);
	if(write(actual_pipe->pipe[1],str,strlen(str))<0)
		error("write send card");
	if(signal(SIGUSR1,give_card)==SIG_ERR)
		error("redefinint sigusr1");
}
void end_child(int sig){
	//ends a child and exlude it from the trating loop
	actual_pipe->alive=0;
	close(actual_pipe->pipe[0]);
	close(actual_pipe->pipe[1]);
	if(signal(SIGUSR2,end_child)==SIG_ERR)
		error("redefinint sigusr2");
}

int main(int arc, char *arv[]){
	int i, n, st, pid,e_wpid=0,wpid=0,e_wpoints=0,wpoints=0,points;
	char s[100];
	int pi[2];
	char *args[] = {"jugador4", "jugador4", NULL};
	init();
	if (arc != 2)
	{
		sprintf(s, "\nError: nombre d'arguments.\nÚs: %s <nombre jugadors [1-10]>\n\n", arv[0]);
		if (write(1, s, strlen(s)) < 0)
			error("Error write 'Error nombre arguments'");
		exit(0);
	}

	n = atoi(arv[1]);
	if (n > MAX_PLAYERS || n < 1)
	{
		sprintf(s, "\nError: nombre de jugadors.\nÚs: %s <nombre jugadors [1-10]>\n\n", arv[0]);
		if (write(1, s, strlen(s)) < 0)
			error("Error write 'Error nombre jugadors'");
		exit(0);
	}
	my_pipe pipes[n];
	
	sprintf(s, "\n**********Inici del joc (%d jugadors, pid croupier=%d)***********\n", n, getpid());
	if(pipe(pi)<0)
		error("Error pipe");
	if (write(1, s, strlen(s)) < 0)
		error("Error write 'Inici del joc'");
	my_pipe p;
	for (i = 0; i < n; i++){
		//we create a pipe for each child
		if(pipe(p.pipe)<0)
			error("creating card pipes");
		p.alive=1;
		switch (pid = fork()){
			case -1:
				error("Error fork");
			
			case 0: /* Fill */
				close(pi[0]);
				close(p.pipe[1]);
				//we close the other childs pipes
				for(int j=0;j<i;j++){
					close(pipes[j].pipe[0]);
					close(pipes[j].pipe[1]);
				}
				dup2(p.pipe[0],5);
				execv(args[0], args);
				error("Error exec");

			default:
				pipes[i]=p;
				sprintf(s, "%s[%d] pid=%d creat%s\n", color_blue, getpid(), pid, color_end);
				if (write(1, s, strlen(s)) < 0)
					error("Error write 'Creació fill'");
		}
	}
	//we close the read pipe as we will not use it
	close(pi[1]);

	//we catch the user sended signals to the specific functions 
	if(signal(SIGUSR1,give_card)==SIG_ERR)
		error("redefinint sigusr1");
	if(signal(SIGUSR2,end_child)==SIG_ERR)
		error("redefinint sigusr2");

	for (i = 0; i < n; i++){
		actual_pipe=&pipes[i];
		give_card(0);
		while(actual_pipe->alive)pause();
	}
	//we make a loop to wait for all childs to end
	for(i=0;i<n;i++){
		do{
			pid = wait(&st);
		}while(pid<0);
		//we divide the status by 256, because wait catches the exit number as bytes
		points=st/256;
		sprintf(s, "%s[%d] pid=%d finalitzat, %2.1f punts%s\n", color_blue, getpid(), pid, points/2.0, color_end);
		if(write(1,s,strlen(s))<0)
			error("write result");
		//we check the winner
		if((points==e_wpoints&&pid<e_wpid)||(points<=15&&points>e_wpoints)){
			e_wpid=pid;
			e_wpoints=points;
		}
	}
	//we read the data from the pipe, trate the data and check who is the winner 
	read_pipe(pi[0],&wpid,&wpoints,n);
	sprintf(s, "\n**********Fi del joc: tots els jugadors han acabat***********\n");
	if (write(1, s, strlen(s)) < 0)
		error("Error write 'Fi del joc'");
	if(e_wpid==0) sprintf(s,"\n**********(usant exit)I el guanyador és NINGÚ***********\n");
	else sprintf(s, "\n**********(usant exit) I el guanyador és pid=%d (%2.1f punts)***********\n",e_wpid,e_wpoints/2.0);
	if (write(1, s, strlen(s)) < 0)
		error("Error write 'Escriure guanyador exit'");

	if(wpid==0) sprintf(s,"\n**********(usant pipes) I el guanyador és NINGÚ***********\n");
	else sprintf(s, "\n**********(usant pipes) I el guanyador és pid=%d (%2.1f punts)***********\n",wpid,wpoints/2.0);
	if (write(1, s, strlen(s)) < 0)
		error("Error write 'Escriure guanyador pipes'");
	close(3);
	exit(0);
}
