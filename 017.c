//	Created by L.H.Ming on 2020/4/27.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
輸入大數運算的模式，
以1代表大數相加；2代表大數相減；3代表大數相乘。
再輸入兩個20位數以上的整數做運算，
並輸出計算過後的結果。

sample input:
1
10000000000000000001
99999999999999999999

sample output:
110000000000000000000

--------------------------------

sample input:
2
10000100001000010000
100001000010000100001

sample output:
-90000900009000090001

--------------------------------

sample input:
3
10000100000000000001
12121212121212121212

sample output:
121213333333333333344242412121212121212
*/

/*
	解法說明

	1.	分別輸入大數到char陣列
	2.	反轉陣列並找出大小
	3.	根據運算模式，呼叫函數
	4.	輸出運算結果
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 100

//輸入
int input (int *num, int n) {
	int size; char arr[n];
	for (int i = 0; i < n; i++) arr[i] = 0;
	
	for (int i = 0; i < n; i++) {
		scanf("%c", &arr[i]);
		if (arr[i] == '\n') {	//結束輸入
			arr[i] = 0;
			size = i;
			break;
		}
		num[i] = arr[i] - 48;	//char轉換成int
	}
	
	return size;	//回傳陣列大小
}

//反轉陣列
void reverse(int *arr, int n) {
	int temp[n];
	for (int i = -1; i < n; i++) temp[n-i-1] = arr[i];
	for (int i = 0; i < n; i++) arr[i] = temp[i];
}

//加法
int add(int *n1, int *n2, int *r, int size){
	int i, carry = 0;
	
	for (i = 0; i < size; i++) {
		r[i] = (n1[i] + n2[i] + carry)%10;	//逐位相加
		carry = (n1[i] + n2[i] + carry)/10;	//檢查是否須進位
	}
	if (carry == 1) {	//最後一位進位
		r[i] = 1;
		size++;
	}
	
	return size;	//回傳陣列大小
}

//減法
int sub(int *n1, int *n2, int *r, int size) {
	int i, borrow = 0;
	
	//比較兩數的大小
	for (i = size; i >= 0; i--) {	
		if (n1[i] < n2[i]) {	//被減數小於減數
			printf("-");		//結果為負
			int *temp;
			temp = n1; n1 = n2; n2 = temp;	//交換被減數及減數
			break;
		}else if (n1[i] > n2[i]) break;	//被減數大於減數
	}
	
	//逐位相減
	for (i = 0; i < size; i++) {
		r[i] = n1[i] - n2[i] - borrow;
		if (r[i] < 0) {	//檢查是否須借位
			r[i] += 10;
			borrow = 1;
		}else borrow = 0;
	}
	
	for (i = size; i > 0 && r[i] == 0; i--) {}	//找出陣列大小
	
	return i+1;	//回傳陣列大小
}

//乘法
int mul(int *n1, int *n2, int *r, int n1_s, int n2_s) {
	for (int i = 0; i < n2_s; i++) {
		for (int j = 0; j< n1_s; j++) {
			r[i+j] += (n1[j] * n2[i]);	//逐位相乘
			if (r[i+j] >= 10) {	//檢查是否須進位
				r[i+j+1] += r[i+j] / 10;
				r[i+j] %= 10;
			}
		}
	}
	
	int size = n1_s + n2_s;	
	for (int i = size; i > 0 && r[i] == 0; i--, size--) {}	//找出陣列大小
	return size + 1;	//回傳陣列大小
}

//輸出
void print(int *r, int size) {
	for (int i= size - 1; i >= 0; i--) printf("%d", r[i]);
	printf("\n");
}

int main(void) {
	//初始化
	int mode, size, n1_size, n2_size;
	int num1[SIZE], num2[SIZE], res[SIZE];
	for (int i = 0; i < SIZE; i++) num1[i] = num2[i] = res[i] = 0;
	
	scanf("%d\n", &mode);			//輸入運算模式
	n1_size = input(num1, SIZE);	//輸入第一個數
	n2_size = input(num2, SIZE);	//輸入第二個數
	reverse(num1, n1_size); reverse(num2, n2_size);	//反轉陣列
	size = n1_size > n2_size? n1_size: n2_size;		//比較大小
	
	//根據運算模式，呼叫函數
	switch (mode) {
		case (1):
			size = add(num1, num2, res, size);	//加法
			break;
		case (2):
			size = sub(num1, num2, res, size);	//減法
			break;
		case (3):
			size = mul(num1, num2, res, n1_size, n2_size);	//乘法
	}
	
	//輸出
	print(res, size);
	
	return 0;
}
