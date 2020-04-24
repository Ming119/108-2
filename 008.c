//	Created by L.H.Ming on 2020/03/25.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
將Code寫成 二個function，每一個function使用一層迴圈
輸入圖案編號與層數，輸出各種圖形

輸入：選擇欲輸出圖形模式及參數
輸出：輸出預期的圖形

Sample Input：
1
5

Sample Output：
1
12
123
1234
12345
54321
4321
321
21
1
1
22
333
4444
55555
------------------------------
Sample Input：
2
5

Sample Output：
1
121
12321
1234321
123454321
___1___
__212__
_32123_
4321234
4321234
_32123_
__212__
___1___
*/

/*
	解法說明

	1.	分別輸入圖形模式及參數
	2.	根據圖形模式及參數 輸出圖形
	3.	使用嵌套迴圈 Nested Loop
	
*/

#include <stdio.h>

//圖形模式1
void p1(int n) {
	for(int i=1; i<=n; i++) {
        for(int j=1; j<=i; j++) printf("%d", j);
        printf("\n");
    }
    for(int i=n; i>0; i--) {
        for(int j=i; j>0; j--) printf("%d", j);
        printf("\n");
    }
    for(int i=1; i<=n; i++) {
        for(int j=0; j<i; j++) printf("%d", i);
        printf("\n");
   }
}

//圖形模式2
void p2(int n) {
	for(int i=1; i<n+1; i++) {
        for(int j=1; j<i; j++) printf("%d", j);
        for(int j=i; j>0; j--) printf("%d", j);
        printf("\n");
    }
    for(int i=1; i<n; i++) {
        for(int j=1; j<n-i; j++) printf("_");
        for(int j=i; j>1; j--) printf("%d", j);
        for(int j=1; j<=i; j++) printf("%d", j);
        for(int j=1; j<n-i; j++) printf("_");
        printf("\n");
    }
    for(int i=1; i<n; i++) {
        for(int j=1; j<i; j++) printf("_");
        for(int j=n-i; j>1; j--) printf("%d", j);
        for(int j=1; j<=n-i; j++) printf("%d", j);
        for(int j=1; j<i; j++) printf("_");
        printf("\n");
    }
}

int main() {
	//初始化
    int patten, num;
	//輸入
    scanf("%d\n%d", &patten, &num);
	
	//根據圖形模式呼叫函數
    if (patten == 1) p1(num);
    else if (patten == 2) p2(num);
	
    return 0;
}
