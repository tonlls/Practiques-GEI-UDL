#ifndef udp_h__
#define udp_h__
#include "common.h"

int udp_create_server(int *sockfd,struct sockaddr_in *servaddr, struct sockaddr_in *cliaddr,int port);
int udp_close_server(int sockfd);
int udp_send_message(int sockfd, struct sockaddr_in *servaddr, char *message, int message_size);
int udp_receive_message(int sockfd, struct sockaddr_in *servaddr, char *message, int message_size);

#endif // udp_h__