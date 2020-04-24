//	Created by L.H.Ming on 2020/4/25.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
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

輸入格式
每組測試資料固定有十一行。
第一到九行，依照球員順序， 每一行代表位球員的打擊資訊 。每一行開始有一個正整數 a (1<=a<=5)，代表球員總共打 a 次。接下來有 a 個字元，依序代表每次打擊結果。資料間均以一個空白字元隔開。球員打擊資訊不會有錯誤與缺漏。
第十行有一個正整數 b (1<=b<=27)，表示想計算當總出局數累計到 b 時，該球隊的得分 。輸入打擊資訊中至少包含 b個出局。
第十一行有一個正整數 m (1<=m<=9)，表示想計算第m個球員在總計第 b個出局數時的安打數與到達本壘的次數。


輸出格式
計算在總計第b個出局數發生時的總得分。
計算第m個球員在總計第 b個出局數的安打數與到達本壘的次數。


sample input:
5 1 1 O O 1
5 1 2 O O O
4 O H O 1
4 O O O H
4 1 1 1 1
4 O O 3 O
4 1 O O O
4 O O 2 2
4 3 O O O
3
4

sample output:
0
0,0

------------------

sample input:
5 1 1 O O 1
5 1 2 O O O
4 O H O 1
4 O O O H
4 1 1 1 1
4 O O 3 O
4 1 O O O
4 O O 2 2
4 3 O O O
6
7

sample output:
5
1,1
*/

/*
	解法說明

	1.	球員的打擊資訊輸入到二維char陣列，b及m輸入到int
	2.	使用迴圈，在第b個出局數退出迴圈
		a.	檢查該局是否出局		=>	出局數+1
		b.	檢查該局是否第b個出局數	=>	退出迴圈
		c.	檢查該局是否三振		=>	清空壘包
	3.	根據打擊情況跑壘，回傳該局得分
	4.	輸出在第b個出局數時的總得分
	5.	輸出第m個球員在第b個出局數時的安打數及到達本壘的次數
	
*/

#include <stdio.h>

//跑壘
int movement(int *base, int data[][2], int player, int step) {	//base = 當前賽況，player = 當前球員，step = 移動步數
	int score = 0;	//記錄本回合分數
	base[3] = player;	//當前球員進入本壘
    data[player-1][0] ++;	//纍計當前球員的打擊數
    
    while(step--) {
		if(base[0]) {
            data[base[0]-1][1] ++;	//回到本壘的球員纍計加分 //註：回到本壘的球員不一定是當前球員
            score ++;	//本回合纍計加分
        }
		
		//一步一步移動
        for(int x = 0; x < 4; x++) {
            if (x + 1 < 4) base[x] = base[x + 1];
            else base[x] = 0; 
        }
    }
	
	return score;
}

int main(void) {
	int a, b, m, countOut, totalOut, score;
	countOut = score = 0;
	int data[9][2], base[4] = {0,0,0,0};	//data[*][0] = 球員的安打數，data[*][1] = 球員到達本壘的次數
	char c[9][5];
	
	//初始化
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 5; j++) c[i][j] = '0';
		for (int j = 0; j < 2; j++) data[i][j] = 0;
	}
	
	//輸入
	for (int i = 0; i < 9; i++) {
		scanf("%d%*c", &a);	//讀取球員的打擊次數
		for (int j = 0; j < a; j++) scanf("%c%*c", &c[i][j]);
	}
	scanf("%d\n%d", &b, &m);
	
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 9; i++) {
			int t = c[i][j];
			if (t == 'O') {	//纍計出局
				totalOut ++;
				countOut ++; 	
			if (countOut == b) {	//出局數達到b則輸出、結束程式
				printf("%d\n", score);
                printf("%d,%d\n", data[m-1][0], data[m-1][1]);
				return 0;
			}
			if (countOut == 3) {		//出局數纍積到3， 清空壘包
				for (int x = 0; x <4; x++) base[x] = 0;
				countOt = 0;
			}
			
			//根據打擊情況跑壘
			if (t == 'H') score += movement(base, data, i+1, 4);
			if (t == '3') score += movement(base, data, i+1, 3);
			if (t == '2') score += movement(base, data, i+1, 2);
			if (t == '1') score += movement(base, data, i+1, 1);
		}
	}
	
	return 0;
}
	