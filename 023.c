//	Created by L.H.Ming on 2020/05/21.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
賴先生騎腳踏車挑戰一日N塔，N<10。
每一個塔位在編號 1, 2, 3, ...,N 城市中。
兩兩個城市都有一段距離的公路相連。
請計算 "從第 1 個" 城市出發，"騎過每一個" 城市的 "最短距離"。
例如 :
N = 5，以下是兩兩城市之間公路的距離 :

--- C1 C2 C3 C4 C5
C1 0 4 2 3 6
C2 4 0 3 1 4
C3 2 3 0 2 5
C4 3 1 2 0 3
C5 6 4 5 3 0

城市 C1 和城市 C1 的距離是 0 (同一個地方)，
城市 C1 和城市 C2 的距離是 4，
城市 C1 和城市 C3 的距離是 2，
城市 C1 和城市 C4 的距離是 3，
城市 C1 和城市 C5 的距離是 6，
等等...以此類推

則從城市 1 出發，騎完所有城市的距離最短是，經由 13245 的距離 = 2+3+1+3= 9。
----------------------------------------------------------------------------------
輸入說明
第 1 筆資料是 N，
第 2 筆資料是第 1 個城市和其他城市的公路距離。
第 3 筆資料是第 2 個城市和其他城市的公路距離。
....
第 N+1 筆資料是第 N 個城市和其他城市的公路距離。
輸出說明
輸出從第 1 個城市出發，騎完所有城市最短距離。
----------------------------------------------------------------------------------
sample input :
5
0 4 2 3 6
4 0 3 1 4
2 3 0 2 5
3 1 2 0 3
6 4 5 3 0

sample output :
9
----------------------

sample input :
4
0 18 52 23
18 0 12 11
52 12 0 3
23 11 3 0

sample output :
32
*/

#include <stdio.h>

#define SIZE 9

void way(int result[SIZE*SIZE][SIZE], int *times, int passed[SIZE], int inside, int citynum) {
    for (int i = 1; i < citynum; i++) {
        if (passed[i]) continue;
        passed[i] = 1;
        result[*times][inside - 1] = i;
        
		if (inside == citynum - 1) *times ++;
        else way(result, times, passed, inside ++, citynum);
		
        passed[i] = 0;
    }
}

void treat(int result[SIZE*SIZE][SIZE], int times, int citynum) {
    for (int i = 0; i < times; i++)
        for (int j = 0; j < citynum - 1; j++)
            if (!(result[i][j])) result[i][j] = result[i - 1][j];
}

void compute(int cities[SIZE][SIZE], int citynum) {
    int result[SIZE*SIZE][SIZE] = {0}, times = 0, passed[SIZE] = {0};
    way(result, &times, passed, 1, citynum);
    treat(result, times, citynum);
	
    int min = 999999;
    for (int i = 0; i < times; i++) {
        int answer = cities[0][result[i][0]], j;
        for (j = 0; j < citynum - 2; j++) {
            int waylength = cities[result[i][j]][result[i][j + 1]];
            answer += waylength;
            if (waylength == 0) {
                answer = 999999;
                break;
            }
        }
        if (answer < min) min = answer;
    }
    printf("%d\n", min);
}

int main(void) {
	int n;
	scanf("%d", &n);
	int cities[SIZE][SIZE];
	for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) scanf("%d", &cities[i][j]);
	
	compute(cities, n);
	
	return 0;
}
