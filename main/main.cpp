// Copyright 2024 Marina Usova

#define DMASSIVE
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
        TPair<int, int> pair2;
        std::cin >> pair2;
        std::cout << "Pair1 = " <<
            pair1 << ", Pair2 = " << pair2 << std::endl;
        pair1.swap(pair2);
        std::cout << "After swap: Pair1 = " <<
            pair1 << ", Pair2 = " << pair2 << std::endl;
        return 0;
    }
#endif  // Pair
#ifdef LIST
#include "../lib_list/tlist.h"
    int main() {
        TList<int> list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        for (auto it = list.begin(); it != list.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        return 0;
    }
#endif  // List

#ifdef DMASSIVE
#include "../lib_dmassive/archive.h"
    int main() {
        TDMassive<int> mas;
        mas.push_back(4);
        mas.push_back(5);
        mas.push_back(6);

        for (auto it = mas.begin(); it != mas.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        return 0;
    }
#endif  // DMassive
