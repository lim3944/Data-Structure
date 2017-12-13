#include<stdio.h>

int add(int x,int y){
	return x+y;
}

int sub(int x,int y){
	return x-y;
}

int mul(int x,int y){
	return x*y;
}

int div(int x,int y){
	return x/y;
}

int main(){
	int(*pf[4])(int,int)={add,sub,mul,div};
	while(1){
		printf("====================\n");
		printf("0. add\n");
		printf("1. sub\n");
		printf("2. mul\n");
		printf("3. div\n");
		printf("4. exit\n");
		int n,a,b;
		printf("==========\n");
		printf("Select Operation :");
		scanf("%d",&n);
		if(n==4){
			return 0;
		}
		printf("Input 2 operand :");
		scanf("%d %d",&a,&b);
		int ans=(*pf[n])(a,b);
		printf("Result = %d\n",ans);
	}
}
		
