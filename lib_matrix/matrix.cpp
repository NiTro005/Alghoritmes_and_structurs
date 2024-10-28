//#include <iostream>
//
//#include <utility>
//#include "../lib_vector/tvector.h"
//#include "../lib_matrix/matrix.h"
//
//template <typename T> class TVector;
//template <typename T>
//std::ostream& operator<<(std::ostream& out, const TUpperTriangularMatrix<T>& m);
//template <class T>
//class TUpperTriangularMatrix : TVector<TVector<T>> {
//private:
//    using TVector<TVector<T>>::_data;
//    using TVector<TVector<T>>::_start_index;
//public:
//    TUpperTriangularMatrix(size_t size = STEP_CAPACITY) : TVector<TVector<T>>(size) {
//        for (size_t i = 0; i < size; i++) {
//            _values[i] = TVector<T>(size - i, i);
//        }
//    }
//
//    TUpperTriangularMatrix(T const* const * arr, size_t size) : TVector<TVector<T>>(size) {
//        for (size_t i = 0; i < size; i++) {
//            _values[i] = TVector<T>(size - i, i);
//            for (size_t j = 0; j < size - i; j++) {
//                _values[i][j + i] = arr[i][j + i];
//            }
//        }
//    }
//
//    TUpperTriangularMatrix(const TUpperTriangularMatrix &m) : TVector<TVector<T>>(m) {}
//    TUpperTriangularMatrix(const TVector<TVector<T>> &m) : TVector<TVector<T>>(m) {}
//    ~TUpperTriangularMatrix() {}
//
//    size_t size() const { return _values.size(); }
//
//    using TVector<TVector<T>>::operator[];
//    using TVector<TVector<T>>::operator=;
//
//    TUpperTriangularMatrix& operator+=(const TUpperTriangularMatrix& other) {
//        *this = this->TVector<TVector<T>>::operator+(other);
//        return *this;
//    }
//
//    TUpperTriangularMatrix operator+(const TUpperTriangularMatrix& other) {
//        return TVector<TVector<T>>::operator+(other);
//    }
//
//    friend std::ostream& operator <<<T>(std::ostream& out, const TUpperTriangularMatrix<T>& m);
//
//    /* ... */
//};
//
//template <class T>
//std::ostream& operator << <T>(std::ostream& out, const TUpperTriangularMatrix<T>& m) {
//    for (size_t i = 0; i < m.size(); i++) {
//        for (size_t j = 0; j < m.size(); j++) {
//            if (j < i) { out << 0 << " "; }
//            else { out << m[i][j] << " "; }
//        }
//        out << "\n";
//    }
//    return out;
//}
//
//int main() {
//    int vec_data[] = { 1, 2, 3, 4, 5 };
//    int vec_size = 5;
//    TVector<int> vec1(vec_data, vec_size), vec2(5), vec3(10), res_v(5);
//
//    for (int i = 0; i < 5; i++) {
//        vec2[i] = -5 + rand() % 11;
//    }
//
//    int matrix_size = 3;
//    int **matrix_data = new int*[matrix_size];
//    for (int i = 0; i < matrix_size; i++) {
//        matrix_data[i] = new int[matrix_size];
//        for (int j = 0; j < matrix_size; j++) {
//            matrix_data[i][j] = -5 + rand() % 11;
//        }
//    }
//
//    TUpperTriangularMatrix<int> m1(matrix_data, matrix_size);
//
//    for (int i = 0; i < matrix_size; i++) {
//        matrix_data[i] = new int[matrix_size];
//        for (int j = 0; j < matrix_size; j++) {
//            matrix_data[i][j] = -5 + rand() % 11;
//        }
//    }
//
//    TUpperTriangularMatrix<int> m2(matrix_data, matrix_size), res_m;
//
//    std::cout << "CHECK VECTOR OPERATIONs" << std::endl << std::endl;
//
//    std::cout << "vec1: " << vec1 << std::endl;
//    std::cout << "vec2: " << vec2 << std::endl;
//
//    vec1 += vec2;
//
//    std::cout << "vec1+=vec2" << std::endl; 
//    std::cout << "vec1: " << vec1 << std::endl;
//    std::cout << "vec2: " << vec2 << std::endl;
//
//    res_v = vec1 + vec2;
//
//    std::cout << "res = vec1 + vec2" << std::endl;
//    std::cout << "res: " << res_v << std::endl;
//    std::cout << "vec1: " << vec1 << std::endl;
//    std::cout << "vec2: " << vec2 << std::endl;
//
//    std::cout << std::endl << "CHECK MATRIX OPERATIONs" << std::endl << std::endl;
//
//    std::cout << "m1: " << std::endl << m1 << std::endl;
//    std::cout << "m2: " << std::endl << m2 << std::endl;
//
//    m1 += m2;
//
//    std::cout << "m1+=m2" << std::endl;
//    std::cout << "m1: " << m1 << std::endl;
//    std::cout << "m2: " << m2 << std::endl;
//
//    res_m = m1 + m2;
//
//    std::cout << "res = m1 + m2" << std::endl;
//    std::cout << "res: " << std::endl<< res_m << std::endl;
//    std::cout << "m1: " << std::endl << m1 << std::endl;
//    std::cout << "m2: " << std::endl << m2 << std::endl;
//
//    system("pause");
//    return 0;
//}