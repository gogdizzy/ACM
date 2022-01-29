//
// Created by 关鑫 on 2021/9/13.
//

#include <stdio.h>
#include <stdint.h>
#include <algorithm>

const int P = 1000000007;
const int N = 100001;

int a[N];
int m[N];
int cnt[32][N];

//const int SqrtN = 1000;
//int b[SqrtN];
//
//int getOr(int st, int ed) {
//    int blockSt = (st + SqrtN - 1) / SqrtN;
//    int blockEd = (ed + 1) / SqrtN;
//    int ans = 0;
//    if (blockSt >= blockEd) {
//        for (int i = st; i <= ed; ++i) ans |= a[i];
//    }
//    else {
//        for( int i = st; i < blockSt * SqrtN; ++i ) ans |= a[i];
//        for( int i = blockSt; i < blockEd; ++i ) ans |= b[i];
//        for( int i = blockEd * SqrtN; i <= ed; ++i ) ans |= a[i];
//    }
//    return ans;
//}

int calc(int bit, int st, int ed) {

    int64_t andValue = bit % P;
    int64_t orValueSum = 0;
    for (int k = 0; k < 32; ++k) {
        int64_t orValue = m[ed - st];
        int pos = st;
        while (pos < ed) {
            if (cnt[k][pos] > 0) {
                int len = std::min(ed - pos, cnt[k][pos]);
                orValue -= m[len];
                pos += len;
            }
            else {
                pos = -cnt[k][pos];
            }
        }
        orValueSum = (orValueSum + orValue * (1 << k) % P + P) % P;
    }
    printf("%x %d %d %lld %lld\n", bit, st, ed, andValue, orValueSum);
    return andValue * orValueSum % P;
}

int main() {

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", a + i);
    for (int i = 0; i < N; ++i) m[i] = (int64_t)i * (i + 1) / 2 % P;

    for (int k = 0; k < 32; ++k) {
        int bit = (1 << k);
        int pos = n;
        int cnt0 = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (a[i] & bit) {
                cnt0 = 0;
                cnt[k][i] = -pos;
            }
            else {
                pos = i;
                cnt[k][i] = ++cnt0;
            }
        }
    }

    int ans = 0;
    for (int k = 0; k < 32; ++k) {
        int bit = (1 << k);
        int st = -1;
        int ed = -1;
        for (int i = 0; i <= n; ++i) {
            if (a[i] & bit) {
                if (st < 0) st = i;
            }
            else {
                if (st >= 0) {
                    ed = i;
                    ans = (ans + calc(bit, st, ed)) % P;
                    st = -1;
                }
            }
        }
    }
    
    printf("%d\n", ans);

    return 0;
}