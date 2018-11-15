#include<stdio.h>

int binomial(int n, int m);

int main(){
	int n = 6, m = 4;
	printf("C(%d,%d) = %d\n",n,m,binomial(n,m));
}

/*
*
* C(n,m) = C(n-1,m) + C(n-1,m-1)
*
* input: 
*		n,m
* output:
*		binomial coefficient result
*/
int binomial(int n, int m){
	if(n == m || m == 0)
		return 1;
	else
		return binomial(n-1,m) + binomial(n-1,m-1);
}

