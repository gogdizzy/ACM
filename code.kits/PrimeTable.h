//
// Created by 关鑫 on 2021/9/2.
//

#pragma once

#include <cstdint>
#include <cmath>
#include <vector>

class PrimeTable {

    typedef uint32_t Type;
    typedef std::vector<Type>::iterator Iter;
    
public:
    PrimeTable(uint32_t maxn) :
        _maxn(maxn), _isPrime(_maxn, true)
    {
        _isPrime[0] = _isPrime[1] = false;
        Type rt = static_cast<Type>(sqrt((double)_maxn) + 1);
        for (Type i = 2; i <= _maxn; ++i) {
            if (_isPrime[i]) {
                _primes.push_back(i);
                if (i < rt) {
                    for (Type j = i * i; j <= _maxn; j += i) {
                        _isPrime[j] = false;
                    }
                }
            }
        }
    }

    inline
    bool isPrime(int x) { return _isPrime[x]; }

    inline
    Iter begin() { return _primes.begin(); }

    inline
    Iter end() { return _primes.end(); }

    inline
    size_t size() { return _primes.size(); }

private:
    uint32_t _maxn;
    std::vector<Type> _primes;
    std::vector<bool> _isPrime;
};
