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
        fprintf(stderr, "Socket cration failed\n");
        return 1;
    }
    int abc = 45;
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(80);  // Port 80
    serverAddr.sin_addr.s_addr = inet_addr("8.8.8.8");
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        fprintf(stderr, "Connection failed with error code: %d\n", WSAGetLastError());
        return 1;
    }
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
