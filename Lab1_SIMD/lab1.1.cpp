#include <iostream>
#include <cmath>   // Для std::pow
#include <chrono>  // Для измерения времени
#include <immintrin.h> // Для SIMD

// Методы численного интегрирования

// Метод прямоугольников
double rectangular_method(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double integral = 0.0;
    for (int i = 0; i < n; ++i) {
        integral += f(a + (i + 0.5) * h);
    }
    return integral * h;
}

// Метод трапеций
double trapezoidal_method(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double integral = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; ++i) {
        integral += f(a + i * h);
    }
    return integral * h;
}

// Метод Симпсона
double simpson_method(double (*f)(double), double a, double b, int n) {
    if (n % 2 == 1) n++;  // n должен быть четным
    double h = (b - a) / n;
    double integral = f(a) + f(b);
    for (int i = 1; i < n; i += 2) {
        integral += 4 * f(a + i * h);
    }
    for (int i = 2; i < n - 1; i += 2) {
        integral += 2 * f(a + i * h);
    }
    return integral * (h / 3);
}

// Функция для вычисления π
double f(double x) {
    return 4.0 / (1.0 + x * x);
}