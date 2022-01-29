//
// Created by 关鑫 on 2021/9/24.
//

#pragma once

#include <vector>
#include <algorithm>

template <typename T1, typename T2>
void ToOrderIndex(T1 inputBeg, T1 inputEnd, T2 outputBeg) {
    std::vector< typename std::iterator_traits<T1>::value_type > tmp(inputBeg, inputEnd);
    std::sort(tmp.begin(), tmp.end());
    auto cnt = std::unique(tmp.begin(), tmp.end()) - tmp.begin();
    auto oit = outputBeg;
    for (auto it = inputBeg; it != inputEnd; ++it, ++oit) {
        *oit = std::lower_bound(tmp.begin(), tmp.begin() + cnt, *it) - tmp.begin();
    }
}

