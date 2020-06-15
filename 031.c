//	Created by L.H.Ming on 2020/06/16.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
***請務必使用struct進行解題***

開發專案時，
專案會被分割為許多項目，分配給多組程式設計師開發。
但這些項目是有順序關係，只有當順序在前的項目完成，才能開始開發順序在後的項目。
用一個有向無環圖，表示這些開發順序。
每個節點代表一個項目，節點內的數字為節點編號， 上方所列數字代表開發這個項目所需天數；
邊表示開發順序。
以下方敘述為例，只有在節點2完成後，才能開始節點4的開發。
同理，只有在節點3與節點4都完成後，才能開始節點5的開發。
一軟體公司的專案準備開始開發，你是公司專案經理，根據開發流程圖，
老闆想知道專案要多久才能完成。
------------------------------------------------------------------
例子 :
節點1→6天
節點2→5天
節點3→11天
節點4→4天
節點5→8天

節點1→節點2→節點4→節點5
↓
節點3______________↗

------------------------------------------------------------------
輸入 :
第一行是整數，代表後續測試資料組數。
每組測試資料代 表專案有向圖。
每組測試資料的第一行是正整數N，代表專案 共有 N 個工作事項(節點)，N<=100。
接下來N 行測試資料，每一行依序代表一個項目節點(從第1個節點開始)，
第一個正整數表示完成這個項目所需天數，
第二個正整數 K 表示這個節點有K 條指向其他節點的邊，
接下來K 個正整數表示所指向的項目節點編號。

輸出 :
從第1個節點到最後一個節點N總共所需要花費的時間。
---------------------------------------------------------------------------

範例輸入 :
2
2
8 1 2
2 0
5
6 2 2 3
5 1 4
11 1 5
4 1 5
8 0

範例輸出 :
10
25
*/

#include <stdio.h>

#define SIZE 128

typedef struct task_s{
	int pTask[SIZE];
	int pNo;
	int day;
	int tDay;
} 	task_t;

int isCanCompute(task_t *tasks, task_t t) {
	int flag = 1, id = 0;
	
	for (int i = 0; i < t.pNo; i++) {
		id = t.pTask[i];
		if (tasks[id].tDay == -1) flag = 0;
	}
	
	return flag;
}

int isYetCompute(task_t t) {
	if (t.tDay == -1) return 1;
	else return 0;
}

int computeDay(task_t *tasks, task_t t) {
	int maxDay = 0, id = 0;
	
	for (int i = 0; i < t.pNo; i++) {
		id = t.pTask[i];
		if (tasks[id].tDay > maxDay) maxDay = tasks[id].tDay;
	}
	
	return (maxDay + t.day);
}

void input(int n, task_t *data) {
	int c = 0, id = 0, index = 0;
	for (int i = 1; i <= n; i++) {
		data[i].pNo = 0;
		data[i].tDay = -1;
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &data[i].day);
		scanf("%d", &c);
		for (int j = 0; j < c; j++) {
			scanf("%d", &id);
			index = data[id].pNo;
			data[id].pTask[index] = i;
			data[id].pNo++;
		}
	}
}	

void printAnswer(int n, task_t *data) {
	int maxDay = 0;
	for (int i = 1; i <= n; i++) 
		if (data[i].tDay > maxDay) maxDay = data[i].tDay;
	printf("%d\n", maxDay);
}

int getId(int n, task_t *data) {
	for (int i = 1; i <= n; i++) 
		if (isYetCompute(data[i]) && isCanCompute(data, data[i])) return i;
	return -1;
}

int main(void) {
	int no = 0;
	scanf("%d", &no);
	
	for (int i = 0; i < no; i++) {
		int n = 0, count = 0, id = 0;
		task_t data[SIZE];
		scanf("%d", &n);
		
		input(n, data);
		
		while (count<SIZE) {
			id = getId(n, data);
			if (id>=1) {
				data[id].tDay = computeDay(data, data[id]);
				count++;
			}	else break;
		}
		
		printAnswer(n, data);
	}
	
	return 0;
}