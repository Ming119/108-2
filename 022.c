//	Created by L.H.Ming on 2020/05/10.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
檢查10*10五子棋可以構成5個連為一線的位置。1表示有放棋子，0表示沒有放棋子
給定指定盤面，於特定座標位置下棋(即該位置0變 1 )可以使五子連成一線，並且列出所有可能座標位置

輸入範例：
(棋盤盤面與以0和1表示之棋子分布)
(範例會以全形的０及１方便同學理解盤面分布，實際輸入仍為半形)
輸出範例：
所有連成五子一線之座標的可能，若無法連成五子一線，則輸出"impractical attempt!"

Sample Input：
０　０　０　０　０　０　０　０　１　０
０　０　０　０　０　０　１　１　０　０
０　０　０　０　０　０　１　０　０　０
０　０　０　０　０　０　１　１　１　１
０　０　０　０　１　０　１　０　０　０
０　０　０　０　０　０　０　０　０　０
０　０　０　１　０　０　０　０　０　０
０　０　０　１　０　０　０　０　０　０
０　０　１　１　１　１　０　０　０　０
０　０　０　１　０　０　０　０　０　０

0 0 0 0 0 0 0 0 1 0
0 0 0 0 0 0 1 1 0 0
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 0 1 0 1
0 0 0 0 1 0 1 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0
0 0 1 0 1 1 0 0 0 0
0 0 0 1 0 0 0 0 0 0

0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 1 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0

Sample Output：
0 6
3 5
5 3
5 6
8 1
8 6
--------------------------------------------------------
Sample Input：
０　０　０　０　０　０　１　０　０　０
０　０　０　０　０　０　０　０　０　０
０　０　０　０　０　０　０　０　０　０
０　０　０　０　０　１　０　０　０　０
０　０　０　０　０　０　０　０　０　０
０　０　０　１　０　０　１　０　０　０
０　０　０　０　０　０　０　０　０　０
０　０　０　０　０　０　０　０　０　０
０　１　０　０　０　０　１　０　０　０
０　０　０　０　０　０　０　０　０　０

Sample Output：
impractical attempt!
*/

#include <stdio.h>

#define SIZE 10

int getPossibility(int arr[SIZE][SIZE]) {
	int x, y, i, j, countSpace, countPiece, countPossibility, tempX, tempY;
	countSpace = countPiece = countPossibility = 0;
	tempX = tempY = -1;
	
	//直
	for (y = 0; y < SIZE-4; y ++) {
		for (x = 0; x < SIZE; x ++) {
			countPiece = countSpace = 0; tempY = -1;
			for (i = y; i < y+5; i ++) {
				if (arr[i][x] == 1) countPiece ++;
				else {
					countSpace ++; tempY = i;
				}
				if (countSpace == 2) break;
			}
			if (countPiece == 4) {
				if (tempY == -1) arr[i-1][x] = 2;
				else arr[tempY][x] = 2;
				countPossibility ++;
			}
		}
	}
	
	//橫
	for (y = 0; y < SIZE; y ++) {
		for (x = 0; x < SIZE-4; x ++) {
			countPiece = countSpace = 0; tempX = -1;
			for (j = x; j < x+5; j ++) {
				if (arr[y][j] == 1) countPiece ++;
				else {
					countSpace ++; tempX = j;
				}
				if (countSpace == 2) break;
			}
			if (countPiece == 4) {
				if (tempX == -1) arr[y][j-1] = 2;
				else arr[y][tempX] = 2;
				countPossibility ++;
			}
		}
	}

	//斜
	for (y = 0; y < SIZE-4; y ++) {
		for (x = 0; x < SIZE-4; x ++) {
			
			countPiece = countSpace = 0; tempX = tempY = -1;
			for (i = y, j = x; i < y+5 && j < x+5; i ++, j ++) {
				if (arr[i][j] == 1) countPiece ++;
				else {
					countSpace ++; tempY = i; tempX = j;
				}
				if (countSpace == 2) break;
			}
			if (countPiece == 4) {
				if (tempX == -1) arr[i-1][j-1] = 2;
				else arr[tempY][tempX] = 2;
				countPossibility ++;
			}
			
			countPiece = countSpace = 0; tempX = tempY = -1;
			for (i = y, j = x+4; i < y+5 && j >= x; i ++, j --) {
				if (arr[i][j] == 1) countPiece ++;
				else {
					countSpace ++; tempY = i; tempX = j;
				}
				if (countSpace == 2) break;
			}
			if (countPiece == 4) {
				if (tempX == -1) arr[i-1][j+1] = 2;
				else arr[tempY][tempX] = 2;
				countPossibility ++;
			}
			
		}
	}

	return countPossibility;
}

int main(void) {
	////初始化 & Input
	int checkerboard[SIZE][SIZE];
	for (int i = 0; i < SIZE; i ++) for (int j = 0; j < SIZE; j ++) scanf("%d", &checkerboard[i][j]);
	
	int possibility = getPossibility(checkerboard);
	
	//Output
	if (!(possibility)) printf("impractical attempt!\n");
	else for (int i = 0; i < SIZE; i ++) for (int j = 0; j < SIZE; j ++) if (checkerboard[i][j] == 2) printf("%d %d\n", i, j);
	
	return 0;
}
