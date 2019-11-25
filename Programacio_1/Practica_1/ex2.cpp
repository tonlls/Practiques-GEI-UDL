#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAPITAL_INI 1000

int main () {
	int win=0,lose=0,in_game,money=CAPITAL_INI,in_money,rand_number,in_number;
	srand(time(NULL));
	printf("Benvingut al joc de la ruleta!\n");
	do{
		printf("\nTens un capital de %i€\n",money);
		do{		
			printf("A quin joc vols jugar:\n");
			printf("\t0 - Sortir\n");
			printf("\t1 - Endevina un nombre de l'1 al 36\n");
			printf("\t2 - Endevina si es parell o senar\n");
			scanf("%i[^.]",&in_game);
		}while(in_game<0||in_game>2);
		if(in_game!=0){
			do{
				printf("Tens un capital de %i€, quina quantitat vols apostar?\n",money);
				scanf("%i",&in_money);
				if(in_money<0){
					printf("El valor no pot ser negatiu(%i)",money);
				}
				else if(in_money>money){
					printf("No pots apostar mes diners dels que tens,no ets el Banc Popular!\n");
				}
			}while(in_money<0||in_money>money);
		}
		switch(in_game){
			case 1:{//nombre entre 1 i 36
				do{
					printf("Introdueïx un nombre entre 1 i 36:\n");
					scanf("%i",&in_number);
					if(in_number<1||in_number>36){
						printf("El valor introduït(%i) no es valid\n",in_number);
					}
				}while(in_number<1||in_number>36);
				rand_number=rand()%37;
				printf("Has apostat pel nombre %i i ha sortit %i\n",in_number,rand_number);
				if(in_number!=rand_number){
					printf("Has perdut %i€\n",in_money);
					money=money-in_money;
					lose++;
				}
				else{
					in_money=36*in_money;
					printf("Has guanyat %i€\n",in_money);
					money=money+in_money;
					win++;
				}
			}break;
			case 2:{//parell o senar
				do{
					printf("A que vols apostar?\n");
					printf("\t1 - Senar\n");
					printf("\t2 - Parell\n");
					scanf("%i",&in_number);
					if(in_number<1||in_number>2){
						printf("El valor introduït(%i) no es valid\n",in_number);
					}
				}while(in_number<1||in_number>2);
				rand_number=rand();
				printf("Has apostat per un nombre ");
				if(in_number%2==0){
					printf("parell");
				}
				else{
					printf("senar");
				}
				printf("(%i) i ha sortit un nombre ",in_number);
				if(rand_number%2==0){
					printf("parell");
				}
				else{
					printf("senar");
				}
				printf("\n");
				if((in_number%2==0&&rand_number%2==0)||(in_number%2!=0&&rand_number%2!=0)){
					in_money=2*in_money;
					printf("Has guanyat %i€\n",in_money);
					money=money+in_money;
					win++;
				}
				else{
					money=money-in_money;
					printf("Has perdut %i€\n",in_money);
					lose++;
				
				}
			}break;
		}
	}while(in_game!=0&&money!=0);
	
	if(money==0){
		printf("Ho has perdut tot!!\n");
	}
	else{
		printf("El teu capital final es de %i€\n",money);
	}
	printf("Has guanyat %i partides i n'has perdut %i\n",win,lose);
}
