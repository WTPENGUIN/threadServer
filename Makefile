#########################################
#    SIMPLE_IOT_SERVER_MAKEFILE         #
#########################################

CC = gcc
TARGET = IOT_SERVER
LIB1 = -lpthread
LIB2 = -lmysqlclient
LIB3 = -ljson-c
THREAD_SAFE = -D_REENTRANT
DEBUG = -D__DEBUG_

$(TARGET): Server_Main.o CTR_Client.o Send_MSG.o Server_Init.o Client_Accept.o Token_Login.o Auth.o Server_Command.o DB_Command.o Encrpytion.o Config.o
	@echo ========================================
	@echo ========================================
	@echo Build start.....
	$(CC) -o IOT_SERVER Server_Main.o CTR_Client.o Send_MSG.o Server_Init.o Client_Accept.o Token_Login.o Auth.o Server_Command.o DB_Command.o Encrpytion.o Config.o $(LIB1) $(LIB2) $(LIB3) $(THREAD_SAFE)

debug : Server_Main_DEBUG CTR_Client_DEBUG Send_MSG_DEBUG Server_Init_DEBUG Client_Accept_DEBUG Token_Login_DEBUG Auth_DEBUG Server_Command_DEBUG DB_Command_DEBUG Encrpytion_DEBUG Config_DEBUG
	@echo ========================================
	@echo ========================================
	@echo Build start..... DEBUG MODE
	$(CC) -o IOT_SERVER_DEBUG Server_Main.o CTR_Client.o Send_MSG.o Server_Init.o Client_Accept.o Token_Login.o Auth.o Server_Command.o DB_Command.o Encrpytion.o Config.o $(LIB1) $(LIB2) $(LIB3) $(DEBUG) $(THREAD_SAFE)

Server_Main.o : Server_Header.h Server_Main.c
	@echo ---------------------------------------
	@echo Compile : Server_Main.c
	@echo ---------------------------------------
	$(CC) -c Server_Main.c $(LIB1) $(THREAD_SAFE)

Server_Main_DEBUG : Server_Header.h Server_Main.c
	@echo ---------------------------------------
	@echo Compile : Server_Main.c DEBUG MODE
	@echo ---------------------------------------
	$(CC) -c Server_Main.c $(LIB1) $(DEBUG) $(THREAD_SAFE)

Server_Command.o : Server_Header.h Server_Command.c
	@echo ---------------------------------------
	@echo Compile : Server_Command.c
	@echo ---------------------------------------
	$(CC) -c Server_Command.c $(THREAD_SAFE)

Server_Command_DEBUG : Server_Header.h Server_Command.c
	@echo ---------------------------------------
	@echo Compile : Server_Command.c
	@echo ---------------------------------------
	$(CC) -c Server_Command.c $(DEBUG) $(THREAD_SAFE)

CTR_Client.o : Server_Header.h CTR_Client.c
	@echo ---------------------------------------
	@echo Compile : CTR_Client.c
	@echo ---------------------------------------
	$(CC) -c CTR_Client.c $(LIB1) $(THREAD_SAFE)

CTR_Client_DEBUG : Server_Header.h CTR_Client.c
	@echo ---------------------------------------
	@echo Compile : CTR_Client.c DEBUG MODE
	@echo ---------------------------------------
	$(CC) -c CTR_Client.c $(LIB1) $(DEBUG) $(THREAD_SAFE)

Send_MSG.o : Server_Header.h Send_MSG.c
	@echo ---------------------------------------
	@echo Compile : Send_MSG.c
	@echo ---------------------------------------
	$(CC) -c Send_MSG.c $(LIB1) $(THREAD_SAFE)

Send_MSG_DEBUG : Server_Header.h Send_MSG.c
	@echo ---------------------------------------
	@echo Compile : Send_MSG.c DEBUG MODE
	@echo ---------------------------------------
	$(CC) -c Send_MSG.c $(LIB1) $(DEBUG) $(THREAD_SAFE)

Server_Init.o : Server_Header.h Server_Init.c
	@echo ---------------------------------------
	@echo Compile : Server_Init.c
	@echo ---------------------------------------
	$(CC) -c Server_Init.c $(THREAD_SAFE)

Server_Init_DEBUG : Server_Header.h Server_Init.c
	@echo ---------------------------------------
	@echo Compile : Server_Init.c DEBUG MODE
	@echo ---------------------------------------
	$(CC) -c Server_Init.c $(DEBUG) $(THREAD_SAFE)

Client_Accept.o : Server_Header.h Client_Accept.c
	@echo ---------------------------------------
	@echo Compile : Client_Accept.c
	@echo ---------------------------------------
	$(CC) -c Client_Accept.c $(LIB1) $(THREAD_SAFE)

Client_Accept_DEBUG : Server_Header.h Client_Accept.c
	@echo ---------------------------------------
	@echo Compile : Client_Accept.c DEBUG MODE
	@echo ---------------------------------------
	$(CC) -c Client_Accept.c $(LIB1) $(DEBUG) $(THREAD_SAFE)

Token_Login.o : Server_Header.h Token_Login.c
	@echo ---------------------------------------
	@echo Compile : Token_Login.c
	@echo ---------------------------------------
	$(CC) -c Token_Login.c $(THREAD_SAFE)

Token_Login_DEBUG : Server_Header.h Token_Login.c
	@echo ---------------------------------------
	@echo Compile : Token_Login.c DEBUG MODE
	@echo ---------------------------------------
	$(CC) -c Token_Login.c $(DEBUG) $(THREAD_SAFE)

Auth.o : Server_Header.h Auth.c
	@echo ---------------------------------------
	@echo Compile : Auth.c
	@echo ---------------------------------------
	$(CC) -c Auth.c $(LIB2) $(THREAD_SAFE)

Auth_DEBUG : Server_Header.h Auth.c
	@echo ---------------------------------------
	@echo Compile : Auth.c DEBUG MODE
	@echo ---------------------------------------
	$(CC) -c Auth.c $(LIB2) $(DEBUG) $(THREAD_SAFE)

DB_Command.o : Server_Header.h DB_Command.c
	@echo ---------------------------------------
	@echo Compile : DB_Command.c
	@echo ---------------------------------------
	$(CC) -c DB_Command.c $(LIB2) $(THREAD_SAFE)

DB_Command_DEBUG : Server_Header.h DB_Command.c
	@echo ---------------------------------------
	@echo Compile : DB_Command.c DEBUG MODE
	@echo ---------------------------------------
	$(CC) -c DB_Command.c $(LIB2) $(DEBUG) $(THREAD_SAFE)

Encrpytion.o : Server_Header.h Encrpytion.c
	@echo ---------------------------------------
	@echo Compile : Encrpytion.c
	@echo ---------------------------------------
	$(CC) -c Encrpytion.c $(THREAD_SAFE)

Encrpytion_DEBUG : Server_Header.h Encrpytion.c
	@echo ---------------------------------------
	@echo Compile : Encrpytion.c DEBUG MODE
	@echo ---------------------------------------
	$(CC) -c Encrpytion.c $(DEBUG) $(THREAD_SAFE)

Config.o : Server_Header.h Config.c
	@echo ---------------------------------------
	@echo Compile : Config.c
	@echo ---------------------------------------
	$(CC) -c Config.c $(LIB3) $(THREAD_SAFE)

Config_DEBUG : Server_Header.h Config.c
	@echo ---------------------------------------
	@echo Compile : Config.c
	@echo ---------------------------------------
	$(CC) -c Config.c $(LIB3) $(DEBUG) $(THREAD_SAFE)
	
clean:
	rm *.o

