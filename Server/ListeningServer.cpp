#include <iostream>
#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include "ListeningServer.h"

void ListeningServer::ReportError(int errorCode, const char * function) {
	char errMsg[128] = {};
	errMsg[127] = '\0';
	sprintf(errMsg, "Call to %s returned error %d.", function), errorCode;
	MessageBox(NULL, errMsg, "socketIndication", MB_OK);
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
	SOCKET listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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

	/* Wait for client */
	SOCKET client = accept(listeningSocket, NULL,NULL);
	checkError(client,"accept()");

	/* Do stuff here, send and recieve from the client */

	/* Close the connection */
	closesocket(client);
	closesocket(listeningSocket);
	WSACleanup();

	return NETWORK_OK;
}