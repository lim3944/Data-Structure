#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef struct studnet{
	char name[30];
	int literature;
	int math;
	int science;
} student;

int main(int argc, char** argv){
	int i,j;
	FILE *ifp,*ofp;
	
	//open file
	ifp=fopen(argv[1],"r");
	ofp=fopen(argv[2],"w+");
	int n=fgetc(ifp)-'0';

	//dynamic allocation
	student *info;
	info=(student*)malloc(sizeof(student)*n);

	//read file
	for(i=0;i<n;i++){
	fscanf(ifp,"%s %d %d %d",info[i].name,&info[i].literature,&info[i].math,&info[i].science);
	}

	//write on file
	fprintf(ofp,"      Name");
	for(i=0;i<n;i++){
		fprintf(ofp,"%30s",info[i].name);
	}
	fprintf(ofp,"\n");
	fprintf(ofp,"Literature");
	for(i=0;i<n;i++){
		fprintf(ofp,"%30d",info[i].literature);
	}
	fprintf(ofp,"\n");
	fprintf(ofp,"      Math");
	for(i=0;i<n;i++){
		fprintf(ofp,"%30d",info[i].math);
	}
	fprintf(ofp,"\n");
	fprintf(ofp,"   Science");
	for(i=0;i<n;i++){
		fprintf(ofp,"%30d",info[i].science);
	}

	//close file
	fclose(ifp);
	fclose(ofp);

	free(info);
	return 0;
}
