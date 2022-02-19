#ifndef common_h__
#define common_h__
 
#define  _GNU_SOURCE
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h> 
#include <time.h>
#include <errno.h>

#include <sys/shm.h>
#include <sys/socket.h> 
#include <sys/select.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>

#include <arpa/inet.h> 

#include <netinet/in.h> 


 
#define MAX_MSG_SIZE 10000

#define MAX_CLI 10

#define TCP_MAX_CONN 5

#define MAX_FILENAME 100

#define IP_LEN 16

#define ID_LEN 7
#define MAC_LEN 13
#define RAND_LEN 7
#define UDP_DATA_LEN 50
#define TCP_DATA_LEN 150
#define UDP_PDU_LEN (ID_LEN+MAC_LEN+RAND_LEN+UDP_DATA_LEN+1)
#define TCP_PDU_LEN (ID_LEN+MAC_LEN+RAND_LEN+TCP_DATA_LEN+1)


int DEBUG=0;

// typedef enum t_STATE{
// 	DISCONNECTED=0,
// 	WAIT_REG=1,
// 	REGISTERED=2,
// 	ALIVE=3
// }STATE;
// typedef enum t_ERROR{
// 	ID_ERR=1,
// 	MAC_ERR,
// 	NUM_ERR,
// 	IP_ERR,
// 	CONN_ERR
// }ERROR;
// typedef enum t_PDU_TYPE{
// 	REGISTER_REQ=0x10,
// 	REGISTER_ACK=0x11,
// 	REGISTER_NACK=0x12,
// 	REGISTER_REJ=0x13,
// 	ALIVE_INF=0x20,
// 	ALIVE_ACK=0x21,
// 	ALIVE_NACK=0x22,
// 	ALIVE_REJ=0x23,
// 	PUT_FILE=0x30,
// 	PUT_DATA=0x31,
// 	PUT_ACK=0x32,
// 	PUT_NACK=0x33,
// 	PUT_REJ=0x34,
// 	PUT_END=0x35,
// 	GET_FILE=0x40,
// 	GET_DATA=0x41,
// 	GET_ACK=0x42,
// 	GET_NACK=0x43,
// 	GET_REJ=0x44,
// 	GET_END=0x45
// }PDU_TYPE;
// typedef enum t_pdu_type{
// 	UDP=0,
// 	TCP=1
// }pdu_type;
// typedef struct t_pdu{
// 	PDU_TYPE type;
// 	char id[ID_LEN];
// 	char mac[MAC_LEN];
// 	char num[RAND_LEN];
// 	char data[TCP_DATA_LEN];
// }pdu;
// typedef struct t_client{
// 	STATE actual_state;
// 	char id[ID_LEN];
// 	char ip[IP_LEN];
// 	char mac[MAC_LEN];
// 	char num[RAND_LEN];
// 	struct sockaddr_in *cliaddr;
// 	int sock;
// 	clock_t timer;
// }client;
// typedef struct t_shared_mem{
// 	client clis[MAX_CLI];
// 	int n_clis;
// }shared_mem;
// typedef struct t_config{
// 	char id[ID_LEN];
// 	char mac[MAC_LEN];
// 	int udp_port;
// 	int tcp_port;
// }config;

void error(char str[]);
int debug(const char *format, ...);
char *itoa(int value, char *result, int base);
void concat(char dst[], char src[], int start);
void fill(char dst[], char c, int start, int end);

#endif