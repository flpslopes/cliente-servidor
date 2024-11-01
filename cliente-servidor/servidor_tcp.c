#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Inicializa a biblioteca Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Falha na inicialização do Winsock. Erro: %d\n", WSAGetLastError());
        return 1;
    }

    // Cria o socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Falha ao criar socket. Erro: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Configura o endereço do servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Faz o bind do socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Erro ao fazer bind. Erro: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    // Escuta por conexões
    if (listen(server_socket, 3) == SOCKET_ERROR) {
        printf("Erro ao escutar. Erro: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Servidor TCP aguardando conexão...\n");

    // Aceita uma conexão
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
    if (client_socket == INVALID_SOCKET) {
        printf("Erro ao aceitar conexão. Erro: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Cliente conectado.\n");

    // Cria ou abre o arquivo na área de trabalho
    FILE *file = fopen("C:\\Users\\Felipe\\Desktop\\ARQUIVO SALVO.txt", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    // Recebe dados do cliente
    int bytes_received;
    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, sizeof(char), bytes_received, file);
    }

    printf("Arquivo recebido via TCP.\n");

    // Fecha os sockets e o arquivo
    fclose(file);
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
