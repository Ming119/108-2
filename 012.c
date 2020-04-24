//	Created by L.H.Ming on 2020/04/23.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
葛雷碼 (Gray code)
反射二進位編碼-葛雷碼 (Gray code)，是編碼成兩個連續的不同位元
其編碼規則如下
G_1 = {0, 1}
G_1_r = {1, 0}
G_n = {0G_(n-1), 1G_(n-1)_r }
[G_n_r 是 G_n 的逆向順序]
例 :
G_2 = {0G_1, 1G_1_r} = {00, 01, 11, 10}
G_2_r = {10, 11, 01, 00}

-------------
輸入說明 :
第一行是一個測試案例資料，整數 n k
n代表Gray code的位元數
k代表G_n中的第幾個元素
接著是一行 0 分隔測試資料
第三行是第二個測試案例資料
....
最後 -1 結束

-------------
輸出說明 :
二進位 Gray code
每一行是一個測試案例資料的結果

-------------
Sample Input:
1 1
0
2 3
0
3 6
0
4 12
-1
-------------
Sample Output:
1
10
101
1010

-------------
Sample Input:
5 3
0
6 10
-1
-------------
Sample Output:
00010
001111
*/

/*
	解法說明

	1.	輸入位數n 及 元素k
	2.	使用遞迴輸出葛雷碼
	3.	輸入-1時退出迴圈
	
*/

#include <stdio.h>
#include <math.h>

//葛雷碼 Gray Code
int Gray_Code(int n, int k) {
    if (n==1) return k;
    if (k<pow(2,n-1)){
        printf("0");
        return Gray_Code(n-1, k);	//遞迴 Recursion
    }
    if (k>=pow(2,n-1)) {
        printf("1");
        return Gray_Code(n-1,pow(2,n)-1-k);	//遞迴 Recursion
    }
}

int main(void) {
	//初始化
    int n, k, contin = 0;
	
	//-1時退出迴圈
    while(contin != -1){
        scanf("%d%d%d", &n, &k, &contin);	//輸入
        printf("%d\n", Gray_Code(n, k));	//輸出
    }
	
    return 0;
}
