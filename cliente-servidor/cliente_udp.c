#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1" // Altere se necessário

int main()
{
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in serverAddr;
    char *filename = "documento.txt"; // Nome do arquivo a ser enviado
    FILE *file;
    char buffer[1024];

    // Inicializa o Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("Falha ao inicializar Winsock. Erro: %d\n", WSAGetLastError());
        return 1;
    }

    // Cria o socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET)
    {
        printf("Falha ao criar socket. Erro: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Configura o endereço do servidor
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Abre o arquivo para leitura
    file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("Falha ao abrir o arquivo: %s\n", filename);
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Lê o arquivo e envia os dados
    while (fread(buffer, 1, sizeof(buffer), file) > 0)
    {
        sendto(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
        memset(buffer, 0, sizeof(buffer)); // Limpa o buffer
    }

    printf("Arquivo enviado com sucesso.\n");

    // Fecha o arquivo e limpa
    fclose(file);
    closesocket(sock);
    WSACleanup();

    return 0;
}
