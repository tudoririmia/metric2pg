#include <iostream>

enum List { C_NONE, C_CREATE, C_DUMP, C_INFO, C_LIST, C_RESTORE, C_LAST,
        C_LASTUPDATE, C_FIRST, C_UPDATE, C_FETCH, C_GRAPH, C_GRAPHV,
        C_TUNE,
        C_RESIZE, C_XPORT, C_QUIT, C_LS, C_CD, C_MKDIR, C_PWD,
        C_UPDATEV, C_FLUSHCACHED
    };


int metric2pg_create (int argc, char**argv);
int metric2pg_update (int argc, char**argv);
int metric2pg_fetch (int argc, char**argv);
