#include<stdio.h>
#include <unistd.h>

int main(){

    printf("Hello , this is subtraction process, pid = %d\n",getpid());
    int a = ~0;
    while(a--);
    printf("subtraction finish\n");
    
    return 0;
}