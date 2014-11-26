#include <iostream>
#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include "ListeningServer.h"

using namespace std;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR lpCmdLine, int nCmdShow) {
	int port = 80;
	cout << "Please enter a port number (default is 80): ";
	cin >> port;

	ListeningServer ls;
	ls.setupListening(port);
	// char * buf = new char[256];
	// ls.recieve(buf);

	// cout << buf;

	ls.closeServer();
	return 0;
}

