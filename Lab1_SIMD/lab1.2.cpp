#include <immintrin.h> 

// SIMD версия метода прямоугольников
double simd_rectangular_method(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    __m128d h_vec = _mm_set1_pd(h);
    __m128d integral_vec = _mm_setzero_pd();

    for (int i = 0; i < n; i += 2) {
        __m128d x_vec = _mm_add_pd(_mm_set1_pd(a + (i + 0.5) * h), h_vec);
        integral_vec = _mm_add_pd(integral_vec, _mm_loadu_pd(&(f(x_vec[0]), f(x_vec[1]))));
    }

    double integral[2];
    _mm_storeu_pd(integral, integral_vec);

    return (integral[0] + integral[1]) * h;
}

// SIMD версия метода трапеций
double simd_trapezoidal_method(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    __m128d h_vec = _mm_set1_pd(h);
    __m128d integral_vec = _mm_setzero_pd();

    integral_vec = _mm_add_pd(integral_vec, _mm_set1_pd(f(a)));
    integral_vec = _mm_add_pd(integral_vec, _mm_set1_pd(f(b)));

    for (int i = 1; i < n; i += 2) {
        __m128d x_vec = _mm_add_pd(_mm_set1_pd(a), _mm_mul_pd(_mm_set1_pd(i * h), h_vec));
        integral_vec = _mm_add_pd(integral_vec, _mm_loadu_pd(&(f(x_vec[0]), f(x_vec[1]))));
    }

    return (integral_vec[0] + integral_vec[1]) * (h / 2);
}

// SIMD-версия функции Симпсона
double simpson_method_simd(double (*f)(double), double a, double b, int n) {
    if (n % 2 == 1) n++;  // n должен быть четным
    double h = (b - a) / n;

    // Начальные значения
    __m256d integral_even = _mm256_loadu_pd((double[]) { f(a), f(a + 2 * h), f(a + 4 * h), f(a + 6 * h) });
    __m256d integral_odd = _mm256_setzero_pd();

    // Цикл по интервалам
    for (int i = 1; i < n; i += 2) {
        double x = a + i * h;
        __m256d x_vector = _mm256_set1_pd(x);
        integral_odd = _mm256_add_pd(integral_odd, _mm256_set1_pd(f(x_vector[0])));
        integral_odd = _mm256_add_pd(integral_odd, _mm256_set1_pd(f(x_vector[1])));
        integral_odd = _mm256_add_pd(integral_odd, _mm256_set1_pd(f(x_vector[2])));
        integral_odd = _mm256_add_pd(integral_odd, _mm256_set1_pd(f(x_vector[3])));
    }

    __m256d result = _mm256_add_pd(integral_even, _mm256_mul_pd(integral_odd, _mm256_set1_pd(4.0)));

    // Суммируем значения из SIMD в скалярное значение
    double sum[4];
    _mm256_storeu_pd(sum, result);
    double integral = sum[0] + sum[1] + sum[2] + sum[3];

    // Добавляем границы интегрирования
    integral += f(a) + f(b);

    return integral * (h / 3);
}

void test_simd_methods(int n) {
    double a = 0.0;
    double b = 1.0;

    auto start = std::chrono::high_resolution_clock::now();
    double pi_rect_simd = simd_rectangular_method(f, a, b, n);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_rect_simd = end - start;
    std::cout << "SIMD метод прямоугольников: π ≈ " << pi_rect_simd << " (время: " << elapsed_rect_simd.count() << " с)\n";

    auto start = std::chrono::high_resolution_clock::now();
    double pi_trap_simd = simd_trapezoidal_method(f, a, b, n);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_trap_simd = end - start;
    std::cout << "SIMD метод трапеций: π ≈ " << pi_trap_simd << " (время: " << elapsed_trap_simd.count() << " с)\n";

    auto start = std::chrono::high_resolution_clock::now();
    double pi_simd = simpson_method_simd(f, a, b, n);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_simd = end - start;
    std::cout << "Метод Симпсона (SIMD): π ≈ " << pi_simd << " (время: " << elapsed_simd.count() << " с)\n";
}


