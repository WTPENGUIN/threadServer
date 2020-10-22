#ifndef __SERVER__HEADER__
#define __SERVER__HEADER__
#include "Server_Header.h"
#endif

// Server Init
int server_Init(char *port) {

	int sv_Sock;
	struct sockaddr_in sv;
	int reuseADDR = 1;

	sv_Sock = socket(PF_INET, SOCK_STREAM, 0);

	if(sv_Sock < 0) {
		#ifdef __DEBUG_
		perror("socket fail.");
		#endif
		exit(1);
	}

	// Set Socket REUSEADDR Option
	if(setsockopt(sv_Sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuseADDR, sizeof(reuseADDR)) < 0) {
		#ifdef __DEBUG_
		perror("SERVER Setting Socket Option fail.");
		#endif
		exit(1);
	}

	memset(&sv, 0, sizeof(sv));
	sv.sin_family = AF_INET;
	sv.sin_addr.s_addr = htonl(INADDR_ANY);
	sv.sin_port = htons(atoi(port));

	// Bind Fail.
	if(bind(sv_Sock, (struct sockaddr*) &sv, sizeof(sv)) < 0) {
		#ifdef __DEBUG_
		perror("bind error");
		#endif
		exit(1);
	}

	// Listen Fail.
	if(listen(sv_Sock, 5) < 0) {
		#ifdef __DEBUG_
		perror("listen error");
		#endif
		exit(1);
	}

	return sv_Sock;
}