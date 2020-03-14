#include <stdio.h>

#include "./include/BinaryTree.h"
#include "./include/showError.h"
#include "./include/PrintTree.h"
#include "./include/userType.h"

typedef void (*Travel)(BTree *bTree);
typedef void (*NonTravel)(Node **root, MY_STACK *rootStack);

static int Pow(int num, int N);
static int GetTreeHight(const BTree *root);
static void PrintTree(const BTree *root, int h);
static void PrintNode(Item item, int h);
static void TravelFirstRoot(BTree *root);
static void TravelMiddleRoot(BTree *root);
static void TravelLastRoot(BTree *root);
static void NonRecursTravel(BTree *bTree, NonTravel travelRoot);
static void FirstRoot(Node **root, MY_STACK *rootStack);
static void MidRoot(Node **root, MY_STACK *rootStack);
static void LastRoot(Node **root, MY_STACK *rootStack);

const Travel RECURSTRAVEL[] = {
	TravelFirstRoot,
	TravelMiddleRoot,
	TravelLastRoot,
};

const NonTravel NONRECURSTRAVEL[] = {
	FirstRoot,
	MidRoot,
	LastRoot,	
};

static void PrintNode(Item item, int h) {
	int i = 0;

	for (i = 0; i < h; i++) {
		printf("   ");
	}
	printf("%c\n", item);
}

void PrintBinaryTree(const BTree *bTree) {
	PrintTree(bTree, 0);		
}

static void PrintTree(const BTree *root, int h) {
	if (NULL == root) {
		return;
	}
	
	PrintTree(root->leftChild, h + 1);
	PrintNode(root->item, h);
	PrintTree(root->rightChild, h + 1);
}

static void TravelFirstRoot(BTree *root) {
	if (root == NULL) {
		return;
	}
	PrintItem(&root->item);
	TravelFirstRoot(root->leftChild);
	TravelFirstRoot(root->rightChild);
} 

static void TravelMiddleRoot(BTree *root) {
	if (root == NULL) {
		return;
	}
	
	TravelMiddleRoot(root->leftChild);
	PrintItem(&root->item);
	TravelMiddleRoot(root->rightChild);
}

static void TravelLastRoot(BTree *root) {
	if (root == NULL) {
		return;
	}

	TravelLastRoot(root->leftChild);
	TravelLastRoot(root->rightChild);
	PrintItem(&root->item);
}

static int GetTreeHight(const BTree *root) {
	if (root == NULL) {
		return 0;
	}
	return 1 + Max(GetTreeHight(root->leftChild),
						 GetTreeHight(root->rightChild));
}

void TravelTree(BTree *bTree, int TRAVEL) {
	if (NULL == bTree || TRAVEL < FIRSTROOT 
			|| TRAVEL > NONRECURSIVE_LASTROOT) {
		return;
	}

	TRAVEL < LASTROOT ? RECURSTRAVEL[TRAVEL](bTree) : NonRecursTravel(bTree, NONRECURSTRAVEL[TRAVEL - NONRECURSIVE_FIRSTROOT]);
}

static int Pow(int num, int N) {
	int accumulate = 1;

	while (N-- > 0 && num != 0) {
		accumulate *= num;
	} 

	return num == 0 ? 0 : accumulate;
}

static void NonRecursTravel(BTree *bTree, NonTravel travelRoot) {
	MY_STACK *rootStack = NULL;
	Node *root = bTree;

	initStack(&rootStack, Pow(2, GetTreeHight(bTree)));

	while (NULL != root || FALSE == isStackEmpty(rootStack) ) {
		travelRoot(&root, rootStack);	
	}
	destoryStack(&rootStack);
}

static void FirstRoot(Node **root, MY_STACK *rootStack) {
	if (NULL != *root) {
			PrintItem(&(*root)->item);
			push(rootStack, *root); 
			*root = (*root)->leftChild;
	}
	else {
		*root = (Node *)pop(rootStack);
		*root = (*root)->rightChild; 
	}
}

static void MidRoot(Node **root, MY_STACK *rootStack) {
	if (NULL != *root) {
		push(rootStack, *root);
		*root = (*root)->leftChild;
	}
	else {
		*root = (Node *)pop(rootStack);
		PrintItem(&(*root)->item);
		*root = (*root)->rightChild; 
	}
}

static void LastRoot(Node **root, MY_STACK *rootStack) {
	static Node* rightChild = NULL;
	
	if (NULL != *root) {
		push(rootStack, *root);
		*root = (*root)->leftChild;
	}
	else {
		*root = (Node *)readTop(rootStack);
		if (NULL == (*root)->rightChild
						 || rightChild == (*root)->rightChild) {
			*root = (Node *)pop(rootStack);
			PrintItem(&(*root)->item);
			rightChild = *root;
			*root = NULL; 
		}
		else {
			*root = (*root)->rightChild;
		}
	} 
}

