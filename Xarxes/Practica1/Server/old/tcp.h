#ifndef tcp_h__
#define tcp_h__
#include "common.h"

int tcp_create_server(int *sockfd,struct sockaddr_in *servaddr,struct sockaddr_in *cliaddr,int port);
int tcp_close_server(int sockfd);
int tcp_send_message(int sockfd,char *msg,int len,struct sockaddr_in *cliaddr);
int tcp_receive_message(int sockfd,char *msg,int len,struct sockaddr_in *cliaddr);

#endif // tcp_h__