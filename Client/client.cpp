#include <iostream>
#include <windows.h> 
#include <winsock.h> 
#include <stdio.h>
#include "Connection.h"

using namespace std;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmd, int nShow) {
	int port = 80;
	char ip[32];
	char name[MAX_MESSAGE_SIZE];

	cout << "Please enter a username: ";
	cin.getline(name,MAX_MESSAGE_SIZE);

	cout << "Please enter a port number (default is 80): ";
	cin >> port;

	cout << "Please enter an ip address: ";
	cin >> ip;

	// port = 88;
	// char * ip = "127.0.0.1";

	Connection conn;
	conn.setupConnection(port, ip);
	conn.sendMessage(name);

	char msg[MAX_MESSAGE_SIZE] = {};

	while(strcmp(msg,"close")) {
		cin.getline(msg,MAX_MESSAGE_SIZE);
		printf("Message is %s\n", msg);
		conn.sendMessage(msg);
	}

	conn.closeConnection();

	return 0;
}