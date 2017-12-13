#include<stdio.h>
#include<stdlib.h>

#define EmptyTOS -1

//data type declare
typedef struct HeapStruct* Heap;
struct HeapStruct{
	int Capacity;
	int Size;
	int *Elements;
};

//function prototype declare
Heap CreateHeap(int size);
void Insert(Heap H,int value);
int DeleteMax(Heap H);
void PrintHeap(Heap H);
void DeleteHeap(Heap H);

int main(int argc, char** argv){
	FILE *ifp;
	ifp=fopen(argv[1],"r");
	char order[2]={0,0};
	int temp=0;
	int max=0;
	Heap H=NULL;
	while(order[0]!='q'){
		order[0]='q';
		fscanf(ifp,"%s",order);
		switch(order[0]){
			case 'n':
				fscanf(ifp,"%d",&temp);
				H=CreateHeap(temp);
				break;
			case 'i':
				fscanf(ifp,"%d",&temp);
				Insert(H,temp);
				break;
			case 'd':
				max=DeleteMax(H);
				if(max==EmptyTOS)
					printf("Heap is empty!\n");
				else
					printf("%d is deleted\n",max);
				break;
			case 'p':
				PrintHeap(H);
				break;		
			}
	}
	DeleteHeap(H);
	return 0;
}

//Create a empty heap
Heap CreateHeap(int size){
	Heap H;
	H=malloc(sizeof(struct HeapStruct));
	H->Capacity=size;
	H->Size=0;
	H->Elements=(int*)malloc(sizeof(int)*(size+1));
	return H;
}

//Insert the value to the heap
void Insert(Heap H,int value){
	int i;
	if(H->Size==H->Capacity){
		printf("Insertion fail %d! Heap is Full!\n",value);
		return ;
	}
	for(i=++H->Size; H->Elements[i/2]<value;i/=2){
		if (i/2 == 0) {
			break;
		}
		H->Elements[i]=H->Elements[i/2];
	}
	H->Elements[i]=value;
}

//Return and delete the max value(top of the heap) from the heap
int DeleteMax(Heap H){
	if(H->Size==0)
		return EmptyTOS;
	int i,C;
	int Max,Last;
	Max=H->Elements[1];
	Last=H->Elements[H->Size--];

	for(i=1;i*2<=H->Size;i=C){
		C=i*2;
		if(C!=H->Size&&H->Elements[C+1]>H->Elements[C])
			C++;
		if(Last<H->Elements[C])
			H->Elements[i]=H->Elements[C];
		else
			break;
	}
	H->Elements[i]=Last;
	return Max;
}

//Print all the member of heap by the level
void PrintHeap(Heap H){
	int i,j,level=1;
	if(H->Size==0)
		printf("Heap is empty!\n");
	else{	
		for(i=1;i<=H->Size;i){
			printf("level : %d  ",level++);
			for(j=i;j<i*2;j++){
				if(j<=H->Size)
					printf("%d ",H->Elements[j]);
			}
			printf("\n");
			i=j;
			}
	}
}

//Delete the heap
void DeleteHeap(Heap H){
	free(H->Elements);
	free(H);
}
