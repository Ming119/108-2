//	Created by L.H.Ming on 2020/03/10.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
003.工資計算

假設工作一小時x元(整數) ，而全部薪資所得的8%取到小數第一位是稅金，每個月勞保費為最低工資y元(整數)的5%取到小數第一位。
請分開輸入二個月工作時數(整數) 、還有x與 y。
輸出扣完稅與勞保後實際所得、勞保費、稅金。

---------------
Input
100
200
160
23000

Output
43010.0
1150.0
3840.0

---------------
Input
0
300
200
20000

Output
54200.0
1000.0
4800.0
*/

/*
	解法說明

	1.	分別輸入兩個月的工作時數，x及y到int
	2.	計算 稅金，勞保費，實際所得
	3.	輸出 實際所得，勞保費、稅金
	
*/

#include <stdio.h>

int main() {
	//初始化
	//m1 = 第一個月的工作時數，m2 = 第一個月的工作時數
	//x = 時薪，y = 最低工資
    int m1, m2, x, y;	
    m1 = m2 = x = y = 0;
	
	//輸入
    scanf("%d%d%d%d", &m1, &m2, &x, &y);
	
    float total = (m1 + m2) * x;	//全部薪資
    float tax = total * 0.08;			//稅金
    float fee = y * 0.05;				//勞保費
    float act_income = total - tax - fee;	//實際所得
	
	//輸出
    printf("%.1f\n%.1f\n%.1f", act_income, fee, tax);

    return 0;
}