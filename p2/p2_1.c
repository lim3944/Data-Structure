#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void pm(char input[],int i,int n,FILE *ofp);

int main(int argc,char** argv){
	FILE *ifp,*ofp;
	char input[105];
	
	//open file
	ifp=fopen(argv[1],"r");
	ofp=fopen(argv[2],"w+");

	//read file
	fgets(input,105,ifp);

	//permutation function
	pm(input,1,strlen(input)-1,ofp);

	//close file
	fclose(ifp);
	fclose(ofp);
	return 0;
}

//permutation fuction
void pm(char input[],int i,int n,FILE *ofp){
	int j;
	char temp;
	if(i==n){
		fputs(input,ofp);
	}
	else{
		for(j=i;j<n;j=j+2){
			temp=input[i];
			input[i]=input[j];
			input[j]=temp;
			pm(input,i+2,n,ofp);
			temp=input[i];
			input[i]=input[j];
			input[j]=temp;
		}
	}
}
