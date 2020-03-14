#include <stdio.h>

#include "./include/showError.h"
#include "./include/BinaryTree.h"
#include "./include/PrintTree.h"

int main(int argc, char const *argv[]) {	
	BTree *btree_root = NULL;
	char str[1024] = {0};

	printf("请输入二叉树表达式：例如:A(B,C)或A(B(C,D),E(F,G))\n");
	gets(str);

	if (TRUE == CreatBinaryTree(&btree_root, str)) {
		printf("先根序:");
		TravelTree(btree_root, NONRECURSIVE_FIRSTROOT);
		printf("\n");
		printf("中根序:");
		TravelTree(btree_root, NONRECURSIVE_MIDDLEROOT);
		printf("\n");
		printf("后根序:");
		TravelTree(btree_root, NONRECURSIVE_LASTROOT);
		printf("\n");
		PrintBinaryTree(btree_root);
	}
	showError();

	DestoryBTree(btree_root);
	return 0;
}
