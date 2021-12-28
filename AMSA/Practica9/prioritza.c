#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/resource.h>

void asign_prioriti(int prioriti)
{

    int pri=getpriority(PRIO_PROCESS,0);
    int c;
    if(prioriti>pri)
        c=prioriti-pri;
    else
        c=-(pri-prioriti);
    return c;
}
void main(int argc, char *argv[])
{
    nice -n 10 escriure &
int status = system("gzip foo");
}