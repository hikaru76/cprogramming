#include <stdio.h>
#include <math.h>

double f(double x, double y) {
    return x + y;
}

double answer(double x) {
    return -(1.0 + x) + exp(x);
}

double eulerf(double x, double y, double h, double (*f)(double, double)) {
    // 前進オイラー法
	return (y + h * f(x, y));
}

double eulerb(double x, double y, double h, double (*f)(double, double)) {
    // 後退オイラー法
	return ((y + h * (x + h)) / (1 - h));
}

double heun(double x, double y, double h, double (*f)(double, double)) {
    // ホイン法
	return (y + (h / 2) * f(x, y) + (h / 2) * f(x + h, y + h * f(x, y)));
}

double euler2(double x, double y, double h, double (*f)(double, double)) {
    // 修正オイラー法
	return (y + h * f(x + h / 2, y + h * f(x, y) / 2));
}

double runge(double x,double y,double h,double (*f)(double, double)) {
    double k1 = f(x, y);
    double k2 = f(x + h / 2, y + h * k1 / 2);
    double k3 = f(x + h / 2, y + h * k2 / 2);
    double k4 = f(x + h, y + h * k3);
    return (y + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4));
}

int main() {
    const int N = 100;
    const double h = 5.0 / N;
    const double x_0 = 0.0;
    const double y_0 = 0.0;

    double y_true;
    double x = x_0;
    double y = y_0;
    double error = 0.0;
    for (int i = 0; i < N; i++) {
        y = euler2(x, y, h, f);
        x = x + h;
        y_true = answer(x);
        error += (y_true - y) * (y_true - y);
        //printf("%f %f %f\n", x, y, y_true);
    }
    error = sqrt(error / N);
    printf("euler2's Error: %.8f\n", error);
    
    error = 0.0;
    x = x_0;
    y = y_0;
    for (int i = 0; i < N; i++) {
        y = heun(x, y, h, f);
        x = x + h;
        y_true = answer(x);
        error += (y_true - y) * (y_true - y);
        //printf("%f %f %f\n", x, y, y_true);
    }
    error = sqrt(error / N);
    printf("heun's Error: %.8f\n", error);
    
    error = 0.0;
    x = x_0;
    y = y_0;
    for (int i = 0; i < N; i++) {
        y = eulerb(x, y, h, f);
        x = x + h;
        y_true = answer(x);
        error += (y_true - y) * (y_true - y);
        //printf("%f %f %f\n", x, y, y_true);
    }
    error = sqrt(error / N);
    printf("eulerb's Error: %.8f\n", error);
    
    error = 0.0;
    x = x_0;
    y = y_0;
    for (int i = 0; i < N; i++) {
        y = eulerf(x, y, h, f);
        x = x + h;
        y_true = answer(x);
        error += (y_true - y) * (y_true - y);
        //printf("%f %f %f\n", x, y, y_true);
    }
    error = sqrt(error / N);
    printf("eulerf's Error: %.8f\n", error);
    
    error = 0.0;
    x = x_0;
    y = y_0;
       for (int i = 0; i < N; i++) {
           y = runge(x, y, h, f);
           x = x + h;
           y_true = answer(x);
           error += (y_true - y) * (y_true - y);
           //printf("%f %f %f\n", x, y, y_true);
       }
       error = sqrt(error / N);
       printf("runge's Error: %.8f\n", error);
}