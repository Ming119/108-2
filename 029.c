//	Created by L.H.Ming on 2020/06/05.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*以struct實做長小數的運算
(上機考必考必選題)

將長小數(包含整數部位與小數部位)，整數位數不超過60位，小數位數也不超過60位。
計算兩小數的相加、相減、相乘。

輸入說明:
輸入兩個小數數字
輸入N，表示兩小數計算後結果顯示到小數點後第N位
例如:N=15，表示2小數計算後的結果只需顯示到小數點後第15位

輸出說明:
輸出兩小數的相加、相減、相乘結果到小數點後第N位
---------------------------------------------------
輸入範例:
999999999999999999999999999999999999999999999999999999999999.999999999999999999999999999999999999999999999999999999999999
999999999999999999999999999999999999999999999999999999999999.999999999999999999999999999999999999999999999999999999999999
12
輸出範例:
1999999999999999999999999999999999999999999999999999999999999.999999999999
0
999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999998
---------------------------------------------------
輸入範例:
-999999999999999999999999999999999999999999999999999999999999.999999999999999999999999999999999999999999999999999999999999
-999999999999999999999999999999999999999999999999999999999999.999999999999999999999999999999999999999999999999999999999999
12
輸出範例:
-1999999999999999999999999999999999999999999999999999999999999.999999999999
0
999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999998
---------------------------------------------------
輸入範例:
999999999999999999999999999999999999999999999999999999999999.999999999999999999999999999999999999999999999999999999999999
-9999999999999.99999999999
12
輸出範例:
999999999999999999999999999999999999999999999990000000000000.000000000009
1000000000000000000000000000000000000000000000009999999999999.999999999989
-9999999999999999999999989999999999999999999999999999999999999999999999999.999999999999
---------------------------------------------------
輸入範例:
-999999999999999999999999999999999999999999999999999999999999.999999999999999999999999999999999999999999999999999999999999
9999999999999.99999999999
12
輸出範例:
-999999999999999999999999999999999999999999999990000000000000.000000000009
-1000000000000000000000000000000000000000000000009999999999999.999999999989
-9999999999999999999999989999999999999999999999999999999999999999999999999.999999999999
---------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 128
#define SIZE2 256

//自定義結構struct
typedef struct longDouble {
	int array[SIZE2];	//整數陣列
	int point;			//小數點的位置
	int flag;			//是否為負
}	longDouble;

//把 字串string 轉換成 自定義結構struct
longDouble convert(char *str) {
	longDouble res;
	for (int i = 0; i < SIZE2; i++) res.array[i] = 0;	//整數陣列預設為0
	
	res.flag = str[0] == '-'? 1: 0;			//檢查是否為負，記錄在flag

	for (int i = 0, l = strlen(str)-1; l >= res.flag; l--) {
		if (str[l] == '.') res.point = i;	//找到小數點，把它的位置記錄在point
		else res.array[i++] = str[l]-'0';	//char to int, 放到整數陣列
	}
	
	//DEBUG
	/*
	printf("res.flag = %d, res,point = %d\nres.array:\n", res.flag, res.point);
	for (int i=0; i<SIZE; i++) printf("%d ", res.array[i]);
	printf("\n\n");
	*/
	
	return res;
}

//移位，對準小數位
void shift(longDouble *num1, longDouble *num2) {
	int diff = abs(num1->point - num2->point);	//兩個數的小數位相差
	
	//num1的小數位 '多於' num2的小數位
	if (num1->point > num2->point) {
		for(int i = SIZE-diff; i >= 0; i--) 
			num2->array[i+diff] = num2->array[i];
		for (int i = 0; i < diff; i++) num2->array[i] = 0;
	}
	//num1的小數位 '少於' num2的小數位
	if (num1->point < num2->point) {
		for (int i = SIZE-diff; i >= 0; i--)
			num1->array[i+diff] = num1->array[i];
		for (int i = 0; i < diff; i++) num1->array[i] = 0;
	}
	
	//DEBUG
	/*
	printf("num1.array:\n");
	for (int i=0; i<SIZE; i++) printf("%d ", num1->array[i]);
	printf("\n\nnum2.array:\n");
	for (int i=0; i<SIZE; i++) printf("%d ", num2->array[i]);
	printf("\n\n");
	*/
	
}

//加法及減法
longDouble add(longDouble num1, longDouble num2) {
	longDouble res = convert("0");
	res.point = num1.point > num2.point? num1.point: num2.point;	//答案的小數點位置 = 較多小數位的小數點位數
	
	if (num1.flag == num2.flag) {	//正正 或 負負
		res.flag = num1.flag;		//正加正必為正，負加負必為負
		
		//加法算法
		for(int i = 0; i < SIZE; i++)  {
			res.array[i] += num1.array[i] + num2.array[i];
			//進位
			if(res.array[i] > 9) {		//本位大於9
				res.array[i] -= 10;		//本位減10
				res.array[i+1] += 1;	//下位加1
			}
		}
		
	}	else if (num1.flag && !num2.flag) { //num1為負, num2為正
		
		//比較大小	註：for迴圈的內容跟L138, L157的條件判斷有關
		for(int i = SIZE-1; i >= 0; i--) {
			if (num1.array[i] > num2.array[i]) {				//num1比num2大
				res.flag = 1; 	break;							//答案為負
			} 	else if (num1.array[i] < num2.array[i])	break;	//num1比num2小，答案為正
		}
		//減法算法
		for(int i = 0; i < SIZE; i ++) {
			if (res.flag)	res.array[i] += num1.array[i] - num2.array[i];	//答案為負時 (num1比num2大)， num1 - num2
			else res.array[i] += num2.array[i] - num1.array[i];				//答案為正時 (num1比num2小)， num2 - num1
			//借位
			if (res.array[i] < 0) {		//本位少於0
				res.array[i] += 10;		//本位加10
				res.array[i+1] -= 1;	//下位減1
			}				
		}
		
	}	else if (!num1.flag && num2.flag)	return add(num2, num1);	//num1為正, num2為負, 要把num1 num2反過來算 (Goto L138)
	
	//DEBUG
	/*
	printf("res.flag = %d, res,point = %d\nres.array:\n", res.flag, res.point);
	for (int i=0; i<SIZE; i++) printf("%d ", res.array[i]);
	printf("\n\n");
	*/
	
	return res;
}

//乘法
longDouble mul(longDouble num1, longDouble num2) {
	longDouble res = convert("0");
	int point = num1.point > num2.point? num1.point: num2.point;	//答案的小數點位置 = 較多小數位的小數點位數
	res.point = point*2;											//再乘2
	
	if (num1.flag != num2.flag)	res.flag = 1;	//正負得負
	//乘法算法
	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			res.array[i+j] += num1.array[j] * num2.array[i];//留意乘法算法的本位為[i+j]
			//進位
			if (res.array[i+j] > 9) {						//本位大於9
				res.array[i+j+1] += res.array[i+j] / 10;	//下位加本位除10(十位)
				res.array[i+j] = res.array[i+j] % 10;		//本位mod 10	(個位)
			}
		}
	}
	
	//DEBUG
	/*
	printf("res.flag = %d, res,point = %d\nres.array:\n", res.flag, res.point);
	for (int i=0; i<SIZE; i++) printf("%d ", res.array[i]);
	printf("\n\n");
	*/
	
	return res;
}

//檢查是否全0
int checkZero(longDouble res, int n) {
	//printf("%d, %d\n", res.point, n);
	for (int index = res.point-n; index < res.point; index++) 	//從 小數點-n 的低位開始檢查
		if (res.array[index]) return index+1;					//直到不為0為止
	return 0;	//全為0，回傳0
}

//輸出
void print(longDouble res, int n) {
	if (res.flag) printf("-");	
	
	int i, index;
	//輸出整數部份
	for (index = SIZE2-1; index > res.point; index--)					//從高位開始檢查
		if (res.array[index]) break;									//直到不為0為止
	for (i = index; i >= res.point; i--) printf("%d", res.array[i]);	//開始輸出，直到小數點的位置
	
	//輸出小數部份
	if (index = checkZero(res, n)) { //檢查是否全0
		printf(".");											//輸出小數點
		for (; i >= index-1; i--) printf("%d", res.array[i]);	//小數點的位置開始輸出
	}
	
	printf("\n");
}

int main(void) {
	int n;
	char str1[SIZE], str2[SIZE];
	for (int i = 0; i < SIZE; i++) str1[i] = str2[i] = 0;	//字串預設為0
	
	scanf("%s\n%s\n%d", str1, str2, &n);	//輸入
	
	//DEBUG
	/*
	printf("str1:\n");
	for (int i=0; i<SIZE; i++) printf("%d ", str1[i]);
	printf("\n\nstr2:\n");
	for (int i=0; i<SIZE; i++) printf("%d ", str2[i]);
	printf("\n\n");
	*/
	
	longDouble num1 = convert(str1);	//把 字串string 轉換成 自定義結構struct
	longDouble num2 = convert(str2);	//把 字串string 轉換成 自定義結構struct
	
	shift(&num1, &num2);	//移位，對準小數位
	
	print(add(num1, num2), n);		//輸出加法
	
	num2.flag = num2.flag? 0: 1;	//把num2的正負反轉，就是減法
	print(add(num1, num2), n);		//輸出減法
	
	num2.flag = num2.flag? 0: 1;	//把num2的正負還原
	print(mul(num1, num2), n);		//輸出乘法
	
	return 0;
}