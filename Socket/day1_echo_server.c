//echo_server

#include <stdio.h>
#include <sys/types.h>      
#include <sys/socket.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

const char *PORT = "12345";

int server_sock;
int client_sock;

void interrupt(int arg){
	printf("\nYou typed Ctrl + C\n");
	printf("Bye\n");

	close(client_sock);
	close(server_sock);
	exit(1);
}

void removeEnterChar(char *buf){
	int len = strlen(buf);
	for (int i = len - 1; i >= 0; i--){
		if (buf[i] == '\n'){
			buf[i] = '\0';
			break;
		}
	}
}

int main(){
	signal(SIGINT, interrupt);

	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock == -1){
		printf("ERROR :: 1_Socket Create Error\n");
		exit(1);
	}
	printf("Server On..\n");	

	int optval = 1;
	setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, (void *)&optval, sizeof(optval));

	struct sockaddr_in server_addr = {0};
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(atoi(PORT));
	socklen_t server_addr_len = sizeof(server_addr);

	if (bind(server_sock, (struct sockaddr *)&server_addr, server_addr_len) == -1){
		printf("ERROR :: 2_bind Error\n");
		exit(1);
	}
	printf("Bind Success\n");	

	if (listen(server_sock, 5) == -1){
		printf("ERROR :: 3_listen Error");
		exit(1);
	}
	printf("Wait Client...\n");

	client_sock = 0;
	struct sockaddr_in client_addr = {0};
	socklen_t client_addr_len = sizeof(client_addr);

	while (1){
		memset(&client_addr, 0, client_addr_len);

		client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len);
		if (client_sock == -1){
			printf("ERROR :: 4_accept Error\n");
			break;
		}
		printf("Client Connect Success!\n");		

		char buf[100];
		while (1){
			memset(buf, 0, 100);

			int len = read(client_sock, buf, 99);
			removeEnterChar(buf);

			if (len == 0){
				printf("INFO :: Disconnect with client... BYE\n");
				break;
			}

			if (!strcmp("exit", buf)){
				printf("INFO :: Client want close... BYE\n");
				break;
			}
			write(client_sock, buf, strlen(buf));
		}
		close(client_sock);
		printf("Client Bye!\n");
	}
	close(server_sock);
	printf("Server off..\n");
	return 0;
}