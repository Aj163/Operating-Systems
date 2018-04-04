// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
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

	str[p] = '\0';
}

int main(int argc, char const *argv[])
{
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char msg[300];
	char buffer[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}

	printf("Connection established with server.\n\n");
	while(strcmp(msg, "exit"))
	{
		valread = read(sock, buffer, 1024);
		printf("\tSERVER : %s\n", buffer);

		printf("\tCLIENT : ");
		read_string(msg);
		
		send(sock, msg, strlen(msg)+1, 0);
	}
	return 0;
}