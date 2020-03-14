#ifndef _BinaryTree_H_
#define _BinaryTree_H_

#include "myStack.h"
#include "boolean.h"
#include "userType.h"

#define RIGHTCHILD 	0
#define LEFTCHILD 	1

#define BTREE_EXPRESS_STAUS_BEGIN		0	
#define BTREE_EXPRESS_STAUS_COMMA		1
#define BTREE_EXPRESS_STAUS_ALPHA		2
#define BTREE_EXPRESS_STAUS_RIGHTS		3
#define BTREE_EXPRESS_STAUS_LEFTS		4
#define BTREE_EXPRESS_STAUS_END			5

#define Max(x,y) ((x) > (y) ? (x) : (y))

typedef struct Node {
	Item item;
	struct Node *leftChild;
	struct Node *rightChild;
	int hight;
}Node;

typedef Node BTree;

typedef struct arg {
	int index;
	boolean finshed;
	boolean ok;
	short status;
	Node *root;
	MY_STACK *rootStack;
	int blankMatch;
	short whichChild;
}BTree_Arg; 

boolean CreatBinaryTree(BTree **btree_root,char *str);

#endif

