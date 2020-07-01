//	Created by L.H.Ming on 2020/06/30.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
給定前序或後序以及中序，產生唯一個Binary Tree，依序印出Tree的內容，印出順序，由上而下，由左而右印出。

前序代碼：P
中序代碼：I
後序代碼：O

--------------
輸入說明

第一筆輸入前序、中序或後序代碼。
第二筆輸入上一筆輸入種類尋訪的結果，大寫英文字母。
第三筆輸入前序、中序或後序代碼。
第四筆輸入上一筆輸入種類尋訪的結果，大寫英文字母。

-------------
輸出說明

輸出為一二元樹的內容，由上而下，由左而右。

範例一
-------------
Input:
P
ABCDEFGHI
I
BCAEDGHFI

--------------
Output :
ABDCEFGIH


範例二:
-------------
Input:
O
CBEHGIFDA
I
BCAEDGHFI

--------------
Output:
ABDCEFGIH
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 64
//#define DEBUG

typedef struct node_s {
	char data;
	struct node_s *left, *right;
} 	tree_t;
typedef tree_t *btree;

#ifdef DEBUG
	void preOrder(btree root) {
		if (root != NULL) {
			printf("%c", root->data);
			preOrder(root->left);
			preOrder(root->right);
		}
	}
	void inOrder(btree root) {
		if (root != NULL) {
			inOrder(root->left);
			printf("%c", root->data);
			inOrder(root->right);
		}
	}
	void postOrder(btree root) {
		if (root != NULL) {
			postOrder(root->left);
			postOrder(root->right);
			printf("%c", root->data);
		}
	}
#endif

int getHeight(btree node) {
    if (node == NULL) return 0;
    else {
        int lheight = getHeight(node->left);
        int rheight = getHeight(node->right);
		return (lheight > rheight)? (lheight+1): (rheight+1);
    }
}
void printGivenLevel(btree root, int level) { 
    if (root == NULL) return; 
    if (level == 1) printf("%c", root->data); 
    else if (level > 1) {
        printGivenLevel(root->left, level-1); 
        printGivenLevel(root->right, level-1); 
    }
}
void printLevelOrder(btree root) {
	int h = getHeight(root);
    for (int i = 1; i <= h; i++) printGivenLevel(root, i);
	printf("\n");
} 

int Search(char *arr, char ch, int start, int end) {
	for (int i = start; i <= end; i++)
        if (arr[i] == ch) return i;
	return -1;
}

btree pre_in_tree(char *preorder, char*inorder, int start, int end) {
	static int preIndex = 0;
	if (start > end) return NULL;
	
	btree root = (btree)malloc(sizeof(tree_t));
	root->data = preorder[preIndex++];
	
	if(start == end) return root;
	int rootIndex = Search(inorder, root->data, start, end);
	
	root->left = pre_in_tree(preorder, inorder, start, rootIndex-1);
	root->right = pre_in_tree(preorder, inorder, rootIndex+1, end);
	
	return root;
}

btree post_in_tree(char *postorder, char*inorder, int start, int end, int postIndex) {
	if (postIndex < 0 || start > end) return NULL;
	
	btree root = (btree)malloc(sizeof(tree_t));
	root->data = postorder[postIndex--];
	int rootIndex = Search(inorder, root->data, start, end);
	
	if (rootIndex == -1) {
		root = post_in_tree(postorder, inorder, start, end, postIndex);
	}	else {
		root->left = post_in_tree(postorder, inorder, start, rootIndex-1, postIndex);
		root->right = post_in_tree(postorder, inorder, rootIndex+1, end, postIndex);
	}
	
	return root;
}

int main(void) {
	char order[2], pre[SIZE], ino[SIZE], pos[SIZE];
	for (int i = 0; i < SIZE; i++) pre[i] = ino[i] = pos[i] = 0;
	
	for (int i = 0; i < 2; i++) {
		scanf("%c\n", &order[i]);
		if (order[i] == 'P') scanf("%s", pre);
		if (order[i] == 'I') scanf("%s", ino);
		if (order[i] == 'O') scanf("%s", pos);
		getchar();
		
		#ifdef DEBUG
			printf("%c\n", order[i]);
			printf("  %s\n", pre);
			printf("  %s\n", ino);
			printf("  %s\n", pos);
		#endif
	}
	
	int len = strlen(ino);
	if ((order[0] == 'P' && order[1] == 'I') || (order[0] == 'I' && order[1] == 'P')) {
		#ifdef DEBUG
			preOrder(pre_in_tree(pre, ino, 0, len-1));	printf("\n");
			inOrder(pre_in_tree(pre, ino, 0, len-1));	printf("\n");
			postOrder(pre_in_tree(pre, ino, 0, len-1));	printf("\n");
		#endif
		printLevelOrder(pre_in_tree(pre, ino, 0, len-1));
	}
	if ((order[0] == 'O' && order[1] == 'I') || (order[0] == 'I' && order[1] == 'O')) {
		#ifdef DEBUG
			preOrder(post_in_tree(pos, ino, 0, len-1, len-1));	printf("\n");
			inOrder(post_in_tree(pos, ino, 0, len-1, len-1));	printf("\n");
			postOrder(post_in_tree(pos, ino, 0, len-1, len-1));	printf("\n");
		#endif
		printLevelOrder(post_in_tree(pos, ino, 0, len-1, len-1));
	}
	
	return 0;
}