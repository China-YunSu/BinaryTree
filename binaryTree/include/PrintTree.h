#ifndef _PrintTree_H_
#define _PrintTree_H_

#include "BinaryTree.h"

#define MAXCAPACITY		30

#define Max(x,y) ((x) > (y) ? (x) : (y))

#define FIRSTROOT					0
#define MIDDLEROOT 					1
#define	LASTROOT					2
#define NONRECURSIVE_FIRSTROOT		3
#define NONRECURSIVE_MIDDLEROOT		4
#define NONRECURSIVE_LASTROOT		5


void PrintBinaryTree(const BTree *bTree);
void TravelTree(BTree *bTree, int TRAVEL);

#endif 