//	Created by L.H.Ming on 2020/06/30.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
***本題務必使用 Link List***

輸入兩個多項式，輸出相加、相減、相乘的結果。例如:

2x^4 + 3x^3 + x -1
x^5 - x^3 + 4x^2 - 3x +2
結果：
x^5 + 2x^4 + 2x^3 + 4x^2 - 2x + 1
-x^5 + 2x^4 + 4x^3 - 4x^2 + 4x - 3
2x^9 + 3x^8 - 2x^7 + 6x^6 + 5x^5 - 6x^4 + 11x^3 - 7x^2 + 5x - 2

輸入說明
輸入兩筆資料，分別代表兩個多項數。
每一筆輸入 n 個整數，第一個代表 n-1次方的係數，第 n 個代表 0 次方係數。

輸出說明
兩個多項式計算後從最高次方到0次方的係數，計算結果為0的係數也需印出。


Sample Input
2 3 0 1 -1
1 0 -1 4 -3 2

Sample Output
1 2 2 4 -2 1
-1 2 4 -4 4 -3
2 3 -2 6 5 -6 11 -7 5 -2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 64
//#define DEBUG

typedef struct node_s{
	int data;
	int exp;
	struct node_s *next;
}	node_t;
typedef node_t *nodep_t;

nodep_t create(int data, int exp) {
	nodep_t newNode = (nodep_t)malloc(sizeof(node_t));
	newNode->data = data;
	newNode->exp = exp;
	newNode->next = NULL;
	return newNode;
}

void insert(nodep_t *p, int data, int exp) {
	nodep_t newNode = create(data, exp);
	if (*p == NULL) *p = newNode;
	else {
		newNode->next = *p;
		*p = newNode;
	}
}

void printList(nodep_t p) {
	nodep_t current = p;
	int flag = 0;
	
	while (current != NULL) {
		if (current->data || current->next == NULL) flag = 1;
		if (flag) 
			printf("%d ", current->data);
		
		#ifdef DEBUG
			printf("(%d)  ", current->exp);
		#endif
		
		current = current->next;
	}
	printf("\n");
}

nodep_t calc(nodep_t p1, nodep_t p2, char mode) {
	nodep_t newp = {NULL};
	nodep_t pp1 = p1;
	nodep_t pp2 = p2;

	int exp = 0;
	while(pp1 != NULL && pp2 != NULL) {
		if (mode == '+') insert(&newp, pp1->data + pp2->data, exp);
		if (mode == '-') insert(&newp, pp1->data - pp2->data, exp);
		pp1 = pp1->next;
		pp2 = pp2->next;
		exp++;
	}
	
	if (pp1 == NULL) {
		while (pp2 != NULL) {
			if (mode == '+') insert(&newp, pp2->data, exp);
			if (mode == '-') insert(&newp, -pp2->data, exp);
			pp2 = pp2->next;
			exp++;
		}
	}
	if (pp2 == NULL) {
		while (pp1 != NULL) {
			insert(&newp, pp1->data, exp);
			pp1 = pp1->next;
			exp++;
		}
	}
	
	return newp;
}

nodep_t mul(node_t *p1, node_t *p2) {
	nodep_t newp = {NULL}, npp = newp;;
	
	nodep_t pp1 = p1;
	while (pp1 != NULL) {
		nodep_t pp2 = p2;
		while (pp2 != NULL) {
			int ndata = pp1->data * pp2->data;
			int nexp = pp1->exp + pp2->exp;
			
			if (npp == NULL) insert(&newp, ndata, nexp);
			else {
				for (int i = newp->exp; i >= 0; i--) {
					if (npp == NULL) break;
					if (npp->exp != nexp) npp = npp->next;
				}
			
				if (npp == NULL) insert(&newp, ndata, nexp);
				else npp->data += ndata;
			}
			
			#ifdef DEBUG
				printList(newp);
			#endif
			
			npp = newp;
			pp2 = pp2->next;
		}
		pp1 = pp1->next;
	}
	
	return newp;
}

int main(void) {
	nodep_t p1 = {NULL}, p2 = {NULL};
	
	
	char data[SIZE], data2[SIZE], *token;
	gets(data);
	strcpy(data2, data);
	int i = 0;
	token = strtok(data2, " ");
	while (token != NULL) {
		i++;
		token = strtok(NULL, " ");
	}
	strcpy(data2, data);
	token = strtok(data2, " ");
	while (token != NULL) {
		insert(&p1, atoi(token), --i);
		token = strtok(NULL, " ");
	}
	
	gets(data);
	strcpy(data2, data);
	i = 0;
	token = strtok(data2, " ");
	while (token != NULL) {
		i++;
		token = strtok(NULL, " ");
	}
	strcpy(data2, data);
	token = strtok(data, " ");
	while (token != NULL) {
		insert(&p2, atoi(token), --i);
		token = strtok(NULL, " ");
	}
	
	#ifdef DEBUG
		printList(p1);
		printList(p2);
	#endif
	
	printList(calc(p1, p2, '+'));
	printList(calc(p1, p2, '-'));
	printList(mul(p1, p2));
	
	return 0;
}