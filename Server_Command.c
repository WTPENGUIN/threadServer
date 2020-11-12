#ifndef __SERVER__HEADER__
#define __SERVER__HEADER__
#include "Server_Header.h"
#endif

void * sv_Function(void *arg) {
	
	char buf_username[50];
	char buf_password[50];
	
	printf("명령어 목록 : help, list, userlist, adduser, deluser, clear, quit\n");
	
	while (1) {
		char bufmsg[512];
		int command_Number = 0;
		
		fprintf(stderr, "\033[1;32m");                    // Text Color : green
		
		printf("[SERVER]>");                              // Output cursor
		fgets(bufmsg, 512, stdin);                        // Input Command
		
		if (!strcmp(bufmsg, "\n")) continue;     	      // ignore \n
		
		// help command
		else if (!strcmp(bufmsg, "help\n"))  {
			printf("help - 도움말\n");
			printf("list - 현재 클라이언트 리스트 출력\n");
			printf("userlist - 계정 데이터베이스에 있는 모든 계정 ID를 가져옵니다.\n");
			printf("adduser <name> <passward> - 계정 데이터베이스에 새로운 계정을 추가합니다.\n");
			printf("deluser <name> - 계정 데이터베이스에 있는 기존 계정을 삭제합니다.\n");
			printf("clear - 화면을 지웁니다.\n");
			printf("quit - 서버 종료\n");
		}
		// list command
		else if (!strcmp(bufmsg, "list\n")) { 	          
			printf("현재 접속한 클라이언트 ID : ");
			pthread_mutex_lock(&mutex_c);
			for(int i = 0; i < cl_num; i++) {
				if(cl_socks[i].login_MODE == 2)
					printf("  %s(%d번 소켓 SYSTEM)", cl_socks[i].ID, cl_socks[i].num_sock);
				else
					printf("  %s(%d번 소켓)", cl_socks[i].ID, cl_socks[i].num_sock);
				}
			pthread_mutex_unlock(&mutex_c);
			printf("\n");
		}
		// 유저 조회 명령어
		else if(!strcmp(bufmsg, "userlist\n")) {
			db_Command("SELECT", "ACCOUNT", "USER", NULL, NULL, 0);
			printf("\n");
		}
		// 유저 추가 명령어
		else if(!strcmp(bufmsg, "adduser\n")) {
			printf("새로운 사용자 이름을 입력해 주세요 : ");
			fgets(buf_username, 50, stdin);
			
			if (!strcmp(buf_username, "\n")) {
				printf("사용자 이름은 공백일 수 없습니다..\n");
			}
			
			// 끝에 개행 문자 대신 널 문자로 교체
			for(int i = 0; i <= 50; i++) {
				if(buf_username[i] == '\n') {
					buf_username[i] = '\0';
					break;
				}
			}
			
			printf("비밀번호를 입력해 주세요 : ");
			fgets(buf_password, 50, stdin);
			
			if (!strcmp(buf_password, "\n")) {
				printf("비밀번호는 공백일 수 없습니다..\n");
			}

			// 끝에 개행 문자 대신 널 문자로 교체
			for(int i = 0; i <= 50; i++) {
				if(buf_password[i] == '\n') {
					buf_password[i] = '\0';
					break;
				}
			}
			
			// DB 추가 명령
			db_Command("INSERT", "ACCOUNT", "USER", buf_username, hash_my_password(buf_password), 0);
			
			// 버퍼 초기화
			memset(buf_username, 0, sizeof(buf_username));
			memset(buf_password, 0, sizeof(buf_password));
		}
		// 유저 삭제 명령어
		else if(!strcmp(bufmsg, "deluser\n")) {
			printf("삭제할 사용자 이름을 입력해 주세요 : ");
			fgets(buf_username, 50, stdin);
			
			if (!strcmp(buf_username, "\n")) {
				printf("사용자 이름은 공백일 수 없습니다..\n");
			}
			
			// 끝에 개행 문자 대신 널 문자로 교체
			for(int i = 0; i <= 50; i++) {
				if(buf_username[i] == '\n') {
					buf_username[i] = '\0';
					break;
				}
			}
			
			// DB 삭제 명령
			db_Command("DELETE", "ACCOUNT", "USER", buf_username, NULL, 0);
			
			//버퍼 초기화
			memset(buf_username, 0, sizeof(buf_username));
		}
		// 화면 지우기
		else if(!strcmp(bufmsg, "clear\n")) {
			system("clear");
		}
		// 서버 종료
		else if (!strcmp(bufmsg, "quit\n"))
			printf("구현중입니다.(임시로 Ctrl + c를 사용하세요.)\n");
		else
			printf("해당 명령어가 없습니다. help를 참조하세요.\n");
	}
}