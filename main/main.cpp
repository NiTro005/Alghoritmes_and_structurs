// Copyright 2024 Marina Usova
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <ctime>
#include <cstdint>
#include <random>
#define   POLINOM
#ifdef EASY_EXAMPLE
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
        std::mt19937 gen(static_cast<unsigned int>(time(NULL)));
        int64_t size;
        std::cout << "Enter the size of the array: ";
        std::cin >> size;
        TList<int64_t> mas;
        TList<int64_t> mas1;
        TList<int64_t> mas2;

        double timespent[10];
        clock_t start = clock();
        for (size_t i = 0; i < size; i++) {
            mas.push_back(i);
        }

        clock_t end = clock();
        timespent[0] = static_cast<double>(end - start);
        std::cout << "Time spent push_back method in list: "
            << timespent[0] << " ms" << std::endl;
        start = clock();
        mas.find(0 + gen() % size);
        mas.find(0 + gen() % size);
        mas.find(0 + gen() % size);
        mas.find(0 + gen() % size);
        mas.find(0 + gen() % size);
        mas.find(0 + gen() % size);
        mas.find(0 + gen() % size);
        end = clock();
        timespent[6] = static_cast<double>(end - start) / 7;
        std::cout << "Time spent find method in list: "
            << timespent[6] << " ms" << std::endl;

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas1.push_front(0 + gen() % 1000);
        }
        end = clock();
        timespent[1] = static_cast<double>(end - start);

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas2.insert(i, 0 + gen() % 1000);
        }
        end = clock();
        timespent[2] = static_cast<double>(end - start);
        std::cout << std::endl;
        std::cout << "Time spent push_front method in list: "
            << timespent[1] << " ms" << std::endl;
        std::cout << "Time spent insert method in list: "
            << timespent[2] << " ms" << std::endl;

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas.pop_back();
        }
        end = clock();
        timespent[3] = static_cast<double>(end - start);

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas1.pop_front();
        }
        end = clock();
        timespent[4] = static_cast<double>(end - start);

        for (auto it = mas.begin(); it != mas.end(); ++it) {
            std::cout << *it << " ";
        }

        std::cout << std::endl;
        std::cout << "Time spent pop_back method in list: "
            << timespent[3] << " ms" << std::endl;
        std::cout << "Time spent pop_front method in list: "
            << timespent[4] << " ms" << std::endl;

        std::cout << "Theoretical memory usage for 10000 elements: "
            << size * (sizeof(int) + sizeof(TNode<int>*)) << " bytes\n";

        return 0;
    }
#endif  // List

#ifdef DMASSIVE
#include "../lib_dmassive/archive.h"

    int main() {
        std::mt19937 gen(static_cast<unsigned int>(time(NULL)));
        int64_t size;
        std::cout << "Enter the size of the array: ";
        std::cin >> size;
        TDMassive<int64_t> mas(size);
        TDMassive<int64_t> mas1(size);
        TDMassive<int64_t> mas2(size);

        double timespent[10];
        clock_t start = clock();
        for (size_t i = 0; i < size; i++) {
            mas.push_back(0 + gen() % size);
        }
        clock_t end = clock();
        timespent[0] = static_cast<double>(end - start);
        std::cout << "Time spent push_back method in massive: "
            << timespent[0] << " ms" << std::endl;

        start = clock();
        mas.find_first(0 + gen() % size);
        mas.find_first(0 + gen() % size);
        mas.find_first(0 + gen() % size);
        mas.find_first(0 + gen() % size);
        mas.find_first(0 + gen() % size);
        mas.find_first(0 + gen() % size);
        mas.find_first(0 + gen() % size);
        end = clock();
        timespent[6] = static_cast<double>(end - start) / 7;
        std::cout << "Time spent find method in massive: "
            << timespent[6] << " ms" << std::endl;

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas1.push_front(0 + gen() % 1000);
        }
        end = clock();
        timespent[1] = static_cast<double>(end - start);

        std::cout << "Time spent push_front method in massive: "
            << timespent[1] << " ms" << std::endl;

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas2.insert(0 + gen() % 1000, i);
        }
        end = clock();
        timespent[2] = static_cast<double>(end - start);

        std::cout << "Time spent insert method in massive: "
            << timespent[2] << " ms" << std::endl;
        std::cout << std::endl;

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas.pop_back();
        }
        end = clock();
        timespent[3] = static_cast<double>(end - start);

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas1.pop_front();
        }
        end = clock();
        timespent[4] = static_cast<double>(end - start);

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas2.remove_by_index(i);
        }
        end = clock();
        timespent[5] = static_cast<double>(end - start);

        /*for (auto it = mas.begin(); it != mas.end(); ++it) {
            std::cout << *it << " ";
        }*/

        std::cout << std::endl;
        std::cout << "Time spent pop_back method in massive: "
            << timespent[3] << " ms" << std::endl;
        std::cout << "Time spent pop_front method in massive: "
            << timespent[4] << " ms" << std::endl;
        std::cout << "Time spent remove_by_index method in massive: "
            << timespent[5] << " ms" << std::endl;

        std::cout << "Actual memory usage: " << mas.capacity()
            * sizeof(int) + 16 << " bytes\n";
        return 0;
    }
#endif  // DMassive

#ifdef STACKS
#include "../lib_stack/stack.h"
#include "../lib_stackOnList/lstack.h"

    int main() {
        std::mt19937 gen(static_cast<unsigned int>(time(NULL)));
        int64_t size;
        std::cout << "Enter the size of the array: ";
        std::cin >> size;
        TStack<int64_t> mas(size);
        LStack<int64_t> mas1(size);
        double timespent[10];
        clock_t start = clock();
        for (size_t i = 0; i < size; i++) {
            mas.push(i);
        }
        clock_t end = clock();
        timespent[0] = static_cast<double>(end - start);
        std::cout << "Time spent push method in stack on massive: "
            << timespent[0] << " ms" << std::endl;

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas1.push(i);
        }
        end = clock();
        timespent[1] = static_cast<double>(end - start);
        std::cout << "Time spent push method in stack on list: "
            << timespent[1] << " ms" << std::endl;

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas.pop();
        }
        end = clock();
        timespent[3] = static_cast<double>(end - start);

        std::cout << std::endl;
        std::cout << "Time spent pop method in stack on massive: "
            << timespent[3] << " ms" << std::endl;

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas1.pop();
        }
        end = clock();
        timespent[2] = static_cast<double>(end - start);

        std::cout << std::endl;
        std::cout << "Time spent pop method in stack on list: "
            << timespent[2] << " ms" << std::endl;
        return 0;
    }
#endif  // Stacks

#ifdef POLINOM
#include <vector>
#include <string>
#include "../lib_polinom/polinom.h"

    int main() {
        CMonom m1(3.0);
        m1._powers[0] = 2;
        m1._powers[1] = 1;

        CMonom m2(4.0);
        m2._powers[0] = 2;
        m2._powers[1] = 1;

        CMonom m3 = m1 + m2;
        std::cout << "m3: " << m3 << std::endl;

        CPolynom p1;
        p1.monoms.push_back(m1);
        p1.monoms.push_back(CMonom(2.0));

        CPolynom p2;
        p2.monoms.push_back(m2);
        p2.monoms.push_back(CMonom(1.0));

        CPolynom p3 = p1 + p2;

        std::vector<float> values = { 2, 3, 1 };
        std::cout << "p3 evaluated: " << p3.evaluate(values) << std::endl;

        std::string polynomStr = "3x1^2x2^1 + 4x1^2x2^1 + 2";
        CPolynom p4(polynomStr);
        return 0;
    }
#endif  // Polinom
