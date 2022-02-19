#ifndef udp_c__
#define udp_c__

#include "udp.h"
#include "common.h"

int udp_create_server(int *sockfd,struct sockaddr_in *servaddr, struct sockaddr_in *cliaddr,int port){
    // Creating socket file descriptor 
	if ( (*sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		debug("socket creation failed"); 
		return EXIT_FAILURE; 
	} 
	memset(servaddr, 0, sizeof(*servaddr)); 
	memset(cliaddr, 0, sizeof(*cliaddr)); 
	// Filling server information 
	servaddr->sin_family = AF_INET; // IPv4 
	servaddr->sin_addr.s_addr = htons(INADDR_ANY); 
	servaddr->sin_port = htons(port);  

	// Bind the socket with the server address 
	if (bind(*sockfd,(const struct sockaddr *)servaddr,sizeof(*servaddr))<0) {
		debug("bind failed"); 
		return EXIT_FAILURE; 
	} 
	debug("udp server created");
    return EXIT_SUCCESS;
}

int udp_close_server(int sockfd){
    close(sockfd);
    debug("udp server closed");
    return EXIT_SUCCESS;
}

int udp_send_message(int sockfd, struct sockaddr_in *servaddr, char *message, int message_size){
    int n;
    if ( (n = sendto(sockfd, message, message_size, 0, (const struct sockaddr *)servaddr, sizeof(*servaddr))) < 0) {
        debug("send failed");
        return EXIT_FAILURE;
    }
    debug("udp message sent");
    return EXIT_SUCCESS;
}

#endif