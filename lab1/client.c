#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])

{
//	printf("hellno world from the other side ;)");
	int PORT=atoi(argv[2]);
//	
	int sock=0,valread;
	struct sockaddr_in serv_addr;
	const char* hello[100];
	printf("Say Something I'm giving up on you\n\n");
	gets(hello);

	char buffer[1024]={0};

	if((sock = socket(AF_INET, SOCK_STREAM, 0))< 0 )
	{
		printf("Socket creation error");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
	{
		printf("Address not supported");
		return -1;
	}

	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
	{
		printf("Connection failed oh no");
		return -1;
	}

	send(sock, hello, strlen(hello),0);
	printf("\n\n Sent hello message\n\n");
	valread = read(sock, buffer, 1024);
	printf("%s\n\n",buffer);
	return 0;

}

