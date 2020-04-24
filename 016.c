//	Created by L.H.Ming on 2020/4/25.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
分散度
----------------

輸入一串整數序列和m分散度，輸出m分散度數量。
m分散度定義為，序列中擁有長度為m 且有m 種不同數字的連續子序列之數量。

例如，m = 3，序列{1 2 3 5 4 5 4}，3 分散度數量{1 2 3}, {2 3 5}, {3 5 4}，總共三個。

sample input:
1235454
3

sample output:
3

----------------

sample input:
1866454122
5

sample output:
0
*/

/*
	解法說明

	1.	整數序列輸入到char陣列，分散度m輸入到int
	2.	使用指標，傳遞char陣列及分散度到函數
	3.	線性搜尋函數
		a.	分割陣列
		b.	檢查相同元素
	4.	輸出找到的分散度數量
	
*/

#include <stdio.h>

//線性搜尋函數
int check(char *arr, int m) {
	//分割陣列，使用線性搜尋 Linear Search
	for (int i = 0; i < m-1; i++) {
		for (int j = i+1; j < m; j++) {
			if (arr[i] == arr[j]) return 0;	//找到相同的元素，回傳0
		}
	}
	return 1;	//沒有找到相同的元素，回傳1
}

int main(void) {
	//初始化
	int m = 0, size = 20, count = 0;
	char arr[size];
	for (int i = 0; i < size; i++) arr[i] = '\0';
	
	//輸入
	for (int i = 0; i < size; i++) {
		scanf("%c", &arr[i]);
		if (arr[i] == '\n') {	//結束輸入
			size = i;	//儲存輸入的位數
			break;
		}			
	}
	scanf("%d", &m);
	
	for (int i = 0; i < size-m+1; i++) count += check(arr+i, m);
	
	//輸出
	printf("%d\n", count);
	
	return 0;
}