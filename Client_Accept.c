#ifndef __SERVER__HEADER__
#define __SERVER__HEADER__
#include "Server_Header.h"
#endif

// Define ERROR MESSAGE
const char LOG_ERR_A[]      = "ALREADY_LOGINED\n";
const char LOG_ERR_F[]      = "LOGIN_FAILED\n";
const char LOG_SUC[]        = "LOGIN_SUCCESS\n";
const char LOG_SUC_DEBUG[]  = "LOGIN_SUCCESS_DEBUG\n";

// Client Connection accept  FORM( ID:PASSWD:LOGINMODE )
Client cl_Accept(int sv_Sock) {
	int cl_Sock;                   // Client Socket Distritor
	int cl_size;			       // Client Struct Size
	int read_b;                    // Read bytes
	char read_msg[BUF_SIZE];       // Read Message

	struct sockaddr_in cl;         // Client Socket Struct 
	Client __currntClient;         // Client Structure for login success
	Login __currntLogin;           // LOGIN Structure
	struct timeval timer;

	// init Struct
	memset(&__currntClient, 0, sizeof(struct Client));
	memset(&__currntLogin, 0, sizeof(struct Login));

	// Timer set
	timer.tv_sec = 30;
	timer.tv_usec = 0;

	cl_size = sizeof(cl);
	cl_Sock = accept(sv_Sock, (struct sockaddr*)&cl, &cl_size);

	// accept fail
	if(cl_Sock < 0) {
		#ifdef __DEBUG_
		perror("accept fail.");
		#endif

		__currntClient.num_sock = -1;
		return __currntClient;
	}

	read_b = read(cl_Sock, &read_msg, BUF_SIZE);
	read_msg[read_b] = '\0'; // unused data cut

	#ifdef __DEBUG_
	printf("Read Complete. %s\n", read_msg);
	#endif

	// Read Fail Login Structure
	if(read_b <= 0 ) {
		#ifdef __DEBUG_
		printf("Read Login Info faild\n");
		#endif
		
		write(cl_Sock, LOG_ERR_F, sizeof(LOG_ERR_F));
		__currntClient.num_sock = -1;
		close(cl_Sock);
		return __currntClient;
	}

	#ifdef __DEBUG_
	printf("Read Check Complete.\n");
	#endif

	returnLogin(&__currntLogin, read_msg);

	//returnLogin Fail.
	if(strcmp(__currntLogin.ID, "FAIL") == 0 && strcmp(__currntLogin.PW, "FAIL") == 0) {
		
		#ifdef __DEBUG_
		printf("Return Login corrupt.\n");
		#endif

		write(cl_Sock, LOG_ERR_F, sizeof(LOG_ERR_F));
		__currntClient.num_sock = -1;
		close(cl_Sock);
		return __currntClient;
	}

	// Check Same connection
	pthread_mutex_lock(&mutex_c);
	for(int i = 0; i <= cl_num; i++) {
		if(cl_socks[i].ID == __currntLogin.ID) {
			
			write(cl_Sock, LOG_ERR_A, sizeof(LOG_ERR_A));

			//Same Connection Detect
			__currntClient.num_sock = -1;
			close(cl_Sock);
			pthread_mutex_unlock(&mutex_c);
			return __currntClient;
		}
	}
	pthread_mutex_unlock(&mutex_c);

	#ifdef __DEBUG_
	printf("ID : %s, PASSWORD(HASH) : %s LOGIN MODE : %d\n", __currntLogin.ID, __currntLogin.PW , __currntLogin.login_MODE);
	#endif

	// Login Mode Check
	if(__currntLogin.login_MODE < 0 || __currntLogin.login_MODE > 2 ) {

		#ifdef __DEBUG_
		printf("ID : %s is Wrong Login Mode!\n", __currntLogin.ID);
		#endif

		write(cl_Sock, LOG_ERR_F, sizeof(LOG_ERR_F));
		__currntClient.num_sock = -1;
		close(cl_Sock);
		return __currntClient;
	}

	// Debug Mode Login
	if(__currntLogin.login_MODE == 2) { 

		#ifdef __DEBUG_ 
		printf("ID : %s in DEBUG MODE!\n", __currntLogin.ID);
		#endif
		
		write(cl_Sock, LOG_SUC_DEBUG, sizeof(LOG_SUC_DEBUG));

		// Client Structure setting start
		strncpy(__currntClient.ID, __currntLogin.ID, strlen(__currntLogin.ID)); // ID SET
		__currntClient.num_sock = cl_Sock;										// Socket Number Set
		memcpy(&(__currntClient.info_client), &cl, sizeof(struct sockaddr_in)); // Socket Structure Set
		__currntClient.login_MODE = __currntLogin.login_MODE;					// Login Mode Set

		#ifdef __DEBUG_
		printf("ID(client_debug) : %s Check.\n", __currntClient.ID);
		printf("ID(login_debug) : %s Check.\n", __currntLogin.ID);
		#endif

		return __currntClient;
	}

	// Auth Check
	if(auth(__currntLogin) < 0) {

		#ifdef __DEBUG_
		printf("ID : %s Auth Fail.\n", __currntLogin.ID);
		#endif

		write(cl_Sock, LOG_ERR_F, sizeof(LOG_ERR_F));
		__currntClient.num_sock = -1;
		close(cl_Sock);
		return __currntClient;
	}
	// Login Process END

	// Client Structure Set.
	strncpy(__currntClient.ID, __currntLogin.ID, strlen(__currntLogin.ID));
	__currntClient.num_sock = cl_Sock;
	memcpy(&(__currntClient.info_client), &cl, sizeof(struct sockaddr_in));
	__currntClient.login_MODE = __currntLogin.login_MODE;

	if(setsockopt(cl_Sock, SOL_SOCKET, SO_RCVTIMEO, &timer, sizeof(timer)) == -1 ) {
		#ifdef __DEBUG_
		perror("Client Setting Socket Option fail.");
		#endif
		write(cl_Sock, LOG_ERR_F, sizeof(LOG_ERR_F));
		__currntClient.num_sock = -1;
		close(cl_Sock);
		return __currntClient;
	}
	
	#ifdef __DEBUG_
	printf("ID(client) : %s Check.\n", __currntClient.ID);
	printf("ID(login) : %s Check.\n", __currntLogin.ID);
	#endif

	//LOGIN MESSAGE
	write(cl_Sock, LOG_SUC, sizeof(LOG_SUC));

	return __currntClient;
}