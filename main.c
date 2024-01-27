#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
    WSADATA ws;
    if (WSAStartup(MAKEWORD(2, 2), &ws))
    {
        fprintf(stderr, "WSAStartup failed\n");
        return 1;
    }
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET)
    {
        fprintf(stderr, "Socket creation failed\n");
        return 1;
    }
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(80);  // Port 80
    serverAddr.sin_addr.s_addr = inet_addr("93.184.216.34");
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        fprintf(stderr, "Connection failed with error code: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    const char* GetRequest="GET / HTTP/1.1\r\n"
                           "Host: www.example.com\r\n"
                           "Connection: close\r\n\r\n";
    if (send(clientSocket,GetRequest,strlen(GetRequest),0)==SOCKET_ERROR)
    {
        fprintf(stderr, "Connection failed with error code: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    char buffer[4096];
    int bytesCount=0;
    while ((bytesCount=recv(clientSocket,buffer, sizeof(buffer),0))>0)
    {
        fwrite(buffer, 1, bytesCount, stdout);
    }
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
