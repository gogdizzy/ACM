//
// Created by 关鑫 on 2021/11/26.
//

#pragma once

#include <algorithm>

template<typename T>
void Swap(T beg, T mid, T end) {
    std::reverse(beg, mid);
    std::reverse(mid, end);
    std::reverse(beg, end);
}

template<typename T>
void MergeSortArray(T* arr, size_t len) {
    T* end = arr + len;
    for (size_t step = 1; step < len; step *= 2) {
        for (T* pLeft = arr, *pRight = pLeft + step; pRight < end; pLeft = pRight + step, pRight = pLeft + step) {
            T* pLeftCur = pLeft;
            T* pRightCur = pRight;
            while (pLeftCur < pRightCur && pRightCur < end) {

            }
        }
    }
}