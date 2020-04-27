//  Created by L.H.Ming on 2020/04/09.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
撲克牌
A, 2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K
A~10 點數為 1~10，J, K, Q 為 0.5。
電腦與玩家各隨機發撲克牌，加總點數接近 10.5 則贏。
超過 10.5 爆掉分數為 0 且該方不得繼續要牌。
任一回合並未要牌的一方，失去要牌權利。
程式：
電腦發一張撲克牌給玩家，玩家可選擇要牌或不要牌。
電腦發一張撲克牌給電腦，電腦判斷是否停發牌。
以下情況電腦才會要牌：1. 總點數比玩家小 或 2. 總點數8點以下(含8點)
輸出電腦與玩家的點數，以及電腦贏或玩家贏或平手。(平手輸出：It's a tie)

輸入範例註解：
A 先發一張給給玩家(玩家獲得A)
J 再發一張給電腦(電腦獲得J)
Y 玩家選擇要牌
9 發一張給玩家(玩家獲得9)
8 電腦牌面0.5點，未超過8點，再發一張給電腦(電腦a獲得8)
N 玩家選擇不要牌
5 電腦牌面8.5，低於玩家的10，因此再抽(獲得5)

輸出範例註解：
10.0 vs. 0.0
player wins

Sample Input：
4
6
Y
A
2
Y
5
J
N
2

Sample Output：
10.0 vs. 10.5
computer wins

Sample Input：
5
5
Y
5
J
Y
K
5
N

Sample Output：
10.5 vs. 10.5
It's a tie
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
float conv(char card) {
    if (card == 'A') return 1.0;
    else if (card == 'Q' || card == 'J' || card == 'K') return 0.5;
    else if (card == '1') {
        scanf("%*c");	//去掉第二個位
        return 10.0;
    } else return (card - '0');
}
	
int main() {
	//初始化
    char c, hit;
    float player_point, dealer_point;
    int player_flag, dealer_flag;

    player_point = dealer_point = 0.0;
    player_flag = dealer_flag = 1;
	
	//輸入
    scanf("%c%*c", &c);
    player_point += conv(c);
    scanf("%c%*c", &c);
    dealer_point += conv(c);
	
	//如果條件符合，繼續發牌
    while (player_flag || dealer_flag){
	//玩家
        if (player_flag) {
            scanf("%c%*c", &hit);	//是否繼續拿牌
            if (hit == 'Y') {
                scanf("%c%*c", &c);	//拿牌
                player_point += conv(c);
                if (player_point > 10.5) {	//爆分
                    player_point = 0;
                    break;	//退出迴圈
                }
            } else if (hit =='N') player_flag = 0;	//不再拿牌
        }
		
	//電腦
        if (dealer_flag) {
            if (dealer_point < player_point || dealer_point <= 8) {
                scanf("%c%*c", &c);	//拿牌
                dealer_point += conv(c);
                if (dealer_point > 10.5) {	//爆分
                    dealer_point = 0;	
                    break;	//退出迴圈
                }
            } else dealer_flag = 0;	//達到不再拿牌的條件
        }
    }
	
    printf("%.1f vs. %.1f\n", player_point, dealer_point);	//輸出兩位玩家的得分
	
	//判斷誰贏
    if (player_point > dealer_point) printf("player wins");
    else if (dealer_point > player_point) printf("computer wins");
    else printf("It's a tie");	//平手
	
    return 0;
}
