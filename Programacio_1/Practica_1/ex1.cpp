#include <stdio.h>

#define POLZADA_CM 2.54

#define TABLE_RANGE 2

//relació 4:3
#define REL_1_A 0.6 //per calcular l'altura
#define REL_1_B 0.8 //per calcular la base
//relació 16:9
#define REL_2_A 0.4903 //per calcular l'altura
#define REL_2_B 0.8716 //per calcular la base

int main(){
	int in_polzades,in_relacio;
	float altura,base,diagonal;	
	printf("Introdueïx la mida de la TV en polzades:\n");
	scanf("%i",&in_polzades);
	if(in_polzades<5)
		printf("El valor de polzades introduit(%i) no es valid\n",in_polzades);
	if(in_polzades>5){
		printf("Selecciona la relació d'aspecte:\n");
		printf("\t1 - 4:3\n");
		printf("\t2 - 16:9\n");
		scanf("%i[^.]",&in_relacio);
		
		if(in_relacio<1||in_relacio>2)
			printf("El nombre introduï(%i) no es valid\n",in_relacio);
		if(in_relacio>=1&&in_relacio<=2){
			printf("\n| %-10s | %-10s | %-11s | %-10s |\n","Polzades","Base","Alçada","Superficie");
			for(int i=in_polzades-TABLE_RANGE;i<=in_polzades+TABLE_RANGE;i++){
				diagonal=(i*POLZADA_CM);
				switch(in_relacio){
					case 1:{ //relacio 4:3
						altura=diagonal*REL_1_A;
						base=diagonal*REL_1_B;
					}break;
					case 2:{ //relacio 16:9
						altura=diagonal*REL_2_A;
						base=diagonal*REL_2_B;
					}break;
				}
				printf("| %-10i | %-10.2f | %-10.2f | %-10.2f %c\n",i,base,altura,base*altura,'|');
			}
		}
	}
}
