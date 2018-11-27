/**
 * http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1055
 * 最长等差数列V2
 * 思路：每次贪心查找一个最长的，剪枝：1 不可能超过答案直接跳；2 只查序列前两项；3 尾部不存在直接跳
 **/

#include <stdio.h>
#include <algorithm>
#include <unordered_map>

#define MAXN 50000
#define MINANS 200

int a[MAXN];

int main() {

    int n, maxa = 1, ans = MINANS - 1;
    std::unordered_map< int, int > cnt( MAXN * 2 );

    scanf( "%d", &n );
    for( int i = 0; i < n; ++i ) {
        scanf( "%d", a + i );
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
            long long tail = beg + (long long)delta * ( ans - 1 );
            if( tail >= maxa ) break;
            if( cnt.count( beg - delta ) || !cnt.count( (int)tail ) ) continue;
            int tmp = 2;
            while( cnt.count( end + delta ) ) {
                end += delta;
                ++tmp;
            }
            if( tmp > ans ) ans = tmp;
        }
    }

    if( ans >= MINANS ) printf( "%d\n", ans );
    else puts( "No Solution" );

    return 0;
}

