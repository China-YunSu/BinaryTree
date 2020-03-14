#include <stdio.h>
#include <ctype.h>

#include "./include/BinaryTree.h"
#include "./include/boolean.h"
#include "./include/myStack.h"
#include "./include/showError.h"

extern char *errorMess;

static Node* DealExpressionStatusBegin(BTree_Arg *args, char ch);
static void DealExpressionStatusComma(BTree_Arg *args, char ch);
static void DealExpressionStatusAlpha(BTree_Arg *args, char ch);
static void DealExpressionStatusRights(BTree_Arg *args, char ch);
static void DealExpressionStatusLefts(BTree_Arg *args, char ch);
static boolean ProgressStatusLefts(BTree_Arg *args);
static boolean ProgressStatusRights(BTree_Arg *args);
static void ProgressStatusComma(BTree_Arg *args);
static void ProgressStatusAlpha(BTree_Arg *args, char ch);

void DestoryBTree(BTree *root) {
	if (root == NULL) {
		return;
	}

	DestoryBTree(root->leftChild);
	DestoryBTree(root->rightChild);
	free(root);
}

Node *CreatOneNode(char ch) {
	Node *res = (Node *) calloc(sizeof(Node),1);
	
	res->item = ch;
	res->leftChild = NULL;
	res->rightChild = NULL;

	return res;
}

static void ProgressStatusAlpha(BTree_Arg *args, char ch) {
	if (args->whichChild == LEFTCHILD) {
		args->root->leftChild = CreatOneNode(ch);
		args->root = args->root->leftChild;
	}
	else if (args->whichChild == RIGHTCHILD) {
		args->root->rightChild = CreatOneNode(ch);
		args->root = args->root->rightChild;
	}
	
	args->index++;
 	args->status = BTREE_EXPRESS_STAUS_ALPHA;
}

static void ProgressStatusComma(BTree_Arg *args) {
	args->root = (Node *)readTop(args->rootStack);
	args->whichChild = RIGHTCHILD;

	args->index++;
 	args->status = BTREE_EXPRESS_STAUS_COMMA;
}

static boolean ProgressStatusRights(BTree_Arg *args) {
	Node *root_tmp = NULL;

	if (--(args->blankMatch) < 0) {
		return FALSE;
	}

	root_tmp = (Node *)pop(args->rootStack);
	args->root = root_tmp;

	args->index++;
 	args->status = BTREE_EXPRESS_STAUS_RIGHTS;
	return TRUE;
}

static boolean ProgressStatusLefts(BTree_Arg *args) {
	++(args->blankMatch);

	if (TRUE == push(args->rootStack, args->root)) {
		args->whichChild = LEFTCHILD;

		args->index++;
 		args->status = BTREE_EXPRESS_STAUS_LEFTS;

 		return TRUE;
	}

	return FALSE;

}

static void DealExpressionStatusLefts(BTree_Arg *args, char ch) {
	if ('(' == ch) {
 		//TODO����������
		if(FALSE == ProgressStatusLefts(args)) {
			args->ok = FALSE;
			errorMess = "��ĸ��ջʧ�ܣ�";
		}
 	}
 	else if (')' == ch){
 		//����������
		if (FALSE ==ProgressStatusRights(args)) {
			args->ok = FALSE;
			errorMess = "�����Ų�ƥ��";
		}
 	}
 	else if (',' == ch) {
 		//����������
 		ProgressStatusComma(args);
 	}
 	else if (isalpha(ch)) {
 		//������ĸ
 		ProgressStatusAlpha(args,ch);
 	}
 	else {
 		args->status = BTREE_EXPRESS_STAUS_END;
 	}
}

static void DealExpressionStatusRights(BTree_Arg *args, char ch) {
	if ('(' == ch) {
 		//����������
		if(FALSE == ProgressStatusLefts(args)) {
			args->ok = FALSE;
			errorMess = "��ĸ��ջʧ�ܣ�";
		}
 	}
 	else if (')' == ch){
 		//����������
		if (FALSE ==ProgressStatusRights(args)) {
			args->ok = FALSE;
			errorMess = "�����Ų�ƥ��";
		}
 	}
 	else if (',' == ch) {
 		//����������
 		ProgressStatusComma(args);
 	}
 	else if (isalpha(ch)) {
 		//������ĸ
 		ProgressStatusAlpha(args,ch);
 		
 	}
 	else {
 		args->status = BTREE_EXPRESS_STAUS_END;
 	}
}


static void DealExpressionStatusAlpha(BTree_Arg *args, char ch) {
	if ('(' == ch) {
 		//����������
		if(FALSE == ProgressStatusLefts(args)) {
			args->ok = FALSE;
			errorMess = "��ĸ��ջʧ�ܣ�";
		}
 	}
 	else if (')' == ch){
 		//����������
		if (FALSE ==ProgressStatusRights(args)) {
			args->ok = FALSE;
			errorMess = "�����Ų�ƥ��";
		}
 	}
 	else if (',' == ch) {
 		//����������
 		ProgressStatusComma(args);
 	}
 	else {
 		args->status = BTREE_EXPRESS_STAUS_END;
 	}
}

static void DealExpressionStatusComma(BTree_Arg *args, char ch){
 	if ('(' == ch) {
 		//����������
		if(FALSE == ProgressStatusLefts(args)) {
			args->ok = FALSE;
			errorMess = "��ĸ��ջʧ�ܣ�";
		}
 	}
 	else if (')' == ch){
 		//����������
		if (FALSE ==ProgressStatusRights(args)) {
			args->ok = FALSE;
			errorMess = "�����Ų�ƥ��";
		}
 	}
 	else if (isalpha(ch)) {
 		//������ĸ
 		ProgressStatusAlpha(args,ch);
 	}
 	else {
 		args->status = BTREE_EXPRESS_STAUS_END;
 	}
 }

 static Node *DealExpressionStatusBegin(BTree_Arg *args, char ch) {
 	
 	if (isalpha(ch)) {
 		//������ĸ
 		args->root = CreatOneNode(ch);

 		args->index++;
 		args->status = BTREE_EXPRESS_STAUS_ALPHA;
 		return args->root;
 	}
 	else {
 		args->status = BTREE_EXPRESS_STAUS_END;
 	}

 	return NULL;
 }

int SkipBlank(char *str) {
	int i;

	for (i = 0; str[i] == ' '; i++)
		;
	
	return i;
}

boolean CreatBinaryTree(BTree **btree_root,char *str) {
	BTree_Arg args = {
		0,								//int index;
		FALSE,							//boolean finshed;
		TRUE,							//boolean ok;
		BTREE_EXPRESS_STAUS_BEGIN,		//short status;
		*btree_root, 					//Node *root;
		NULL,							//MY_STACK *rootStack
		0,								//int blankMatch;
		LEFTCHILD						//short whichChild;
	};

	initStack(&args.rootStack, strlen(str) / 2 + 1);
	while (args.ok && !args.finshed) {
		// ���˿ո�
		args.index += SkipBlank(str + args.index);
		
		if (BTREE_EXPRESS_STAUS_BEGIN == args.status) {
			//����ʼ״̬
			*btree_root = DealExpressionStatusBegin(&args, str[args.index]);
		} 
		else if (BTREE_EXPRESS_STAUS_COMMA == args.status){
			//������״̬
			DealExpressionStatusComma(&args, str[args.index]);
		} 
		else if (BTREE_EXPRESS_STAUS_ALPHA == args.status){
			//������ĸ״̬
			DealExpressionStatusAlpha(&args, str[args.index]);
		} 
		else if (BTREE_EXPRESS_STAUS_RIGHTS == args.status){
			//����������״̬
			DealExpressionStatusRights(&args, str[args.index]);
		} 
		else if (BTREE_EXPRESS_STAUS_LEFTS == args.status){
			//����������״̬
			DealExpressionStatusLefts(&args, str[args.index]);
		}
		else if (BTREE_EXPRESS_STAUS_END == args.status) {
			//�������״̬
			if (args.blankMatch > 0) {
				errorMess = "�����Ų�ƥ�䣡";
				args.ok = FALSE;
			}
			if (str[args.index] == '\0') {
				args.finshed = TRUE;
			}
			else {
				args.ok = FALSE;
				errorMess = "�����ַ���";
			}
		}
	}

	if (args.ok == FALSE) {
		DestoryBTree(*btree_root);
		*btree_root = NULL;
	}else {
		initTreeHight(*btree_root);
	}

	destoryStack(&args.rootStack);

	return args.ok;
}

int initTreeHight(BTree *root) {
	if (NULL == root) {
		return 0;
	}

	root->hight = 1 + Max(initTreeHight(root->leftChild), initTreeHight(root->rightChild));
	
	return root->hight;
}