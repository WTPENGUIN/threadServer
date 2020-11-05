#ifndef __SERVER__HEADER__
#define __SERVER__HEADER__
#include "Server_Header.h"
#endif

int auth(Login USER) {
    
    MYSQL       *connection=NULL, conn;
    MYSQL_RES   *sql_result;
    MYSQL_ROW   sql_row;
    int         query_stat;
    char        table_name[5] = "USER"; 

    char ID[10];
    char PASSWD[16];
    char QUERY[100];
    int result;

    mysql_init(&conn);

    connection = mysql_real_connect(&conn, DB_HOST,
                                    DB_USER, DB_PASS,
                                    DB_NAME, DB_PORT,
                                    (char *)NULL, 0);
                                    
    if (connection == NULL) {
        fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
        return 1;
    }

	sprintf(QUERY, "select PASSWD from %s where ID=\"%s\"", table_name, USER.ID);
    query_stat = mysql_query(connection, QUERY);
    #ifdef __DEBUG_
    printf("%s\n",QUERY);
    #endif
    
    if (query_stat != 0) {
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        
        mysql_free_result(sql_result);
        mysql_close(connection);
        return -1;
    }
    
    // Store result
    sql_result = mysql_store_result(connection);
    sql_row = mysql_fetch_row(sql_result);

    //Auth Begin
    #ifdef __DEBUG_
    printf("Auth : %s %s Check\n", sql_row[0], USER.PW);
    #endif

    if(!strcmp(sql_row[0], USER.PW)) {
        #ifdef __DEBUG_
        printf("Auth Clear.\n");
        #endif
        result = 1;
    }
    else {
        #ifdef __DEBUG_
        printf("Auth Fail.\n");
        #endif
        result = -1;
    }

    //Auth End

    mysql_free_result(sql_result);
    mysql_close(connection);
    return result;
}