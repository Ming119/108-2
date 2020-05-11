//	Created by L.H.Ming on 2020/05/10.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
DF - expression是儲存圖片資訊的表達方式。
在一個n*n方陣中，若方格是白色記為0；黑色記為1；
若方格可分為更小方格(左上、右上、左下、右下)，則記2，再依序(左上→右上→左下→右下)記錄這四個方格的資訊。
以下圖為例 :
第一張圖全為白，所以輸出為0。
第二張圖全為黑，所以輸出為1。
第三張圖因為有黑有白，所以記為2，接著繼續切，從左上開始，全為白，記為0，再來右上，有黑有白繼續切，記為2，接著繼續從右上那塊往下做，從左上開始，全為白，記為0，再來右上(白)，記0，左下(黑)，記1，右下(白)，記0，接著回到外面那塊的左下(黑)，記1，再來右下(白)，記0。最後輸出為202001010。

□□□□
□□□□
□□□□
□□□□
0

■■■■
■■■■
■■■■
■■■■
1

□□|□□
□□|■□
--------
■■|□□
■■|□□
202001010

輸入：給定DF - expression的輸入、這張圖像寬度(必為2的非負整數次方)
輸出：這張圖中黑色格子的座標位置(輸出座標順序由左而右、由上到下，最左上為0,0)，如無黑色格子則輸出all white。

Sample Input
1
2

Sample Output
0,0
0,1
1,0
1,1
-------------------------------
Sample Input
202001010
4

Sample Output
1,2
2,0
2,1
3,0
3,1
*/

/
#include <stdio.h>

#define SIZE 64

int solve(int arr[][SIZE], char s[], int l, int r, int u, int d, int now) {
	//不是2，跟據0/1填入二維陣列
    if(s[now] - '0' != 2) {
        for (int i = l; i < r; i ++) for (int j = u; j < d; j ++) arr[j][i] = s[now] - '0';
        now++;
    } else {
        now ++;	
        now = solve(arr, s, l, (l+r)/2, u, (u+d)/2, now);	//左上
        now = solve(arr, s, (l+r)/2, r, u, (u+d)/2, now);	//右上
        now = solve(arr, s, l, (l+r)/2, (u+d)/2, d, now);	//左下
        now = solve(arr, s, (l+r)/2, r, (u+d)/2, d, now);	//右下
    }
    
    return now;
}

int main() {
	//初始化 & Input
	int arr[SIZE][SIZE];
	char s[SIZE*SIZE];
    int n, count =0;
    scanf("%s%d", s, &n);
	
	//初始化二維陣列
    for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) arr[i][j] = -1;
	
    solve(arr, s, 0, n, 0, n, 0);	//進入遞迴
	
	//Output
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            if(arr[i][j] == 1) printf("%d,%d\n", i, j); //找到白色，印出其位置
			else count ++;	//找到黑色
        }
    }
	
	//全黑
    if(count == n*n) printf("all white\n");
    
}