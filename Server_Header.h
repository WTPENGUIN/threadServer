//=========================================================================================//
//                              NAME : SIMPLE IOT SERVER                                   //
//                                  AUTHOR : WTPENGUIN                                     //
//                                    VERSION : 0.01                                       //
//=========================================================================================//

#ifndef __SERVER_HEADER__
#define __SERVER_HEADER__

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <netinet/in.h>

//for MYSQL(Rasbian use Mariadb)
//for MYSQL(Ubuntu use Mysql)
//#include "/usr/include/mariadb/mysql.h"
#include "/usr/include/mysql/mysql.h"

// Define for Client Structure
#define BUF_SIZE      800
#define MAX_CLNT      50
#define MAX_ID        10
#define MAX_PASSWD    20

// Define for MariaDB
#define DB_HOST   "127.0.0.1"
#define DB_USER   "dbconnect"
#define DB_PASS   "5678"
#define DB_NAME   "ACCOUNT"
#define DB_PORT   3306

// CLient Structure
typedef struct Client {
	struct sockaddr_in info_client;
	int num_sock;
	char ID[MAX_ID];

	// Login Mode : 1 - General Mode, 2 - System Mode
	int login_MODE;
}Client;

//Login Structure
typedef struct Login {
	char ID[MAX_ID];
	char PW[MAX_PASSWD];
	int login_MODE;
}Login;

// Funcion Define
int server_Init(char *port);								  // Server Init Func
Client cl_Accept(int sv_Sock);                				  // Client connection accept Func
void * ctr_Client(void * arg);                				  // Client Handle Func(Thread)
void * sv_Function(void *arg);				  				  // Server Command Func(Thread)
void config(void);											  // Server Config
void send_msg(char *msg, int len, int socket_num);            // Message Send Func
void returnLogin(Login *arg, char *msg);      				  // Token Login Message

// Function Define for Auth with Database
int auth(Login USER);                                   // Authentication Function

// Function Define for DB command in Server
void db_Command(const char* command, const char* dbname, const char* table_name, const char* username, const char* passwd, const int value);

// Function for Hash Passward
char* hash_my_password(const char *password);

// Global Variable
int cl_num;           		 // Client Number
Client cl_socks[MAX_CLNT];   // Client Socket Array
pthread_mutex_t mutex_c;  	 // Mutex

#endif