#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
    pid_t pid = fork();

    if(pid < 0){
        perror("Fork failed");
        return 1;
    }
    else if(pid == 0){
        // Child process
        int ret = nice(-5); // decrease nice value → higher priority
        if(ret == -1 && errno) perror("nice() failed");
        printf("Child Process PID=%d, nice value=%d\n", getpid(), ret);
        for(int i=0; i<5; i++){
            printf("Child running %d\n", i+1);
            sleep(1);
        }
    }
    else{
        // Parent process
        printf("Parent Process PID=%d\n", getpid());
        for(int i=0; i<5; i++){
            printf("Parent running %d\n", i+1);
            sleep(1);
        }
        wait(NULL);
    }

    return 0;
}
