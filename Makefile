#########################################
#    SIMPLE_IOT_SERVER_MAKEFILE         #
#########################################

CC = gcc
TARGET = IOT_SERVER
LIB1 = -lpthread
LIB2 = -lmariadbclient
THREAD_SAFE = -D_REENTRANT
DEBUG = -D__DEBUG_

$(TARGET): Server_Main.o CTR_Client.o Send_MSG.o Server_Init.o Client_Accept.o Return_Login.o Auth.o Server_Command.o
	@echo ========================================
	@echo ========================================
	@echo Build start.....
	$(CC) -o IOT_SERVER Server_Main.o CTR_Client.o Send_MSG.o Server_Init.o Client_Accept.o Return_Login.o Auth.o Server_Command.o $(LIB1) $(LIB2) $(THREAD_SAFE)

debug : Server_Main_DEBUG CTR_Client_DEBUG Send_MSG_DEBUG Server_Init_DEBUG Client_Accept_DEBUG Return_Login_DEBUG Auth_DEBUG Server_Command_DEBUG
	@echo ========================================
	@echo ========================================
	@echo Build start..... DEBUG MODE
	$(CC) -o IOT_SERVER_DEBUG Server_Main.o CTR_Client.o Send_MSG.o Server_Init.o Client_Accept.o Return_Login.o Auth.o Server_Command.o $(LIB1) $(LIB2) $(DEBUG) $(THREAD_SAFE)

Server_Main.o : Server_Header.h Server_Main.c
	@echo ---------------------------------------
	@echo Compile : Server_Main.c
	@echo ---------------------------------------
	$(CC) -c Server_Main.c $(LIB1) $(LIB2) $(THREAD_SAFE)

Server_Main_DEBUG : Server_Header.h Server_Main.c
	@echo ---------------------------------------
	@echo Compile : Server_Main.c DEBUG MODE
	@echo ---------------------------------------
	$(CC) -c Server_Main.c $(LIB1) $(LIB2) $(DEBUG) $(THREAD_SAFE)

Server_Command.o : Server_Header.h Server_Command.c
	@echo ---------------------------------------
	@echo Compile : Server_Command.c
	@echo ---------------------------------------
	$(CC) -c Server_Command.c $(LIB1) $(LIB2) $(THREAD_SAFE)

Server_Command_DEBUG : Server_Header.h Server_Command.c
	@echo ---------------------------------------
	@echo Compile : Server_Command.c
	@echo ---------------------------------------
	$(CC) -c Server_Command.c $(LIB1) $(LIB2) $(DEBUG) $(THREAD_SAFE)

CTR_Client.o : Server_Header.h CTR_Client.c
	@echo ---------------------------------------
	@echo Compile : CTR_Client.c
	@echo ---------------------------------------
	$(CC) -c CTR_Client.c $(LIB1) $(LIB2) $(THREAD_SAFE)

CTR_Client_DEBUG : Server_Header.h CTR_Client.c
	@echo ---------------------------------------
	@echo Compile : CTR_Client.c DEBUG MODE
	@echo ---------------------------------------
	$(CC) -c CTR_Client.c $(LIB1) $(LIB2) $(DEBUG) $(THREAD_SAFE)

Send_MSG.o : Server_Header.h Send_MSG.c
	@echo ---------------------------------------
	@echo Compile : Send_MSG.c
	@echo ---------------------------------------
	$(CC) -c Send_MSG.c $(LIB1) $(LIB2) $(THREAD_SAFE)

Send_MSG_DEBUG : Server_Header.h Send_MSG.c
	@echo ---------------------------------------
	@echo Compile : Send_MSG.c DEBUG MODE
	@echo ---------------------------------------
	$(CC) -c Send_MSG.c $(LIB1) $(LIB2) $(DEBUG) $(THREAD_SAFE)

Server_Init.o : Server_Header.h Server_Init.c
	@echo ---------------------------------------
	@echo Compile : Server_Init.c
	@echo ---------------------------------------
	$(CC) -c Server_Init.c $(LIB1) $(LIB2) $(THREAD_SAFE)

Server_Init_DEBUG : Server_Header.h Server_Init.c
	@echo ---------------------------------------
	@echo Compile : Server_Init.c DEBUG MODE
	@echo ---------------------------------------
	$(CC) -c Server_Init.c $(LIB1) $(LIB2) $(DEBUG) $(THREAD_SAFE)

Client_Accept.o : Server_Header.h Client_Accept.c
	@echo ---------------------------------------
	@echo Compile : Client_Accept.c
	@echo ---------------------------------------
	$(CC) -c Client_Accept.c $(LIB1) $(LIB2) $(THREAD_SAFE)

Client_Accept_DEBUG : Server_Header.h Client_Accept.c
	@echo ---------------------------------------
	@echo Compile : Client_Accept.c DEBUG MODE
	@echo ---------------------------------------
	$(CC) -c Client_Accept.c $(LIB1) $(LIB2) $(DEBUG) $(THREAD_SAFE)

Return_Login.o : Server_Header.h Return_Login.c
	@echo ---------------------------------------
	@echo Compile : Return_Login.c
	@echo ---------------------------------------
	$(CC) -c Return_Login.c $(LIB1) $(LIB2) $(THREAD_SAFE)

Return_Login_DEBUG : Server_Header.h Return_Login.c
	@echo ---------------------------------------
	@echo Compile : Return_Login.c DEBUG MODE
	@echo ---------------------------------------
	$(CC) -c Return_Login.c $(LIB1) $(LIB2) $(DEBUG) $(THREAD_SAFE)

Auth.o : Server_Header.h Auth.c
	@echo ---------------------------------------
	@echo Compile : Auth.c
	@echo ---------------------------------------
	$(CC) -c Auth.c $(LIB1) $(LIB2) $(THREAD_SAFE)

Auth_DEBUG : Server_Header.h Auth.c
	@echo ---------------------------------------
	@echo Compile : Auth.c DEBUG MODE
	@echo ---------------------------------------
	$(CC) -c Auth.c $(LIB1) $(LIB2) $(DEBUG) $(THREAD_SAFE)
	
clean:
	rm *.o

