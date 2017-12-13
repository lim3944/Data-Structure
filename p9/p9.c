#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)
//data type declare
typedef struct RBTreeNode *Position;
typedef struct RBTreeNode *RBTree;
struct RBTreeNode{
	int Element;
	RBTree Left;
	RBTree Right;
	RBTree Parent;
	int Color;//red->1, black->0
};

//function prototype
Position Insert(int X, RBTree T, Position P);
void PrintInorder(RBTree T);
void Delete(RBTree T);
Position Uncle(Position P);
Position Grand(Position P);
int ColorReturn(Position P);
void Insert1(RBTree T);
void Insert2(RBTree T);
void Insert3(RBTree T);
void Insert4(RBTree T);
void Insert5(RBTree T);
void Rotate_Left(RBTree T);
void Rotate_Right(RBTree T);
RBTree Insert(int X, RBTree T, Position P);

//global variable declare
Position Last_Input=NULL;

int main(int argc, char** argv){
	FILE *ifp;
	ifp = fopen(argv[1], "r");
	int temp = 0;
	RBTree T = NULL;
	while (!feof(ifp)){
		if (feof(ifp))
			break;
		fscanf(ifp,"%d", &temp);
		T = Insert(temp, T, NULL);
		Insert1(Last_Input);
		while ((T->Parent != NULL)&&(T!=NULL))
			T = T->Parent;
		PrintInorder(T);
		printf("\n");
	}
	Delete(T);
	return 0;
}

//Insert the value to the RBTree
RBTree Insert(int X, RBTree T, Position P){
	if (T == NULL){
		T = (struct RBTreeNode*)malloc(sizeof(struct RBTreeNode));
		T->Color = 1;
		T->Element = X;
		T->Left = T->Right = NULL;
		T->Parent = P;
		if (P == NULL)
			T->Color = 0;
		Last_Input=T;
	}
	else if (X > T->Element){
		T->Right = Insert(X, T->Right, T);
	}
	else{
		T->Left = Insert(X, T->Left, T);
	}
	return T;
}

//Operate the inorder traversal and print
void PrintInorder(RBTree T){
	if (T != NULL){
		PrintInorder(T->Left);
		printf("%d", T->Element);
		if (T->Color == 1)
			printf("(R) ");
		else
			printf("(B) ");
		PrintInorder(T->Right);
	}
}

//Delete the RBTree
void Delete(RBTree T){
	if (T != NULL){
		Delete(T->Left);
		free(T);
		Delete(T->Right);
	}
}

//Return the position of the uncle node
Position Uncle(Position P){
	Position g = Grand(P);
	if (g == NULL)
		return NULL;
	if (P->Parent == g->Left)
		return g->Right;
	else
		return g->Left;
}

//Return the position of the grandparents node
Position Grand(Position P){
	if ((P != NULL) && (P->Parent != NULL))
		return P->Parent->Parent;
	return NULL;
}

//Return the color of the node
int ColorReturn(Position P){
	if (P == NULL)
		return 0;
	return P->Color;
}

//Insert process 1
void Insert1(RBTree T){
	if (T->Parent == NULL)
		T->Color = 0;
	else
		Insert2(T);
}

//Insert process 2
void Insert2(RBTree T){
	if (ColorReturn(T->Parent) == 0)
		return;
	else
		Insert3(T);
}

//Insert procss 3
void Insert3(RBTree T){
	Position U = Uncle(T);
	Position G = Grand(T);
	if (U != NULL&&ColorReturn(U) == 1){
		T->Parent->Color = 0;
		U->Color = 0;
		G->Color = 1;

		Insert1(G);
	}
	else
		Insert4(T);
}

//Insert process 4
void Insert4(RBTree T){
	Position U = Uncle(T);
	Position G = Grand(T);
	if (T == T->Parent->Right&&T->Parent == G->Left){
		Rotate_Left(T->Parent);
		T = T->Left;
	}
	else if (T == T->Parent->Left&&T->Parent == G->Right){
		Rotate_Right(T->Parent);
		T = T->Right;
	}
	Insert5(T);
}

//Insert process 5
void Insert5(RBTree T){
	Position G = Grand(T);
	T->Parent->Color = 0;
	G->Color = 1;

	if (T == T->Parent->Left&&T->Parent == G->Left)
		Rotate_Right(G);
	else
		Rotate_Left(G);
}

//Rotate to the left direction
void Rotate_Left(Position node){
	printf("Rotated\n");
	Position temp = NULL;

	temp = node->Right;
	node->Right = temp->Left;
	if (temp->Left!=NULL)
		temp->Left->Parent = node;
	temp->Parent = node->Parent;
	if (node->Parent!=NULL){
		if (node == node->Parent->Left)
			node->Parent->Left = temp;
		else
			node->Parent->Right = temp;
		temp->Left=node;
		node->Parent=temp;
	}
	temp->Left = node;
	node->Parent = temp;
}

//Rotate to the right direction
void Rotate_Right(Position node){
	printf("Rotated\n");
	Position temp = NULL;

	temp = node->Left;
	node->Left = temp->Right;
	if (temp->Right)
		temp->Right->Parent = node;
	temp->Parent = node->Parent;
	if (node->Parent){
		if (node == node->Parent->Right)
			node->Parent->Right = temp;
		else
			node->Parent->Left = temp;
		temp->Right=node;
		node->Parent=temp;
	}
	temp->Right = node;
	node->Parent = temp;
}
