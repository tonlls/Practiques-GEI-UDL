#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include <time.h> 
void writeFile(char *path){
    int fd = open(path, O_WRONLY|O_CREAT, 0644);
    if(fd == -1){
        printf("Error opening file\n");
        return;
    }
    char *buffer = "Hello World!\n";
    for (int i = 0; i < 100; i++){
        write(fd, buffer, strlen(buffer));
    }
    // write(fd, buffer, strlen(buffer));
    close(fd);
}
void main(int argc, char *argv[]){
    //get the time it least to run writeFile function
    double time_ram,time_fs = 0.0;
    clock_t begin = clock();
    char path_ram[100];
    char path_fs[100];
    sprintf(path_fs, "/tmp/%s",argv[1]);
    sprintf(path_ram, "/tmp/ramdisk/%s",argv[1]);
    
    writeFile(path_ram);
    clock_t end = clock();
    time_ram = (double)(end - begin) / CLOCKS_PER_SEC;
    begin = clock();
    writeFile(path_fs);
    end = clock();
    time_fs = (double)(end - begin) / CLOCKS_PER_SEC;
}