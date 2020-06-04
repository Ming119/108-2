//	Created by L.H.Ming on 2020/06/05.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
輸入長整數運算的模式，
以1代表長整數相加；2代表長整數相減；3代表長整數相乘。
再輸入兩個20位數以上的整數做運算，
並輸出計算過後的結果。

**長整數可能為負數**

sample input:
1
10000000000000000001
99999999999999999999

sample output:
110000000000000000000

--------------------------------

sample input:
2
-45112365412452139545
13245645215412645641

sample output:
-58358010627864785186

--------------------------------

sample input:
3
11111222221111122222
-10000123452000012345

sample output:
-111113593913716999998298869960803830590

--------------------------------

sample input:
3
-10000100000000000001
-12121212121212121212

sample output:
*/

#include <stdio.h>
#include <string.h>

#define SIZE 128

//自定義結構struct
typedef struct longInt{
	int array[SIZE];	//整數陣列
	int flag;			//是否為負
}	longInt;

//把 字串string 轉換成 自定義結構struct
longInt convert(char *str) {
	longInt res;
	for (int i = 0; i < SIZE; i++) 	res.array[i] = 0;	//整數陣列預設為0
	
	res.flag = str[0] == '-'? 1: 0;		//檢查是否為負，記錄在flag
	
	for(int l = strlen(str)-1, i = 0; l >= res.flag; l--)	res.array[i++] = str[l] - '0';	//char to int, 放到整數陣列
	
	//DEBUG
	/*
	printf("res.flag = %d\nres.array:\n", res.flag);
	for (int i=0; i<SIZE; i++) printf("%d ", res.array[i]);
	printf("\n\n");
	*/
	
	return res;
}

//加法及減法
longInt add(longInt num1, longInt num2) {
	longInt res = convert("0");
	
	if (num1.flag == num2.flag) {	//正正 或 負負
		res.flag = num1.flag;		//正加正必為正，負加負必為負
		
		//加法算法
		for(int i = 0; i < SIZE; i++)  {
			res.array[i] += num1.array[i] + num2.array[i];
			//進位
			if(res.array[i] > 9) {		//本位大於9
				res.array[i] -= 10;		//本位減10
				res.array[i+1] += 1;	//下位加10
			}
		}
		
	}	else 	if (num1.flag && !num2.flag) {	//num1為負, num2為正
		
		//比較大小	註：for迴圈的內容跟L97, L116的條件判斷有關
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
		
	}	else if (!num1.flag && num2.flag)	return add(num2, num1); //num1為正, num2為負, 要把num1 num2反過來算 (Goto L97)
	
	//DEBUG
	/*
	printf("res.flag = %d\nres.array:\n", res.flag);
	for (int i=0; i<SIZE; i++) printf("%d ", res.array[i]);
	printf("\n\n");
	*/
	
	return res;
}

//減法
longInt sub(longInt num1, longInt num2) {
	//把num2的正負反轉，就是減法
	num2.flag = num2.flag? 0: 1;
	return add(num1, num2);
}

//乘法
longInt mul(longInt num1, longInt num2) {
	longInt res = convert("0");
	
	if (num1.flag != num2.flag)	res.flag = 1;	//正負得負
	//乘法算法
	for(int i = 0; i < SIZE/2; i++) {
		for(int j = 0; j < SIZE/2; j++) {
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
	printf("res.flag = %d\nres.array:\n", res.flag);
	for (int i=0; i<SIZE; i++) printf("%d ", res.array[i]);
	printf("\n\n");
	*/
	
	return res;
}

//輸出
void print(longInt res) {
	if (res.flag) printf("-");
	
	int index;
	for (index = SIZE-1; index >= 0; index--)					//從高位開始檢查
		if (res.array[index] != 0)	break;						//直到不為0為止
	for (int i = index; i >=0; i--)	printf("%d", res.array[i]);	//開始輸出，直到小數點的位置
	printf("\n");
}

int main(void) {
	int mode;
	char str1[SIZE], str2[SIZE];
	for (int i = 0; i < SIZE; i++) str1[i] = str2[i] = 0;	//字串預設為0
	
	scanf("%d%s%s", &mode, str1, str2);	//輸入
	
	//DEBUG
	/*
	printf("str1:\n");
	for (int i=0; i<SIZE; i++) printf("%d ", str1[i]);
	printf("\n\nstr2\n");
	for (int i=0; i<SIZE; i++) printf("%d ", str2[i]);
	printf("\n");
	*/
	
	longInt num1 = convert(str1), num2 = convert(str2);	//把 字串string 轉換成 自定義結構struct
	
	switch(mode){
		case 1:	print(add(num1, num2));	break;	//加法
		case 2:	print(sub(num1, num2));	break;	//減法
		case 3:	print(mul(num1, num2));	break;	//乘法
	}
	
	return 0;
}