#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFLEN 2048
#define SERVER "10.100.12.231"
#define PORT 3000

char buffer[BUFLEN];

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

int main () 
{

	struct sockaddr_in *serverAddr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));

	int socket_filedescriptor;
	socklen_t received_bytes;

	socklen_t socketServerLength = sizeof(*serverAddr);

	socket_filedescriptor = socket(AF_INET, SOCK_DGRAM, 0);
	if (socket_filedescriptor < 0) 
	{
		perror("error");
		return 0;
	}
	printf("Client Created\n\n");

	serverAddr->sin_family = AF_INET;
	serverAddr->sin_port = htons(PORT);

	inet_aton(SERVER, &serverAddr->sin_addr);

	memset(buffer, '\0', BUFLEN);

	while(1)
	{
		printf("\tCLIENT : ");
		read_string(buffer);

		sendto(socket_filedescriptor, buffer, BUFLEN, 0, (struct sockaddr *)serverAddr, sizeof(*serverAddr));

		received_bytes = recvfrom(socket_filedescriptor, buffer, BUFLEN, 0, (struct sockaddr *)serverAddr, &socketServerLength);

		if (received_bytes != -1) 
			printf("\tSERVER : %s\n", buffer);
	}
}