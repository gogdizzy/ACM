/**
 * http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1277
 * 字符串中的最大值
 * 思路：KMP 或 后缀自动机
 **/

#include <stdio.h>
#include <string.h>

#define MAXN 100002

char s[MAXN];
int n[MAXN];
long long sum[MAXN];

int main() {
	scanf( "%s", s + 1 );
	int len = strlen( s + 1 );
	long long ans = 0, tmp;

	// s[1..n[i]] is suffix of s[1..i]
	n[1] = 0;
	for( int i = 2; i <= len; ++i ) {
		int j = n[i - 1];
		while( j && s[j + 1] != s[i] ) j = n[j];
		if( s[j + 1] == s[i] ) ++j;
		n[i] = j;
	}

	for( int i = len; i > 0; --i ) {
		tmp = i * ++sum[i];
		if( tmp > ans ) ans = tmp;
		sum[n[i]] += sum[i];
	}

	printf( "%lld\n", ans );
	return 0;
}
