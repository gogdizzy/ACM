//
// Created by 关鑫 on 2021/7/3.
//

#include <stdio.h>
#include <bitset>

const int N = 10;
const int M = 10;
const int K = 1001;

int SG[K];
int A[N];
int B[M];
int n, m;

void initSG() {
    for(int i = 1; i < K; ++i) {
        std::bitset<12> bs;
        for(int z = 0; B[z] <= i && z < m; ++z) {
            bs.set(SG[i - B[z]], true);
        }
        for(int z = 0; ; ++z) {
            if(!bs.test(z)) {
                SG[i] = z;
                break;
            }
        }
    }
}

int main() {

    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", A + i);

    scanf("%d", &m);
    for(int i = 0; i < m; ++i) scanf("%d", B + i);

    initSG();

    int nim = 0;
    for(int i = 0; i < n; ++i) nim ^= SG[A[i]];

    for(int i = 0; i < n; ++i) {
        for(int z = 0; B[z] <= A[i] && z < m; ++z) {
            if((nim ^ SG[A[i]] ^ SG[A[i] - B[z]]) == 0) {
                printf("YES\n%d %d\n", i + 1, B[z]);
                return 0;
            }
        }
    }
    puts("NO");
    return 0;
}