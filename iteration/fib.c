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
	else{	
		int n1 = 0, n2 = 1, n3, i;

		for(i = 2; i <= n ; ++i){
			n3 = n1 + n2;
			
			// shift right
			n1 = n2;
			n2 = n3;
		}

		return n3;
	}
}

