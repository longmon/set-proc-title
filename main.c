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
    cli_set_proc_title_init(argc,argv,environ);
    cli_set_proc_title("title:%s asddd\n", "aaaaaa");
    printf("os_main_argv:%p\n", os_main_argv);
    printf("os_main_argv_end:%p\n", os_main_argv_end);
}

void cli_set_proc_title( const char *fmt, ...) {
    va_list vp;
    char *p;
    int i;
    va_start(vp, fmt);
    vsprintf(p, fmt, vp);
    va_end(vp);

}

void cli_set_proc_title_init(int argc, char *argv[], char **envp) {
    int i;
    for( i = 0; envp[i]; i++ ) continue;
    if( i > 0 ) {
        os_main_argv_end = envp[i-1]+strlen(envp[i-1])+1;
    } else {
        os_main_argv_end = argv[argc-1]+strlen(argv[argc-1])+1;
    }
    for( i = 0; envp[i]; i++ ){
        environ[i] = (char **)calloc( sizeof(char), strlen(envp[i])*sizeof(char));
        strcpy(environ[i], envp[i]);
    }
    environ[i] = NULL;
    os_main_argv = argv;
}