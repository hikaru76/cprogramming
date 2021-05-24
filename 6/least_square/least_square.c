#include <math.h>
#include "matrix.h"

int	least_square(matrix *a, matrix points, int order)
{
	matrix	k;
	matrix	q;
	int		i;
	int		j;
	int		l;
	double	tmp;
	double	tmp2;		

	mat_alloc(&k, order, order);
	mat_alloc(&q, order, 1);

	i = -1;
	while (++i < points.cols)
	{
		j = -1;
		while (++j < points.rows)
		{
			l = -1;
			tmp = 0;
			tmp2 = 0;
			while (++l < points.rows)
			{
				tmp += 2 * pow(mat_elem(points, l, 0), i + j - 2);
				tmp2 += 2 * pow(mat_elem(points, l, 0), i - 1) * mat_elem(points, l, 1);
			}
			mat_elem(k, i, j) = tmp;
			mat_elem(q, i, 0) = tmp2;
			// printf("%lf %lf %lf %lf\n", tmp, mat_elem(k, i, j), tmp2, mat_elem(q, i, 0));
		}
	}
	if (mat_solve(a, k, q))
		return (1);
	return (0);
}
