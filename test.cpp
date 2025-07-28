#include <iostream>

#include "mf/matrix.hpp"

#define pr_expr(e) std::cout << #e << ": " << (e) << "\n"

typedef mf::Mat<double, 2, 2> Mat2x2;

template<typename DataType, int Rows, int Cols> void print_mat(const mf::Mat<DataType, Rows, Cols> &mat) {
    int i, j;

    for(i = 0; i != Rows; ++i) {
        printf("| ");
        for(j = 0; j != Cols; ++j) {
            std::cout << reinterpret_cast<const DataType(&)[Rows][Cols]>(mat)[i][j] << " ";
        }
        printf("|\n");
    }
    printf("\n");
}

int main(void) {
    Mat2x2 m;
    print_mat(m);

    m.at(0, 0) = 1;
    m.at(0, 1) = 2;
    m.at(1, 0) = 3;
    m.at(1, 1) = 4;
    print_mat(m);

    Mat2x2 m2({
        {5, 6},
        {7, 8},
    });
    print_mat(m2);

    m2 = {
        {-1, 0},
        {25, 7},
    };
    print_mat(m2);

    Mat2x2 m3({5, 6, 7, 8});
    print_mat(m3);

    m3 = {0, 1, 2, 3};
    print_mat(m3);

    m3[0][0] = 1;
    m3[0][1] = 2;
    m3[1][0] = 3;
    m3[1][1] = 4;
    print_mat(m3);

    Mat2x2 mt = m.transpose();
    print_mat(mt);

    return 0;
}
