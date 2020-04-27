//	Created by L.H.Ming on 2020/04/09.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
數位電路模擬I
模擬一個數位IC，內有回饋電路與紀錄器電路
輸入m 是二進位 8 位元，輸出是二進位 4 位元
輸入範圍從 00000000 到 11111111 (十進位 0~255)
回饋方式為 :
C(m) = m if m = 0 or m = 1 (十進位)
C(m) = C(m/2) if m 偶數(十進位)
C(m) = C((m+1)/2) if m 奇數(十進位)
例 :
m=00001010(十進位 10)，則電路回饋依序為十進位 5, 3, 2, 1
C(10)= C(5)=C(3)=C(2)=C(1)=1，共回饋 4 次
紀錄器會記錄回饋電路的回饋次數
R(m) = [C(m) 的回饋次數]，例如 R(10) = 4
若數位IC的輸入為m=00001010(十進位 10) ，因回饋電路的回饋次數為4，則此數位IC輸出為 0100 (十進位 4)

-------------
輸入說明 :
二進位 8 bit 位元
第一行是第一個測試案例資料
接著是一行 0 分隔測試資料
第三行是第二個測試案例資料
....
最後 -1 結束

-------------
輸出說明 :
二進位 4 bit 位元
每一行是一個測試案例資料的結果

-------------
Sample Input:
00000000
0
11111111
0
00000001
0
10000000
0
00111111
-1
-------------
Sample Output:
0000
1000
0000
0111
0110

-------------
Sample Input:
00001010
0
01100100
-1
-------------
Sample Output:
0100
0111

*/

/*
	解法說明

	1.	輸入八位元二進位
	2.	轉換成10進制
	3.	使用遞迴計算回饋次數
	4.	輸出回饋次數的二進制
	5.	輸入-1時退出迴圈
	
*/

#include <stdio.h>

//回饋次數遞迴
int C(int m, int count) {
    	if (m==0 || m==1) return count;
	count++;
   	if (m%2==0) return C(m/2, count);
   	if (m%2==1) return C((m+1)/2, count);
}

//10轉2
int dec_to_bin(int num) {
    int conv_num = 0;
	
    for (int i=1; num!=0; i*=10) {
        conv_num += (num%2)*i;
        num /= 2;
    }
	
    return conv_num;
}

//2轉10
int bin_to_dec(int num) {
    int conv_num = 0;
	
    for (int i=0; num!=0; i++) {
        conv_num += (num%10)*pow(2,i);
        num /= 10;
    }
	
    return conv_num;
}

int main(void) {
	//初始化
    int num, con, control = 0;
	
	//-1時退出迴圈
    while(control != -1){
        scanf("%d\n%d", &num, &control);	//輸入
		
        con = C(bin_to_dec(num), 0);	//進入遞迴
		
		//補0
        if (con<2){printf("000%d\n", dec_to_bin(con));}
        else if(con<4){printf("00%d\n", dec_to_bin(con));}
        else if(con<8){printf("0%d\n", dec_to_bin(con));}
        else {printf("%d\n", dec_to_bin(con));}
    }
	
    return 0;
}
