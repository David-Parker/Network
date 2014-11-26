#ifndef LISTSER_H
#define LISTSER_H

#define NETWORK_ERROR  -1
#define NETWORK_OK 		0
#define NUM_CONNECTIONS 10

#define checkError(item, str)	do { \
		 							if(item == SOCKET_ERROR) {\
		 								nret = WSAGetLastError();\
		 								ReportError(nret,str);\
		 								WSACleanup();\
		 								return NETWORK_ERROR;\
									}\
								} while(0);

class ListeningServer {
private:

public:
	void ReportError(int errorCode, const char * function);
	int setupListening(int port);
};

#endif