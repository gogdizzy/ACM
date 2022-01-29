//
// Created by 关鑫 on 2021/12/21.
//

#pragma once

template <typename T>
class Matrix2D {
public:
    Matrix2D(size_t dim1, size_t dim2) {
        dim[0] = dim1;
        dim[1] = dim2;
        size_t size = dim1 * dim2;
        data = new T[size];
        memset(data, 0, sizeof(T) * size);
    }
    ~Matrix2D() {
        if (data) {
            delete[] data;
            data = nullptr;
        }
    }

    void Set(const std::initializer_list<T>& lis) {
        size_t pos = 0;
        for (auto x : lis) data[pos++] = x;
    }

    Matrix2D& operator=(const Matrix2D& other) {
        size_t size = dim[0] * dim[1];
        for (int i = 0; i < size; ++i) data[i] = other.data[i];
        return *this;
    }

    T& At(const size_t p1, const size_t p2) {
        return data[p1 * dim[1] + p2];
    }

    const T& At(const size_t p1, const size_t p2) const {
        return data[p1 * dim[1] + p2];
    }

    Matrix2D operator+(const Matrix2D& other) {
        size_t size = dim[0] * dim[1];
        Matrix2D rv(dim[0], dim[1]);
        for (int i = 0; i < size; ++i) rv.data[i] = this->data[i] + other.data[i];
        return rv;
    }

    Matrix2D operator-(const Matrix2D& other) {
        size_t size = dim[0] * dim[1];
        Matrix2D rv(dim[0], dim[1]);
        for (int i = 0; i < size; ++i) rv.data[i] = this->data[i] - other.data[i];
        return rv;
    }

    Matrix2D operator*(const Matrix2D& other) {
        size_t size = dim[0] * dim[1];
        Matrix2D rv(dim[0], dim[1]);

        for (int i = 0; i < dim[0]; ++i) {
            for (int j = 0; j < dim[1]; ++j) {
                for (int k = 0; k < other.dim[1]; ++k) rv.At(i, k) += this->At(i, j) * other.At(j, k);
            }
        }
        return rv;
    }

    Matrix2D operator*(const T& p) {
        size_t size = dim[0] * dim[1];
        Matrix2D rv(dim[0], dim[1]);
        for (int i = 0; i < size; ++i) rv.data[i] = this->data[i] * p;
        return rv;
    }

    Matrix2D operator%(const T& p) {
        size_t size = dim[0] * dim[1];
        Matrix2D rv(dim[0], dim[1]);
        for (int i = 0; i < size; ++i) rv.data[i] = this->data[i] % p;
        return rv;
    }

    void print() {
        size_t size = dim[0] * dim[1];
        for (int i = 0; i < size; ++i) printf("%lld ", data[i]);
        putchar('\n');
    }



private:
    T* data;
    size_t dim[2];
};
