#include<stdio.h>
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(int argc, char *argv[]){
    printf(ANSI_COLOR_CYAN"p1's process name = %s\n"ANSI_COLOR_RESET,argv[0]);
    printf(ANSI_COLOR_CYAN"%s\n"ANSI_COLOR_RESET,argv[1]);
    printf(ANSI_COLOR_MAGENTA"Hello , this is p1\n"ANSI_COLOR_RESET);
    return 1;
}