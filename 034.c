//	Created by L.H.Ming on 2020/06/16.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
本題必須使用後所附程式碼架構
(使用規定架構進行實作並通過所有測資才予以給分，期末會進行檢查)
以下邏輯電路圖，輸入為 I1, I2, I3，輸出為 O1, O2, O3

　　　　　　　　O1
I1 --->A--->B　 ↑
　　　　　 	B---★----------->D　 O2
I2 -------->B　　　 |　　　　D　 ↑
　　　　　　　　　  --->C  　D---★--->F　 O3
　　　　　　　　　　　  C--->D　　　  F　 ↑
I3 -------------------->C　　D　　　  F---★
　　　　　　　　　　　　　　　　　    F
I4------------------E---------------->F

(社團會再放一張更整齊的版本，同學可以去查看)

輸入I1, I2, I3, I4，以及設定AND, OR, XOR, NOT四種邏輯閘與Empty邏輯閘(即不設置邏輯閘)
輸出O1, O2, O3

A, E邏輯閘：單輸入單輸出邏輯閘(NOT 與 Empty)
B, C, D, F邏輯閘：雙輸入單輸出邏輯閘(AND, OR與XOR)

輸入說明:
第一行依次輸入I1, I2, I3, I4為 0 或 1，中間以逗號間隔。
第二行輸入A, B, C, D, E, F邏輯閘的設定，欲輸入的邏輯閘種類代號如下所示：
A：AND Gate
O：OR Gate
X：XOR Gate
N：NOT Gate
E：Empty Gate
(A邏輯閘僅代表順序第一順位輸入，並非固定為AND閘，只會有N與E邏輯閘種類代號輸入)
輸入順序：
I1,I2,I3,I4
A,B,C,D,E,F


輸出說明:
輸出O1, O2, O3為 0 或 1，中間以逗號間隔
輸出順序：O1,O2,O3

範例:

Sample Input:
0,0,0,0
N,A,O,X,N,A

Sample Output:
0,0,0

-------------

Sample Input:
1,0,1,1
E,X,A,A,N,O

Sample Output:
1,1,1


------程式碼架構規範之範例---------------------

#include
#include
#define GATEVALUE(TYPE) int(*GateValue)(void)
typedef struct _Gate{
	GATEVALUE();
}Gate;
int GateGetValue(){return 0;}

typedef struct _GateAnd{
	GATEVALUE();
}GateAnd;
int GateAndValue(){return 1;}

void CreateGate(Gate *obj){
	obj->GateValue = GateGetValue;
}
void CreateGateAND(GateAnd *obj){
	obj->GateValue = GateAndValue;
}
int main(int argc, char *argv[]){
	Gate gate;
	CreateGate(&gate);
	GateAnd and;
	CreateGateAND(&and);
	printf("Gate = %d, GateAND = %d\n", gate.GateValue(), and.GateValue());
	return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>

#define GATEVALUE(TYPE) int(*GateValue)(int a, int b)

typedef struct _Gate {GATEVALUE();}	Gate;
typedef struct _GateAnd {GATEVALUE();}	GateAND;
typedef struct _GateOR {GATEVALUE();}	GateOR;
typedef struct _GateXOR {GATEVALUE();}	GateXOR;
typedef struct _GateNOT {GATEVALUE();}	GateNOT;

int GateGetValue(int a, int b) {return a;}
void CreateGate(Gate *obj) {obj->xGateValue = GateGetValue;}

int GateAndValue(int a, int b){return a&b;}
void CreateGateAND (GateAND *obj) {obj->GateValue = GateAndValue;}

int GateORValue(int a, int b){return a|b;}
void CreateGateOR(GateOR *obj) {obj->GateValue = GateORValue;}

int GateXORValue(int a, int b){return a^b;}
void CreateGateXOR(GateXOR *obj) {obj->GateValue = GateXORValue;}

int GateNOTValue(int a, int b){return !a;}
void CreateGateNOT(GateNOT *obj) {obj->GateValue = GateNOTValue;}


int f(char c, int a, int b) {
	Gate gate;
	GateAND and;
	GateOR or;
	GateXOR xor;
	GateNOT not;
	
	switch(c) {
		case 'A':
			CreateGateAND(&and);
			return and.GateValue(a, b);
			break;
		case 'O':
			CreateGateOR(&or);
			return or.GateValue(a, b);
			break;
		case 'X':
			CreateGateXOR(&xor);
			return xor.GateValue(a, b);
			break;
		case 'N':
			CreateGateNOT(&not);
			return not.GateValue(a, a);
			break;
		case 'E':
			CreateGate(&gate);
			return gate.GateValue(a, a);
			break;
	}
}

int main(void) {
	int arr[4], out;
	scanf("%d,%d,%d,%d\n", &arr[0], &arr[1], &arr[2], &arr[3]);
	
	char c[6];
	for (int i = 0; i < 6; i++) {
		scanf("%c", &c[i]);
		getchar();
	}
	
	out = f(c[1], f(c[0], arr[0], arr[0]), arr[1]);
	printf("%d,", out);
	
	out = f(c[3], f(c[2], out, arr[2]), out);
	printf("%d,", out);
	
	out = f(c[5], f(c[4], arr[3], arr[3]), out);
	printf("%d\n", out);
	
	return 0;
}