// Copyright 2024 Marina Usova

#define PAIR
#ifdef EASY_EXAMPLE
#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"



int main() {
    int a, b;
    float result;

    a = 1; b = 4;

    try {
        result = division(a, b);
        std::cout << a << " / " << b << " = "
            << std::setprecision(2) << result << std::endl;
    }
    catch (std::exception err) {
        std::cerr << err.what() << std::endl;
    }

    a = 1; b = 0;

    try {
        result = division(a, b);
        std::cout << a << " / " << b << " = "
            << std::setprecision(2) << result << std::endl;
    }
    catch (std::exception err) {
        std::cerr << err.what() << std::endl;
    }
    return 0;
    }
#endif  // EASY_EXAMPLE
#ifdef PAIR
#include "../lib_pair/pair.h"
    int main() {
        TPair<int, int> pair1(1, 4);
        TPair<int, int> pair2(10, 10);
        pair1.swap(pair2);
        std::cout << "After swap: Pair1 = " <<
            pair1 << ", Pair2 = " << pair2 << std::endl;
        return 0;
    }
#endif  // Pair
