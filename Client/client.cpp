#include <iostream>
#include <windows.h> 
#include <winsock.h> 
#include <stdio.h>
#include "Connection.h"

using namespace std;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmd, int nShow) {
	int port = 80;
	char ip[32];

	cout << "Please enter a port number (default is 80): ";
	cin >> port;

	cout << "Please enter an ip address: ";
	cin >> ip;

	Connection conn;

	return conn.setupConnection(port, ip);
}