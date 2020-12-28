#include "headers.h"
 

void str_echo (int confd)
{
	int n;
	int bufsize=1024;
	char *buffer = malloc(bufsize);
again :
	while((n==recv(confd,buffer,bufsize,0))>0)
		send(confd,buffer,n,0);
	if(n<0)
		goto again;
}

int main()
{
	int cont,listenfd,confd,addrlen,addrlen2,fd,pid,addrlen3;

	struct sockaddr_in address,cli_address;

	if((listenfd = socket(AF_INET, SOCK_STREAM,0))>0)
		printf("The socket has been created \n");

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(15001);

	printf("the address before bind is %s...\n",inet_ntoa(address.sin_addr));
	if(bind(listenfd,(struct sockaddr*)&address, sizeof(address))==0)
		printf("Binding socket\n");

	printf("The address after bind is %s ...\n",inet_ntoa(address.sin_addr));

	listen(listenfd,3);
	printf("Server is now listening");

	getsockname(listenfd,(struct sockaddr *)&address,&addrlen3);

	printf("The server's local address %s and port %d \n",inet_ntoa(address.sin_addr),htons(address.sin_port));

	while(1)
	{
		addrlen = sizeof(struct sockaddr_in);
		confd = accept(listenfd, (struct sockaddr *)&cli_address, &addrlen);

		addrlen2=sizeof(struct sockaddr_in);
		int i = getpeername(confd,(struct sockaddr *)&cli_address,&addrlen);

		printf("The client %s is connected on port %d\n",inet_ntoa(cli_address.sin_addr),htons(cli_address.sin_port));
while(1){
	str_echo(confd);
}

close(confd);
}
return 0;
}
