#include<stdio.h>

void hanoi(int n, char source, char temp, char target);

int main(){
	int num = 10;
	hanoi(num,'A','B','C');
}

void hanoi(int n, char source, char temp, char target){
	if(n == 1)
		printf("move disk from %c to %c\n",source,target);
	else{
		hanoi(n-1,source,target,temp);
		printf("move disk from %c to %c\n",source,target);
		hanoi(n-1,temp,source,target);
	}
}
