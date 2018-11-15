#include<stdio.h>

int ackerman(int m, int n);

int main(){
	int m = 2, n = 2;
	printf("ackerman of (%d,%d) = %d\n",m,n,ackerman(m,n));
}

int ackerman(int m, int n){
	if(m == 0)
		return n+1;
	else if(n == 0)
		return ackerman(m-1,1);
	else
		return ackerman(m-1,ackerman(m,n-1));
}

