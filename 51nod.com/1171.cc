/**
 * https://www.51nod.com/Challenge/Problem.html#!#problemId=1171
 * 两个数的平方和
 * 思路：http://www.cppblog.com/wujiawei/archive/2010/08/18/123784.html
 *      https://blog.csdn.net/new_ke_2014/article/details/22200943
 **/


#include <cstdio>
#include <map>
#include <vector>
#include <set>
#include <tuple>

#define LL long long

template <typename T>
T gcd( T a, T b ) {
    return b == 0 ? a : gcd( b, a % b );
}

template < typename T >
T mulmod( const T& a, const T& b, const T& p ) {
    T ans = 0, tmp = a, b0 = b;
    while( b0 != 0 ) {
        if( b0 & 1 ) ans = (ans + tmp) % p;
        tmp = ( tmp + tmp ) % p;
        b0 /= 2;
    }
    return ans;
}

template < typename T >
T powmod( const T& a, const T& b, const T& p ) {
    T ans = 1, tmp = a, b0 = b;
    while( b0 != 0 ) {
        if( b0 & 1 ) ans = mulmod(ans, tmp, p);
        tmp = mulmod(tmp, tmp, p);
        b0 /= 2;
    }
    return ans;
}

template < typename T >
struct MillerRabin {
    static bool test( const T &p, int iter ) {

        if( !( p & 1 ) ) return p == 2;  // even number

        T pd1 = p - 1, d = p - 1;
        int s = 0;
        while( !( d & 1 ) ) {
            d /= 2;
            ++s;
        }

        for( int i = 0; i < iter; ++i ) {
            T a = rand() % ( p - 1 ) + 1;
            if( a == 1 ) continue;


            T m = powmod( a, d, p );
            printf("a = %lld %lld %lld %lld\n", a, d, p, m);
            int r = 0;
            for( ; r < s && m != 1 && m != pd1; ++r ) {
                // m = mulmod( m, m, p );
                printf("m = %lld\n", m);
                m = mulmod(m, m, p);
            }
            if( r > 0 && m != pd1 ) return false;
        }
        return true;
    }
};

template < typename T >
struct PollardRho {
    std::vector <T> factors;

    void factorsize( T n ) {
        while( !( n & 1 ) ) {
            factors.push_back( 2 );
            n /= 2;
        }

        if( MillerRabin< T >::test( n, 10 ) ) {
            factors.push_back( n );
            return;
        }
        printf("MR test not prime %lld\n", n);

        T f;
        do {
            T base = rand() % ( n - 2 ) + 2;
            T c = rand() % ( n - 1 ) + 1;
            f = find1( n, base, c );
        } while( f == n );
        factorsize( f );
        factorsize( n / f );
    }


protected:
    T find1( const T &n, const T &base, const T &c ) {
        T x = base;
        T y = base;
        T d = 1;
        auto g = [ & ]( const T &x ) { return ( mulmod(x, x, n) + c ) % n; };
        while( d == 1 ) {
            x = g( x );
            y = g( g( y ) );
            d = gcd( ( x - y + n ), n );
        }
        return d;
    }

    T find2( const T &n, const T &base, const T &c ) {
        T x_fixed = base, x = base, d = 1;
        int size = 2;
        while( d == 1 ) {
            for( int count = 1; ( count <= size ) && ( d <= 1 ); ++count ) {
                x = ( mulmod(x, x, n) + c ) % n;
                d = gcd( x - x_fixed + n, n );
            }
            size = size * 2;
            x_fixed = x;
        }
        return d;
    }
};

//把a限定在[-m/2, m/2]范围内
LL limit(LL a, LL m)
{
    if (a > (m >> 1)) {
        a -= m;
    }
    else if (a < -(m >> 1)) {
        a += m;
    }
    return a;
}

// (a * b + c * d) / p
LL calc(LL a, LL b, LL c, LL d, LL p) {
    __int128 ans = ((__int128)a * b + (__int128)c * d) / p;
    return ans;
}

std::pair<LL, LL> primeToAB(LL p) {
    LL a, b, m, u, v;
    if (p == 2) {
        a = b = 1;
    }
    else
    {
        for (LL x = p - 2; x > 1; --x) {
            a = powmod(x, (p - 1) / 4, p);
            if (powmod(a, 2LL, p) == p - 1) break;
        }
        b = 1;
        while ((m = calc(a, a, b, b, p)) != 1) {
            printf("m == %lld\n", m);
            u = limit(a % m, m);
            v = limit(b % m, m);

            LL tmp = calc(u, b, -v, a, m);
            a = calc(u, a, v, b, m);
            b = tmp;
        }
    }
    return std::make_pair(std::abs(a), std::abs(b));
}

typedef std::set< std::pair<LL, LL> > MySet;
std::vector< std::tuple<LL, LL, int> > abc;
MySet identity{{0, 1}};
MySet ans;

void cross(const MySet & a0, const MySet & b0, MySet & ret) {
    LL a, b;
    for (auto& ait : a0) {
        for (auto& bit : b0) {
            a = std::abs(ait.first * bit.first + ait.second * bit.second);
            b = std::abs(ait.first * bit.second - ait.second * bit.first);
            if (a > b) std::swap(a, b);
            ret.emplace(a, b);
            a = std::abs(ait.first * bit.second + ait.second * bit.first);
            b = std::abs(ait.first * bit.first - ait.second * bit.second);
            if (a > b) std::swap(a, b);
            ret.emplace(a, b);
        }
    }
}

void crossN(const MySet & a0, int pos, int cnt, MySet& ret) {
    if (cnt == 0) {
        ret = a0;
        return;
    }
    MySet tmp = a0;
    for (int i = 0; i < cnt; ++i) {
        ret.clear();
        cross(tmp, {{std::get<0>(abc[pos]), std::get<1>(abc[pos])}}, ret);
        tmp = ret;
    }
}

void print(const MySet & a0) {
    printf("  set:\n");
    for (auto& it : a0) {
        printf("    %lld %lld\n", it.first, it.second);
    }
}

void dfs(int pos, const MySet & a0, const MySet & b0) {
    if (pos >= abc.size()) {
printf("Add\n");
print(a0);
print(b0);
        cross(a0, b0, ans);
printf("Add end\n");
        return;
    }

    int cnt = std::get<2>(abc[pos]);
    MySet a, b;
    for (int i = 0; i <= cnt; ++i) {
        a.clear(); b.clear();
        crossN(a0, pos, i, a);
        crossN(b0, pos, cnt - i, b);
        dfs(pos + 1, a, b);
    }
}

int main() {
    LL n;
    scanf( "%lld", &n );

    std::map<LL, int> primeFactors;
    PollardRho<LL> pollardRho;
    pollardRho.factorsize(n);
    for (auto p : pollardRho.factors) {
        ++primeFactors[p];
        printf("factor: %lld\n", p);
    }

    LL commonMul = 1;

    for (auto kv : primeFactors) {
        if (kv.first % 4 == 3) {
            if (kv.second % 2 == 1) {
                puts("No Solution");
                return 0;
            }
            else {
                for (int i = 0; i < kv.second / 2; ++i) {
                    commonMul *= kv.first;
                }
            }
        }
        else {
            auto ab = primeToAB(kv.first);
            if (ab.first > ab.second) std::swap(ab.first, ab.second);
            printf("%lld %d -> %lld %lld\n", kv.first, kv.second, ab.first, ab.second);
            abc.emplace_back(ab.first, ab.second, kv.second);
        }
    }

    dfs(0, identity, identity);
    for (auto& it : ans) {
        printf("%lld %lld\n", it.first * commonMul, it.second * commonMul);
    }


    return 0;
}