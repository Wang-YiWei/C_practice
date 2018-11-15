#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
/**
 * 
 * Goal : 
 *        Create a parent-child relationship as follows.
 *        m2 wait for p2 p3 p4
 *        m1 wait for m2 p1
 * 
 *                  m1
 *                 /  \
 *                /    \
 *               m2     p1    
 *             / | \
 *            /  |  \
 *           p2  p3  p4
 * 
*/
int main(){
    int child_count = 0;
    pid_t wait_pid[3]; /* There are at most 3 children at the same time. 
                        (m2 create p2 p3 p4) */

    printf("m1 pid = %d\n",getpid());

    pid_t m2_pid = fork();
    if(m2_pid == 0) printf("m2 pid = %d\n",getpid());
    else wait_pid[child_count++] = m2_pid; 
    
    if(m2_pid == 0){  /* Only m2 can enter here, m1 cannot */ 

        int j = 2; /* In conformity with process name */
        for(j = 2; j < 5; j++){
            pid_t pj_pid = fork();
            if(pj_pid == 0){  /* m2 cannot enter here */ 
                switch(j){
                    case 2:
                        printf("p2 pid = %d\n",getpid());            
                        execlp("./child_process/p2","./p2",NULL);
                    case 3:
                        printf("p3 pid = %d\n",getpid());
                        execlp("./child_process/p3","./p3",NULL);
                    case 4:
                        printf("p4 pid = %d\n",getpid());                    
                        execlp("./child_process/p4","./p4",NULL);
                }
            }
            else {
                wait_pid[child_count++] = pj_pid; 
            }
        }

        /* m2 wait for p2 p3 p4 */
        int status;    
        int i = 0; 
        for(i = 0; i < child_count; i++){   // child_count = 3 (p2 p3 p4)
            waitpid(wait_pid[i], &status, 0);
            printf(ANSI_COLOR_GREEN
            "Parent (%d) wait for Child (%d) successfully. "
            "Child's return value is: %d\n"ANSI_COLOR_RESET, 
            getpid(),wait_pid[i], WEXITSTATUS(status));
        }
    }
    else{   /* Only m1 can enter here, m2 cannot  */ 
        pid_t p1_pid = fork();
        if(p1_pid == 0){  /* m1 cannot enter here */ 
            printf("p1 pid = %d\n",getpid());
            execlp("./child_process/p1","p1","C programming is interesting",NULL);
        }
        else{   /* m1 enter here */
            wait_pid[child_count++] = p1_pid;        
            int status;    
            int i = 0;
            for(i = 0 ; i < child_count; i++){  // child_count = 2 (m2 p1)
                /* m1 wait for p1 and m2 */
                waitpid(wait_pid[i], &status, 0);
                printf(ANSI_COLOR_GREEN
                        "Parent (%d) wait for Child (%d) successfully. "
                        "Child's return value is: %d\n"ANSI_COLOR_YELLOW, 
                        getpid(),wait_pid[i], WEXITSTATUS(status));
            }
            printf(ANSI_COLOR_YELLOW"All process finish\n"ANSI_COLOR_YELLOW);
        }
    }

    return 0;

}

/**
 * 
 * 註[1]：
 *   execlp 參數用法如下：
 *     execlp(執行檔的路徑, 想幫該執行檔取的 process name,其他欲傳進該執行檔的參數...)
 * 
 * 註[2]：
 *   child_count 這個變數只是來自 parent 的 child_count 的 copy 。
 *   (亦即在 parent process fork 出 child process 的當下，
 *    若 parent 的 child_count 為 100, 則 child_count 值亦為 100，
 *    但 child_count 在 parent process 與 child process 的記憶體位址是不同的，
 *    也就是說 parent 與 child 不會修改到同一份 child_count。)
 * 
*/
