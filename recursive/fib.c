#include<stdio.h>

int fib(int n);

int main(){
	int n = 10;
	printf("fib(%d) = %d\n",n,fib(n));
}

int fib(int n){
	if(n == 0)
		return 0;
	else if(n == 1)	
		return 1;
	return fib(n - 1) + fib(n - 2);
}
