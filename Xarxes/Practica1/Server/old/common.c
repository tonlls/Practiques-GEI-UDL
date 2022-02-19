#ifndef common_c__
#define common_c__

#include "common.h"


/*  UTILS  */
void error(char str[]){
	if(DEBUG)
		printf("ERROR: %s",strerror(errno));
}

int debug(const char *format, ...){
	if(DEBUG){
		printf("%s", "DEBUG: ");
		va_list ptr;
		va_start(ptr, format);
		int done=vprintf(format, ptr);
		va_end(ptr);
		printf("\n");
		return done;
	}
	return -1;
}

char *itoa(int value, char *result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) {
        *result = '\0';
        return result;
    }
    char *ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;
    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 +(tmp_value - value * base)];
    } while (value);
    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

void concat(char dst[], char src[], int start){
    int i=0;
    while(src[i]!='\0'){
        dst[start+i]=src[i];
        i++;
    }
    dst[start+i]='\0';
}
void fill(char dst[], char c, int start, int end){
    int i=0;
    for(i=start;i<end;i++){
        dst[i]=c;
    }
    dst[i]='\0';
}

#endif