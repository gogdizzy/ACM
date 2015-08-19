/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1423

@solution
	任意选2点作为区间计算，肯定超时，因为光区间就O(n^2)种
	我们发现每个值作为最大值时，它是有一个“控制范围的”，向左或向右碰到比它大的为止
	这种题型让我们想到了单调栈
	先考虑这个元素作为最大值，次大值在它的左边，那么我们只需要维护一个递减的单调栈
	在当前元素入栈前，先pop所有比它小的元素，因为后面的计算将用不到这些值，这些pop
	出得值是可以作为次大值的，用它们和当前元素异或，更新答案
	然后对数组反方向再做一次即可，总体复杂度O(n)

	后来查看了@8rfuz的代码，发现了一次遍历的方法，就是维持正向遍历不变，当push当前
	元素时，直接用它和栈顶元素异或一下，这样就无需反向遍历了。这是因为反向遍历时，
	当前元素作为次大，最大是不会越过当前栈顶的，因为当前栈顶比当前元素大。这个方法
	对时间和空间都有比较大的改善，总体复杂度O(n)
*/

#define VER2

#ifdef VER2

#include <stdio.h>

#define INF  0x7FFFFFFF
#define MAXN 100000

int s[MAXN+1];
int top = -1;

int main() {

	int  n, i, x;
	int  ans = 0;

	s[++top] = INF;
	scanf( "%d", &n );
	for( i = 0; i < n; ++i ) {
		scanf( "%d", &x );
		while( s[top] < x ) {
			if( ( x ^ s[top] ) > ans ) ans = x ^ s[top];
			--top;
		}
		if( top > 0 ) {
			if( ( x ^ s[top] ) > ans ) ans = x ^ s[top];
		}
		s[++top] = x;
	}

	printf( "%d\n", ans );

	return 0;
}

#endif


#ifdef VER1

#include <stdio.h>
#include <stack>

using namespace std;

#define MAXN 100000

int s[MAXN];
stack< int >  stk;

int main() {

	int  n, i, pre, tmp;
	int  ans = 0;

	scanf( "%d", &n );
	for( i = 0; i < n; ++i ) scanf( "%d", s + i );

	stk.push( s[0] );
	for( i = 1; i < n; ++i ) {
		while( !stk.empty() ) {
			pre = stk.top();
			if( pre < s[i] ) {
				tmp = pre ^ s[i];
				if( tmp > ans ) ans = tmp;
				stk.pop();
			}
			else break;
		}
		stk.push( s[i] );
	}

	while( !stk.empty() ) stk.pop();
	stk.push( s[n-1] );
	for( i = n - 2; i >= 0; --i ) {
		while( !stk.empty() ) {
			pre = stk.top();
			if( pre < s[i] ) {
				tmp = pre ^ s[i];
				if( tmp > ans ) ans = tmp;
				stk.pop();
			}
			else break;
		}
		stk.push( s[i] );
	}
	
	printf( "%d\n", ans );

	return 0;
}

#endif
