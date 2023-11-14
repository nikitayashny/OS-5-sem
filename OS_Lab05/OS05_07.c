#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

// watch ps -eo pid,ppid,ni,cmd

int main() {
    int i;
    pid_t pid = fork();

    if (pid < 0) {
        perror("error");
        return 1;
    }
    else if (pid == 0) { 
        for (i = 1; ; i++) {
            if (i == 10)
                nice(10);
            //printf("Child process: %d\n", i);
            sleep(1);
        }
    }
    else {
        for (i = 1; ; i++) {
            //printf("Parent process: %d\n", i);
            sleep(1);
        }
    }

    return 0;
}