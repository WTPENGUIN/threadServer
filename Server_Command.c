#ifndef __SERVER__HEADER__
#define __SERVER__HEADER__
#include "Server_Header.h"
#endif

void * sv_Function(void *arg) {
    int i;

	printf("명령어 목록 : help, list, quit\n");

	while (1) {
		char bufmsg[512];
		int command_Number = 0;

		fprintf(stderr, "\033[1;32m");                    // Text Color : green

		printf("[SERVER]>");                              // Output cursor
		fgets(bufmsg, 512, stdin);                        // Input Command

		if (!strcmp(bufmsg, "\n")) continue;     	      // ignore \n

		else if (!strcmp(bufmsg, "help\n"))  {   		  // help command
			printf("help - 도움말\n");
			printf("list - 현재 클라이언트 리스트 출력\n");
			printf("quit - 서버 종료\n");
		}
		else if (!strcmp(bufmsg, "list\n")) { 	          // list command
			printf("현재 접속한 클라이언트 ID : ");
			pthread_mutex_lock(&mutex_c);
			for(i = 0; i < cl_num; i++) {
				if(cl_socks[i].login_MODE == 2)
					printf("  %s(%d번 소켓 DEBUG)", cl_socks[i].ID, cl_socks[i].num_sock);
				else
					printf("  %s(%d번 소켓)", cl_socks[i].ID, cl_socks[i].num_sock);
			}
			pthread_mutex_unlock(&mutex_c);
			printf("\n");
		}
        else if (!strcmp(bufmsg, "quit\n")) 			   // quit command
			printf("구현중입니다.(임시로 Ctrl + c를 사용하세요.)\n");
		else //예외 처리
			printf("해당 명령어가 없습니다. help를 참조하세요.\n");
	}
}