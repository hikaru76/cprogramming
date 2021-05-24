#include <math.h>
#include "matrix.h"
#include <stdio.h>

double lagrange(double x, matrix points) {
    double px = 0.0, l = 0.0;
    int n = points.rows;

    for (int i = 0; i < n + 1; i++) {
        l = 1;
        for (int j = 0; j < n + 1; j++) {
            if (j == i)
                continue;
            if (mat_elem(points, i, 0) - mat_elem(points, j, 0) == 0)
                continue;
            else
                l *= (x - mat_elem(points, j, 0)) / (mat_elem(points, i, 0) - mat_elem(points, j, 0));
        }
        px += l * mat_elem(points, i, 1);
    }
    return px;
}
