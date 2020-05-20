//
// Created by 关鑫 on 2020/5/18.
//

#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 100010

template < typename T >
class binary_indexed_tree_1d1mrq {

public:
    binary_indexed_tree_1d1mrq( int maxlen ) {
        this->maxlen = maxlen;
        bit_a = new T[maxlen + 1];
        memset( bit_a, 0, sizeof(T) * (maxlen + 1 ) );
    }

    virtual ~binary_indexed_tree_1d1mrq() {
        if( bit_a != nullptr ) delete[] bit_a;
    }

    inline int lowbit( int x ) { return x & -x; }

    // 修改点x的值，加v
    inline void modify( int x, T v ) {
        for( ; 0 < x && x <= maxlen; x += lowbit( x ) ) {
            bit_a[x] += v;
        }
    }

    // 查询a[1..x]的和
    inline T query( int x ) {
        T s = T();
        for( x = x > maxlen ? maxlen : x; x > 0; x -= lowbit( x ) ) {
            s += bit_a[x];
        }
        return s;
    }

    // 查询a[x1..x2]的和
    inline T query( int x1, int x2 ) {
        return query( x2 ) - query( x1 - 1 );
    }

private:
    // 基于1，所以注意数组边界
    // a[i]表示原来数组的值
    // bit_a就是在a的基础上做树状数组
    int maxlen;
    T *bit_a;
};

struct Edge {
    int son;
    int next;
};
int ec = 0;
Edge edge[MAXN * 2];
int fc[MAXN];
int pos = 0;
int st[MAXN];
int ed[MAXN];
binary_indexed_tree_1d1mrq< int > bit( MAXN * 2 );
long long ans = 0;

void dfs1( int x, int fa ) {
    st[x] = ++pos;
    for( int s = fc[x]; s; s = edge[s].next ) {
        if( edge[s].son != fa ) {
            dfs1( edge[s].son, x );
        }
    }
    ed[x] = ++pos;
}

void dfs2( int x, int fa ) {
    ans += bit.query( st[x] );
    bit.modify( st[x], 1 );
    bit.modify( ed[x], -1 );
    for( int s = fc[x]; s; s = edge[s].next ) {
        if( edge[s].son != fa ) {
            dfs2( edge[s].son, x );
        }
    }
    bit.modify( st[x], -1 );
    bit.modify( ed[x], 1 );
}

int main() {

    ios::sync_with_stdio( false );
    cin.tie( 0 );

    int n, x, y;

    cin >> n;

    ec = 0;
    for( int i = 1; i < n; ++i ) {
        cin >> x >> y;
        edge[++ec].next = fc[x]; fc[x] = ec; edge[ec].son = y;
        edge[++ec].next = fc[y]; fc[y] = ec; edge[ec].son = x;
    }
    dfs1( 1, 0 );

    ec = 0;
    memset( fc, 0, sizeof( fc ) );
    for( int i = 1; i < n; ++i ) {
        cin >> x >> y;
        edge[++ec].next = fc[x]; fc[x] = ec; edge[ec].son = y;
        edge[++ec].next = fc[y]; fc[y] = ec; edge[ec].son = x;
    }
    dfs2( 1, 0 );

    cout << ans << '\n';

    return 0;
}

