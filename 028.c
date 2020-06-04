//	Created by L.H.Ming on 2020/06/05.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
使用切割面積加總法公式(將函式切成N個梯形)，

計算函式f(x)從f(p)到f(q)之間的面積

T = (h/2)(f(p) + f(q) + 2 f(xi)) ,

h = (q-p)/n，h 是 double。

x 值從區間起始 p 到區間終點 q 的面積，

n 為 切割數，初始設定 n=1，每次不符合所期待的精確度err時*2( n=n*2 )。

err為精確小數位數，例如 err=6，即 "目前"與"上一次"兩次切割，

計算出的面積值的差小於 10 的負6次方，亦即小於 0.000001。

f1(x) =((a-x^2))^(1/2), a 為常數。 f2(x) = (ax^3 + 7x)/(a+x)^(1/2), a 為常數。

輸入說明：
輸入 1 代表計算 f1(x) 面積，輸入 2 代表計算 f2(x)面積，
接著依序，輸入 a, p, q, err，輸入0為停止輸入。

此題測試資料為連續輸入一至多筆資料(有可能一次輸入包含多組測資)。

答案需輸出到小數點第12位

範例一.
Input:
1
4
-2
1
9
0
Output:
5.054815608319

範例二.
Input:
2
1
0
3
9
0
Output:
29.752380952687
*/

#include <stdio.h>
#include <math.h>

double f1(double a, double x) {return sqrt(a - pow(x,2));}				//f1(x) =((a-x^2))^(1/2), a 為常數
double f2(double a, double x) {return (a*pow(x, 3)+7*x) / sqrt(a+x);}	//f2(x) = (ax^3 + 7x)/(a+x)^(1/2), a 為常數。

//計算f(x)在(p,q)間以n等份逼近的積分數值，使用梯形公式 Trapezoidal rule
double integral(double (*f)(double, double), double a, double p, double q, double n) {
	//這是公式 ((b-a)/N) * (((f(a)+f(b))/2) + sum_{k=1}^{N-1} f(a+k*((b-a)/N)))
	double h = fabs((q-p) / n);
	double T = (fabs((*f)(a, p)) + fabs((*f)(a, q))) / 2.0;
	
	double next = p;
	for (int k = 1; k < n; k++) T += fabs(((*f)(a, next+=h)));
	
	return T*h;
}

int main(void) {
	int func, err;
	double (*f)(double, double); //函式指標f: a pointer to function(double, double) returning double
	double a, p, q, n;
	while (scanf("%d", &func) && func) {	//輸入func
		if (func == 1) f = f1;				//輸入為1，函式指標 f = f1
		else if (func == 2) f = f2;			//輸入為2，函式指標 f = f2
		scanf("%lf%lf%lf%d", &a, &p, &q, &err);		//輸入a, p, q, err
		
		n = 2.0;
		double last = integral(f, a, p, q, 1.0), curr = integral(f, a, p, q, 2.0);	//先用 n = 1 及 n = 2 做兩次積分
		while (fabs(curr - last) > pow(10, -err)) {		//本次積分和上次積分的差不少於10^(-err)
			last = curr;						//把本次積分放在上次積分
			curr = integral(f, a, p, q, n*=2);	//n = n*2, 再做積分
		}
		
		printf("%.12f\n", curr);	//輸出
	}
	
	return 0;
}