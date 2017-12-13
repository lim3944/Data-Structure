#include<stdio.h>

int main(){
	printf("enter your name:");
	char name[35];
	scanf("%[ a-zA-Z]", name);
	printf("your name is %s",name);
	return 0;
}
