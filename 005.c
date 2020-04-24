//	Created by L.H.Ming on 2020/03/19.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
第二周 005
撲克牌
A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K
A~10 點數為 1~10，J, K, Q 為 0.5。
X, Y 兩個人各發三張撲克牌，加總點數越接近 10.5 的贏；超過 10.5 ，爆掉且分數為 0。
程式：
輸入：X, Y 兩個人的三張撲克牌。
輸出：兩個人的點數，以及A wins.或B wins.或It's a tie.。

Sample Input：
A
2
3
2
3
4
Sample Output：
6.0
9.0
B wins.

Sample Input：
A
2
3
A
2
3
Sample Output：
6.0
6.0
It's a tie.
*/

/*
	解法說明

	1.	使用迴囤，分別輸入兩位玩家的撲克牌
	2.	計算兩位玩家的得分
	3.	判斷是否爆分
	4.	輸出兩位玩家的得分及贏家
	
*/

#include <stdio.h>

//根據牌面轉換成分數
float card_to_point(char card) {
    if (card == 'A') return 1.0;
    else if (card == 'Q' || card == 'J' || card == 'K') return 0.5;
    else if (card == '1') {
        scanf("%*c");	//去掉第二個位
        return 10.0;
	} else return (card - '0');
}

int main(void) {
	//初始化
    float A_point = 0, B_point = 0;
    char card;
	
	//三張牌給第一位玩家
    for (int i=0; i<3; i++) {
        scanf("%c%*c", &card);
        A_point += card_to_point(card);
    }
	
	//三張牌給第二位玩家
    for (int i=0; i<3; i++) {
        scanf("%c%*c", &card);
        B_point += card_to_point(card);
    }
	
	//判斷是否爆分
    if (A_point > 10.5) A_point = 0;
    if (B_point > 10.5) B_point = 0;
	
	//輸出兩位玩家的得分
    printf("%.1f\n%.1f\n", A_point, B_point);
	
	//判斷誰贏
    if (A_point > B_point) printf("A wins.\n");
    else if (B_point > A_point) printf("B wins.\n");
    else printf("It's a tie.\n");	//平手

    return 0;
}