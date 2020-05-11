//	Created by L.H.Ming on 2020/05/10.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
考慮一個數列 A = (a[1], a[2], a[3], ..., a[n] )。如果 A中兩個數 a[i]和 a[j]滿足 i < j 且 a[i] > a[j]，則說 (a[i], a[j])是 A中的一個 反序 (inversion)。
定義W(A)為數列A中反序數量。例如，在數列 A = (3, 1, 9, 8, 9, 2)中，共有 (3, 1)、(3, 2)、(9, 8)、(9, 2)、 (8, 2)、(9, 2) 6個反序 ，所以 W(A) =6。

計算 W(A)簡單方法是對所有1 <= i < j <= n檢查數對(a[i], a[j])，但在序列太長時，計算時間會超過給定時限。
以下運用分而治之(divide and conquer)策略所設計更有效率方法。
將A等分為前後兩個數列 X 與 Y，其中 X的長度是 n/2。
遞迴計算 W(X) 和W(Y)。
計算W(A) = W(X) + W(Y) + S(X, Y)，其中 S(X, Y)是由 X中的數字與 Y中的數字構成的反序數量 。

以 A = (3, 1, 9, 8, 9, 2) 為例，W(A) 計算如下。
將 A 分為兩個數列 X = (3, 1, 9) 與 Y = (8, 9, 2)。
遞迴計算得到 W(X) = 1和 W(Y) = 2。
計算 S(X, Y) = 3。因為有三個反序 (3, 2)、(9, 8)、(9, 2)是由 X中的數字與中的數字與 Y中的數字所構成。
所以得到 W(A) = W(X) + W(Y) + S(X, Y) = 1+2+3 = 6。

請撰寫一個程式，計算 一個數列 A的反序數量 W(A)。

-----------------
輸入格式:
測試資料有兩列，第一列為一個正整數 n，代表A的長度。
第二列有 n個不大於 10^6的非負整數，代表 a[1], a[2], a[3], ..., a[n]，數字間以空白隔開 。

-----------------
輸出格式:
A的反序數量 W(A)。可能超過32-bit 整數範圍。

-------------
Sample Input:
6
3 1 9 8 9 2
-------------
Sample Output:
6

-------------
Sample Input:
5
5 5 4 3 1
-------------
Sample Output:
9
*/

/* 先看看用 for 迴圈的寫法 (Linear Search) 時間複雜度: O(n)，因此很容易超時
#include <stdio.h>

int main(void) {
	int n;
	unsigned long long count = 0;
	scanf("%d", &n);
	int arr[n];
	
	for (int i = 0; i < n; i++) scanf("%d%*c", &arr[i]);

	for (int i = 0; i < n-1; i++) {
		for (int j = i+1; j < n; j++) {
			if (arr[i] > arr[j]) count++;
		}
	}
	
	printf("%llu\n", count);
	return 0;
}
*/

//	使用Recursion 時間複雜度: O(log n)
//	此解使用分治法(Divide and Conquer)
#include <stdio.h>

//合併解法，我不太會解釋，自己體會
int merge(int *arr, int *temp, int l, int m, int r) { 
	int count = 0, i, j;
	
	for(i = l; i <= r; i++) temp[i] = arr[i];
	
	int k = l;
	for(i = l, j = m + 1; i <= m && j <= r;k++) {
		if(temp[i] > temp[j]) {
			count += m - i + 1;
			arr[k] = temp[j++];
		} else arr[k] = temp[i++];
	}
	
	if(i > m) {
		while(j <= r) arr[k++] = temp[j++];
	} else {
		while(i <= m) arr[k++] = temp[i++];
	}
	
	return count;
}

int rev_pair(int *arr, int *temp, int l, int r) {
	if(l == r) return 0;	//無法再細分
	
	int m = (l + r) / 2;	//找出中點位置
	
	int ln = rev_pair(arr, temp, l, m);		//左分
	int rn = rev_pair(arr, temp, m + 1, r);	//右分
	int mn = merge(arr, temp, l, m, r);		//合併
	
	return ln + rn + mn;	//回傳合併解
}

int main(void) {
	//初始化 & Input
	int n;
	scanf("%d", &n);
	int arr[n], temp[n];
	
	for (int i = 0; i < n; i++) scanf("%d%*c", &arr[i]);
	
	printf("%llu\n", rev_pair(arr, temp, 0, n-1));	//P.S. 答案有機會過大，此處使用unsigned long long int輸出
	
	return 0;
}
