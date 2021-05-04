#include "matrix.h"

// ----------------------------------------------------------------------------
// 行列演算用関数群
// ----------------------------------------------------------------------------

bool is_same_size(matrix mat1, matrix mat2) {
    return mat1.rows == mat2.rows && mat1.cols == mat2.cols;
}

bool is_valid(matrix mat) {
    return mat.rows > 0 && mat.cols > 0 && mat.elems != NULL;
}

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
	if (!is_valid(*res) || !is_valid(mat1) || !is_valid(mat2)) return false;
    if (res->rows != mat1.rows || mat1.cols != mat2.rows || res->cols != mat2.cols) return false;

    matrix temp;
    if (!mat_alloc(&temp, res->rows, res->cols)) return false;


    #pragma omp parallel for
    for (int i = 0; i < res->rows; i++) {
        for (int j = 0; j < res->cols; j++) {
            mat_elem(temp, i, j) = 0.0;
            for (int k = 0; k < mat1.cols; k++) {
                mat_elem(temp, i, j) += mat_elem(mat1, i, k) * mat_elem(mat2, k, j);
            }
        }        
    }
    
    mat_copy(res, temp);
    mat_free(&temp);
    
    return true;
}

// mat_muls: mat2をc倍（スカラー倍）した結果を*mat1に代入する
bool mat_muls(matrix *res, matrix mat, double c) {
	int i;
	
	i = -1;
	while (++i <= res->cols * res->rows)
		res->elems[i] = mat.elems[i] * c;
	return (true);
}

// mat_trans: mat2の転置行列を*mat1に代入する
bool mat_trans(matrix *res, matrix mat) {
	matrix  tmp;
	int     i;
	int     j;

	if(mat.rows != res->cols || mat.cols != res->rows)
		return (false);
	tmp.cols = mat.cols;
	tmp.rows = mat.rows;
	mat_alloc(&tmp, mat.cols, mat.rows);
	tmp.elems = (double *)malloc(mat.cols * mat.rows * sizeof(double));
	i = -1;
	while (++i < mat.rows)
	{
		j = -1;
		while (++j < mat.cols)
			mat_elem(tmp,j,i)=mat_elem(mat,i,j);
	}
	mat_copy(res,tmp);
	return (true);
}

// mat_unit: 単位行列を与える
bool mat_ident(matrix *mat) {
	int i;
	int j;
	
	if (mat->rows != mat->cols)
		return (false);
	i = -1;
	while (++i < mat->rows)
	{
		j = -1;
		while (++j < mat->cols)
			mat_elem(*mat, i, j) = (i == j) ? 1.0 : 0.0;
	}
	return (true);
}

// mat_equal: mat1とmat2が等しければtrueを返す
bool mat_equal(matrix mat1, matrix mat2) {
	int     i;
	int     j;
	double  eps;

	eps = 1.0e-12;
	if (mat1.cols != mat2.cols || mat1.rows != mat2.rows)
		return (false);
	i = -1;
	while (++i < mat1.rows)
	{
		j = -1;
		while (++j < mat1.cols)
			if (fabs(mat_elem(mat1, i, j) - mat_elem(mat2, i, j)) >= eps)
				return (false);
	}
	return (true);
}

// mat_solve: 連立一次方程式 ax=b を解く．ピボット選択付き
bool mat_solve(matrix *x, matrix A_, matrix b_) {
	static const double epsilon = 1.0e-12;

    if (!is_valid(*x) || !is_valid(A_) || !is_valid(b_)) return false;
    if (A_.cols != x->rows || A_.rows != b_.rows || x->cols != b_.cols) return false;

    // 行列Aと行列bの値を書き換えないよう，別の行列を用意する
    matrix A, b;
    if (!mat_alloc(&A, A_.rows, A_.cols)) return false;
    if (!mat_alloc(&b, b_.rows, b_.cols)) return false;
    mat_copy(&A, A_);
    mat_copy(&b, b_);

    
    // ガウスの消去法
    int pivot = 0;
    for (int i = 0; i < A.rows - 1; i++) {
        // ピボット選択
        pivot = i;
        for (int j = i + 1; j < A.rows; j++) {
            if (fabs(mat_elem(A, pivot, i)) < fabs(mat_elem(A, j, i))) {
                pivot = j;
            }
        }

        // 行の入れ替え
        #pragma omp parallel for
        for (int j = i; j < A.cols; j++) {
            swap(mat_elem(A, i, j), mat_elem(A, pivot, j));
        }

        #pragma omp parallel for
        for (int j = 0; j < b.cols; j++) {
            swap(mat_elem(b, i, j), mat_elem(b, pivot, j));
        }

        // それでもピボットが0ならば特異行列
        if (fabs(mat_elem(A, i, i)) < epsilon) {
            fprintf(stderr, "[ ERROR ] matrix is singular!\n");
            mat_free(&A);
            mat_free(&b);
            return false;
        }

        // ピボットより下の行を消去する
        #pragma omp parallel for
        for (int j = i + 1; j < A.rows; j++) {
            const double ratio = mat_elem(A, j, i) / mat_elem(A, i, i);
            for (int k = i; k < A.cols; k++) {
                mat_elem(A, j, k) -= ratio * mat_elem(A, i, k);
            }

            for (int k = 0; k < b.cols; k++) {
                mat_elem(b, j, k) -= ratio * mat_elem(b, i, k);
            }
        }
    }

    #pragma omp parallel for
    // 後退代入
    for (int i = A.rows - 1; i >= 0; i--) {
        
        for (int k = 0; k < b.cols; k++) {
            for (int j = i + 1; j < A.rows; j++) {
                mat_elem(b, i, k) -= mat_elem(A, i, j) * mat_elem(b, j, k);
            }
            mat_elem(b, i, k) /= mat_elem(A, i, i);
        }
    }

    mat_copy(x, b);
    mat_free(&A);
    mat_free(&b);

    return true;
}

// mat_inverse: 行列Aの逆行列を*invAに与える
bool mat_inverse(matrix *invA, matrix A) {
	matrix	tmp;
	bool	flag;

	if (A.rows != A.cols || invA->cols != A.cols || invA->rows != A.rows)
		return (false);
	if (!mat_alloc(&tmp, A.rows, A.cols))
		return (false);
	mat_ident(&tmp);
	flag = mat_solve(invA, A, tmp);
	mat_free(&tmp);
	return (flag);
}
