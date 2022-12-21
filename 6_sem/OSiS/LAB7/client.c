// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define PORT 5051

pthread_t write_thread, read_thread;
char message[100];
int sock = 0;

void write_to_serv()
{
    while(1) {
        fgets(message, 100, stdin);
        send(sock, message, strlen(message), 0);
    };
}

void read_from_serv()
{
    int valread;
    char buffer[1024] = {0};
    while(1) {
        valread = read( sock , buffer, 1024);
        buffer[valread] = '\0';
	    printf(buffer);
    };
}

int main(int argc, char const *argv[])
{
    int valread;
    char buffer[1024] = {0};
    pthread_create(&write_thread, NULL, write_to_serv, NULL);
    pthread_create(&read_thread, NULL, read_from_serv, NULL);
	struct sockaddr_in serv_addr;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}

    valread = read( sock , buffer, 1024);
    buffer[valread] = '\0';
    printf("%s\n", buffer);

    pthread_join(read_thread, NULL);
	pthread_join(write_thread, NULL);

	return 0;
}