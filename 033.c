//	Created by L.H.Ming on 2020/06/16.
//  Copyright © 2020 L.H.Ming. All rights reserved.

/*
利用結構 struct 定義
Shape（圖形）, Circle（圓）, Rectangle（矩形）, Square（正方形）, Triangle（三角形）。
圓有半徑，矩形有長和寬，正方形有邊長，三角形有三個邊。
計算各個圖形的周長，以及所有圖形的周長加總。
此題須使用以下struct及function pointer實作，否則不予計分。
(使用規定架構進行實作並通過所有測資才予以給分，期末會進行檢查)

輸入說明:
圖形個數、圖形種類與其屬性
圖形種類以代號輸入，代號如下所示：
C：圓形，屬性內容具有radius (圓周率請使用3.14)
R：矩形，屬性內容具有length、width
S：正方形，屬性內容具有edge
T：三角形，屬性內容具有3個edge

輸出說明：
各個圖形的周長、各個圖形的周長總和
(四捨五入到小數點後第2位，總和請先加總好再四捨五入)

Sample Input：
4
T 1.1 2.2 3.3
S 1.1
R 1.1 2.2
C 1.0

Sample Output：
6.60
4.40
6.60
6.28
23.88

-----------------

Sample Input：
1
C 0.31847

Sample Output：
2.00
2.00



------程式碼架構規範之範例---------------------
#define ShapeText(TYPE) char name[10];\
						double (*perimeter)(struct TYPE*);\
						double (*area)(struct TYPE*);

typedef struct shape_s {
	ShapeText(shape_s);
} shape_t;
typedef struct circle_s {
	ShapeText(circle_s);
	double radius;
} circle_t;
*/

#include <stdio.h>
#include <string.h>

#define ShapeText(TYPE) double (*perimeter)(struct TYPE*);

typedef struct shape_s {
	ShapeText(shape_s);
	//double perimeter;
} 	shape_t;

typedef struct circle_s {
	ShapeText(circle_s);
	//double perimeter;
	double radius;
} 	circle_t;

typedef struct rectangle_s {
	ShapeText(rectangle_s);
	//double perimeter;
	double length;
	double width;
} 	rectangle_t;

typedef struct square_s {
	ShapeText(square_s);
	//double perimeter;
	double edge;
} 	square_t;

typedef struct triangle_s {
	ShapeText(triangle_s);
	//double perimeter;
	double edge1;
	double edge2;
	double edge3;
} 	triangle_t;

double shapePerimeter(shape_t *obj) {return 0;}
void shapeNew(shape_t *obj) {obj->perimeter = shapePerimeter;}

double circlePerimeter(circle_t *obj) {return 2*3.14 * obj->radius;}
void circleNew(circle_t *obj) {obj->perimeter = circlePerimeter;}

double rectanglePerimeter(rectangle_t *obj) {return 2 * (obj->length + obj->width);}
void rectangleNew(rectangle_t *obj) {obj->perimeter = rectanglePerimeter;}

double squarePerimeter(square_t *obj) {return 4 * obj->edge;}
void squareNew(square_t *obj) {obj->perimeter = squarePerimeter;}

double trianglePerimeter(triangle_t *obj) {return obj->edge1 + obj->edge2 + obj->edge3;}
void triangleNew(triangle_t *obj) {obj->perimeter = trianglePerimeter;}

int main(void) {
	int n;
	char type;
	double total;
	
	scanf("%d\n", &n);
	shape_t *list[n];
	
	circle_t c;
	rectangle_t r;
	square_t s;
	triangle_t t;
	
	for (int i = 0; i < n; i++) {
		scanf("%c ", &type);
		switch (type) {
			case 'C':
				circleNew(&c);
				scanf("%lf", &c.radius);
				getchar();
				//printf("%.2lf\n", c.perimeter);
				//total += c.perimeter;
				list[i] = (shape_t*)&c;
				break;
			case 'R':	
				rectangleNew(&r);
				scanf("%lf%lf", &r.length, &r.width);
				getchar();
				//printf("%.2lf\n", r.perimeter);
				//total += r.perimeter;
				list[i] = (shape_t*)&r;
				break;
			case 'S': 
				squareNew(&s);
				scanf("%lf", &s.edge);
				getchar();
				//printf("%.2lf\n", s.perimeter);
				//total += s.perimeter;
				list[i] = (shape_t*)&s;
				break;
			case 'T': 
				triangleNew(&t);
				scanf("%lf%lf%lf", &t.edge1, &t.edge2, &t.edge3);
				getchar();
				//printf("%.2lf\n", t.perimeter);
				//total += (shape_t*)&t.perimeter;
				list[i] = (shape_t*)&t;
				break;
		}
		
		shape_t *o = list[i];
		printf("%.2lf\n", o->perimeter(o));
		total += o->perimeter(o);
		
	}
	
	printf("%.2lf\n", total);
}