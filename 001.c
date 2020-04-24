//	Created by L.H.Ming on 2020/03/10.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
001. 一元二次方程式

一元二次方程式，aX^2 + bx + c = 0，輸入a, b, c, 求 方程式的兩個實根。

---------------
輸入說明

第一個數(int) a
第二個數(int) b
第三個數(int) c

---------------
輸出說明

第一個實根 x1 = ((-b)+sqrt(b*b-4*a*c))/(2*a)
第二個實根 x2 = ((-b)-sqrt(b*b-4*a*c))/(2*a)

x1, x2 輸出到小數點第一位
print("%.1f" %x1);

---------------
Input
1
-2
1

Output
1.0
1.0

---------------
Input
1
-4
4

Output
2.0
2.0

*/

/*
	解法說明

	1.	分別輸入a, b, c到int
	2.	根據公式計算兩個實根
	3.	輸出兩個實根
	
*/

#include <stdio.h>
#include <math.h>

int main() {
	//初始化
    int a, b, c;
	
	//輸入
    scanf("%d%d%d", &a, &b, &c);
	
	//計算兩個實根
    float determinant = b*b-4*a*c;
    float x1 = ((-b)+sqrt(determinant))/(2*a);
    float x2 = ((-b)-sqrt(determinant))/(2*a);

	//輸出
    printf("%.1f\n%.1f", x1, x2);
	
	return 0;
}

