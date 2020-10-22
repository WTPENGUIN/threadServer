#ifndef __SERVER__HEADER__
#define __SERVER__HEADER__
#include "Server_Header.h"
#endif

// Message to Login Structure
void returnLogin(Login *arg, char *msg) {

    char *tempArr[3] = {NULL,NULL,NULL};
    int i = 0;

	char *ptr = strtok(msg, ":");

	while(ptr != NULL) {

        tempArr[i] = ptr;
        i++;

		ptr = strtok(NULL, ":");
	}

    //strtok fail
    if(tempArr[1] == NULL) { // PW token fail
        strcpy(arg->ID, "FAIL");
        strcpy(arg->PW, "FAIL");
        arg->login_MODE = -1;
    }
    //strtok sucess
    else {
        strcpy(arg->ID, tempArr[0]);
        strcpy(arg->PW, tempArr[1]);
        arg->login_MODE = atoi(tempArr[2]);
    }
}