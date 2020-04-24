//	Created by L.H.Ming on 2020/03/10.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
002. 跑壘問題

輸入棒球隊球員打擊結果，計算出隊得分。假設球員打擊情況：
安打：以1, 2, 3 和 H代表一、二、三和全(四)壘打。
出局：以 O表示 (OUT)。
簡化版的規則如下：
球場 上有四個壘包， 稱為本壘、一、二和三壘。
本壘握球棒打的稱「擊球員」 ，在另外三個壘包的稱為「跑員」。
當擊球員打擊「安打」時， 擊球員與跑壘員可移動；「出局」時，跑壘員不動，擊球員離場換下一位。
比賽開始由第 1位打擊，接著2, 3, 4, 5位球員。
打出 K 壘打時，場上球員(擊球員和跑壘員)會前進 K個壘包。本壘到一壘，接著二、三壘，最後回到本壘。回到本壘可得 1分。
每達到三個出局數時，壘包清空(跑壘員都得離開)，重新開始。
輸入5位打者打擊資料，輸出最後一、二、三壘狀況，有人為1，沒人為0。

---------------
Input
1
1
O
O
1

Output
1
1
1

---------------
Input
1
H
O
3
1

Output
1
0
0
*/

/*
	解法說明

	1.	使用迴圈分別輸入5位球員的打擊情況
	2.	根據輸入打擊情況跑壘
	3.	輸出最後一、二、三壘的狀況
	
*/

//	方法1，使用位移儲存壘包資訊
#include <stdio.h>

int main() {
	//初始化
    char h;
    int num, base, out;
	num = base = out = 0;

    for (int i=0; i<5; i++) {
        scanf("%c%*c", &h);
        if (h == 'H') num = 4;
        else if (h == '3') num = 3;
        else if (h == '2') num = 2;
        else if (h == '1') num = 1;
        else num = 0;
		
        if (num == 0) out++;	//出局
		//跑壘
        else {
			base = (base << num) | (1 << (num-1));	//使用位移儲存壘包資訊
			base = base & 7;	//7 = 0111_2
        }
		
		//三振出局，清空壘包
        if (out == 3) {
            out = 0;
            base = 0;
		}
	}
   
	//輸出
	printf("%d\n%d\n%d", base & 1, (base>>1) & 1, (base>>2) & 1);
	
	return 0;
}

//	方法2，使用陣列儲存壘包資訊
/*
#include <stdio.h>

int main() {
	//初始化
    char h;
    int num, out = 0;
    int base[4] = {0,0,0,0};	//四個壘包

    for (int i=0; i<5; i++) {	//5位球員
        scanf("%c%*c", &h);		//輸入打擊情況
		
		//根據輸入打擊情況跑壘
        if (h == 'H') num = 4;
        else if (h == '3') num = 3;
        else if (h == '2') num = 2;
        else if (h == '1') num = 1;
        else num = 0;

        if (num == 0) out++;	//出局
		//跑壘
        else {
            base[0] = 1;	//球員進入本壘
            for (int x = 3; x >= 0; x--) {
                if (base[x] == 1) {
                    if (x + num <= 4) base[x + num] = 1;
                    base[x] = 0;
                }
			}
        }
		
		//三振出局，清空壘包
        if (out == 3) {
            out = 0;
            base[0] = base[1] = base[2] = base[3] = 0;
		}
	}
   
	//輸出
	printf("%d\n%d\n%d", base[1], base[2], base[3]);
	
	return 0;
}
*/