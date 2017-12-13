#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)
//data type declare

typedef struct HashTable *Hash;

struct HashTable{
	int TableSize;
	int * Table;
};

//function prototype declare
void Insert(int key, Hash H);
int  Find(Hash H, int value);

int main(int argc, char** argv){
	FILE *ifp;
	int size;

	int data;
	int offset;

	char line1[200], line2[200];
	char *p = line1;

	ifp = fopen(argv[1], "r");
	fscanf(ifp, "%d", &size);
	fscanf(ifp, " %[^\n]", line1);
	fscanf(ifp, " %[^\n]", line2);

	Hash H;
	H = (struct HashTable*)malloc(sizeof(struct HashTable));
	H->TableSize = size;
	H->Table = (int *)malloc(sizeof(int)*size);

	int i = 0;
	for (int i = 0; i < size; i++){
		H->Table[i] = 0;
	}

	printf("Insertion\n");
	while (sscanf(p, "%d%n", &data, &offset) != EOF){
		Insert(data, H);
		p += offset;
	}

	p = line2;

	printf("Find\n");
	while (sscanf(p, "%d%n", &data, &offset) != EOF){
		if (Find(H, data))
			printf("%d Exist!\n",data);
		else
			printf("%d Do not exist!\n",data);
		p += offset;
	}

	free(H);
	return 0;

}

//Insert with the Hash function(modulation + f(i))
void Insert(int key, Hash H){
	int position = key % (H->TableSize);
	
	if (Find(H, key)){
		printf("%d Duplicated\n",key);
		return;
	}
	
	if (H->Table[position]!=0)
		printf("%d Collision!\n",key);
	else
		printf("%d Insert success!\n",key);
	while (H->Table[position]){
		position=(position+1)%(H->TableSize);
	}
	H->Table[position] = key;
}

//Return 1 if the value is exist,else 0
int  Find(Hash H, int value){
	int i;
	for (int i = 0; i < H->TableSize; i++)
		if (H->Table[i] == value)
			return 1;
	return 0;
}










