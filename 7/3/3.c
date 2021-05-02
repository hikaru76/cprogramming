#include <stdio.h>
#include <math.h>
#include <string.h>
#include "matrix.h"

void f(double x, matrix y, matrix *dxdy) {
    matrix dxdy_;

    mat_alloc(&dxdy_, 2, 1);
    mat_elem(dxdy_, 0, 0) = mat_elem(y, 1, 0);
    mat_elem(dxdy_, 1, 0) = -x * mat_elem(y, 0, 0);
    mat_copy(dxdy, dxdy_);
}

void runge(double x, matrix y0, double h, matrix *y1, void (*f)(double, matrix, matrix *)) {
    matrix k0, k1, k2, k3, k4;
    
    mat_alloc(&k0, 2, 1);
    mat_alloc(&k1, 2, 1);
    mat_alloc(&k2, 2, 1);
    mat_alloc(&k3, 2, 1);
    mat_alloc(&k4, 2, 1);
    mat_elem(k0, 0, 0)=0;
    mat_elem(k0, 1, 0)=0;
    mat_elem(k1, 0, 0)=0;
    mat_elem(k1, 1, 0)=0;
    mat_elem(k2, 0, 0)=0;
    mat_elem(k2, 1, 0)=0;
    mat_elem(k3, 0, 0)=0;
    mat_elem(k3, 1, 0)=0;
    mat_elem(k4, 0, 0)=0;
    mat_elem(k4, 1, 0)=0;
    f(x, y0, &k1);
    mat_muls(&k2, k1, 0.5);
    mat_muls(&k2, k2, h);
    mat_add(&k2, y0, k2);
    f(x, k2, &k2);
    mat_muls(&k3, k2, 0.5);
    mat_muls(&k3, k3, h);
    mat_add(&k3, k3, y0);
    f(x, k3, &k3);
    mat_muls(&k4, k3,  h);
    mat_add(&k4,  y0,  k4);
    f(x,  k4,  &k4);
    mat_muls(&k2,  k2,  2);
    mat_add(&k0,  k1,  k2);
    mat_muls(&k3,  k3,  2);
    mat_add(&k3,  k3,  k0);
    mat_add(&k4,  k3,  k4);
    
    mat_muls(&k4,  k4,  h/6);
    mat_add(y1,  y0,  k4);
   
}

int main(int argc,  char **argv) {
    double k, m, h;
	char *s;
    //k=10;
    //m=10;

	printf("kの値を入力してください:");
	scanf("%lf", &k);
	printf("mの値を入力してください:");
	scanf("%lf", &m);
    h=0.5;
    
    double x=k/m;
    matrix y0, y1, y2;
    mat_alloc(&y0, 2, 1);
    mat_alloc(&y1, 2, 1);
    mat_alloc(&y2, 2, 1);
    
    mat_elem(y0, 0, 0) = 20; //初期位置0
    mat_elem(y0, 0, 1) = 0; //初期速度5 y0もy1も同じ構造　０回微分と一階微分のベクトル
    mat_copy(&y2, y0);
    mat_copy(&y1, y0);

	//ファイル用意
	if (argc == 1)
	{
		s = (char *)malloc(sizeof(char) * 6);
		strcpy(s, "a.csv");
	}
	else
	{
		s = (char *)malloc(sizeof(char) * (strlen(argv[1]) + 1));
		strcpy(s, argv[1]);
	}
	FILE *fp = fopen(s, "w");
	//ファイル書き込み
    for (double t=0; t < 1024; t++) {
        runge(x, y2, h, &y1, f);
        fprintf(fp, "%f, %f, %f\n", t, mat_elem(y1, 0, 0), mat_elem(y1, 1, 0));
        mat_copy(&y2, y1);
    }
    fclose(fp);
	free(s);
	return (0);
}