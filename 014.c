//	Created by L.H.Ming on 2020/04/09.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
數位電路模擬II
模擬一個數位IC，內有回饋電路與紀錄器電路
輸入m 是二進位 8 位元，輸出是二進位 4 位元
輸入範圍從 00000000 到 11111111 (十進位 0~255)
回饋方式為 :
C(m) = m if m = 0 or m = 1 (十進位)
C(m) = C(m/2) if m 偶數(十進位)
C(m) = C((m+1)/2) if m 奇數(十進位)
例如 m=00001010(十進位 10)，則電路回饋依序為十進位 5, 3, 2, 1
C(10)= C(5)=C(3)=C(2)=C(1)=1，共回饋 4 次
紀錄器功能如下 :
給予回饋電路輸入 0, 1, 2, ..., m，並記錄每次回饋次數，R(0), R(1), ..., R(m)。例如R(10)=4 [C(10)的回饋次數]
會累加所有回饋電路的回饋次數。Out(10) = R(0)+R(1)+...+R(10)

-------------
輸入說明:
二進位 8 bit 位元
第一行是第一個測試案例資料
接著是一行 0 分隔測試資料
第三行是第二個測試案例資料
....
最後 -1 結束

-------------
輸出說明:
二進位 11 bit 位元
每一行是一個測試案例資料的結果

-------------
Sample Input:
00000000
0
11111111
0
10101010
-1
-------------
Sample Output:
00000000000
11011111001
10001010001

-------------
Sample Input:
00001010
0
01100100
-1
-------------
Sample Output:
00000011001
01000111101
*/

/*
	解法說明

	1.	輸入八位元二進位
	2.	轉換成10進制
	3.	使用遞迴計算回饋次數
	4.	加總回饋次數
	4.	輸出回饋次數總和的二進制
	5.	輸入-1時退出迴圈
	
*/

#include <stdio.h>
#include <math.h>

//回饋次數遞迴
int C(int m, int count) {
    if (m==0 || m==1) return count;
    count++;
    if (m%2==0) return C(m/2, count);
    if (m%2==1) return C((m+1)/2, count);
}

//回饋次數總和遞迴
int R(int m, int count) {
    if (m==-1) return count;
    count += C(m, 0);
    return R(m-1, count);
}

//10轉2
long long dec_to_bin(int num) {
    long long conv_num = 0;
    for (long long i=1; num!=0; i*=10) {
        conv_num += (num%2)*i;
        num /= 2;
    }
    return conv_num;
}

//2轉10
int bin_to_dec(long num) {
    int conv_num = 0;
    for (int i=0; num!=0; i++) {
        conv_num += (num%10)*pow(2,i);
        num /= 10;
    }
    return conv_num;
}

int main(void) {
	//初始化
    int con, control = 0;
    long num;
	
	//-1時退出迴圈
    while(control != -1){
        scanf("%ld\n%d", &num, &control);	//輸入
		
        con = R(bin_to_dec(num), 0);	//進入遞迴
		
		//補0
        if (con<2){printf("0000000000%lld\n", dec_to_bin(con));}
        else if(con<4){printf("000000000%lld\n", dec_to_bin(con));}
        else if(con<8){printf("00000000%lld\n", dec_to_bin(con));}
        else if(con<16){printf("0000000%lld\n", dec_to_bin(con));}
        else if(con<32){printf("000000%lld\n", dec_to_bin(con));}
        else if(con<64){printf("00000%lld\n", dec_to_bin(con));}
        else if(con<128){printf("0000%lld\n", dec_to_bin(con));}
        else if(con<256){printf("000%lld\n", dec_to_bin(con));}
        else if(con<512){printf("00%lld\n", dec_to_bin(con));}
        else if(con<1024){printf("0%lld\n", dec_to_bin(con));}
        else {printf("%lld\n", dec_to_bin(con));}
    }
	
    return 0;
}

