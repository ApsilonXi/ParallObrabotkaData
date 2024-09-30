#ifndef integ_methods
#define integ_methods

double rectangular_method(double (*f)(double), double a, double b, int n);
double trapezoidal_method(double (*f)(double), double a, double b, int n);
double simpson_method(double (*f)(double), double a, double b, int n);
double f(double x);
void test_integration_methods(int n);

#endif // integ_methods