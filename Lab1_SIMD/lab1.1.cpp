#include <iostream>
#include <cmath>   // Для std::pow
#include <chrono>  // Для измерения времени

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

void test_integration_methods(int n) {
    double a = 0.0;
    double b = 1.0;

    auto start = std::chrono::high_resolution_clock::now();
    double pi_rect = rectangular_method(f, a, b, n);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_rect = end - start;
    std::cout << "Метод прямоугольников: π ≈ " << pi_rect << " (время: " << elapsed_rect.count() << " с)\n";

    start = std::chrono::high_resolution_clock::now();
    double pi_trap = trapezoidal_method(f, a, b, n);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_trap = end - start;
    std::cout << "Метод трапеций: π ≈ " << pi_trap << " (время: " << elapsed_trap.count() << " с)\n";

    start = std::chrono::high_resolution_clock::now();
    double pi_simp = simpson_method(f, a, b, n);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_simp = end - start;
    std::cout << "Метод Симпсона: π ≈ " << pi_simp << " (время: " << elapsed_simp.count() << " с)\n";
}

