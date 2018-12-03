/**
 * http://hihocoder.com/contest/hiho231/problem/1
 * 小Ho的强迫症
 * 思路：计算每个周期里是否会踩到
 *      每个脚印都在格子内部，则说明F<=L
 *      如果存在解，那么一定可以把这个解向左平移，使得至少有一个脚跟对准缝隙
 *      设G = gcd( D, L )
 *      如果延伸到无限远，那么可以知道对于一个长度为L的区间，脚跟可以到达的点为0, G, 2G, 3G, ... L-G
 *      所以只要F > G，那么当脚跟位于L-G时就一定会踩到缝隙
 **/


#include <stdio.h>

template <typename T>
T gcd( T a, T b ) {
    return b == 0 ? a : gcd( b, a % b );
}

int main() {
    int t, l, f, d;
    scanf( "%d", &t );

    while( t-- ) {
        scanf( "%d%d%d", &l, &f, &d );
        puts( gcd( l, d ) >= f ? "YES" : "NO" );
    }
    return 0;
}

