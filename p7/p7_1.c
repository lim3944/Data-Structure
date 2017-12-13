#include<stdio.h>
#include<stdlib.h>

//data type declare
typedef struct Tree* Root;
typedef struct Tree* Node;

struct Tree{
	int value;
	Node left;
	Node right;
};

//function prototype declare
Root insertNode(Root T, int key);
Root deleteNode(Root T, int key);
Node findNode(Root T, int key);
Node findMin(Root T);
Node findMax(Root T);
void printInorder(Root T);
void printPreorder(Root T);
void printPostorder(Root T);
void deleteTree(Root T);

int main(int argc,char** argv){
	FILE *ifp;
	ifp=fopen(argv[1],"r");
	char order[3]={0,0,0};
	int key=0;
	Node temp=NULL;
	Root T;
	while(order[0]!='q'){
		order[0]='q';
		fscanf(ifp,"%s",order);
		switch(order[0]){
			case 'i':
				fscanf(ifp,"%d",&key);
				T=insertNode(T,key);
				break;
			case 'd':
				fscanf(ifp,"%d",&key);
				T=deleteNode(T,key);
				break;
			case 'f':
				fscanf(ifp,"%d",&key);
				temp=findNode(T,key);	
				if(temp==NULL)
					printf("%d is not in the tree\n",key);
				else
					printf("%d is in the tree\n",key);
				break;
			case 'p':
				if(order[1]=='i')
					printInorder(T);
				else if(order[1]=='r')
					printPreorder(T);
				else
					printPostorder(T);
				printf("\n");
				break;
			}
		}
	deleteTree(T);
	return 0;
}

//insert the input vlaue to the proper position
Root insertNode(Root T,int key){
	if(T==NULL){
		T=malloc(sizeof(struct Tree));
		T->value=key;
		T->left=T->right=NULL;
		return T;
	}
	else if(key<T->value){
	 	T->left=insertNode(T->left,key);
	}
	else if(key>T->value){
		T->right=insertNode(T->right,key);
	}
	else
		printf("%d is already exist!\n",key);
	return T;
}

//delete the node that have the input value
Root deleteNode(Root T,int key){
	Node temp;
	if(key<T->value)
		T->left=deleteNode(T->left,key);
	else if (key>T->value)
		T->right=deleteNode(T->right,key);
	else if (T->left&&T->right){
		temp=findMin(T->right);
		T->value=temp->value;
		T->right=deleteNode(T->right,T->value);
	}
	else{
		temp=T;
		if(T->left==NULL)
			T=T->right;
		else if(T->right==NULL)
			T=T->left;
		free(temp);
	}
	return T;
}

//find the node with the input value
Node findNode(Root T,int key){
	if(T==NULL){
		return NULL;
	}
	if (key<T->value)
		return findNode(T->left,key);
	if(key>T->value)
		return findNode(T->right,key);
	else
		return T;
}

//find the minimum value
Node findMin(Root T){
	if(T==NULL)
		return NULL;
	else if(T->left==NULL)
		return T;
	else
		return findMin(T->left);
}

//find the maximum value
Node findMax(Root T){
	if(T==NULL)
		return NULL;
	else if(T->right==NULL)
		return T;
	else 
		return findMax(T->right);
}

//print the inorder traversal
void printInorder(Root T){
	if(T!=NULL){
		printInorder(T->left);
		printf("%d ",T->value);
		printInorder(T->right);
	}
}

//print the preorder traversal
void printPreorder(Root T){
	if(T!=NULL){
		printf("%d ",T->value);
		printPreorder(T->left);
		printPreorder(T->right);
	}
}

//print the postorder traversal
void printPostorder(Root T){
	if(T!=NULL){
		printPostorder(T->left);
		printPostorder(T->right);
		printf("%d ",T->value);
	}
}

//delete the tree
void deleteTree(Root T){
	if(T!=NULL){
		deleteTree(T->left);
		deleteTree(T->right);
		free(T);
	}
}
