#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    pid_t parent_pid=getpid();
    pid_t child_pid[n];


    printf("A process id = %d\n", getpid());
    pid_t maybe_child_pid = fork();
    printf("B process id = %d\n", getpid());

    if (maybe_child_pid > 0) {
        child_pid[0]=maybe_child_pid;
        printf("I am the parent process %d,"
               " child pid = %d\n", 
               parent_pid, child_pid[0]);
    } else if (maybe_child_pid == 0) {
        child_pid[0]=getpid();
        printf("I am the child process %d,"
               " parent pid = %d\n"
               
               , 
               child_pid[0], parent_pid);
         if (execl("./hello", "hello", NULL) == -1) {
            perror("exec");
            exit(EXIT_FAILURE);
        }
    } else {
        // Fork failed
        printf("Fork failed!\n");
    }
    printf("C process id = %d\n", getpid());

    return 0;
}