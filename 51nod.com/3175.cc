//
// Created by 关鑫 on 2021/5/8.
//

#include <iostream>

using namespace std;

const int MAXN = 100001;
const int P = 23333333;

int dp[MAXN];

inline
int min(int a, int b) {
    return a < b ? a : b;
}

int main() {

    ios::sync_with_stdio( false );
    cin.tie( 0 );

    int n, max = 0;
    cin >> n;
    dp[0] = 1;
    for(int i = 1; i <= n; ++i) {
        //for(int v = i; v <= n && v <= i * i; v += i) {
        for(int v = i; v <= n && v <= i; v += i) {
            //for(int p = max + v; p >= v; --p) {
            for(int p = n; p >= v; --p) {
                dp[p] = (dp[p] + dp[p - v]) % P;
            }
        }
        if(max < n) max = min(max + i * i, n);
    }

    cout << dp[n];

    return 0;
}