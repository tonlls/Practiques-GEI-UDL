#include <stdio.h>
#include <stdlib.h>

#define R 2
#define W 3

int main(int argc,char **argv){
	char buff[30];
	int iterations;
	unsigned int vect[100];
	if(argc<2)exit(1);
	FILE *f=fopen(argv[1],"r");
	// FILE *fitxer;
	int i=0;
	while(i<100){
		fscanf(f,"%d",&vect[i]);
		i++;
	}
	fclose(f);
	printf("introdueix el nombre de iterations:");
	scanf("%d",&iterations);
	printf("\n");
	sprintf(buff,"tr_%d.prg",iterations);
	f=fopen(buff,"w");
	while(iterations!=0){
		fprintf(f,"%d %p\n",R,&iterations);
		i=0;
		fprintf(f,"%d %p\n",W,&i);
		while(i<(100-1)){
			fprintf(f,"%d %p\n",R,&i);
			vect[i]=(int)(vect[i]+vect[i+1])/2;
			fprintf(f,"%d %p\n",R,&i);
			fprintf(f,"%d %p\n",R,&vect[i]);
			fprintf(f,"%d %p\n",R,&vect[i+1]);
			fprintf(f,"%d %p\n",W,&vect[i]);
			i++;
			fprintf(f,"%d %p\n",W,&i);
		}
		iterations--;
		fprintf(f,"%d %p\n",W,&iterations);
	}
	for(int j=0;j<100;j++){
		// fprintf(f,"%d %p\n",R,&j);
		fprintf(f,"%d %p\n",R,&j);
		printf("%d  ",vect[j]);
		fprintf(f,"%d %p\n",R,&j);
		fprintf(f,"%d %p\n",R,&vect[j]);
		fprintf(f,"%d %p\n",W,&j);
		// fprintf(f,"%d %p\n",W,&j);
	}
	printf("\n");
	fclose(f);
}