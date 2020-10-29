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

#define MAX_PLAYERS 10

char *color_blue = "\033[01;34m";
char *color_end = "\033[00m";

void error(char *m)
{
	write(2, m, strlen(m));
	write(2, "\n", 1);
	exit(0);
}

int main(int arc, char *arv[])
{
	int i, n, st, pid;
	char s[100];
	char *args[] = {"jugador", "jugador", NULL};

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
	if (write(1, s, strlen(s)) < 0)
		error("Error write 'Inici del joc'");

	for (i = 0; i < n; i++)
	{
		switch (pid = fork())
		{
		case -1:
			error("Error fork");

		case 0: /* Fill */
			execv(args[0], args);
			error("Error exec");

		default:
			sprintf(s, "%s[%d] pid=%d creat%s\n", color_blue, getpid(), pid, color_end);
			if (write(1, s, strlen(s)) < 0)
				error("Error write 'Creació fill'");
		}
	}
	for(i=0;i<n;i++){
		pid = wait(&st);
		if (pid == -1)
			error("Error wait");
		sprintf(s, "%s[%d] pid=%d finalitzat%s\n", color_blue, getpid(), pid, color_end);
		if (write(1, s, strlen(s)) < 0)
			error("Error write finalització fill");
	}
	sprintf(s, "\n**********Fi del joc: tots els jugadors han acabat***********\n");
	if (write(1, s, strlen(s)) < 0)
		error("Error write 'Fi del joc'");

	exit(0);
}
