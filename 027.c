//	Created by L.H.Ming on 2020/06/05.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
題目:
********：必須使用enum定義不同評分制資料型別，使用union定義分數資料型別。***********
一個班級有N位同學(ID)，M門課，每一門課可以設定評分方式。
設定M門課評分制，輸入N位同學M門課成績，根據下表換算，計算每一位同學百分制對照平均成績，
印出前三名ID與平均成績，四捨五入到整數。

等第 GPA 百分制區間 百分制對照
A+ 4.3 90-100 95
A 4.0 85-89 87
A- 3.7 80-84 82
B+ 3.3 77-79 78
B 3.0 73-76 75
B- 2.7 70-72 70
C+ 2.3 67-69 68
C 2.0 63-66 65
C- 1.7 60-62 60
F 0 59以下 50



先輸入有幾門課 M ，並依序設定評分方式 等第 = G, GPA = GPA,百分制區間 = S
在輸入學生數量與學生學號、成績。

範例1.
Input:
2
G
GPA
5
10801
A+
4.3
10802
B+
4.0
10803
B-
3.3
10804
C
2.3
10805
F
0

Ouput:
10801
95
10802
83
10803
74

範例2.
Input:
2
G
S
5
10801
F
59以下
10802
C
63-66
10803
B
73-76
10804
A
85-89
10805
A+
90-100

Output:
10805
95
10804
87
10803
75
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef enum type_s {G, GPA, S} type_t;
typedef struct student_s {
	int id;
	double score;
}	student_t;

int cmp(const void* a, const void* b) {
	if(((student_t*)a)->score < ((student_t*)b)->score) return 1;
	if(((student_t*)a)->score > ((student_t*)b)->score) return -1;
	if(((student_t*)a)->score == ((student_t*)b)->score) return 0;
}

int addScore(char* grade) {
	if (!(strcmp(grade, "A+") && strcmp(grade, "4.3") && strcmp(grade, "90-100"))) return 95;
	if (!(strcmp(grade, "A") && strcmp(grade, "4.0") && strcmp(grade, "85-89"))) return 87;
	if (!(strcmp(grade, "A-") && strcmp(grade, "3.7") && strcmp(grade, "80-84"))) return 82;
	if (!(strcmp(grade, "B+") && strcmp(grade, "3.3") && strcmp(grade, "77-79"))) return 78;
	if (!(strcmp(grade, "B") && strcmp(grade, "3.0") && strcmp(grade, "73-76"))) return 75;
	if (!(strcmp(grade, "B-") && strcmp(grade, "2.7") && strcmp(grade, "70-72"))) return 70;
	if (!(strcmp(grade, "C+") && strcmp(grade, "2.3") && strcmp(grade, "67-69"))) return 68;
	if (!(strcmp(grade, "C") && strcmp(grade, "2.0") && strcmp(grade, "63-66"))) return 65;
	if (!(strcmp(grade, "C-") && strcmp(grade, "1.7") && strcmp(grade, "60-62"))) return 60;
	if (!(strcmp(grade, "F") && strcmp(grade, "0") && strcmp(grade, "59以下"))) return 50;
}

int main(void) {
	char grade[8];
	int m, n;
	
	scanf("%d", &m);	//輸入課堂數量 M
	type_t types[m][4];										// !這是沒用的!
	for (int i = 0; i < m; i++) scanf("%s", *(types+i));	// !這是沒用的!
	
	scanf("%d", &n);	//輸入學生數量 N
	student_t students[n];
	for(int i = 0; i < n; i++) students[i].score = 0;	//預設為0
	
	for (int i = 0; i < n; i++) {
		scanf("%d\n", &students[i].id);	//輸入學號
		for (int j = 0; j < m; j++) {
			scanf("%s", grade);	
			students[i].score += addScore(grade);	//加分
		}
		students[i].score /= m;	//計算平均分
	}
	
	qsort(students, n, sizeof(student_t), cmp);	//快排
	
	for (int i = 0; i < 3; i++) printf("%d\n%.0f\n", students[i].id, ceil(students[i].score));	//輸出前三
	
	return 0;
}