#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt =1;
	int addrlen = sizeof(address);
	char buffer[1024]={0};
	char *hello = "I AM THE HUNTER? NAH, SERVER";
        
printf("Adele, is that you?\n\n");
	//Create socket here, file descriptor is returned here
	if((server_fd=socket(AF_INET, SOCK_STREAM,0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	

	//Attach to PORT defined above, so 8080
	//wait up, what is this? read up maybe?
	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR |SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt error");
		exit(EXIT_FAILURE);
	}
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=INADDR_ANY; //this means something too bruh
	address.sin_port = htons(PORT);

	//What does bind call do?
	//
	if(bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)

	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if(listen(server_fd,3)<0)
	{
		perror("listen failed oh no");
		exit(EXIT_FAILURE);

	}
	//listening socket sir
	if((new_socket= accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
	{
		perror("acceptance error ma");
		exit(EXIT_FAILURE);
	}

//	printf("\n\n Server up");
//read call, new_socket cuz that's where you're reaidng from no?
	valread = read(new_socket , buffer, 1024);

	printf("%s\n",buffer);

	send(new_socket, hello, strlen(hello),0);
	printf("Hello message sent from my side also, we're friends now\n\n");

	return 0;

}




