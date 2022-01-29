//
// Created by 关鑫 on 2021/9/2.
//

#pragma once

#include <map>
#include <set>
#include <functional>

template<typename T1, typename T2, typename T3>
T1 powerModulo(T1 x, T2 p, T3 m) {
    T1 ans = 1;
    T1 tmp = x;
    while (p) {
        if (p & 1) ans = ans * tmp % m;
        p >>= 1;
        tmp = tmp * tmp % m;
    }
    return ans;
}

template<typename T>
std::map<T, int> getPrimeFactors(T n) {
    std::map<T, int> ans;
    for (T i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            int cnt = 0;
            do {
                ++cnt;
                n /= i;
            } while(n % i == 0);
            ans.insert({i, cnt});
        }
    }
    if (n > 1) ans.insert({n, 1});
    return ans;
}

template<typename T, typename Iter>
std::map<T, int> getPrimeFactors(T n, Iter primeBegin, Iter primeEnd) {
    std::map<T, int> ans;
    for (Iter it = primeBegin; *it * *it <= n && it != primeEnd; ++it) {
        auto i = *it;
        if (n % i == 0) {
            int cnt = 0;
            do {
                ++cnt;
                n /= i;
            } while(n % i == 0);
            ans.insert({static_cast<T>(i), cnt});
        }
    }
    if (n > 1) ans.insert({n, 1});
    return ans;
}

template<typename T>
std::set<T> getFactors(T n) {
    std::set<T> ans;
    for(T i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            ans.insert(i);
            ans.insert(n / i);
        }
    }
    return ans;
}

template<typename T, typename Iter>
std::set<T> getFactors(T n, Iter primeBegin, Iter primeEnd) {
    std::set<T> ans;
    std::map<T, int> primeFactors = getPrimeFactors(n, primeBegin, primeEnd);
    typedef typename std::map<T, int>::iterator FactorIt;
    std::function<void(FactorIt, T)> dfs;
    dfs = [&](FactorIt it, T v) {
        if (it == primeFactors.end()) {
            ans.insert(v);
            return;
        }
        T tmp = 1;
        FactorIt nextIt = it;
        ++nextIt;
        for (int i = 0; i <= it->second; ++i) {
            dfs(nextIt, v * tmp);
            tmp *= it->first;
        }
    };
    dfs(primeFactors.begin(), 1);
    return ans;
}
