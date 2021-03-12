#include <sys/select.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int check_command(char str[]){
    if(strcmp(str,"list")==0)
        printf("list comand\n");
    else if(strcmp(str,"quit")==0)
        return 1;
    else 
        printf("Comand '%s' dosen't exist.\n",str);
    return 0;
}
void console(){
	fd_set rfds;
    int ret, len;
    char buff[255] = {0};
	int end=0;
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);

    while(!end){
		ret=select(1, &rfds, NULL, NULL, NULL);
		if(ret==-1){
            //TODO tractar error
		}
		else{
			fgets(buff, sizeof(buff), stdin);
            len = strlen(buff)-1;
            if (buff[len] == '\n')
                buff[len] = '\0';
            end=check_command(buff);
		}
	}
}
int main(){
    int pid=fork();
    if(pid==0)console();
    else wait(NULL);
}