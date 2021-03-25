#include <time.h>
#include <stdlib.h>
void main(){

    srand(time(NULL));   // Initialization, should only be called once.
    int r;
    while(1){

        r = rand();
        printf("%06d\n",r%999999);
        sleep(1);
    }
}