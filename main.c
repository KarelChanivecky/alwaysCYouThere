#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>


_Noreturn void execute( char * const * argv ) {

    while ( 1 ) {
        pid_t child = fork();

        if (child == 0) {
            puts("starting child");
            int stat =execvp(argv[1], (argv + 1));
            fprintf(stderr, "Could not start child: status=%d errno=%s\n", stat, strerror(errno));
            exit(EXIT_SUCCESS);
        } else {
            int stat;
            wait(&stat);
            printf("child exit status: %d", stat);
        }
    }
}

int main( int argc, char ** argv) {
    if (argc < 2) {
        perror("You must pass at least one arg");
    }
    execute( argv );
}
