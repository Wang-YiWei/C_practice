#include<stdio.h>

void perm(char *input, int i, int n);
void swap(char *input, int i, int j);

int main(){

	int i, n = 4;
	char input[n];
	
	for(i = 0; i < n; ++i)
		input[i] = 'A' + i;
	
	perm(input,0,n);
}

void perm(char *input, int i, int n){
	
	if(i == n){
		int j;
		for(j = 0; j < n; ++j)
			printf("%c",input[j]);

		printf("\n");
	}else{
		int j;
		for(j = i; j < n; ++j){
			swap(input,i,j);  // input[j] becomes current head
			perm(input,i+1,n);
			swap(input,i,j);  // revert content of input
		}
	}
}

void swap(char *input, int i, int j){
	char temp = input[i];
	input[i] = input[j];
	input[j] = temp;
}
