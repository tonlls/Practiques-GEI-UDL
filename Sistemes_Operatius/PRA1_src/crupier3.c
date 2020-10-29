/* -----------------------------------------------------------------------
 PRA1. Processos, pipes i senyals: El 7,5
 Codi font : crupier.c

 Nom complet autor1.  
 Nom complet autor2.  
 ---------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include<fcntl.h>

#define MAX_PLAYERS 10

char *color_blue = "\033[01;34m";
char *color_end = "\033[00m";

void error(char *m)
{
	write(2, m, strlen(m));
	write(2, "\n", 1);
	exit(0);
}

/*void read_data(char *s,int start,int *pid,int *points){
	char str[15];
	int i=start,j=0;
	while(s[i]!='-'){
		str[j++]=s[i++];
	}
	str[j]='\0';
	*pid=atoi(str);
	j=0;

	while(s[i]!='\n'){
		str[j++]=s[i++];
	}
	str[j]='\0';
	*points=atoi(str);
	printf("\n%d,%d\n",*pid,*points);
}*/
void test(char *s, int bytes){
	printf("%d\n",sizeof(char));
	printf("--------------------\n");
	for(int i=0;i<bytes;i++)
		printf("%c,",s[i]);
	printf("---------------------\n");

}
void read_pipe(int fd, int *wpid,int * wpoints,int n){
	char s[16*n];
	char str1[16];
	char str2[16];
	int points=0,pid=0;
	int j=0,k=0;
	int bytes=read(3,s,sizeof(s));
	 test(s,bytes);
	// printf("\n%d,%d\n",bytes,bytes/16);
	// printf("\n%d,%d\n",bytes,bytes/16);
	// for(int i=0;i<bytes/16;i++){
	while(1){
		while(s[j]!='p'&&j<bytes)j++;
		if(s[j]=='p'){
			k=0;
			j++;
			while(s[j]!='-')
				str1[k++]=s[j++];	
			str1[k]='\0';
			k=0;
			j++;
			printf("arribo aqui\n");
			while(s[j]!='.')
				str2[k++]=s[j++];	
			str2[k]='\0';
			pid=atoi(str1);
			points=atoi(str2);
			// printf("%d,%d \n",points,pid);
			// printf("\n%s,%s\n",str1,str2);
			if((points==*wpoints&&pid<*wpid)||(points<=15&&points>*wpoints)){
				*wpid=pid;
				*wpoints=points;
			}
		}
		else break;
	}
	/*while(i<strlen(s)){
		k=0;
		j=0;
		while(s[i]!='-')
			str[k][j++]=s[i++];	
		str[k][j]='\0';
		printf("\n%s",str[k]);
		j=0;
		k++;
		i++;
		while(s[i]!='\n')
			str[k][j++]=s[i++];	
		str[k][j]='\0';
		pid=atoi(str[0]);
		points=atoi(str[1]);
		printf("\nooo %d,%d\n",points,pid);
		if((points==*wpoints&&pid<*wpid)||(points<=15&&points>*wpoints)){
			*wpid=pid;
			*wpoints=points;
		}
		i++;
		// i++; 	
		printf("\niiiiii %d\n",i);
		// break;
	}*/
}
int main(int arc, char *arv[])
{
	int i, n, st, pid,e_wpid=0,wpid=0,e_wpoints=0,wpoints=0,points;
	char s[100];
	int pi[2];
	char *args[] = {"jugador3", "jugador3", NULL};
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

	sprintf(s, "\n**********Inici del joc (%d jugadors, pid croupier=%d)***********\n", n, getpid());
	if(pipe(pi)<0)
		error("Error pipe");
	if (write(1, s, strlen(s)) < 0)
		error("Error write 'Inici del joc'");

	for (i = 0; i < n; i++)
	{
		switch (pid = fork())
		{
		case -1:
			error("Error fork");

		case 0: /* Fill */
			close(pi[0]);
			// dup2(3,pi[1]);
			execv(args[0], args);
			error("Error exec");

		default:
			// close(pi[1]);
			sprintf(s, "%s[%d] pid=%d creat%s\n", color_blue, getpid(), pid, color_end);
			if (write(1, s, strlen(s)) < 0)
				error("Error write 'Creació fill'");
		}
	}
	for(i=0;i<n;i++){
		pid = wait(&st);
		points=st/256;
		sprintf(s, "%s[%d] pid=%d finalitzat, %2.1f punts%s\n", color_blue, getpid(), pid, points/2.0, color_end);
		if(write(1,s,strlen(s))<0)
			error("write result");
		if((points==e_wpoints&&pid<e_wpid)||(points<=15&&points>e_wpoints)){
			e_wpid=pid;
			e_wpoints=points;
		}
	}
	/*
	ended=(read(pi[0],&s,sizeof(char)*15*n)-1)/15;
	printf("END=%d",ended);
	for(int i=0;i<ended;i++){
		read_data(s,i*15,&pid,&points);
		if(points==15||(points<15&&points>wpoints)){
			wpid=pid;
			wpoints=points;
		}
		// break;
	}*/
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
	close(pi[0]);
	close(pi[1]);
	exit(0);
}
