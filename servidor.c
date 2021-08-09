/*
Guilherme Mota GRR20197268
Código do servidor
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

	char cardapio[100] = {"-+-CARDÁPIO-+-\n\n01 - X-Burguer\n02 - X-Salada\n03 - X-Bacon\n04 - X-Egg\n05 - X-Frango\n"};

	char xBurger[100] = {"X-Burguer: Pão, hambúrguer 150g e  queijo"};
	char xSalada[100] = {"X-Salada: Pão, hambúrguer 150g,  queijo, alface, tomate e cebola"};
	char xBacon[100] = {"X-Bacon: Pão, hambúrguer 150g,  queijo e bacon"};
	char xEgg[100] = {"X-Egg: Pão, hambúrguer 150g,  queijo e ovo frito"};
	char xFrango[100] = {"X-Frango: Pão, hambúrguer 150g,  queijo e frango desfiado"};

	char buffer[128];
	char mensagem[50];

	struct sockaddr_in caddr;
	struct sockaddr_in saddr = {
		.sin_family = AF_INET,
		.sin_addr.s_addr = inet_addr("127.0.0.1"),
		.sin_port = htons(5000)
	};
	

	int server = socket(AF_INET, SOCK_DGRAM, 0); //criacao do socket
	int length = sizeof(struct sockaddr_in);
	int espera;


	//vincula socket criado a porta
	bind(server, (struct sockaddr *) &saddr, sizeof(saddr));

	while(1){
		
		//recebe mensagem do cliente
		recvfrom(server, buffer, sizeof(buffer), 0, (struct sockaddr *) &caddr, &length);

		printf("Mensagem recebida: %s\n", buffer);

		//trata mensagem do cliente e envia resposta
		if (strcmp(buffer, "Bom dia") == 0){
			//hello
			strcpy(mensagem, "Bom dia, seja bem-vindo ao Cisco Lanches!\n\n");

			sendto(server, mensagem, sizeof(mensagem), 0 , (struct sockaddr *) &caddr, length);

			sendto(server, cardapio, sizeof(cardapio), 0 , (struct sockaddr *) &caddr, length);

		}else if(strcmp(buffer, "1 01") == 0 || strcmp(buffer, "1 02") == 0 || strcmp(buffer, "1 03") == 0 || strcmp(buffer, "1 04") == 0 || strcmp(buffer, "1 05") == 0){
			//pedido
			srand(time(NULL));
			espera = 20 + (rand() % 100);
			printf("Tempo de preparo: %is\n", espera);
			sleep(espera);
			strcpy(mensagem, "Pedido finalizado!\n");
			sendto(server, mensagem, sizeof(mensagem), 0 , (struct sockaddr *) &caddr, length);

		}else if(strcmp(buffer, "2") == 0){
			//cardapio
			sendto(server, cardapio, sizeof(cardapio), 0 , (struct sockaddr *) &caddr, length);

		}else if(strcmp(buffer, "3 01") == 0 || strcmp(buffer, "3 02") == 0 || strcmp(buffer, "3 03") == 0 || strcmp(buffer, "3 04") == 0 || strcmp(buffer, "3 05") == 0){
			//detalhes do prato

			char *substring = strtok(buffer, " ");
			char *substring2 = strtok(NULL, " ");
			
			if (strcmp(substring2, "01") == 0){
				sendto(server, xBurger, sizeof(xBurger), 0 , (struct sockaddr *) &caddr, length);
			}else if(strcmp(substring2, "02") == 0){
				sendto(server, xSalada, sizeof(xSalada), 0 , (struct sockaddr *) &caddr, length);
			}else if(strcmp(substring2, "03") == 0){
				sendto(server, xBacon, sizeof(xBacon), 0 , (struct sockaddr *) &caddr, length);
			}
			else if(strcmp(substring2, "04") == 0){
				sendto(server, xEgg, sizeof(xEgg), 0 , (struct sockaddr *) &caddr, length);
			}else{
				sendto(server, xFrango, sizeof(xFrango), 0 , (struct sockaddr *) &caddr, length);
			}
			
		}else{
			strcpy(mensagem, "Opção inválida!\n");
			sendto(server, mensagem, sizeof(mensagem), 0 , (struct sockaddr *) &caddr, length);
		}

	}

	return 0;
				
}

	