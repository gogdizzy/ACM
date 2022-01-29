//
// Created by 关鑫 on 2021/9/30.
//

#include <iostream>
#include <cstdint>
#include <algorithm>

using namespace std;
typedef u32 u32;

const int N = 100001;

struct PreSum {
    u32 s1;
    u32 s2;
    u32 b1;
    u32 b2;
    u32 s1_x_b1;
    u32 s2_x_b1;
    u32 s1_x_b2;
    u32 s2_x_b2;

    void set(u32 s1, u32 s2, u32 b1, u32 b2) {
        this->s1 = s1;
        this->s2 = s2;
        this->b1 = b1;
        this->b2 = b2;
        s1_x_b1 = s1 * b1;
        s2_x_b1 = s2 * b1;
        s1_x_b2 = s1 * b2;
        s2_x_b2 = s2 * b2;
    }

    void add(const PreSum &other) {
        s1 += other.s1;
        s2 += other.s2;
        b1 += other.b1;
        b2 += other.b2;
        s1_x_b1 += other.s1_x_b1;
        s2_x_b1 += other.s2_x_b1;
        s1_x_b2 += other.s1_x_b2;
        s2_x_b2 += other.s2_x_b2;
    }

    void update(u32 x) {
        if (x < s1) s2 = s1, s1 = x;
        else if (x < s2) s2 = x;

        if (x > b1) b2 = b1, b1 = x;
        else if (x > b2) b2 = x;

        s1_x_b1 = s1 * b1;
        s2_x_b1 = s2 * b1;
        s1_x_b2 = s1 * b2;
        s2_x_b2 = s2 * b2;
    }
};

PreSum sum[N];

u32 ans = 0;

void calc(int l, int r) {
    if (l >= r) return;
    int m = l + (r - l >> 1);
    calc(l, m);
    calc(m + 1, r);
    for (int rr = m + 1; rr <= r; ++rr) {
        asdf
    }
}

int main() {

    ios::sync_with_stdio( false );
    cin.tie( 0 );

    int n;
    u32 x0, x;

    cin >> n;

    if (n <= 1) {
        cout << 0 << endl;
        return;
    }

    cin >> x0 >> x;
    sum[2].set(std::min(x0, x), std::max(x0, x), std::max(x0, x), std::min(x0, x));

    for( int i = 3; i <= n; ++i ) {
        cin >> x;
        sum[i] = sum[i - 1];
        sum[i].update(x);
        sum[i].add(sum[i - 1]);
    }

    calc(1, n);
    cout << ans;

    return 0;
}