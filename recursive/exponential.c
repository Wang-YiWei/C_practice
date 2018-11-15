#include<stdio.h>

int exponential(int x, int n);

int main(){
	int x = 2, n = 10;
	printf("%d^%d = %d\n",x,n,exponential(x,n));
}

int exponential(int x, int n){
	if(x >= 1 && n >= 0){
		if(n == 0)
			return 1;
		else
			return x * exponential(x,n-1);
	}
}

