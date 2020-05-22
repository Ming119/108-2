//	Created by L.H.Ming on 2020/05/21.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
互補字S1, S2的定義是字串S1, S2沒有重複出現的字，且字串S1, S2內的字需包含在字串S內的字。
此處，字串是英文字的一個集合，亦即，元素有重複只算一個，也不管排列情況。
例如"Happy Happy Day"與"Day Happy Day"是相同的字串。輸入n個字串，輸出這n個字串互補的個數。
----------------
輸入說明 :
第一行，字串S
第二行，輸入字串個數n
第三行，第一個字串
第四行，第二個字串
........
----------------
輸出說明 :
第一行，n個字串互補的個數


-------------
Sample Input:
happy birthday to you
4
happy to you
birthday birthday
to you
happy birthday
-------------
Sample Output:
2

-------------
Sample Input:
what are you doing
3
what what are
doing doing
what are are you you
-------------
Sample Output:
1
*/

#include <stdio.h>
#include <string.h>

#define SIZE 128

typedef struct listPtr{
    char* list[SIZE];
    int size;
}listPtr;

void print(const listPtr* Str) {   //輸出分割后的字串
    for(int i = 0; i < Str->size; i++) {
        printf("%s", Str->list[i]);
        i == Str->size - 1 ? printf("\n") : printf(" ");
    }
}

void sort(listPtr* list) {   //選擇排序法：依字串大小排序
    for (int i = 0; i < list->size - 1; i++) {
        int min = i;
        for (int j = i + 1; j < list->size; j++) 
            if (strcmp(list->list[j], list->list[min]) < 0) min = j;
        
        //swap
		char* temp = list->list[i]; 
		list->list[i] = list->list[min]; 
		list->list[min] = temp;
    }
}

void removeSame(listPtr* list) {
    //remove repeated string
    for (int i = 0; i < list->size - 1; i++) {
        for (int j = i + 1; j < list->size;) {
            if (strcmp(list->list[i], list->list[j]) == 0) {
				//列表中刪除指定索引值的字串
                for (int index = j; index < list->size - 1; index++)
					list->list[index] = list->list[index + 1];
					list->list[list->size--] = NULL;
			}
            else j++;
        }
    }
	
    sort(list);
}

void add(listPtr* sum, const listPtr* str1, const listPtr* str2) {   //將兩個list組合起來
    for (int i = 0; i < str1->size; i++)
        sum->list[sum->size++] = str1->list[i];
    for (int i = 0; i < str2->size; i++)
        sum->list[sum->size++] = str2->list[i];
}

int isComplete(const listPtr* complete, const listPtr* str1, const listPtr* str2) {
    //兩個字串做聯集
    listPtr sum = {{0}, 0};
	add(&sum, str1, str2);
    
	removeSame(&sum);

    if (complete->size != sum.size || sum.size != str1->size + str2->size) return 0;

    for (int i = 0; i < complete->size; i++)
        if (strcmp(complete->list[i], sum.list[i])) return 0;

    return 1;
}

void split(listPtr* retrn, char* Str, const char symbol) {	//將字串以symbol分割，並回傳分割后每個字串的指標
    int len = strlen(Str);
    retrn->list[retrn->size++] = &Str[0];	//retrn為回傳值{
	
    for (int i = 1; i < len; i++) {
        if (Str[i] == symbol) {
            Str[i] = '\0';
            while (Str[i + 1] == symbol) i++;
            if(Str[i + 1] != '\0') retrn->list[retrn->size++] = &Str[i + 1];
        }
    }
}

int main(void) {
    char fullStr[SIZE] = {0}, smallStr[SIZE][SIZE] = {0};
    listPtr fullStrSet = {{0}, 0}, smallStrSet[SIZE] = {{0}, 0};
    int totalSmall;

    //輸入完整句子同時轉換爲集合
    gets(fullStr);
    split(&fullStrSet, fullStr, ' ');
    removeSame(&fullStrSet);
    scanf("%d\n", &totalSmall);

    //輸入小句子同時轉換成集合
    for (int i = 0; i < totalSmall; i++) {
        gets(smallStr[i]);
        split(&smallStrSet[i], smallStr[i], ' ');
        removeSame(&smallStrSet[i]); 
    }

    int count = 0;
    for (int i = 0; i < totalSmall - 1; i++) {
        for (int j = i + 1; j < totalSmall; j++) 
            count += isComplete(&fullStrSet, &smallStrSet[i], &smallStrSet[j]);
    }
	
    printf("%d\n", count);
    
	return 0;
}


