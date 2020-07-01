//	Created by L.H.Ming on 2020/06/30.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
使用 Link List 實作queue

在一端進行先進先出（FIFO, First In First Out）的原理運作。
兩種基本操作：enqueue 和 dequeue，

enqueue:將資料放入佇列的尾端（串列形式），佇列尾端tail指標加一。
pop：將頂端數據資料輸出（回傳），佇列頂端top指標減一。
每一次push和pop的一筆資料都包含姓名、年齡、生日(年、月、日)

輸入說明:
1 代表 euqueue，再依序輸入姓名、年齡、生日(年、月、日)，參數之間以空白相隔
2 代表 dequeue，再輸入一個數字，進行不同的操作，操作數字如下:
3 結束程式

dequeue後的數字:
1:印出該次dequeue的資料中的姓名
2:印出該次dequeue的資料中的年齡
3:印出該次dequeue的資料中的生日(年、月、日之間以底線連結)
若queue中為空則印出 The Queue is empty

範例一:
Input:
1 "Marry Hu" 19 1989 7 16
1 "Tom Chen" 22 1996 10 19
2 1
1 "Billy Wu" 15 2005 3 18
2 3
2 2
1 "Seafood" 24 1993 5 21
2 3
2 1
3

Output:
Marry Hu
1996_10_19
15
1993_5_21
The Queue is empty

範例二:
Input:
1 "Tome Hu" 19 1989 7 16
2 3
2 1
1 "Mike Lee" 25 1995 10 9
2 2
2 3
3

Output:
1989_7_16
The Queue is empty
25
The Queue is empty
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 32

//#define DEBUG

typedef struct queue_node_s {
	char name[SIZE];
	int age;
	int dob[3];
	struct queue_node_s *restp;
}	queue_node_t;
typedef struct {
	queue_node_t *rearp;
	queue_node_t *frontp;
}	queue_t;

void dequeue(queue_t *qp, int mode) {
	queue_node_t *p = qp->frontp;
	if (p == NULL) printf("The Queue is empty\n");
	else {
		switch (mode) {
			case 1: printf("%s\n", p->name);break;
			case 2: printf("%d\n", p->age); break;
			case 3: for(int i = 0; i < 2; i++) 
					printf("%d_", p->dob[i]);
					printf("%d\n", p->dob[2]);
		}
		qp->frontp = p->restp;
		free(p);
	}
	if (p == qp->rearp) qp->rearp = NULL;
}

void enqueue(queue_t *qp, char *name, int age, int *dob) {
	queue_node_t *newNode = (queue_node_t*)malloc(sizeof(queue_node_t));
	strcpy(newNode->name, name);
	newNode->age = age;
	for (int i = 0; i < 3; i++) newNode->dob[i] = dob[i];
	newNode->restp = NULL;
	if (qp->rearp == NULL) {
		qp->frontp = qp->rearp = newNode;
		return;
	}
	qp->rearp->restp = newNode;
	qp->rearp = newNode;
}


void printQueue(queue_t *qp) {
	queue_node_t *current = qp->frontp;
	printf("\nThe queue is:\n");
	while(current != NULL) {
		printf("    %s, %d, %d %d %d\n", current->name, current->age, current->dob[0], current->dob[1], current->dob[2]);
		current = current->restp;
	}
	printf("\n");
}

int main(void) {
	queue_t queue = {NULL, NULL};
	
	int key;
	while (scanf("%d", &key) && key != 3) {
		#ifdef DEBUG
			printf("\nkey: %d\n", key);
		#endif
		
		getchar();
		if (key == 1) {
			char c, name[SIZE] = {0};
			int age, cnt = 0, index = 0;
			int dob[3] = {0};
			
			while (1) {
				scanf("%c", &c);
				if (c == '"') cnt++;
				if (cnt == 2) break;
				if (c != '"') name[index++] = c;
			}
			scanf("%d", &age);
			for (int i = 0; i < 3; i++) scanf("%d", &dob[i]);
			
			#ifdef DEBUG
				printf("name: %s\nage: %d\ndob: %d %d %d\n", name, age, dob[0], dob[1], dob[2]);
			#endif
			
			enqueue(&queue, name, age, dob);
			
			#ifdef DEBUG
				printQueue(&queue);
			#endif
		}
		
		if (key == 2) {
			int mode;
			scanf("%d", &mode);
			
			#ifdef DEBUG
				printf("mode: %d\n", mode);
			#endif
			
			dequeue(&queue, mode);
			
			#ifdef DEBUG
				printQueue(&queue);
			#endif
		}
	}
	
	return 0;
}