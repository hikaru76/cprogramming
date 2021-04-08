#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// 要素を交換するマクロ
#define swap(a, b) do { \
    double t = (a);     \
    a = b;              \
    b = t;              \
} while( 0 );

/*
 * 行列用構造体
 * rows: 行数
 * cols: 列数
 * elems: 行列要素を入れた一次元配列
 */
typedef struct {
	int rows;
	int cols;
	double *elems;
} matrix;

// 行列要素を取得するマクロ
#define mat_elem(m, i, j) (m).elems[(i) * (m).cols + (j)]

// ----------------------------------------------------------------------------
// 行列演算用関数群
// ----------------------------------------------------------------------------

// mat_alloc: 行列要素用のメモリを確保する
bool mat_alloc(matrix *mat, int rows, int cols) {
    if (rows <= 0 || cols <= 0)
        return (false);
    mat->elems = (double *)malloc(rows * cols * sizeof(double));
    mat->rows = rows;
    mat->cols = cols;
    return (true);
}

// mat_free: 使い終わった行列のメモリを解放する
void mat_free(matrix *mat) {
    free(mat->elems);
    mat->rows = 0;
    mat->cols = 0;
    mat->elems = 0;
}

// mat_print: 行列の中身を表示する
void mat_print(matrix mat) {
    if (mat.rows == 0 || mat.cols == 0 || mat.elems == NULL) {
        fprintf(stderr, "Matrix is NULL or zero size!\n");
        return;
    }

    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            printf("%6.4f%s", mat_elem(mat, i, j), (j == mat.cols - 1) ? "\n" : "  ");
        }
    }
}

// mat_copy: srcの中身を*dstにコピーする
bool mat_copy(matrix *dst, matrix src) {
    int i;
    int j;

    if (dst->cols != src.cols)
        return (false);
    if (dst->rows != src.rows)
        return (false);
    i = -1;
    while (++i < src.rows)
    {
        j = -1;
        while (++j < src.cols)
            mat_elem(*dst, i, j) = mat_elem(src, i, j);
    }
    return (true);
}

// mat_add: mat2+mat3を*mat1に代入する
bool mat_add(matrix *res, matrix mat1, matrix mat2) {
    int i;
    
    i = -1;
    while (++i <= res->cols * res->rows)
        res->elems[i] = mat1.elems[i] + mat2.elems[i];
    return (true);
}

// mat_sub: mat2-mat3を*mat1に代入する
bool mat_sub(matrix *res, matrix mat1, matrix mat2) {
    int i;
    
    i = -1;
    while (++i <= res->cols * res->rows)
        res->elems[i] = mat1.elems[i] - mat2.elems[i];
    return (true);
}

// mat_mul: mat2とmat3の行列積を*mat1に代入する
bool mat_mul(matrix *res, matrix mat1, matrix mat2) {
    int     i;
    int     j;
    int     k;
    double  val;
    
    if (mat1.cols != mat2.rows || mat1.rows != res->rows || mat2.cols != res->cols)
        return (false);
    i = -1;
    while (++i < res->rows)
    {
        j = -1;
        while (++j < res->cols)
        {
            val = 0.0;
            k = -1;
            while (++k < mat1.cols)
                val += mat_elem(mat1, i, k) * mat_elem(mat2, k, j);
            mat_elem(*res, i, j) = val;
        }
    }
    return (true);
}

// mat_muls: mat2をc倍（スカラー倍）した結果を*mat1に代入する
bool mat_muls(matrix *res, matrix mat, double c) {
    return false;
}

// mat_trans: mat2の転置行列を*mat1に代入する
bool mat_trans(matrix *res, matrix mat) {
    return false;
}

// mat_unit: 単位行列を与える
bool mat_ident(matrix *mat) {
    return false;
}

// mat_equal: mat1とmat2が等しければtrueを返す
bool mat_equal(matrix mat1, matrix mat2) {
    return false;
}

// mat_solve: 連立一次方程式 ax=b を解く．ピボット選択付き
bool mat_solve(matrix *x, matrix A_, matrix b_) {
    return false;
}

// mat_inverse: 行列Aの逆行列を*invAに与える
bool mat_inverse(matrix *invA, matrix A) {
    return false;
}
