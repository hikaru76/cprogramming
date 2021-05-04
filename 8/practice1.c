//コンパイルコマンド：　gcc print.c -fopenmp
//notionに「まとめ」あり

#include <stdio.h>

#ifdef _OPENMP
#include <omp.h>
#endif

int main() {
	int	total = 0;

    #pragma omp parallel for
    for (int i = 1; i <= 10000; i++)
	{
		#pragma omp critical
		{
			total += i;
		}
	}
	printf("%d", total);
	return (0);
}