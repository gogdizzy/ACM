/*
@author gogdizzy
@date   2015-09-21
@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1202
@solution
	我们先假设空序列也是一种方案，最后在结果中减去1就可以
	end[i]表示以数值i为结尾的方案的总个数，在数组中，i可能出现多次

	如果读入一个从没出现的数x，那么end[x]初始值是0，之前的任何一个方案后面
	接x可以组成一个新方案，所以end[x]就是之前的总方案数，现在的总方案数要乘以2

	如果读入一个出现过的数x，设当前方案数为sum，把x接到sum种方案后面，所以以x
	结尾的方案就是sum种，但是总方案数并不是简单乘以2，而是要去除之前以x结尾和
	现在以新读入x结尾两种方案的公共部分，这个公共部分就是之前的end[x]
*/
#include <stdio.h>
#define  P  1000000007
#define  MAXN  100001

int  end[MAXN];

int main() {
	int  n, i, x, y;
	long long sum = 1;
	for( scanf( "%d", &n ), i = 1; i <= n; ++i ) {
		scanf( "%d", &x );
		y = end[x];
		end[x] = sum;
		sum = ( sum + sum - y ) % P;
	}
	printf( "%d\n", sum > 0 ? sum - 1 : sum - 1 + P );
	return 0;
}
