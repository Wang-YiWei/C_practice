#include<stdio.h>

int gcd(int a, int b);

int main(){
	int a = 11*123, b = 11*124;
	printf("gcd of (%d,%d) = %d\n",a,b,gcd(a,b));
}

int gcd(int a, int b){
	if(a%b == 0)
		return b;
	else
		return gcd(b,a%b);
}


