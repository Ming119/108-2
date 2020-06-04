//	Created by L.H.Ming on 2020/03/19.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
第二周 006
檢查三門課程是否衝堂，
依序輸入課程編號(數字)、
上課小時數(1-3小時)、
上課時間(星期1-5, 第1-9節)

輸入說明
1001 (第一門課課程編號)
3 (3小時)
11 (星期1 第1節課)
59 (星期5 第9節課)
25 (星期2 第5節課)
2020 (第二門課課程編號)
2
25
16
2030 (第三門課課程編號)
…

輸出說明 (兩課程編號衝突在哪幾節)
1001 and 2020 conflict on 25

Sample Input：
1001
3
11
12
13
1002
3
21
22
23
1003
3
31
32
13
Sample Output：
1001 and 1003 conflict on 13

Sample Input：
1001
1
11
1002
3
21
22
11
1003
3
31
32
33
Sample Output：
1001 and 1002 conflict on 11
*/

/*
	解法說明

	1.	分別輸入 課程編號，上課時數，及上課時間
	2.	根據上課時數，輸入上課時間
	3.	使用線性搜尋檢查衝堂
	4.	輸出衝堂資訊
	
*/

//	方法一，使用一維陣列
#include <stdio.h>

int main() {
	//初始化
    int class1[5], class2[5], class3[5];
	for(int i = 0; i < 5; i++) {
		class1[i] = 0;
		class2[i] = 0;
		class3[i] = 0;
	}
	
	//輸入
    scanf("%d%d", &class1[0], &class1[1]);						//輸入第一門課的課程編號 及 上課時數
    for(int i=2; i<class1[1]+2; i++) scanf("%d", &class1[i]);	//根據第一門課的上課時數，輸入第一門課的上課時間
	
    scanf("%d%d", &class2[0], &class2[1]);						//輸入第二門課的課程編號 及 上課時數
    for(int i=2; i<class2[1]+2; i++) scanf("%d", &class2[i]);	//根據第二門課的上課時數，輸入第二門課的上課時間
	
    scanf("%d%d", &class3[0], &class3[1]);						//輸入第三門課的課程編號 及 上課時數
    for(int i=2; i<class3[1]+2; i++) scanf("%d", &class3[i]);	//根據第三門課的上課時數，輸入第三門課的上課時間
	
	//使用線性搜尋Linear Search，檢查衝堂，並輸出衝堂資訊
    for(int i=2; i<5; i++){
        for(int j=2; j<5; j++) {
            if(class1[i] == class2[j] && class1[i] != 0) printf("%d and %d conflict on %d\n", class1[0], class2[0], class1[i]);
            else if(class1[i] == class3[j] && class1[i] != 0) printf("%d and %d conflict on %d\n", class1[0], class3[0], class1[i]);
            else if(class2[i] == class3[j] && class2[i] != 0) printf("%d and %d conflict on %d\n", class2[0], class3[0], class2[i]);
        }
    }
	
	return 0;
}

//	方法二，使用二維陣列
/*
#include <stdio.h>

int main() {
	//	{ {第一門課的課程編號，第一門課的上課時數，第一門課的第一個上課時間，第一門課的第二個上課時間，第一門課的第三個上課時間}，
	//	  {第二門課的課程編號，第二門課的上課時數，第二門課的第一個上課時間，第二門課的第二個上課時間，第二門課的第三個上課時間}，
	//	  {第三門課的課程編號，第三門課的上課時數，第三門課的第一個上課時間，第三門課的第二個上課時間，第三門課的第三個上課時間} }
	
	//初始化
    int Class[3][5];
	for(int i = 0; i < 3; i++) for (int j = 0; j < 5; j++) Class[i][j] = 0;
	
	//輸入
    for(int i = 0; i < 3; i++) {
        scanf("%d%d", &Class[i][0], &Class[i][1]);		//輸入第i門課的課程編號 及 上課時數
        for (int j = 2; j < (Class[i][1] + 2); j++) scanf("%d", &Class[i][j]);	//根據第i門課的上課時數，輸入第i門課的上課時間
    }
	
	//使用線性搜尋Linear Search，檢查衝堂，並輸出衝堂資訊
    for(int i = 0; i < 2; i++) {
        for(int j = (i + 1); j < 3; j++) {
            for(int k = 2; k < 5; k++) {
                for(int h = 2; h < 5; h++) {
                    if(Class[i][k] == Class[j][h]) {
                        if(Class[i][k] == 0) continue;
                        else printf("%d and %d conflict on %d\n", Class[i][0], Class[j][0], Class[i][k]);
                    }
                }
            }
        }
    }
	
    return 0;
}
*/
