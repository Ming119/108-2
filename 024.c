//	Created by L.H.Ming on 2020/05/21.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
輸入一篇英文文章 A，文章中英文字以一個空白間隔。另外輸入 2 個英文字(word) P、Q。
(1) 將文章 A 中 P 字串以 Q 字串取代，並輸出。
(2) 在文章 A 中 P 字串前插入 Q 字串，並輸出。
(3) 將文章 A 中 P 字串刪除，並輸出。
(4) 分析文章 A 所有英文字 (word) 的頻率，依頻率由大自小排序， 頻率相同則以 word由小自大排序(That > This....)輸出。

----------------
輸入說明 :
第一行，文章 A
第二行，英文字 P
第三行，英文字 Q
----------------
輸出說明 :
第一行，將文章 A 中的 P 字串以 Q 字串取代之結果
第二行，在文章 A 中的 P 字串前插入 Q 字串之結果
第三行，將文章 A 中的 P 字串刪除之結果
第四行，將文章 A 中所有的英文字出現的次數統計出來，由次數高到低排列，若次數一樣則由字母小到大排列(大寫在小寫之前)，請用 : 隔開單字與次數(冒號前後皆有空白)

-------------
Sample Input:
Can you can a can as a canner can can a can
can
ban
-------------
Sample Output:
Can you ban a ban as a canner ban ban a ban
Can you ban can a ban can as a canner ban can ban can a ban can
Can you a as a canner a
can : 5
a : 3
Can : 1
as : 1
canner : 1
you : 1

-------------
Sample Input:
Whether the weather be cold or whether the weather be hot
the
a
-------------
Sample Output:
Whether a weather be cold or whether a weather be hot
Whether a the weather be cold or whether a the weather be hot
Whether weather be cold or whether weather be hot
be : 2
the : 2
weather : 2
Whether : 1
cold : 1
hot : 1
or : 1
whether : 1
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 32

typedef struct strPrt{
    char* list[SIZE];
    int size;
} strPrt;
 
char *strtok(char *str, const char *delim);
/*	char* strtok(char *str, const char *delim) {
		static char *temp;
		(str == NULL) ? (str = temp) : (temp = str);
		while (*temp != *delim || *temp != '\0') temp ++;
		if (*temp == '\0') return NULL;
		temp ++;
		return str;
	}	*/
int strcmp(const char *str1, const char *str2);
/*	int mstrcmp(const char *str1, const char *str2) {
		if (*str1 > *str2) return 1;
		if (*str1 < *str2) return -1;
		if (*str1 == '\0' && *str2 == '\0') return 0;
		return strcmp(str1 ++, str2 ++);
	}	*/


void replace(char *str, char *p, char *q) {
	char *token = strtok(str,  " ");
	
	while (token != NULL) {
		if(!(strcmp(token, p))) printf("%s ", q);
		else printf("%s ", token);
		token = strtok(NULL, " ");
	}
	
	printf("\n");
}

void insert(char *str, char *p, char *q) {
	char *token = strtok(str,  " ");
	
	while (token != NULL) {
		if(!(strcmp(token, p))) printf("%s %s ", q, token);
		else printf("%s ", token);
		token = strtok(NULL, " ");
	}
	
	printf("\n");
}


void delete(char *str, char *p, char *q) {
	char *token = strtok(str,  " ");
	while (token != NULL) {
		if(strcmp(token, p)) printf("%s ", token);
		token = strtok(NULL, " ");
	}
	printf("\n");
}

void split(strPrt* retrn, char* sentence, const char symbol) {	//retrn為回傳值
	//將字串以symbol分割，並回傳分割后每個字串的指標
    int len = strlen(sentence);
    retrn->list[retrn->size++] = &sentence[0];
	
    for (int i = 1; i < len; i++) {
        if (sentence[i] == symbol) {
            sentence[i] = '\0';
            while (sentence[i + 1] == symbol) i++;
            retrn->list[retrn->size++] = &sentence[i + 1];
        }
    }
}
void sort(strPrt* sentence, int* count) {   //選擇排序法：將全部字串以出現頻率（count）進行降冪排序，相同頻率則以字串大小排序
    strPrt resultString = {{0}, 0};
    int resultCount[100] = {0};

    while(resultString.size != sentence->size) {
        int max = 0;
        for (int i = 0; i < sentence->size; i++) 
            if (count[i] > count[max] || (count[max] != 0 && count[i] == count[max] && strcmp(sentence->list[i], sentence->list[max]) < 0))
                max = i;
        
        resultString.list[resultString.size++] = sentence->list[max];
        resultCount[resultString.size - 1] = count[max]; 
        count[max] = 0;
    }

    for (int i = 0; i < resultString.size; i++)
        printf("%s : %d\n", resultString.list[i], resultCount[i]);
}

void count(strPrt* sentence) {   //計算sentence中每個字的出現頻率
    strPrt str = {{0}, 0};
    int count[100] = {0};

    while(sentence->size) {
        str.list[str.size++] = sentence->list[0];
        for (int i = 0; i < sentence->size;) {
            if (strcmp(sentence->list[i], str.list[str.size - 1]) == 0) {
                count[str.size - 1]++;
                for (int j = i; j < sentence->size - 1; j++)
                    sentence->list[j] = sentence->list[j + 1];
                sentence->size--;
            }
			
            else i++;
        }
    }

    sort(&str, count);
}



int main(void) {
	char input[SIZE*SIZE], temp[SIZE*SIZE], P[SIZE], Q[SIZE];
	
	gets(input);
	scanf("%s%s", P, Q);
	
	strcpy(temp, input);
	replace(temp, P, Q);
	strcpy(temp, input);
	insert(temp, P, Q);
	strcpy(temp, input);
	delete(temp, P, Q);
	
	strPrt strList = {{0}, 0};
	split(&strList, input, ' ');
	count(&strList);
	
	return 0;
}