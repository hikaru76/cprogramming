// 二重インクルードチェック
#include "matrix.h"
#include "matrix.h"

int main() {
    // 関数の定義チェック
    matrix A;
    mat_alloc(&A, 3, 3);
    mat_print(A);
    mat_free(&A);
}
