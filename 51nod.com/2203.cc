//
// Created by 关鑫 on 2021/5/18.
//

#include <cstdio>
#include <map>
#include <functional>

const int MAXN = 100001;

int beg[MAXN];
int end[MAXN];

inline int lowbit( int x ) { return x & -x; }

template < typename T >
class binary_indexed_tree_1drm1q {

public:
    binary_indexed_tree_1drm1q( int maxlen,
                                std::function< T( T, T ) > add = std::plus< T >(),
                                std::function< T( T ) > neg = std::negate< T >() ) {
        this->maxlen = maxlen;
        bit_b = new T[maxlen + 1];
        memset(bit_b, 0, sizeof(T) * (maxlen + 1));
        this->add = add;
        this->neg = neg;
    }

    virtual ~binary_indexed_tree_1drm1q() {
        if( bit_b != nullptr ) delete[] bit_b;
    }

    // 修改a[1..x]的值，加v
    inline void modify( int x, T v ) {
        for( x = x > maxlen ? maxlen : x; x > 0; x -= lowbit( x ) ) {
            bit_b[x] = add( bit_b[x], v );
        }
    }

    // 修改a[x1..x2]的值，加v
    inline void modify( int x1, int x2, T v ) {
        modify( x2, v );
        modify( x1 - 1, neg( v ) );
    }

    // 查询点x的值
    inline T query( int x ) {
        T s = T();
        for( ; 0 < x && x <= maxlen; x += lowbit( x ) ) {
            s = add( s, bit_b[x] );
        }
        return s;
    }

private:
    // 基于1，所以注意数组边界
    // a[i]表示原来数组的值
    // b[i]表示a[1..i]这个区间修改的值，则统计一个点被修改的值，只需要向上累计father值(即所有包含当前点的区间)
    // bit_b就是在b的基础上做树状数组
    int maxlen;
    T *bit_b;
    std::function< T( T, T ) > add;
    std::function< T( T ) > neg;
};

typedef binary_indexed_tree_1drm1q<int> Bit;

#define DEBEG  0
#if DEBEG
#define Printf(...) printf(__VA_ARGS__)
#else
#define Printf(...)
#endif

int main() {
    int t, n, m;

    scanf("%d", &t);
    while(t--) {
        std::map<int, int> order, zero;
        scanf("%d%d", &n, &m);
Printf("n = %d\n", n);
        for(int i = 0; i < n; ++i) {
            scanf("%d%d", beg + i, end + i);
            if(beg[i] == end[i]) {
                zero.insert({beg[i], 1});
                order.insert({beg[i], 1});
                --i, --n;
            }
            else {
                order.insert({beg[i], 1});
                order.insert({end[i] - 1, 1});
                order.insert({end[i], 1});
            }
        }
        int tot = 0;
        for(auto & it : order) {
            it.second = ++tot;

Printf("order %d %d\n", it.first, it.second);
        }
        Bit bitree(MAXN * 3);
        for(int i = 0; i < n; ++i) {
            zero.erase(beg[i]);
            zero.erase(end[i]);
            bitree.modify(order[beg[i]], order[end[i] - 1], 1);
Printf("Add %d %d\n", order[beg[i]], order[end[i] - 1]);
        }

        int ans = 0;
        for(int i = 1; i <= tot; ++i) {
            int parallel = bitree.query(i);
Printf("q: %d %d\n", i, parallel);
            if(parallel > ans) {
                ans = parallel;
Printf("qq: %d %d\n", i, parallel);
            }
        }
        if(ans == 0 && zero.size() > 0) ans = 1;
        for(auto & it : zero) {
            int parallel = bitree.query(order[it.first]);
            if(parallel == ans) {
                ++ans;
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
