#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)
//data type declare
typedef struct ListNode *Position;
typedef Position List;
typedef struct HashTable *Hash;

struct ListNode{
	int Element;
	Position Next;
};

struct HashTable{
	int TableSize;
	List* TheLists;
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
	H->TheLists = (struct ListNode**)malloc(sizeof(struct ListNode*)*size);

	int i = 0;
	for (int i = 0; i < H->TableSize; i++){
		H->TheLists[i] = (Position)malloc(sizeof(struct ListNode));
		H->TheLists[i]->Next = NULL;
	}

	printf("Insertion\n");
	while (sscanf(p, "%d%n", &data, &offset) != EOF){
		Insert(data, H);
		p += offset;
	}

	p = line2;

	printf("Find\n");
	while (sscanf(p, "%d%n", &data, &offset) != EOF){
		if (Find(H, data)==0)
			printf("%d do not exist!\n",data);
		else
			printf("%d exist!\n",data);
		p += offset;
	}

	free(H);
	return 0;

}

//Insert the value according to the hash function(modulation)
void Insert(int key, Hash H){
	int position = key % (H->TableSize);
	Position New = NULL;
	List temp = NULL;
	temp = H->TheLists[position];
	
	if (Find(H, key)){
		printf("%d Duplicated\n",key);
		return;
	}
	
	if (temp->Next != NULL)
		printf("%d Collision!\n",key);
	else
		printf("%d Insert success!\n",key);

	New = (Position)malloc(sizeof(struct ListNode));
	New->Next = (Position)malloc(sizeof(struct ListNode));

	New->Element = key;
	New->Next = temp->Next;
	temp->Next = New;
}

//If the value exist, ruturn 1,else 0
int  Find(Hash H, int value){
	int position = value%(H->TableSize);
	Position P;
	List temp = H->TheLists[position];
	P = temp->Next;
	while (P != NULL&&P->Element!=value){
		P = P->Next;
	}
	if (P == NULL)
		return 0;
	return 1;
}










