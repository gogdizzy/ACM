/**
 * http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1215
 * 数组的宽度
 * 思路：查找每个数组作为最大值和最小值的影响范围，直接累加到一起
 **/

#include <stdio.h>
#include <algorithm>
#include <unordered_map>

#define MAXN 50000
#define MINANS 200

int a[MAXN];
int minl[MAXN], minr[MAXN], maxl[MAXN], maxr[MAXN];

int main() {

    int n;

    scanf( "%d", &n );
    for( int i = 0; i < n; ++i ) scanf( "%d", a + i );

    long long ans = 0;

    printf( "%lld\n", ans );

    return 0;
}
