#ifndef __SERVER__HEADER__
#define __SERVER__HEADER__
#include "Server_Header.h"
#endif

void db_Command(const char* command, const char* dbname, const char* table_name, const char* username, const char* passwd, const int value) {
    MYSQL       *connection=NULL, conn;
    MYSQL_RES   *sql_result;
    MYSQL_ROW   sql_row;

    int query_stat;
    int result;
    char QUERY[100];

    mysql_init(&conn);
    
    connection = mysql_real_connect(&conn, DB_HOST,
                                    DB_USER, DB_PASS,
                                    dbname, DB_PORT,
                                    (char *)NULL, 0);
        
    if (connection == NULL) {
        #ifdef __DEBUG_
        fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
        #endif
    }

    //Command Check(LIST)
    if(strstr(command, "SELECT") != NULL) {

        sprintf(QUERY, "select ID from %s", table_name);
        query_stat = mysql_query(connection, QUERY);
        #ifdef __DEBUG_
        printf("%s\n", QUERY);
        #endif
        
        if (query_stat != 0) {
            #ifdef __DEBUG_
            fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
            #endif
            
            //mysql_free_result(sql_result);
            mysql_close(connection);
        }
        
        // Store result
        sql_result = mysql_store_result(connection);

        // Print
        printf("USERS : ");
        while(sql_row = mysql_fetch_row(sql_result)) {
            printf("%s ", sql_row[0]);
        }

        mysql_free_result(sql_result);
        mysql_close(connection);
    }
    else if(strstr(command, "DELETE") != NULL) {
        if(username != NULL) {

            sprintf(QUERY, "delete from %s where ID=\"%s\"", table_name, username);
            query_stat = mysql_query(connection, QUERY);

            if(query_stat == 0) {
                printf("유저 %s가 데이터베이스에서 삭제되었습니다.\n", username);
            }
            else {
                printf("삭제에 실패하였습니다.\n");
                printf("쿼리 : %s\n", QUERY);
            }
        
            mysql_close(connection);
        }
    }
    else if(strstr(command, "INSERT") != NULL) {
        if(username != NULL) {

            sprintf(QUERY, "insert into %s (ID, PASSWD) values ('%s', '%s')", table_name, username, passwd);
            query_stat = mysql_query(connection, QUERY);

            if(query_stat == 0) {
                printf("유저 %s가 데이터베이스에 추가되었습니다.\n", username);
            }
            else {
                printf("추가에 실패하였습니다.\n");
                printf("쿼리 : %s\n", QUERY);
            }
        
            mysql_close(connection);
        }
    }
}