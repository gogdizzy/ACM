//
// Created by 关鑫 on 2021/4/14.
//
// 参考: https://blog.csdn.net/worldwide_d/article/details/53812713
// 经典nim游戏，先手必输，就是所有堆石子的异或值为0
// 至少有一堆石子数量不变，先统计任意取法数量（包含至少一堆数量不变和所有堆数量都变），如果所有堆都减掉一颗再统计一次（这个就是所有堆数量都变），两个的差值就是至少有一堆不变
// 每一堆石子看成一个二进制数，从高位向低位遍历，假设前k-1位不变，从第k位改变，这要求所有数字的前k-1位的异或是0
// 再遍历一下数组，假设第i堆石子是第一个该位从1变成0的
// 1> 对于第k位为1的堆，这一位从1变成0，有(1 << k)种取法，剩余0 ~ (1<<k)-1 个
// 2> 对于第k位为1的堆，这一位从1变成1（不变），那么剩下的石子有 a[i] % (1 << k) + 1种方法，例如0b110，k=2，可以有0b100，0b101，0b110三种剩余
// 3> 对于第k位为0的堆，这一位就是0，剩下的石子也有a[i] % (1 << k) + 1种方法
// 对于第一种情况，我们可以先取其它数字的情况，即a[i]前面的数字（前k位不动，后面的位按照第二和第三种情况），a[i]后面的数字（前k-1位不动，后面的位按照上面说的三种情况任取），
// 当其它数字都确定了，a[i]的数字也就确定了
// 因为a[i]前面的数字的第k位都不动，所以它们的异或值可以确定
// 因为a[i]是第一个该位变成0的，那么我们就要从后往前做一个dp,
// dp[i][0]表示从后往前到 a[i] 的时候，第k位异或为0有多少种取法
// dp[i][1]表示从后往前到 a[i] 的时候，第k位异或为1有多少种取法

#include <cstdio>
#include <cstdint>

#define P 1000000007
#define N 101

typedef uint64_t MyInt;

int stone[N];
int n;
MyInt dp[N][2];

MyInt solve() {
    MyInt ans(0);
    bool allBitZero = true;
    for(int k = 29; k >= 0; --k) {
        const int curBit = (1 << k);
        dp[n][0] = 1;
        dp[n][1] = 0;
        for(int i = n - 1; i >= 0; --i) {
            const int lowNumCount = stone[i] % curBit + 1;
            if(stone[i] & curBit) {
                dp[i][0] = (dp[i+1][0] * curBit + dp[i+1][1] * lowNumCount) % P;
                dp[i][1] = (dp[i+1][0] * lowNumCount + dp[i+1][1] * curBit) % P;
            }
            else {
                dp[i][0] = (dp[i+1][0] * lowNumCount) % P;
                dp[i][1] = (dp[i+1][1] * lowNumCount) % P;
            }
        }

        int curMask = 0;
        MyInt firstPart(1);
        for(int i = 0; i < n; ++i) {
            const int lowNumCount = stone[i] % curBit + 1;
            if(stone[i] & curBit) {
                ans = (ans + firstPart * dp[i+1][curMask]) % P;
                curMask ^= 1;
            }
            firstPart = (firstPart * lowNumCount) % P;
        }
        if(curMask != 0) {
            allBitZero = false;
            break;
        }
    }
    if(allBitZero) ans = (ans + 1) % P;
    return ans;
}

int main() {

    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", stone + i);

    MyInt c1 = solve();
    for(int i = 0; i < n; ++i) --stone[i];
    MyInt c2 = solve();
    printf("%lld\n", (c1 - c2 + P) % P);

    return 0;
}

/*
#include <cstdio>
#include <cstdint>

#define N 101

template< int P >
struct IntWithMod {
public:
    IntWithMod() : _x(0) {}
    IntWithMod(int64_t x) : _x(x % P) {}
    IntWithMod operator=(int64_t x) {
        _x = x % P;
        return *this;
    }
    inline
    IntWithMod operator+(const IntWithMod &other) {
        return IntWithMod((_x + other._x) % P);
    }
    inline
    IntWithMod operator-(const IntWithMod &other) {
        return IntWithMod((_x - other._x) % P);
    }
    inline
    IntWithMod operator*(const IntWithMod &other) {
        return IntWithMod((_x * other._x) % P);
    }

    inline int64_t value() const { return _x; }
    inline int64_t positiveValue() const { return (_x + P) % P; }
private:
    int64_t _x;
};

typedef IntWithMod<1000000007> MyInt;

int stone[N];
int n;
MyInt dp[N][2];

MyInt solve() {
    MyInt ans(0);
    bool allBitZero = true;
    for(int k = 29; k >= 0; --k) {
        const int curBit = (1 << k);
        dp[n][0] = 1;
        dp[n][1] = 0;
        for(int i = n - 1; i >= 0; --i) {
            const int lowNumCount = stone[i] % curBit + 1;
            if(stone[i] & curBit) {
                dp[i][0] = dp[i+1][0] * curBit + dp[i+1][1] * lowNumCount;
                dp[i][1] = dp[i+1][0] * lowNumCount + dp[i+1][1] * curBit;
            }
            else {
                dp[i][0] = dp[i+1][0] * lowNumCount;
                dp[i][1] = dp[i+1][1] * lowNumCount;
            }
        }

        int curMask = 0;
        MyInt firstPart(1);
        for(int i = 0; i < n; ++i) {
            const int lowNumCount = stone[i] % curBit + 1;
            if(stone[i] & curBit) {
                ans = ans + firstPart * dp[i+1][curMask];
                curMask ^= 1;
            }
            firstPart = firstPart * lowNumCount;
        }
        if(curMask != 0) {
            allBitZero = false;
            break;
        }
    }
    if(allBitZero) ans = ans + 1;
    return ans;
}

int main() {

    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", stone + i);

    MyInt c1 = solve();
    for(int i = 0; i < n; ++i) --stone[i];
    MyInt c2 = solve();
    printf("%lld\n", (c1 - c2).positiveValue());

    return 0;
}
*/