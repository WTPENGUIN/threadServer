#ifndef __SERVER__HEADER__
#define __SERVER__HEADER__
#include "Server_Header.h"
#endif

void read_Config(void) {
    
    struct json_object_iterator it, itEnd;
    struct json_object* obj;
    const char* type;
    const char* name;
    
    /* JSON type의 데이터를 읽는다. */
    obj =  json_object_from_file("./config.json");

    if(obj == NULL) {
        printf("Check json file\n");
        exit(1);
    }
    
    it = json_object_iter_begin(obj);
    itEnd = json_object_iter_end(obj);
    
    while(!json_object_iter_equal(&it, &itEnd)) {
        
        // JSON에서 읽은 데이터 유형 얻기
        type = json_type_to_name(json_object_get_type(json_object_iter_peek_value(&it)));
        name = json_object_iter_peek_name(&it);
        
        if(!strcmp(type,"string")) {
            if(!strcmp("DB_HOST", name)) {
                strcpy(cfg.HOST, json_object_get_string(json_object_iter_peek_value(&it)));
            }
            else if(!strcmp("DB_USER", name)) {
                strcpy(cfg.USER, json_object_get_string(json_object_iter_peek_value(&it)));
            }
            else if(!strcmp("DB_PASS", name)) {
                strcpy(cfg.PASS, json_object_get_string(json_object_iter_peek_value(&it)));
            }
            else
                continue;        
        }
        else if(!strcmp(type,"int")) {
            cfg.PORT = json_object_get_int(json_object_iter_peek_value(&it));
        }
        else {
            printf("Unkown Type.\n");
        }
        json_object_iter_next(&it);
    }
}