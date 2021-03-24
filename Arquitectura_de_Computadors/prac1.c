#include <stdio.h>

#define R 2
#define W 3

int main(int argc,char **argv){
	char buff[30];
	int iterations;
	unsigned int vect[100];
	if(argc<2)exit(1);
	FILE *f=fopen(argv[1],"r");
	// fprintf(fitxer,"%d %p\n",R,argv[1]);
	FILE *fitxer=fopen("traça.txt","w");
	fprintf(fitxer,"%d %p\n",W,f);
	int i=0;
	fprintf(fitxer,"%d %p\n",R,&i);
	while(i<100){
		fprintf(fitxer,"%d %p\n",R,&i);
		// fscanf(f,"%d",&num);
		fscanf(f,"%d",&vect[i]);
		fprintf(fitxer,"%d %p\n",R,&f);
		fprintf(fitxer,"%d %p\n",R,&i);
		fprintf(fitxer,"%d %p\n",W,&vect[i]);
		i++;
		fprintf(fitxer,"%d %p\n",W,&i);
	}
	fclose(f);
	printf("introdueix el nombre de iterations:");
	scanf("%d",&iterations);
	fprintf(fitxer,"%d %p\n",W,&iterations);
	while(iterations!=0){
		fprintf(fitxer,"%d %p\n",R,&iterations);
		i=0;
		fprintf(fitxer,"%d %p\n",W,&i);
		while(i<(100-1)){
			fprintf(fitxer,"%d %p\n",R,&i);
			vect[i]=(int)(vect[i]+vect[i+1])/2;
			fprintf(fitxer,"%d %p\n",R,&i);
			fprintf(fitxer,"%d %p\n",R,&vect[i]);
			fprintf(fitxer,"%d %p\n",R,&vect[i+1]);
			fprintf(fitxer,"%d %p\n",W,&vect[i]);
			i++;
			fprintf(fitxer,"%d %p\n",W,&i);
		}
		iterations--;
		fprintf(fitxer,"%d %p\n",W,&iterations);
	}
	for(int j=0;j<100;j++){
		fprintf(fitxer,"%d %p\n",R,&j);
		printf("%d    ",vect[j]);
		fprintf(fitxer,"%d %p\n",R,&j);
		fprintf(fitxer,"%d %p\n",R,&vect[j]);
		fprintf(fitxer,"%d %p\n",W,&j);
	}
	fclose(fitxer);
}