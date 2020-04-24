//	Created by L.H.Ming on 2020/03/25.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
輸入10進位整數，轉成二進位
輸入二進位，轉成10進位
輸入 b1 進位 x，轉成b2進位 y
(b1及b2只會於2~10之間)
輸入：
1 (10轉2)
2 (2轉10)
3 (b1轉b2，需輸入b1及b2)
以及來源數x
輸出：輸出目標數y

Sample Input：
1
256

Sample Output：
100000000
------------------------
Sample Input：
2
1111

Sample Output：
15
------------------------
Sample Input：
3
4 //b1
3 //b2
1001

Sample Output：
2102
*/

/*
	解法說明

	1.	輸入轉換模式
	2.	根據圖形模式，轉換進制
		a.	10轉2
		b.	2轉10
		c.	b1轉b2 (先轉10，再轉b2)
	
*/

#include <stdio.h>
#include <math.h>

//10轉n
int dec_to_base(int num, int base) {
    int conv_num = 0;
    for (int i=1; num!=0; i*=10) {
        conv_num += (num%base)*i;
        num /= base;
    }
    return conv_num;
}

//n轉10
int base_to_dec(long long int num, int base) {
    int conv_num = 0;
    for (int i=0; num!=0; i++) {
        conv_num += (num%10)*pow(base,i);
        num /= 10;
    }
    return conv_num;
}

//b1轉b2
int base_to_base(int from_base, int to_base, int num) {
	dec_to_base(base_to_dec(num, from_base),to_base);	//先轉10，再轉b2
}

int main() {
	//初始化
    int mode, x, y;
    long long int num;
	
	//輸入
    scanf("%d", &mode);
	
	//根據圖形模式呼叫函數
    switch(mode) {
        case 1:	//10轉2
            scanf("%lld", &num);
            printf("%d", dec_to_base(num, 2));
            break;
        case 2:	//2轉10
            scanf("%lld", &num);
            printf("%d", base_to_dec(num, 2));
            break;
        case 3:	//b1轉b2
            scanf("%d%d%lld", &x, &y, &num);
            printf("%d", base_to_base(x,y,num));
            break;
    }
	
    return 0;
}
