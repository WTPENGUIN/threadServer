#ifndef __SERVER__HEADER__
#define __SERVER__HEADER__
#include "Server_Header.h"
#endif

// Control Client
void * ctr_Client(void * arg) {

	Client CL = *(Client *)arg;

	int str_len = 0, i;
	char msg[BUF_SIZE];
	
	while(1) {
		str_len = read(CL.num_sock, msg, sizeof(msg));

		if(str_len <= 0)
			break;

		send_msg(msg, str_len, CL.num_sock);
	}
	
	// Disconnect Code
	pthread_mutex_lock(&mutex_c);
	for(i = 0; i < cl_num; i++) {
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

	close(CL.num_sock);
	
	return NULL;
}