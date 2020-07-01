//	Created by L.H.Ming on 2020/06/30.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
二元搜尋樹 - 刪除
給定一數列，生成二元搜尋樹，並指定某節點進行刪除，並依照前序、中序與後序依序印出
刪除規則：
1.刪除的節點為leaf則直接刪除即完成
2.若刪除的節點非leaf，則從左方最大值之節點與右方最小值之節點中依照遞補優先度擇一進行遞補
3.優先度：左leaf > 右leaf > 左non-leaf > 右non-leaf

★必須使用struct及linked list實作★

輸入說明：
一串數列
欲刪除之節點值

輸出說明：
以數列呈現刪除節點過後的二元搜尋樹
(依序為前序、中序與後序表示式)

Sample Input :
50,40,30,65,60,45
50

Sample Output :
preorder:45,40,30,65,60
inorder:30,40,45,60,65
postorder:30,40,60,65,45

---------------------------------

Sample Input :
50,40,30,65,60,45
60

Sample Output :
preorder:50,40,30,45,65
inorder:30,40,45,50,65
postorder:30,45,40,65,50
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 128
//#define DEBUG

typedef struct node_s {
	int data;
	struct node_s *left, *right;
} 	tree_t;
typedef tree_t *btree;

void create_btree(btree *root, int data) {
	btree newnode, curr, prev;
	newnode = (btree)malloc(sizeof(tree_t));
	newnode->data = data;
	newnode->left = newnode->right = NULL;
	
	if (*root == NULL) *root = newnode; 
	else {
		curr = *root;
		while (curr != NULL) {
			prev = curr;
			curr = (curr->data > data)? curr->left: curr->right;
		}
		if (prev->data > data) prev->left = newnode;
		else prev->right = newnode;
	}
}

btree getMax(btree root) {
	if (root == NULL) return NULL;
	if (root->right != NULL)
		return getMax(root->right);
	return root;
}
btree getMin(btree root) {
	if (root == NULL) return NULL;
	if (root->left != NULL)
		return getMin(root->left);
	return root;
}

btree delete_node(btree root, int key) {
	if (root == NULL) return NULL;
	
	//找出要刪除的節點
	if (key < root->data)
		root->left = delete_node(root->left, key);
    else if (key > root->data)
        root->right = delete_node(root->right, key);
	else {
		//沒有子樹
		if (root->left == NULL && root->right == NULL) {
			free(root);
			return NULL;
		}
		//單子樹
		else if (root->left == NULL || root->right == NULL) {
			btree child;
			if (root->left == NULL) {
				child = getMin(root->right);
			}
			else {
				child = getMax(root->left)
			}
			return child;
		}
		//雙子樹
		else {
			btree leftChild = getMax(root->left);	//左子樹找最大的節點
			btree rightChild = getMin(root->right);	//右子樹找最小的節點
			
			//左leaf
			if (leftChild->left == NULL && leftChild->right == NULL) {
				root->data = leftChild->data;
				root->left = delete_node(root->left, leftChild->data);
			}
			//右leaf
			else if (rightChild->left == NULL && rightChild->right == NULL && root->right != NULL) {
				root->data = rightChild->data;
				root->right = delete_node(root->right, rightChild->data);
			}
			//左non-leaf
			else if (leftChild->left != NULL || leftChild->right != NULL) {
				root->data = leftChild->data;
				root->left = delete_node(root->left, leftChild->data);
			}
			//右non-leaf
			else if (rightChild->left != NULL || rightChild->right != NULL) {
				root->data = rightChild->data;
				root->right = delete_node(root->right, rightChild->data);
			}
		}
	}
	return root;
}

void preOrder(btree root, int size) {
	static int printed = 0;
	if (root == NULL) return;
	
	printf("%d%c", root->data, (size <= ++printed)? '\n': ',');
	preOrder(root->left, size);
	preOrder(root->right, size);
}
void inOrder(btree root, int size) {
	static int printed = 0;
	if (root == NULL) return;

	inOrder(root->left, size);
	printf("%d%c", root->data, (size <= ++printed)? '\n': ',');
	inOrder(root->right, size);
}
void postOrder(btree root, int size) {
	static int printed = 0;
	if (root == NULL) return;

	postOrder(root->left, size);
	postOrder(root->right, size);
	printf("%d%c", root->data, (size <= ++printed)? '\n': ',');
}

int main(void) {
	btree root = NULL;
	
	int len = 0;
	char data[SIZE], *token;
	
	gets(data);
	token = strtok(data, ",");
	while (token != NULL) {
		create_btree(&root, atoi(token));
		token = strtok(NULL, ",");
		len++;
	}
	
	#ifdef DEBUG
		printf("preorder:");	preOrder(root, len-1);
		printf("inorder:");		inOrder(root, len-1);
		printf("postorder:"); 	postOrder(root, len-1);
	#endif	
	
	int key;
	scanf("%d", &key);
	root = delete_node(root, key);
	
	printf("preorder:");	preOrder(root, len-1);
	printf("inorder:");		inOrder(root, len-1);
	printf("postorder:"); 	postOrder(root, len-1);

	return 0;
}