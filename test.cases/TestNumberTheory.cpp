//
// Created by 关鑫 on 2021/9/2.
//

#include <stdio.h>

#include "NumberTheory.h"
#include "PrimeTable.h"


int main() {
    PrimeTable pt(40000);
    auto mp = getPrimeFactors(100, pt.begin(), pt.end());
    for (auto& it : mp) {
        printf("%d %d\n", it.first, it.second);
    }

    for(auto& x : getFactors(100, pt.begin(), pt.end())) {
        printf("%d\n", x);
    }

    return 0;
}