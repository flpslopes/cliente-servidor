#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET sockfd;
    struct sockaddr_in server_addr, client_addr;
    int addr_len, recv_len;
    char buffer[BUFFER_SIZE];

    // Inicialização do Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Falha na inicialização do Winsock.\n");
        return 1;
    }

    // Criação do socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("Falha ao criar o socket.\n");
        WSACleanup();
        return 1;
    }

    // Configuração do endereço do servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Associação do socket ao endereço
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Falha ao associar o socket.\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("Servidor UDP esperando por mensagens na porta %d...\n", PORT);

    // Receber dados
    addr_len = sizeof(client_addr);
    recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &addr_len);
    if (recv_len < 0) {
        printf("Falha ao receber dados.\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Criar e escrever o arquivo recebido na área de trabalho
    char *desktop_path = getenv("USERPROFILE");
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%s\\Desktop\\documento recebido udp.txt", desktop_path);

    FILE *file = fopen(file_path, "wb");
    if (file == NULL) {
        printf("Falha ao criar o arquivo.\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    fwrite(buffer, sizeof(char), recv_len, file);
    fclose(file);
    printf("Arquivo recebido e salvo em: %s\n", file_path);

    // Fechar o socket
    closesocket(sockfd);
    WSACleanup();
    return 0;
}
