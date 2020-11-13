#ifndef __SERVER__HEADER__
#define __SERVER__HEADER__
#include "Server_Header.h"
#endif

// CLient Control Thread Function
void * ctr_Client(void * arg) {
	
	// Structure Copy
	Client CL = *(Client *)arg;
	
	int str_len = 0;
	char msg[BUF_SIZE];
	
	while(1) {
		
		// Init msg array to 0
		memset(msg, 0, sizeof(msg));

		// Read Socket Message
		str_len = read(CL.num_sock, msg, sizeof(msg));
		
		#ifdef __DEBUG_
		printf("%d socket message, %s\n", CL.num_sock, msg);
		#endif
		
		// if read() return <=0, break loop and excute disconnect code
		if(str_len <= 0)
			break;
		
		// Send message to all Client
		send_msg(msg, str_len, CL.num_sock);
	}
	
	// Disconnect Code
	pthread_mutex_lock(&mutex_c);
	for(int i = 0; i < cl_num; i++) {
		if(CL.num_sock == cl_socks[i].num_sock) {
			for(int j = i; j < cl_num; j++)
				cl_socks[j] = cl_socks[j + 1];
		}
	}
	cl_num--;
	#ifdef __DEBUG_
	printf("%d socket disconnect! %d\n", CL.num_sock, cl_num);
	#endif
	pthread_mutex_unlock(&mutex_c);

	// Socket close
	close(CL.num_sock);
	
	return NULL;
}