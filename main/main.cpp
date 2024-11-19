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
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include "../lib_list/tlist.h"
    int main() {
        srand(time(NULL));
        long int size;
        std::cout << "Enter the size of the array: ";
        std::cin >> size;
        TList<long int> mas;
        TList<long int> mas1;
        TList<long int> mas2;

        double timespent[10];
        clock_t start = clock();
        for (size_t i = 0; i < size; i++) {
            mas.push_back(i);
        }
        
        clock_t end = clock();
        timespent[0] = (double)(end - start);
        std::cout << "Time spent push_back method in list: " << timespent[0] << " ms" << std::endl;
        start = clock();
        mas.find(0 + rand() % size);
        mas.find(0 + rand() % size);
        mas.find(0 + rand() % size);
        mas.find(0 + rand() % size);
        mas.find(0 + rand() % size);
        mas.find(0 + rand() % size);
        mas.find(0 + rand() % size);
        end = clock();
        timespent[6] = (double)(end - start) / 7;
        std::cout << "Time spent find method in list: " << timespent[6] << " ms" << std::endl;

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas1.push_front(0 + rand() % 1000);
        }
        end = clock();
        timespent[1] = (double)(end - start);

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas2.insert(i, 0 + rand() % 1000);
        }
        end = clock();
        timespent[2] = (double)(end - start);
        std::cout << std::endl;
        std::cout << "Time spent push_front method in list: " << timespent[1] << " ms" << std::endl;
        std::cout << "Time spent insert method in list: " << timespent[2] << " ms" << std::endl;

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas.pop_back();
        }
        end = clock();
        timespent[3] = (double)(end - start);

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas1.pop_front();
        }
        end = clock();
        timespent[4] = (double)(end - start);

        for (auto it = mas.begin(); it != mas.end(); ++it) {
            std::cout << *it << " ";
        }

        std::cout << std::endl;
        std::cout << "Time spent pop_back method in list: " << timespent[3] << " ms" << std::endl;
        std::cout << "Time spent pop_front method in list: " << timespent[4] << " ms" << std::endl;

        return 0;
}
#endif  // List

#ifdef DMASSIVE
#include "../lib_dmassive/archive.h"
#include <stdlib.h>
#include <time.h>
#include <ctime>
#define FIND_VALUE 10000000

    int main() {
        srand(time(NULL));
        long int size;
        std::cout << "Enter the size of the array: ";
        std::cin >> size;
        TDMassive<long int> mas(size);
        TDMassive<long int> mas1(size);
        TDMassive<long int> mas2(size);

        double timespent[10];
        clock_t start = clock();
        for (size_t i = 0; i < size; i++) {
            mas.push_back(i);
        }
        clock_t end = clock();
        timespent[0] = (double)(end - start);
        std::cout << "Time spent push_back method in massive: " << timespent[0] << " ms" << std::endl;

        start = clock();
        mas.find_first(0 + rand() % size);
        mas.find_first(0 + rand() % size);
        mas.find_first(0 + rand() % size);
        mas.find_first(0 + rand() % size);
        mas.find_first(0 + rand() % size);
        mas.find_first(0 + rand() % size);
        mas.find_first(0 + rand() % size);
        end = clock();
        timespent[6] = (double)(end - start) / 6;
        std::cout << "Time spent find method in massive: " << timespent[6] << " ms" << std::endl;


        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas1.push_front(0 + rand() % 1000);
        }
        end = clock();
        timespent[1] = (double)(end - start);

        std::cout << "Time spent push_front method in massive: " << timespent[1] << " ms" << std::endl;

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas2.insert(0 + rand() % 1000, i);
        }
        end = clock();
        timespent[2] = (double)(end - start);
        
       
        std::cout << "Time spent insert method in massive: " << timespent[2] << " ms" << std::endl;
        std::cout << std::endl;

       

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas.pop_back();
        }
        end = clock();
        timespent[3] = (double)(end - start);

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas1.pop_front();
        }
        end = clock();
        timespent[4] = (double)(end - start);

        start = clock();
        for (size_t i = 0; i < size; i++) {
            mas2.remove_by_index(i);
        }
        end = clock();
        timespent[5] = (double)(end - start);

            for (auto it = mas.begin(); it != mas.end(); ++it) {
                std::cout << *it << " ";
            }

        std::cout << std::endl;
        std::cout << "Time spent pop_back method in massive: " << timespent[3] << " ms" << std::endl;
        std::cout << "Time spent pop_front method in massive: " << timespent[4] << " ms" << std::endl;
        std::cout << "Time spent remove_by_index method in massive: " << timespent[5] << " ms" << std::endl;
        return 0;
    }
#endif  // DMassive
