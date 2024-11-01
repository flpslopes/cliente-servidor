#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    FILE *file;

    // Inicialização do Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Criar socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        perror("Erro ao criar socket");
        return 1;
    }

    // Configurar endereço do servidor
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Conectando ao localhost

    // Conectar ao servidor
    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Erro ao conectar");
        return 1;
    }

    // Abrir o arquivo para envio
    file = fopen("caminho_do_seu_arquivo.txt", "rb"); // Substitua pelo caminho do arquivo que deseja enviar
    if (file == NULL) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    // Enviar dados para o servidor
    int bytesRead;
    while ((bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, file)) > 0) {
        send(sock, buffer, bytesRead, 0);
    }

    printf("Arquivo enviado via TCP.\n");

    // Fechar arquivos e sockets
    fclose(file);
    closesocket(sock);
    WSACleanup();
    return 0;
}
