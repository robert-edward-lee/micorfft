#ifndef HPP_MF_MATRIX
#define HPP_MF_MATRIX

#include <cassert>
#include <cstring>

#include "mf/types/integral.hpp"

namespace mf {

#define SINGLE 0
#define DOUBLE 1
#define MODEL SINGLE

template<typename DataType, int Rows, int Cols> class MatData {
public:
#if MODEL == SINGLE
    MF_CONSTEXPR_14 DataType &at(int row, int col) MF_NOEXCEPT {
        return data[Cols * row + col];
    }
    MF_CONSTEXPR_14 DataType (&at(int row) MF_NOEXCEPT)[Cols] {
        return reinterpret_cast<DataType(&)[Cols]>(data[Cols * row]);
    }
    MF_CONSTEXPR_14 const DataType &at(int row, int col) const MF_NOEXCEPT {
        return data[Cols * row + col];
    }
    MF_CONSTEXPR_14 const DataType (&at(int row) const MF_NOEXCEPT)[Cols] {
        return reinterpret_cast<const DataType(&)[Cols]>(data[Cols * row]);
    }
#elif MODEL == DOUBLE
    MF_CONSTEXPR_14 DataType &at(int row, int col) MF_NOEXCEPT {
        return data[row][col];
    }
    MF_CONSTEXPR_14 DataType (&at(int row) MF_NOEXCEPT)[Cols] {
        return data[row];
    }
    MF_CONSTEXPR_14 const DataType &at(int row, int col) const MF_NOEXCEPT {
        return data[row][col];
    }
    MF_CONSTEXPR_14 const DataType (&at(int row) const MF_NOEXCEPT)[Cols] {
        return data[row];
    }
#endif

private:
#if MODEL == SINGLE
    DataType data[Rows * Cols];
#elif MODEL == DOUBLE
    DataType data[Rows][Cols];
#endif
};

template<typename DataType, int Rows, int Cols> class Mat {
public:
    MF_CONSTEXPR_14 Mat() MF_NOEXCEPT {
        // std::memset(data, 0, sizeof(data));
    }

    MF_CONSTEXPR_14 Mat(const DataType (&other)[Rows][Cols]) MF_NOEXCEPT {
        std::memcpy(&data, other, sizeof(data));
    }
    MF_CONSTEXPR Mat &operator=(const DataType (&other)[Rows][Cols]) MF_NOEXCEPT {
        std::memcpy(&data, other, sizeof(data));
        return *this;
    }

    MF_CONSTEXPR_14 Mat(const DataType (&other)[Rows * Cols]) MF_NOEXCEPT {
        std::memcpy(&data, other, sizeof(data));
    }
    MF_CONSTEXPR Mat &operator=(const DataType (&other)[Rows * Cols]) MF_NOEXCEPT {
        std::memcpy(&data, other, sizeof(data));
        return *this;
    }

    MF_CONSTEXPR_14 Mat(const Mat &other) MF_NOEXCEPT {
        std::memcpy(&data, &other.data, sizeof(data));
    }
    MF_CONSTEXPR Mat &operator=(const Mat &other) MF_NOEXCEPT {
        std::memcpy(&data, &other.data, sizeof(data));
        return *this;
    }

    MF_CONSTEXPR_14 DataType &at(int row, int col) MF_NOEXCEPT {
        assert(0 <= row && row < Rows);
        assert(0 <= col && col < Cols);

        return data.at(row, col);
    }
    MF_CONSTEXPR_14 DataType (&at(int row) MF_NOEXCEPT)[Cols] {
        assert(0 <= row && row < Rows);

        return data.at(row);
    }

    MF_CONSTEXPR_14 DataType (&operator[](int row) MF_NOEXCEPT)[Cols] {
        return at(row);
    }

    MF_CONSTEXPR_14 Mat<DataType, Cols, Rows> transpose() const MF_NOEXCEPT {
        Mat<DataType, Cols, Rows> tmp;

        for(int i = 0; i != Rows; ++i) {
            for(int j = 0; j != Cols; ++j) {
                tmp.at(i, j) = data.at(j, i);
            }
        }

        return tmp;
    }

    MF_CONSTEXPR_14 void mul_eq(const Mat &other) MF_NOEXCEPT {}

private:
    // DataType data[Rows][Cols];
    MatData<DataType, Rows, Cols> data;
};

} // namespace mf

#endif // HPP_MF_MATRIX
