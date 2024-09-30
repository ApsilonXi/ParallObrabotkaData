#include "integ_methods.h"
#include "SIMD_methods.h"
#include <iostream>

int main() {
    const int n = 1000000;  // Количество шагов

    std::cout << "Тестирование невекторизованных методов:\n";
    test_integration_methods(n);

    std::cout << "\nТестирование векторизованных методов:\n";
    test_simd_methods(n);

    return 0;
}