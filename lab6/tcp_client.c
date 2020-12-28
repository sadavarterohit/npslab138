#include "headers.h"

void str_cli(FILE *fp, int sockfd)
{
	int bufsize=1024,cont;
	char *buffer =malloc(bufsize);

	while(fgets(buffer, bufsize, fp))
	{
		send(sockfd, buffer, sizeof(buffer),0);
		if((cont = recv(sockfd,buffer, bufsize, 0))>0)
		{
			puts(buffer);
		}
	}
	printf("\nEOF\n");
}

int main(int argc, char *argv[])
{
	int create_socket;

	char msg[200];

	struct sockaddr_in address;
	if((create_socket = socket(AF_INET, SOCK_STREAM,0))>0)
		printf("Socket Created\n");

	address.sin_family = AF_INET;
	address.sin_port = htons(15001);

	inet_pton(AF_INET, argv[1], &address.sin_addr);

	if(connect(create_socket, (struct sockaddr *)&address, sizeof(address))==0)
		printf("The connection was accepted with the server %s...\n",argv[1]);
	else
		printf("error in connect \n");

	while(strcmp(msg,"end")!=0){
		printf("enter the message : ");
		scanf("%s",msg);
		send(create_socket, msg, sizeof(msg),0);

		printf("Request Accepted, receiving message \n");
str_cli(stdin, create_socket);
	}
	return close(create_socket);
}
