// kill -SIGTERM 19235
// kill -SIGKILL 19244


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void signal_callback_handler(int signum) {
    int pid = getpid();
    printf("Caught signal %d\n", signum);
    fork();
    kill(pid, SIGKILL);
    return;
}

int main() {
    signal(SIGTERM, signal_callback_handler);
    int counter = 0;

    // printf("This process id is %d\n", getpid());
    
    while(1)
    {
        printf("[%d] Counter: %d\n", getpid(), counter++);
        sleep(1);
    }
    return 0;
}