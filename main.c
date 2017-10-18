#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdarg.h>

extern char **environ;

static char **os_main_argv = NULL;
static char *os_main_argv_end = NULL;

void cli_set_proc_title_init(int argc, char **argv, char **envp);

void cli_set_proc_title( const char *fmt, ...);

int main( int argc, char *argv[] ){
    char *os_argv_last;
    char *p;
    size_t  size;
    size = 0;
    int i;
    for( i = 0; environ[i]; i++ ){
        size += strlen(environ[i])+1;
    }
    p = calloc(sizeof(char), size);
    os_argv_last = argv[0];
    for( i = 0; argv[i]; i++ ){
        if( os_argv_last == argv[i] ){
            os_argv_last = argv[i]+strlen(argv[i])+1;
        }
    }
}

void cli_set_proc_title( const char *fmt, ...) {
    va_list vp;
    char *p;
    int i;
    va_start(vp, fmt);
    vsprintf(p, fmt, vp);
    va_end(vp);
    printf(p);
}

void cli_set_proc_title_init(int argc, char *argv[], char **envp) {
    int i;
    for( i = 0; envp[i]; i++ ) continue;
    if( i > 0 ) {
        os_main_argv_end = envp[i-1]+strlen(envp[i])+1;
    } else {
        os_main_argv_env = argv[argc-1]+strlen(argv[argc-1])+1;
    }
    environ = (char**)calloc( sizeof(char*), sizeof(char*) *(i+1) );
    for( i = 0; envp[i]; i++ ){
        environ[i] = strdup(envp[i]);
    }
    environ[i] = NULL;
}