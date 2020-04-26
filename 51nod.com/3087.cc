//
// Created by 关鑫 on 2020/4/24.
//

#include <cstdio>
#include <cstdint>

#define MAXP 1000001

// rho type cycle

int8_t flag[MAXP];

int main() {
    int64_t n, m, x0, a, b, p, x;
    scanf("%lld %lld", &n, &m);
    scanf("%lld %lld %lld %lld", &x0, &a, &b, &p);

    x = x0;
    int cycle = 0;
    int used = 0;
    while( used < n ) {
        x = (x * a + b) % p;
        if( flag[x] == 2 ) break;
        if( ++flag[x] == 2 ) ++cycle;
        ++used;
    }

    int64_t rep = 0, rem = 0;
    if(cycle > 0) {
        rep = ( n - used ) / cycle + 2;
        rem = ( n - used ) % cycle;
        while( rem > 0 ) {
            ++flag[x];
            x = ( x * a + b ) % p;
            --rem;
        }
    }

    int64_t sum = 0;
    for(int64_t x = p - 1; x >= 0 && m > 0; --x) {
        if( flag[x] ) {
            int64_t cnt = flag[x] == 1 ? 1:
                    flag[x] == 2 ? rep:
                    rep + 1;
            if(m < cnt) {
                sum += x * m;
                m = 0;
            }
            else {
                sum += x * cnt;
                m -= cnt;
            }
        }
    }

    printf("%lld\n", sum);

    return 0;
}

