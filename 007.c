//	Created by L.H.Ming on 2020/03/25.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
求 1~N 之間的質數
質數是除了 1 與本身之外，無法被其他數整除的數。
可利用巢狀迴圈計算 1~100 間任一個數字，是否會被比它小的數字 (從 2 開始) 整除，會整除的就不是質數。找不到可整除的，就是質數。
質數未達三個造成無輸出情況時則輸出字串："含括的質數未達三個"
輸入：100以內任意自然數
輸出：質數每三個輸出一個

Sample Input：
5

Sample Output：
5
----------------------------
Sample Input：
23

Sample Output：
5
13
23
----------------------------
Sample Input：
3

Sample Output：
含括的質數未達三個
*/

/*
	解法說明

	1.	輸入100以內任意自然數
	2.	使用線性搜尋Linear Search，判斷是否質數
	3.	每三個輸出一個 / 質數未達三個
	
*/

#include <stdio.h>

//判斷是否質數
int isPrime(int n) {
    for (int i=2; i<n; i++){
        if (!(n%i)) return 0; //不是質數，回傳0
    }
    return 1;	//是質數，回傳1
}
	
int main() {
    int num, counter = 0;	//初始化
	
    scanf("%d", &num);	//輸入
	
    if (num > 1 && num < 101){	//100以內
        for(int i=2; i<=num; i++) {
            if (isPrime(i)) {
                counter ++;
                if (!(counter%3)) printf("%d\n", i);	//每三個輸出一個
            }
        }
		
		//質數未達三個
        if (counter < 3) printf("含括的質數未達三個\n");	
    }
	
	return 0;
}
