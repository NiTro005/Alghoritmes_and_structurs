// Copyright 2024 Marina Usova

#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"

#include "../lib_pair/pair.h"

int main() {
#ifdef EASY_EXAMPLE

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
#endif  // EASY_EXAMPLE
#ifdef Pair
    TPair<int, int> pair1(1, 4);
    TPair<int, int> pair2(10, 10);

    TPair<int, int> resultPair = pair1 + pair2;
    std::cout << "Pair1 + Pair2 = " << resultPair << std::endl;

    pair1.swap(pair2);
    std::cout << "After swap: Pair1 = " << pair1 << ", Pair2 = " << pair2 << std::endl;
#endif // Pair


    return 0;
}
#endif  // EASY_EXAMPLE

