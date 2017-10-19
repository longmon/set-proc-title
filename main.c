#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdarg.h>

extern char **environ;


void cli_set_proc_title(int argc, char *argv[], const char *title);

int main( int argc, char *argv[] ){
    cli_set_proc_title(argc, argv, "cli_test title");
    int i;
    for( i = 0; argv[i]; i++ ) {
        printf("argv[%d](%p):%s\n", i, argv[i], argv[i]);
    }
    for( i = 0; environ[i]; i++ ) {
        printf("environ[%d](%p):%s\n", i, environ[i], environ[i]);
    }
    for(;;){}
}

void cli_set_proc_title(int argc, char *argv[], const char *title) {
    int i;
    char *p;
    size_t size;
    char **tmpargv;
    size_t argv_size = 0;
    for( i = 0; environ[i]; i++ ){
        size += strlen(environ[i])+1;
    }
    for(i = 0; argv[i]; i++ ) {
        argv_size += strlen(argv[i])+1;
    }
    tmpargv = (char**)calloc(sizeof(char), sizeof(char)*argv_size+strlen(title)+1);
    p = (char*)malloc(size);
    char *last_argv = argv[0];
    for( i = 0; i < argc; i++ ){
        if( last_argv == argv[i] ) {
            last_argv = argv[i]+strlen(argv[i])+1;
        }
    }
    for( i = 0; environ[i]; i++ ) {
        if( last_argv == environ[i] ) {
            last_argv = environ[i]+strlen(environ[i])+1;
            size = strlen(environ[i])+1;
            memcpy(p, environ[i], size);
            environ[i] = (char*)p;
            p += size;
        }
    }
    last_argv--;
    tmpargv[0] = strdup(title);
    argv[0] = tmpargv[0];
    for( i = 1; argv[i]; i++ ) {
        tmpargv[i] = strdup(argv[i]);
        argv[i] = tmpargv[i];
    }

}