// #include <unistd.h>
#include <stdio.h>
#include <getopt.h>
void parse_parameters(int argc, char *argv[]){
	int opt;
    while((opt = getopt(argc, argv,"dc:u:")) != -1){
        switch(opt)  
        {  
            case 'd':
                printf("DEBUG\n");  
                break;  
            case 'c':  
                printf("config filename: %s\n", optarg);  
                break;  
            case 'u':  
                printf("data filename %s\n",optarg);  
                break;  
            case '?':  
                printf("unknown option: %c\n", optopt); 
                break;
        }
    }

}
int main(int argc,char *argv[]){
    parse_parameters(argc,argv);
}