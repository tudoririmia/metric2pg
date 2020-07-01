#include <iostream>
#include <string>
#include <list>
#include <iterator>


enum List { C_NONE, C_CREATE, C_DUMP, C_INFO, C_LIST, C_RESTORE, C_LAST,
        C_LASTUPDATE, C_FIRST, C_UPDATE, C_FETCH, C_GRAPH, C_GRAPHV,
        C_TUNE,
        C_RESIZE, C_XPORT, C_QUIT, C_LS, C_CD, C_MKDIR, C_PWD,
        C_UPDATEV, C_FLUSHCACHED, C_DROP
    };

void showlist (std::list <char*> l); 
std::list <char*> tokenize(char* arg);
int metric2pg_create (std::list <char*> arguments);
int metric2pg_update (std::list <char*> arguments);
int metric2pg_fetch (std::list <char*> arguments);
int metric2pg_drop (std::list <char*> arguments);
