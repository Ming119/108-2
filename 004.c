//	Created by L.H.Ming on 2020/03/19.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
第二周 004
輸入每月網內、網外、市話、通話時間(sec)及網內、網外 簡訊則數，求最佳資費。
費率如下表：
*月租費也要納入考量
資費類型 183型 383型 983型
月租費 183元 383元 983元
優惠內容 月租費可抵等額通信費
語音 網內 0.08 0.07 0.06
(元/秒) 網外 0.1393 0.1304 0.1087
市話(元/秒) 0.1349 0.1217 0.1018
簡訊 網內 1.1287 1.1127 0.9572
(元/則) 網外 1.4803 1.2458 1.1243

輸入 網內語音(sec)、網外語音(sec)、市話(sec)、網內簡訊數、網外簡訊數 測試資料。

Sample Input：
500
120
13
2
5

Sample Output：
183

Sample Input：
200
200
200
200
200

Sample Output：
383
*/

/*
	解法說明

	1.	分別輸入 網內語音、網外語音、市話、網內簡訊數、網外簡訊數 到int
	2.	根據輸入資料，計算不同資費類型的資費
	3.	根據資費，判斷最佳資費類型
	4.	輸出 最佳資費類型
	
*/

#include <stdio.h>
	
int main() {
	//初始化
	//in_voice = 網內語音，out_voice = 網外語音，local = 市話
	//in_sms = 網內簡訊數，out_sms = 網外簡訊數
    int in_voice, out_voice, local, in_sms, out_sms;
    float calc1, calc2, calc3;	//使用陣列儲存資費類型的費率
    float plan1[6] = {183, 0.08, 0.1393, 0.1349, 1.1287, 1.4803};	//183型
    float plan2[6] = {383, 0.07, 0.1304, 0.1217, 1.1127, 1.2458};	//383型
    float plan3[6] = {983, 0.06, 0.1087, 0.1018, 0.9572, 1.1243};	//983型

    scanf("%d%d%d%d%d", &in_voice, &out_voice, &local, &in_sms, &out_sms);	//輸入
	
	//計算資費
	float calcPrice(float plan[]) {
		float price;

		price = plan[1]*in_voice + plan[2]*out_voice + plan[3]*local + plan[4]*in_sms + plan[5]*out_sms;
    
		if (price < plan[0]) return plan[0];
		else return price;
	}
	//計算資費
    calc1 = calcPrice(plan1);
    calc2 = calcPrice(plan2);
    calc3 = calcPrice(plan3);
	
	//判斷及輸出最佳資費類型
    if (calc1 < calc2) printf("183");
    else if (calc2 < calc3) printf("383");
    else printf("983");

    return 0;
}
