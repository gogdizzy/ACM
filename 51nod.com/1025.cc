/**
*  http://51nod.com/onlineJudge/questionCode.html#!problemId=1025
*  矩阵中不重复的元素 V2
*  思路：题目范围不大，可以硬算，只要设计好比较好的数据结构
*    能够重复的数据只能是这样的形式，a^x == b^y，则a^k = b 或 b^k = a
*    所以统计一下10000以内的这样的数，在判断时，直接转为底数最小的形式。
*    剪枝：只是当一个数的平方作为底数不可能出现时，直接就将出现m个不同的数，无需再向set中插入了。
*    不使用剪枝会超时。
*/

#include <cstdio>
#include <set>
using namespace std;
#define  MAXN  10000

set< int >  appear[MAXN];
int fact[10000][2];

int main() {
        int  m, n, a, b, x, y, k, ans = 0;
        scanf( "%d%d%d%d", &m, &n, &a, &b );

        for( x = 2; x < MAXN; ++x ) {
                if( fact[x][0] != 0 ) continue;
                for( y = x, k = 1; y < MAXN; y *= x, ++k ) {
                        fact[y][0] = x;
                        fact[y][1] = k;
                }
        }

        for( x = a; x < a + n; ++x ) {
                if( fact[x][1] == 1 && fact[x][0] * fact[x][0] >= a + n ) {
                         ans += m;  continue;
                }
                for( y = b; y < b + m; ++y ) {
                        appear[ fact[x][0] ].insert( fact[x][1] * y );
                }
        }

        for( x = 2; x < a + n; ++x ) ans += appear[x].size();

        printf( "%d\n", ans );

        return 0;
}