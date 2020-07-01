//	Created by L.H.Ming on 2020/06/30.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
***此題務必使用 Link List***

實作stack
在一端進行後進先出（LIFO, Last In First Out）的原理運作。
兩種基本操作：push 和 pop
push：將數據放入堆疊的頂端（串列形式），堆疊頂端top指標加一。
pop：將頂端數據資料輸出（回傳），堆疊頂端top指標減一。

每一次push和pop的一筆資料都包含姓名、年齡、生日(年、月、日)

輸入說明:
1 代表 push，再依序輸入姓名、年齡、生日(年、月、日)，參數之間以空白相隔
2 代表 pop，再輸入一個數字，進行不同的操作，操作數字如下:
1:印出該次pop的資料中的姓名
2:印出該次pop的資料中的年齡
3:印出該次pop的資料中的生日(年、月、日之間以底線連結)
若stack中為空則印出 The Stack is empty\n
3 結束程式。

Sample Input

1 "Marry Hu" 19 1989 7 16
1 "Tom Chen" 22 1996 10 19
2 1
1 "Billy Wu" 15 2005 3 18
2 3
2 2
1 "Lucas Su" 24 1993 5 21
2 3
2 1
3

Sample Output

Tom Chen
2005_3_18
19
1993_5_21
The Stack is empty
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 32

//#define DEBUG

typedef struct stack_node_s {
	char name[SIZE];
	int age;
	int dob[3];
	struct stack_node_s *restp;
}	stack_node_t;
typedef struct {
	stack_node_t *topp;
}	stack_t;

void pop(stack_t *sp, int mode) {
	stack_node_t *p = sp->topp;
	if (p == NULL) printf("The Stack is empty\n"); 
	else {
		switch (mode) {
			case 1: printf("%s\n", p->name);break;
			case 2: printf("%d\n", p->age); break;
			case 3: for(int i = 0; i < 2; i++) 
					printf("%d_", p->dob[i]);
					printf("%d\n", p->dob[2]);
		}
		sp->topp = p->restp;
		free(p);
	}
}

void push(stack_t *sp, char *name, int age, int *dob) {
	stack_node_t *newNode = (stack_node_t*)malloc(sizeof(stack_node_t));
	strcpy(newNode->name, name);
	newNode->age = age;
	for (int i = 0; i < 3; i++) newNode->dob[i] = dob[i];
	newNode->restp = sp->topp;
	sp->topp = newNode;
}

void printStack(stack_t *sp) {
	stack_node_t *current = sp->topp;
	printf("\nThe stack is:\n");
	while(current != NULL) {
		printf("    %s, %d, %d %d %d\n", current->name, current->age, current->dob[0], current->dob[1], current->dob[2]);
		current = current->restp;
	}
	printf("\n");
}

int main(void) {
	stack_t stack = {NULL};
	
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
			
			push(&stack, name, age, dob);
			
			#ifdef DEBUG
				printStack(&stack);
			#endif
		}
		
		if (key == 2) {
			int mode;
			scanf("%d", &mode);
			
			#ifdef DEBUG
				printf("mode: %d\n", mode);
			#endif
			
			pop(&stack, mode);
			
			#ifdef DEBUG
				printStack(&stack);
			#endif
		}
	}
	
	return 0;
}