//
// Created by 关鑫 on 2021/9/24.
//

#include "PreProcess.h"

void TestToOrderIndex() {

    const int N = 10;
    int a[N] = {5, 5, 4, 4, 3, 3, 2, 2, 1, 1};
    int b[N];
    ToOrderIndex(a, a + N, b);
    for (int i = 0; i < N; ++i) printf("%d ", b[i]);
}

int main() {

    TestToOrderIndex();

    return 0;
}