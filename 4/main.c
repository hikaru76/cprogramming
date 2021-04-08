#include "matrix.h"

int	main(void)
{
	double A[9]={1,2,3,4,5,6,7,8,9};
    double B[9]={-1,2,-1,2,-1,2,-1,2,-1};
    double C[9]={3,1,4,1,5,9,2,6,5};
	matrix	a;
	matrix	b;
	matrix	c;
	matrix	ans1;
	matrix	ans2;
	matrix	ta;
	matrix	tc;
	matrix	fivea;
	matrix	btwo;
	matrix	tmp;

	mat_alloc(&a, 3, 3);
	mat_alloc(&b, 3, 3);
	mat_alloc(&c, 3, 3);
	mat_alloc(&ans1, 3, 3);
	mat_alloc(&ans2, 3, 3);
	mat_alloc(&ta, 3, 3);
	mat_alloc(&tc, 3, 3);
	mat_alloc(&fivea, 3, 3);
	mat_alloc(&btwo, 3, 3);
	mat_alloc(&tmp, 3, 3);

	a.elems = A;
	b.elems = B;
	c.elems = C;

	mat_trans(&ta, a);
	mat_muls(&ans1, ta, 3.0);

	mat_muls(&fivea, a, 5.0);
	mat_muls(&btwo, b, 0.5);
	mat_sub(&tmp, fivea, btwo);
	mat_trans(&tc, c);
	mat_mul(&ans2, tc, tmp);

	mat_print(ans1);
	mat_print(ans2);
	return (0);
}
