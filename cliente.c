/*
Guilherme Mota GRR20197268
Código do cliente
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>
	


int main(){
	char buffer[500];
	char opcao[10];
	char opcoes[180] = {"=====================\n1 - Fazer pedido Ex: 1 03\n2 - Reenviar cardápio\n3 - Detalhe do prato Ex: 3 03\n4 - Sair\n=====================\n\nDigite a opção desejada:"};

	struct sockaddr_in caddr;
	struct sockaddr_in saddr = {
		.sin_family = AF_INET,
		.sin_addr.s_addr = inet_addr("127.0.0.1"),
		.sin_port = htons(5000)
	};

	int client = socket(AF_INET, SOCK_DGRAM, 0); //criacao do socket
	int length = sizeof(struct sockaddr_in);

	//mensagem Hello para o servidor
	sendto(client, "Bom dia", 10, 0, (struct sockaddr *) &saddr, length);

	//recebe bom dia do servidor
	recvfrom(client, buffer, sizeof(buffer), 0, (struct sockaddr *) &caddr, &length);
	printf("%s", buffer);

	//recebe cardapio do servidor
	recvfrom(client, buffer, sizeof(buffer), 0, (struct sockaddr *) &caddr, &length);
	printf("%s", buffer);

	//mostra menu de opcoes
	printf("\n%s\n", opcoes);


	//Loop com o menu
	fgets(opcao, sizeof(opcao), stdin);
	opcao[strlen(opcao) - 1] = 0;
	while(strcmp(opcao, "4") != 0){
		//envia mensagem para o servidor
		sendto(client, opcao, sizeof(opcao), 0, (struct sockaddr *) &saddr, length);

		//recebe resposta do servidor
		recvfrom(client, buffer, sizeof(buffer), 0, (struct sockaddr *) &caddr, &length);
		puts(buffer);

		printf("%s\n", opcoes);
		fgets(opcao, sizeof(opcao), stdin);
		opcao[strlen(opcao) - 1] = 0;
	}
			
	//Finalização		
	printf("Volte sempre!\n");				
	close(client);

	return 0;
	
}

