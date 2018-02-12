#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

void read_string(char str[])
{
	int p = 0;
	char c = getchar();
	while(c != '\n')
	{
		str[p++] = c;
		c = getchar();
	}

	str[p++] = '\0';
	str[p] = '\0';
}

int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char msg[300];
	
	// Creating socket file descriptor
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
	

	if(bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if(listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

	while(strcmp(msg, "exit"))
	{
		printf("\tSERVER : ");
		read_string(msg);
		
		send(new_socket, msg, strlen(msg)+1, 0);
		valread = read(new_socket, buffer, 1024);

		printf("\tCLIENT : %s\n", buffer);
	}

	return 0;
}