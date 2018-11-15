#include<stdio.h>

int fact(int n);

int main(){
	int n = 10;
	printf("%d! = %d\n",n,fact(n));
}

int fact(int n){
	if(n == 0)
		return 1;
	else
		return n * fact(n-1);
}
