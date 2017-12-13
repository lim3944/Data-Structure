#include<stdio.h>
#include<stdlib.h>
#define NUM_HW 6
#define NUM_EXAM 2
#define MAX_ENROLL 5

typedef struct studentT{
	char name[31];
	int hw[NUM_HW];
	int exam[NUM_EXAM];
	double hwAvg;
	double examAvg;
} studentT;

typedef struct courseT{
	studentT students[MAX_ENROLL];
	int numEnrolled;
} courseT;

int main(int argc, char** argv){
	int i,j;
	courseT course;
	FILE *ifp, *ofp;

	//file open
	ifp=fopen(argv[1],"r");
	ofp=fopen(argv[2],"w+");
	
	//reading file
	course.numEnrolled=fgetc(ifp)-'0';
	double HwAvg=0,ExamAvg=0;
	for(i=0;i<course.numEnrolled;i++){
		course.students[i].hwAvg=course.students[i].examAvg=0;

		//read name
		fscanf(ifp,"%s",course.students[i].name);

		//read score
		for(j=0;j<6;j++){
			fscanf(ifp,"%d",&course.students[i].hw[j]);
			course.students[i].hwAvg+=course.students[i].hw[j];
		}
		course.students[i].hwAvg/=6;
		for(j=0;j<2;j++){
			fscanf(ifp,"%d",&course.students[i].exam[j]);
			course.students[i].examAvg+=course.students[i].exam[j];
		}
		course.students[i].examAvg/=2;
		HwAvg+=course.students[i].hwAvg;
		ExamAvg+=course.students[i].examAvg;
	}

	//average score
	HwAvg/=course.numEnrolled;
	ExamAvg/=course.numEnrolled;

	//write on file
	for(i=0;i<course.numEnrolled;i++){
		fprintf(ofp,"%s\n",course.students[i].name);
		fprintf(ofp,"HwAvg %.2lf\n",course.students[i].hwAvg);
		fprintf(ofp,"ExamAvg %.2lf\n",course.students[i].examAvg);
	}
	fprintf(ofp,"\nCourse\n");
	fprintf(ofp,"HwAvg %.2lf\n",HwAvg);
	fprintf(ofp,"ExamAvg %.2lf",ExamAvg);
	
	//close file
	fclose(ifp);
	fclose(ofp);
	return 0;
}
