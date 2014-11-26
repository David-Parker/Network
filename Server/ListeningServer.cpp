#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <process.h>
#include "ListeningServer.h"

using namespace std;
using namespace std::chrono;

void ListeningServer::ReportError(int errorCode, const char * function) {
	char errMsg[128] = {};
	errMsg[127] = '\0';
	sprintf(errMsg, "Call to %s returned error %d.", function, errorCode);
	MessageBox(NULL, errMsg, "socketIndication", MB_OK);
}

unsigned __stdcall ClientSession(void *data)
{
    SOCKET client_socket = (SOCKET)data;
    cout << "A new client connected." << endl;
    char * buf = new char[256];

    while(strcmp(buf,"close")) {
    	ListeningServer ls;
    	ls.recieve(client_socket, buf);
    	printf("%s\n", buf);
    	 //std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int ListeningServer::setupListening(int port) {
	WORD sockVersion;
	WSADATA wsaData;
	int nret;

	/* Winsock version 1.1 */
	sockVersion = MAKEWORD(1,1);

	/* Initialize Winsock */
	WSAStartup(sockVersion, &wsaData);

	/* Create a socket using TCP protocol */
	listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	checkError(listeningSocket,"socket()");

	/* Address Information */
	SOCKADDR_IN serverInfo;

	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = INADDR_ANY;

	serverInfo.sin_port = htons(port);

	/* Bind the socket to the port */
	nret = bind(listeningSocket, (LPSOCKADDR)&serverInfo, sizeof(struct sockaddr));
	checkError(nret,"bind()");

	/* Socket will now listen for a client */
	nret = listen(listeningSocket, NUM_CONNECTIONS);
	checkError(nret,"listen()");

	/* Server successfully established! */
	printf("Server successfully established on port %d!\n", port);

	/* Wait for client */
	while((client = accept(listeningSocket, NULL,NULL))) {
		unsigned threadID;
        HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &ClientSession, (void*)client, 0, &threadID);
	}

	checkError(client,"accept()");

	return NETWORK_OK;
}

void ListeningServer::closeServer() {
	closesocket(client);
	closesocket(listeningSocket);
	WSACleanup();
}

void ListeningServer::recieve(SOCKET sock, char * &buffer) {
	int nret;
	nret = recv(sock, buffer, sizeof(buffer), 0);
	if(nret == SOCKET_ERROR) {
		ReportError(WSAGetLastError(), "recieve()");
	}
}