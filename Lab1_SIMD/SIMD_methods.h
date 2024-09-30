#ifndef SIMD_methods
#define SIMD_methods

double simd_rectangular_method(double (*f)(double), double a, double b, int n);
double simd_trapezoidal_method(double (*f)(double), double a, double b, int n);
double simpson_method_simd(double (*f)(double), double a, double b, int n);
void test_simd_methods(int n);

#endif // SIMD_methods