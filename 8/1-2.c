#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int get_num_threads() {
    int ret = 1;
    #pragma omp parallel
    {
        #pragma omp single
        {
            ret = omp_get_num_threads();
        }
    }
    return ret;
}

double calc_pi_simple(int n) {
    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        sum += (1.0 / i) / i;
    }
    return sqrt(sum * 6.0);
}

double calc_pi_lock(int n) {
	double sum = 0.0;
	omp_lock_t lock;
	omp_init_lock(&lock);
	#pragma omp parallel for
	for (int i = 1; i <= n; i++) {
		omp_set_lock(&lock);
		sum += (1.0 / i) / i;
		omp_unset_lock(&lock);
	}
	return sqrt(sum * 6.0);
}

double calc_pi_critical(int n) {
	double sum = 0.0;
    for (int i = 1; i <= n; i++) {
		#pragma omp critical
		{
        	sum += (1.0 / i) / i;
		}
    }
    return sqrt(sum * 6.0);
}

double calc_pi_atomic(int n) {
	double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        #pragma omp atomic
		sum += (1.0 / i) / i;
    }
    return sqrt(sum * 6.0);
}

double bunkatsu(int n) {
    int N = 1000;
    
    // スレッド数を取得
    const int num_threads = get_num_threads();

    // 各スレッドが担当するセクションの長さ
    // (配列サイズがスレッド数で割り切れない場合を考慮)
    const int section_size = (N + num_threads - 1) / num_threads;

    // 和を求める
    double sum = 0.0;

    #pragma omp parallel for
    for (int t = 0; t < num_threads; t++) {
        const int start = section_size * t + 1;
        const int end = fmin(section_size * (t + 1), N);
        double part_sum = 0.0;
        for (int i = start; i <= end; i++) {
            part_sum += (1.0 / i) / i;
        }

        #pragma omp atomic
        sum += part_sum;
    }
    return sqrt(sum * 6.0);
}

double reduction(int n) {
    int N = 1000;
    
    double sum = 0.0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= N; i++) {
        sum += (1.0 / i) / i;
    }
    return sqrt(sum * 6.0);
}

int main(int argc, char **argv) {
    // 項数の初期値は1000とし、適宜コマンドライン引数から項数を読み取る
    int N = 1000;
    if (argc > 1) N = atoi(argv[1]);

    double pi, start, end;

    // 時間を計測しながら処理を実行する
    start = omp_get_wtime();
    pi = calc_pi_simple(N);
    end = omp_get_wtime();
    printf("Pi (w/o parallel): %.12f\n", pi);
    printf("Time: %f ms\n", 1000.0 * (end - start));

	start = omp_get_wtime();
    pi = calc_pi_lock(N);
    end = omp_get_wtime();
    printf("Pi (lock): %.12f\n", pi);
    printf("Time: %f ms\n", 1000.0 * (end - start));

	start = omp_get_wtime();
    pi = calc_pi_critical(N);
    end = omp_get_wtime();
    printf("Pi (critical): %.12f\n", pi);
    printf("Time: %f ms\n", 1000.0 * (end - start));

	start = omp_get_wtime();
    pi = calc_pi_atomic(N);
    end = omp_get_wtime();
    printf("Pi (atomic): %.12f\n", pi);
    printf("Time: %f ms\n", 1000.0 * (end - start));

	start = omp_get_wtime();
	pi = bunkatsu(N);
	end = omp_get_wtime();
	printf("Pi (bunkatu): %.12f\n", pi);
	printf("Time: %f ms\n", 1000.0 * (end - start));

	start = omp_get_wtime();
	pi = reduction(N);
	end = omp_get_wtime();
	printf("Pi (reduction): %.12f\n", pi);
	printf("Time: %f ms\n", 1000.0 * (end - start));
	return (0);
}