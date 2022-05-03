
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <poll.h>
#include <errno.h>

#define MYPORT "3490"
#define BACKLOG 10


int getAddress(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res){
	int ret;
	
	if((ret = getaddrinfo(node, service, hints, res))!=0){
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(ret));
		exit(EXIT_FAILURE);
	}
	return ret;

}

int getSocket(struct addrinfo *res){
	int ret;
	
	if((ret = socket(res->ai_family, res->ai_socktype, res->ai_protocol))<0){
		fprintf(stderr, "socket error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return ret;
}

int getBind(int sockfd, struct addrinfo *res){
	int ret;

	if((ret = bind(sockfd, res->ai_addr, res->ai_addrlen))<0){
		fprintf(stderr, "bind error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return ret;
}

int getListen(int sockfd, int backlog){
	int ret;

	if((ret = listen(sockfd, backlog))<0){
		fprintf(stderr, "listen error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return ret;
}

int getAccept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
	int ret;

	if((ret = accept(sockfd, addr, addrlen))<0){
		fprintf(stderr, "accept error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return ret;
}


int sendAll(int sockfd, const void *msg, int *len, int flag){
	int ret;
	int sent = 0;
	int left = *len;

	while(sent < *len) {
		ret = send(sockfd, msg+sent, left, 0);
		if(ret<0){
			fprintf(stderr, "send error: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		sent += ret;
		left -= ret;
	}

	*len = sent;

	return ret;
}
int receive(int sockfd, void *buf, int len, int flags){
	int ret;

	if((ret = recv(sockfd, buf, len, flags))<0){
		fprintf(stderr, "receive error: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return ret;
}



int main(int argv, char* argc[]){
	
	if(argv!=2){
		exit(EXIT_FAILURE);
	}
	char* port = argc[1];
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	struct addrinfo hints, *res;
	int sockfd, new_fd;
	char msg[256];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getAddress("localhost", port, &hints, &res);
	

	sockfd = getSocket(res);
	getBind(sockfd, res);
	getListen(sockfd, BACKLOG);
	

	addr_size = sizeof their_addr;
	

	new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);

	{
		receive(new_fd, msg, sizeof msg, 0);

		printf("%s\n", msg);	
	}
	freeaddrinfo(res);	
}

