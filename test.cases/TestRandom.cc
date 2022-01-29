//
// Created by 关鑫 on 2021/9/2.
//

#include "Random.h"

int main() {

    RandomInt ri(1, 10);

    for(int i = 0; i < 100; ++i) {
        printf("%d\n", ri.get());
    }

    return 0;
}