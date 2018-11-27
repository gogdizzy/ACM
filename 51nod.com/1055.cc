/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1055
*  最长等差数列
*  思路：动态规划
*
*  参考：https://www.51nod.com/Challenge/ProblemSubmitDetail.html#!#judgeId=189267
*    每次贪心查找一个最长的，两个剪枝：1 不可能超过答案直接跳；2 只查序列前两项
*/

#define VER2

#ifdef VER2

#include <stdio.h>
#include <algorithm>
#include <unordered_map>

#define MAXN 10000

int a[MAXN];

struct qio {
    static int32_t read_i32() {
        int32_t sign = 1;
    }

    static uint32_t read_u32() {
        uint32_t rv = 0;
        char c = getchar();
        while( c < '0' || c > '9' ) c = getchar();
        while( '0' <= c && c <= '9' ) {
            rv = rv * 10 + c - '0';
            c = getchar();
        }
        return rv;
    }

    static long long read_i64() {

    }

    static unsigned long long read_u64() {

    }
};

int main() {

    freopen( "/Users/guanxin/Downloads/51nod_1055_3_in.txt", "rt", stdin );
    int n, maxa = 1, ans = 2;
    std::unordered_map< int, int > cnt;

    n = qio::read_u32();
    for( int i = 0; i < n; ++i ) {
        a[i] = qio::read_u32();
        ans = std::max( ans, ++cnt[a[i]] );
        if( a[i] > maxa ) maxa = a[i];
    }
    std::sort( a, a + n );
    n = std::unique( a, a + n ) - a;

    for( int i = 0; i < n - ans; ++i ) {
        int beg = a[i];
        for( int j = i + 1; j < n; ++j ) {
            int end = a[j];
            int delta = end - beg;
            long long tail = beg + (long long) delta * ( ans - 1 );
            if( tail >= maxa ) break;
            if( cnt.count( beg - delta ) || !cnt.count( (int) tail ) ) continue;
            int tmp = 2;
            while( cnt.count( end + delta ) ) {
                end += delta;
                ++tmp;
            }
            if( tmp > ans ) ans = tmp;
        }
    }

    printf( "%d\n", ans );

    return 0;
}

#endif

#ifdef VER1

#include <stdio.h>
#include <algorithm>
#include <unordered_map>

#define MAXN 10000

int a[MAXN];
short lap[MAXN][MAXN];

int main() {

    int n, ans = 1;
    std::unordered_map< int, int > cnt;

    scanf( "%d", &n );
    for( int i = 0; i < n; ++i ) {
        scanf( "%d", a + i );
        ans = std::max( ans, ++cnt[a[i]] );
    }
    std::sort( a, a + n );
    n = std::unique( a, a + n ) - a;

    for( int j = 0; j < n; ++j ) {
        for( int k = j + 1; k < n; ++k ) {
            lap[j][k] = 2;
        }
    }

    for( int j = n - 2; j > 0; --j ) {
        int i = j - 1, k = j + 1;
        int j2 = a[j] * 2;
        while( i >= 0 && k < n ) {
            int ik = a[i] + a[k];
            if( ik > j2 ) --i;
            else if( ik < j2 ) ++k;
            else {
                lap[i][j] = lap[j][k] + 1;
                if( lap[i][j] > ans ) ans = lap[i][j];
                --i; ++k;
            }
        }
    }

    printf( "%d\n", ans );

    return 0;
}

#endif


