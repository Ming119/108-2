//	Created by L.H.Ming on 2020/05/21.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
一個字串如果全由大寫英文字母組成，我們稱為大寫字串；如果全由小寫字母組成則稱為小寫字串。字串的長度是它所包含字母的個數，在本題中，字串均由大小寫英文字母組成。假設k是一個自然數，一個字串被稱為「k-交錯字串」，如果它是由長度為k的大寫字串與長度為k的小寫字串交錯串接組成。
舉例來說，「StRiNg」是一個 1 -交錯字串,因為它是一個大寫一個小寫交替出現；而「heLLow」是一個 2 -交錯字串，因為它是兩個小寫接兩個大寫再接兩個小寫。但不管k是多少，「aBBaaa」、「BaBaBB」、「aaaAAbbCCCC」都不是k-交錯字串。本題的目標是對於給定k值，在一個輸入字串找出最長一段連續子字串滿足k-交錯字串的要求。例如k=2且輸入「aBBaaa」，最長的k-交錯字串是「BBaa」，長度為4。又如k=1且輸入「BaBaBB」，最長的k-交錯字串是「BaBaB」，長度為5。
請注意，滿足條件的子字串可能只包含一段小寫或大寫字母而無交替，也可能不存在滿足條件的子字串。
----------------------------------------------------------------------------------
輸入說明
第一行為 k
第二行為一字串
-------------------------------------------------
輸出說明
輸出在輸入字串中最長的一段連續子字串有滿足k-交錯字串之字串長度
----------------------------------------------------------------------------------
sample input :
1
aBBdaaa

sample output :
2
----------------------
sample input :
3
DDaasAAbbCC

sample output :
3
----------------------
sample input :
2
aafAXbbCDCCC

sample output :
8
----------------------
sample input :
3
DDaaAAbbCC

sample output :
0
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 128

// 回傳兩個整數的最大值
int getMax(int x,int y) {return (x >= y? x: y);}

// 取得字母大小寫
char letterCase(char c) {
    if(islower(c)) return 'l';
    if(isupper(c)) return 'u';
    return 'n';
}

int main(void) {
    int k;
    char str[SIZE];
    scanf("%d", &k);
	scanf("%s", str);
	
	int len = strlen(str);
    int maxLen, curLen, countCase;	// maxLen = 交錯字串最大長度, curLen = 目前交錯字串長度, countCase = 目前字母case累積次數
    char curC, preC = 'n';    		// curC = 目前字母, preC = 上一個字母	//大寫u、小寫 l、未知n
	
	maxLen = curLen = countCase = 0;

    //  k 為 1 時要另外處理
    if(k == 1) {
        for(int i = 0; i < len; i++) {
            curC = letterCase(str[i]);			// 取得字母大小寫
            
			if(preC != curC) curLen ++;			// 轉換大小寫時
            else curLen = 1;					// 沒轉換大小寫時
            
			maxLen = getMax(curLen, maxLen);	// maxLen 和 curLen 誰是最大交錯字串長度
            preC = curC;						// 上一個字母case為目前字母case
        }
    }	else {
        for(int i = 0; i < len; i++) {
            curC = letterCase(str[i]);
			if(preC == curC) {
                countCase++;
				
				if(countCase == k) {					// 累積到 k 次
                    curLen += k;						// 加到目前交錯字串長度
                    maxLen = getMax(curLen, maxLen);	// maxLen 和 curLen 誰是最大交錯字串長度
                }
				
				// 目前case次數超過 k 次
				if(countCase > k) curLen = k;		// 目前交錯字串長度也只能等於 k
            }	else if(preC != curC) {				// 轉換大小寫時
                    if(countCase < k) curLen = 0;	// 目前case次數小於 k 次，目前交錯字串長度歸零
                    countCase = 1;             		// case次數從 1 開始
            }
            
			preC = curC;	// 上一個字母case為目前字母case
        }
    }

    printf("%d\n", maxLen);
  
    return 0;
}