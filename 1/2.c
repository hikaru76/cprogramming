#include <math.h>
#include <stdio.h>
#define EPSILON 1.0e-12

double	each(double x, int n)
{
	double		i;
	double	ans;
	double	factorial;

	i = 0;
	factorial = 1;
	while (++i <= n)
		factorial *= i;
	ans = pow(x, n) / factorial;
	return (ans);
}

double	myexp(double const x)
{
	double	ans;
	int		i;

	i = 0;
	if (x >= 0)
		while (++i < 100)
		{
			ans += each(x, i);
			printf("%f\n", ans);
		}
	else
		while (++i < 100)
			ans += each(-1 * x, i);
	if (x >= 0)
		return (ans);
	return (1.0 / ans);
}

int main(int argc, char **argv) {    
    printf("exp(x)の値を計算します。\n");
    printf("xの値を入力してください: ");

    double x;
    if (scanf("%lf", &x) != 1) {
        printf("[ ERROR ] 入力された値は数値ではないようです。\n");
        return 1;
    }
    printf("\n");

    double a = myexp(x);
    double b = exp(x);
    double rel = fabs(a - b) / fabs(b);
    printf("あなたの値: %.8e\n", a);
    printf("正しい値: %.8e\n", b);
    printf("相対誤差: %.8e\n", rel);
    printf("あなたの計算は「%s」です\n", rel < EPSILON ? "正しい" : "間違い");
	return (0);
}
