#include<stdio.h>
#include<stdlib.h>

//data type declare
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
struct AVLNode{
	int Element;
	AVLTree Left;
	AVLTree Right;
	int height;
};

//function prototype declare
Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);
AVLTree Insert(int X, AVLTree T);
void printInorder(AVLTree T);
int max(int a,int b);
void DeleteTree(AVLTree T);
int Height(Position T);

int main(int argc,char** argv){
	FILE *ifp;
	ifp=fopen(argv[1],"r");
	int temp=0;
	AVLTree T=NULL;
	while(!feof(ifp)){
		if(feof(ifp)!=0)
			break;
		fscanf(ifp,"%d",&temp);
		T=Insert(temp,T);
		printInorder(T);
		printf("\n");
	}
	fclose(ifp);
	DeleteTree(T);
	return 0;
}

//Return the bigger value between a and b
int max(int a,int b){
	if(a>b) return a;
	else return b;
}

//Return the height or the node
int Height(Position T){
	if(T==NULL)
		return -1;
	else 
		return T->height;
}

//Operate the single rotation with left node
Position SingleRotateWithLeft(Position node){
	Position temp=NULL;

	temp=node->Left;
	node->Left=temp->Right;
	temp->Right=node;

	node->height=max(Height(node->Right),Height(node->Left))+1;
	temp->height=max(Height(temp->Left),node->height)+1;
	return temp;
}

//Operate the sigle rotation with right node
Position SingleRotateWithRight(Position node){
	Position temp=NULL;

	temp=node->Right;
	node->Right=temp->Left;
	temp->Left=node;

	node->height=max(Height(node->Right),Height(node->Left))+1;
	temp->height=max(Height(temp->Right),node->height)+1;
	return temp;
}

//Operate the double rotation with left node
Position DoubleRotateWithLeft(Position node){
	node->Left=SingleRotateWithRight(node->Left);
	return SingleRotateWithLeft(node);
}

//Operate the double rotation with right node
Position DoubleRotateWithRight(Position node){
	node->Right=SingleRotateWithLeft(node->Right);
	return SingleRotateWithRight(node);
}

//Insert the value to the AVL Tree
AVLTree Insert(int X,AVLTree T){
	if(T==NULL){
		T=(struct AVLNode*)malloc(sizeof(struct AVLNode));	
		T->Element=X;
		T->height=0;
		T->Right=T->Left=NULL;
	}
	else if(X<T->Element){
		T->Left=Insert(X,T->Left);
		if(Height(T->Left)-Height(T->Right)==2){
			if(X<T->Left->Element)
				T=SingleRotateWithLeft(T);
			else
				T=DoubleRotateWithLeft(T);
		}
	}
	else if(X>=T->Element){
		T->Right=Insert(X,T->Right);
		if(Height(T->Right)-Height(T->Left)==2){
			if(X>T->Right->Element)
				T=SingleRotateWithRight(T);
			else
				T=DoubleRotateWithRight(T);
		}
	}
	T->height=max(Height(T->Left),Height(T->Right))+1;
	return T;
}

//Operate the inorder traversal and print
void printInorder(AVLTree T){
	if(T!=NULL){
		printInorder(T->Left);
		printf("%d ",T->Element);
		printInorder(T->Right);
	}
}

//Delete the AVL Tree
void DeleteTree(AVLTree T){
	if(T!=NULL){
		DeleteTree(T->Left);
		DeleteTree(T->Right);
		free(T);
	}
}
