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
void main(char *argv[])
{
    char fullPath[500];
    //can parse 2 arguments, if not, print error
    //1st argument is the a boolean to write at a fs file or a ram file
    //2nd argument is the file name
    if(argv[1] == NULL || argv[2] == NULL)
    {
        printf("Error: missing arguments\n");
        return;
    }
    //if the first argument is 0, write to ram
    if(strcmp(argv[1], "0") == 0)
    {
        //if the file name is not valid, print error
        if(!isValidFileName(argv[2]))
        {
            printf("Error: invalid file name\n");
            return;
        }
        //if the file name is valid, write to ram
        else
        {
            sprintf(fullPath, "/tmp/ramdisk/%s", argv[2]);
            write(argv[2]);
        }
    }
    //if the first argument is 1, write to fs
    else if(strcmp(argv[1], "1") == 0)
    {
        //if the file name is not valid, print error
        if(!isValidFileName(argv[2]))
        {
            printf("Error: invalid file name\n");
            return;
        }
        //if the file name is valid, write to fs
        else
        {
            sprintf(fullPath, "/home/ton/Descktop/%s", argv[2]);
            write(argv[2]);
        }
    }
}