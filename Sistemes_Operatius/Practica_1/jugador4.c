/* -----------------------------------------------------------------------
 PRA1. Processos, pipes i senyals: El 7,5
 Codi font : jugador4.c

 Ton Llucià Senserrich.
 ---------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

#define TRUE 1
#define FALSE 0

char *color_red = "\033[01;31m";
char *color_yellow = "\033[01;33m";
char *color_green = "\033[01;32m";
char *color_end = "\033[00m";


/* Codificació cartes: 0:rei, 1:as, 2:2, ..., 7:7, 8:sota, 9:cavall */
/* Per no gestionar decimals, es guarda el valor numèric multiplicat per 2 */
#define NUM_CARTES 10

struct{
	char *nom;
	int valor;
} cartes[NUM_CARTES] ={
	{"rei", 1},
	{"as", 2},
	{"2", 4},
	{"3", 6},
	{"4", 8},
	{"5", 10},
	{"6", 12},
	{"7", 14},
	{"sota", 1},
	{"cavall", 1}};



void error(char *m){
	write(2, m, strlen(m));
	write(2, "\n", 1);
	exit(0);
}
void send(int points){
	char s[16];
	//sends the pid and the points to daddy
	sprintf(s,"%d-%d.",getpid(),points);
	if (write(4, s, strlen(s)) < 0)
		error("write resultat + decisió");
}
void get_card(int *carta){
	//we read fromthe pipe to get the card
	char str[3];
	read(5,str,3);
	*carta=atoi(str);
}
void card_request(){
	kill(getppid(),SIGUSR1);
}
void end_card_request(){
	kill(getppid(),SIGUSR2);
}
void inicialitzacions(){
	srand(getpid());
}
int main(){
	int no_fi = TRUE;
	int actual = 0, previ = 0;
	int carta;
	char s[100];
	inicialitzacions();
	while (no_fi){
		get_card(&carta);
		previ = actual;
		actual += cartes[carta].valor;

		sprintf(s,"[%d] valor previ=%2.1f, carta rebuda=%s, valor actual=%2.1f\n",getpid(), previ / 2.0, cartes[carta].nom, actual / 2.0);

		if (write(1, s, strlen(s)) < 0)
			error("write info. cartes");

		if (actual > 15){ /* 15 = 7.5 * 2 */
			sprintf(s, "%s[%d] M'he passat\n%s", color_red, getpid(), color_end);
			no_fi = FALSE;
		}
		else if (actual == 15){
			sprintf(s, "%s[%d] Em planto amb 7.5\n%s", color_green, getpid(), color_end);
			no_fi = FALSE;
		}
		else{
			if ((rand() % 3) == 0)
			{
				sprintf(s, "%s[%d] Decideixo plantar-me amb %2.1f\n%s", color_yellow, getpid(), actual / 2.0, color_end);
				no_fi = FALSE;
			}
			else{
				sprintf(s, "[%d] Decideixo continuar\n", getpid());
			}
		}
		
		//we send sigusr1 if we want another card and sigusr2 if we don't want more
		if(no_fi)card_request();
		else end_card_request();

		/* Per introduir una certa aleatorietat en el temps d'execució dels jugadors */
		sleep(rand() % 2);
	}
	//we send the data only if we have possibilities to win(actual<=15)
	if(actual<=15)
		send(actual);
	if(write(1,s,strlen(s))<0)
		error("printar resultat");
	close(4);
	close(5);
	exit(actual);
}
