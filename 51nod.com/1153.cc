/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1153

@solution
	维护一个递减单调栈，每个位置附加一个数据，表示到这个位置累加的最长序列长度
	每个数据自己就是一个子序列，长度为1
	假设目前栈中有 s[0] > s[1] > s[2] 3个数据，新来一个数据x，并且
	s[0] > x > s[1] > s[2]

	1>
	对于s[2]来说，它和x之间没有比它大的数，否则之前就会把s[2]弹出，所以如果B序列
	中把x的下标排在s[2]的下标前是可以的，因为他们之间的所有数字都比s[2]小，所以
	x为开头的序列长度就是s[2]的序列长度加1，弹出s[2]

	2>
	再来看s[1]，因为它和s[2]之间所有的数据都小于s[1]，也小于s[2]（如果大于s[2]，则
	在s[1]，s[2]之间还会有其他数据），所以B序列中s[1]下标放在s[2]前面也是可以的，
	所以这时应该更新s[1]的长度为 max( l[1], l[2] + 1 )，就是之前计算它的时候的长度
	和它后面一个数据的长度加1，取较大值

	接下来对比x和s[1]，和上面对比x和s[2]一个思路（步骤1>），会把s[1]弹出，并更新x
	的长度，然后碰到s[0]停止，将x和它对应的长度放入栈中，所以接下来栈的状态就变成了
	s[0] > x ，只包含两个元素了。

	当所有的数据都更新完成时，如果栈中还有数据，就把他们依次向前更新，一直到头，
	头部数据对应的长度就是答案。

*/

#include <stdio.h>

#define MAXN 50000
#define MAX( a, b ) ( (a) > (b) ? (a) : (b) )

int q[MAXN];
int qc = 0;
int l[MAXN];

int main() {
    
    int n, x, ans = 0, tmp;
    scanf( "%d", &n );
    
    while( n-- ) {
        scanf( "%d", &x );
        tmp = 1;
        while( qc > 0 && x > q[qc-1] ) {
            tmp = MAX( tmp, l[qc-1] ) + 1;
            --qc;
        }
        q[qc] = x;
        l[qc] = tmp;
        ++qc;
    }
    
    for( int i = qc - 1; i > 0; --i ) {
        l[i-1] = MAX( l[i-1], l[i] + 1 );
    }
    
    ans = l[0];
    printf( "%d\n", ans );
    
    return 0;
}
