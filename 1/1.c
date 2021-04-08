#include <math.h>
#include <stdio.h>
#define EPSILON 1.0e-12

int	main(void)
{
	double a, b, c;

	scanf("%lf %lf %lf", &a, &b, &c);
	if (fabs((a - b) - c) < EPSILON)
		printf("a - b == c\n");
	else
		printf("a - b != c\n");
	return (0);
}
