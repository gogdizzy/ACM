//
// Created by 关鑫 on 2021/9/2.
//

#include "PrimeTable.h"

int main() {

    PrimeTable pt(10000);

    for(auto it = pt.begin(); it != pt.end(); ++it) {
        printf("%u\n", *it);
    }

    return 0;
}