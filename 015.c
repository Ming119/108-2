//	Created by L.H.Ming on 2020/04/11.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
分數四則運算

計算兩個分數四則運算 。

輸入說明:
----------------------------
輸入四行，第一、二行各代表一個分數，第三行代表數學運算符號，第四行代表是否繼續運算

--------------------
輸出說明:
----------------------------
輸出分數結果

**輸入分子可能大於分母**
若有輸入分數的分母為0，則輸出ERROR。
若分數大於1，則分數部分要加括號，如一又六分之一輸出為1(1/6)
若為負數，負號在最前面。
若輸出為0，則顯示0
輸出的結果必須化簡為最簡分數
----------------
Sample input:
----------------
1/2
2/3
+
y
-1/4
1/5
*
n

----------------
Sample output:
----------------
1(1/6)
-1/20

----------------
Sample input:
----------------
2/0
2/3
-
n

----------------
Sample output:
----------------
ERROR
*/

/*
	解法說明

	1.	輸入運算元及運算子
	2.	根據運算子進行運算
	3.	化簡約分
	4.	輸出結果
	5.	如果繼續，重複步驟1-4
	
*/

#include <stdio.h>
#include <math.h>

//最大公倍數GCD
int GCD (int x, int y) {return y?GCD(y, x%y):x;}

//運算
int operation(int n1, int n2, int n3, int n4, char op) {
    int numerator, denominator;
	
    if (op == '+') {	//加法
        numerator = (n1*n4 + n3*n2);
        denominator = n2 * n4;
    } else if (op == '-') {	//減法
        numerator = n1*n4 - n3*n2;
        denominator = n2 * n4;
    } else if (op == '*') {	//乘法
        numerator = n1*n3;
        denominator = n2 * n4;
    } else if (op == '/') {	//除法
        numerator = n1*n4;
        denominator = n2 * n3;
    }
	
    simplify(numerator, denominator);
}

//化簡
int simplify(int n1, int n2) {
    int s = GCD(n1,n2);	//找出最大公倍數GCD
	
    n1 /= s;
    n2 /= s;
	
    if (n1*n2<0) printf("-");	//結果為負數
	
    n1 = abs(n1);
    n2 = abs(n2);
	
    if (n1==0) printf("0\n");	//分子為0
    else if (n1 < n2) printf("%d/%d\n", n1, n2);	//結果為真分數
    else if (!(n1%n2)) printf("%d\n", n1/n2);	//結果為整數
    else if (n2 < n1)printf("%d(%d/%d)\n", n1/n2, n1%n2, n2);	//結果為帶分數
}

int main(void) {
    char op, contin;
    int num1, num2, num3, num4;
	//輸入
    while (contin != 'n') {
        scanf("%d/%d%d/%d%*c%c%*c", &num1, &num2, &num3, &num4, &op);	//num1 = 分子1，num2 = 分母1，num3 = 分子2，num4 = 分母2，op = 運算子
		
        if (num2==0 || num4==0) {	//分母為0
            printf("ERROR");
            break;
        }
        operation(num1, num2, num3, num4, op);
		
		//是否繼續
        scanf("%c%*c", &contin);
    }
    return 0;
}
