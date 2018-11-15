#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int status;
    printf("parent pid = %d\n",getpid());

    pid_t pid1 = fork();
    if(pid1 == 0){
        printf("child pid = %d\n",getpid());
        execlp("./child_process/subtraction","subtraction",NULL);
    }
    
    pid_t pid_that_I_wait_for;
    pid_that_I_wait_for = wait(&status);
    printf("parent wait for %d successfully\n",pid_that_I_wait_for);
    printf("All process finish\n");

    return 0;
}

/**
 * 
 * 註：
 *   如果有一個兒子被其 parent fork() 出來之後就執行 exec()
 *   那麼該 parent 還是可以 wait() ，等該兒子做完
 * 
*/