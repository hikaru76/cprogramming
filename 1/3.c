#include <math.h>
#include <stdio.h>

double	taylor(double x)
{
	int		i;
	double	ans;
	
	i = -1;
	ans = 0;
	while (++i < 300)
		ans += 1.0 / (2 * i + 1) * pow((x - 1) / (x + 1), 2 * i + 1);
	return (2 * ans);
}

int	main(void)
{
	printf("log(x)の値を計算します。\n");
    printf("xの値を入力してください: ");

    double x;
    if (scanf("%lf", &x) != 1) {
        printf("[ ERROR ] 入力された値は数値ではないようです。\n");
        return 1;
    }
	printf("%f\n", taylor(x));
	return (0);
}
