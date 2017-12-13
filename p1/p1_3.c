#include<stdio.h>
#include<stdlib.h>

int main(int argc,char** argv){
	int n;
	n=atoi(argv[1]);
	char **name;
	printf("enter %d names:\n",n);
	name=(char**)malloc(sizeof(char*)*n);
	for(int i=0;i<n;i++){
		name[i]=(char*)malloc(sizeof(char)*31);
		scanf("%s",name[i]);
	}
	printf("the names you entered:\n");
	for(int i=0;i<n;i++){
		printf("%s\n",name[i]);
	}
	free(name);
	return 0;
}
