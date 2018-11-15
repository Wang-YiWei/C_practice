#include<stdio.h>

int main(){
	int n = 10, i;
	int fib[n+1];
	
	fib[0] = 0;
	fib[1] = 1;
	
	for(i = 2; i<= n ; ++i)
		fib[i] = fib[i-1] + fib[i-2];
}
