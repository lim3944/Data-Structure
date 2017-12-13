#include<stdio.h>

void swap(int* a, int* b){
	int temp;
	temp=*b;
	*b=*a;
	*a=temp;
}

int main(){
	int a,b;
	printf("enter 2 integers\n");
	scanf("%d %d",&a,&b);
	printf("you entered\n%d %d\n",a,b);
	printf("after swawpping\n");
	swap(&a,&b);
	printf("%d %d",a,b);
	return 0;
}
