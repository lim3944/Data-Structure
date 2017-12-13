#include<stdio.h>
#include<stdlib.h>

typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

struct Node{
	ElementType element;
	Position next;
};


//function prototype
List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void Delete(ElementType X, List L);
Position FindPrevious(ElementType X, List L);
Position Find(ElementType X, List L);
void Insert(ElementType X, List L, Position P);
void DeleteList(List L);
void PrintAll(List L);

//main function
int main(int argc, char** argv){
	FILE *ifp;
	ifp = fopen(argv[1], "r");
	char input[2];
	int x, y;
	List L = NULL;
	Position P = NULL, temp = NULL;
	L = MakeEmpty(L);
	while (1){
		input[0]='q';
		fscanf(ifp, "%s", input);

		//condition of quit
		if (input[0] == 'q'){
			DeleteList(L);
			free(L);
			return 0;
		}
		//insert menu
		else if (input[0] == 'i'){
			fscanf(ifp, "%d %d", &x, &y);
			if (y != -1){
				temp = Find(y, L);
				if (temp == NULL){
					printf("Insertion(%d) Failed : element %d is not in the list\n", x, y);
				}
				else
					Insert(x, L, temp);
			}
			else{
				if (IsEmpty(L) == 1){
					Insert(x, L, L);
				}
				else
					Insert(x, L, L->next);
			}
		}

		//delete menu
		else if (input[0] == 'd'){
			fscanf(ifp, "%d", &x);
			Delete(x, L);
		}
		//find menu
		else if (input[0] == 'f'){
			fscanf(ifp, "%d", &x);
			if (Find(x, L) == NULL){
				printf("Could not find %d in the list\n", x);
			}
			else{
				temp = FindPrevious(x, L);
				if (temp->element == 0)
					printf("Key of the previous node of %d is header\n", x);
				else
					printf("Key of the previous node of %d is %d\n", x, temp->element);
			}
		}
		//print menu
		else if (input[0] == 'p'){
			PrintAll(L);
		}
		else if (input[0] == 'a') {
			DeleteList(L);
			free(L);
			return 0;
		}
	}
}

//create header node
List MakeEmpty(List L){
	L = (List)malloc(sizeof(struct Node));
	L->element = 0;
	L->next = NULL;
	return L;
}

//retrun true if L is empty
int IsEmpty(List L){
	return L->next == NULL;
}


//return true if P is the last porition in list L
int IsLast(Position P, List L){
	return P->next == NULL;
}

//retrun position of X in list L or NULL if not found
Position Find(ElementType X, List L){
	Position P=NULL;
	P = L->next;
	while (P != NULL&&P->element != X){
		P = P->next;
	}
	return P;
}
//insert new data in list L after the node position P
void Insert(ElementType X, List L, Position P){
	Position temp=NULL;
	temp = (Position)malloc(sizeof(struct Node));

	temp->element = X;
	temp->next = P->next;
	P->next = temp;
}

//delete node with element X
void Delete(ElementType X, List L){
	Position P=NULL, temp=NULL;
	P = FindPrevious(X, L);
	if (P == NULL){
		printf("Deletion faied : element %d is not int the list\n", X);
	}
	else if (!IsLast(P, L)){
		temp = P->next;
		P->next = temp->next;
		free(temp);
	}
}

//delete all the list without header
void DeleteList(List L){
	Position P = NULL, temp = NULL;
	P = L->next;
	L->next = NULL;
	while (P != NULL){
		temp = P->next;
		free(P);
		P = temp;
	}
}

//printf all the elements of list L
void PrintAll(List L){
	List temp = NULL;
	temp = L;
	while (L->next != NULL){
		L = L->next;
		printf("key:%d  ", L->element);
	}
}

//return previous position of X
Position FindPrevious(ElementType X, List L){
	Position P=NULL;
	P = L;
	while (P->next != NULL&&P->next->element != X)
		P = P->next;
	if(P->next==NULL)
		return P=NULL;
	else;
		return P;
}




