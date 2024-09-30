#include "integ_methods.h"
#include "SIMD_methods.h"
#include <iostream>

int main() {
    const int n = 1000000;  // ���������� �����

    std::cout << "������������ ����������������� �������:\n";
    test_integration_methods(n);

    std::cout << "\n������������ ��������������� �������:\n";
    test_simd_methods(n);

    return 0;
}