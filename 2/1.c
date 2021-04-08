#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int	main(void)
{
	int		n;
	int		i;
	double	total;
	double	tmp;
	double	*a;

	printf("入力する実数値の個数を入力してください:");
	scanf("%d", &n);
	a = (double *)calloc(n, sizeof(double));
	printf("実数値をn個入力してください\n");
	i = -1;
	while (++i < n)
	{
		scanf("%lf", &a[i]);
		total += a[i];
	}	
	total = total / n;
	tmp = 0;
	i = -1;
	while (++i < n)
		tmp += pow(a[i] - total, 2);
	tmp = pow(tmp / n, 0.5);
	printf("平均値は%f 標準偏差は%fです", total, tmp);
	free(a);
	return (0);
}
