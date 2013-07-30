/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1027
*  大数乘法
*  思路：模拟乘法，硬算，用10^8进制
*/

#include <stdio.h>

#define  LL  long long
#define  CARRY  100000000LL

LL  num1[130], num2[130], ans[260];
int len1, len2, lena;
char  buf[1001];

void  parse( char* str, LL* num, int & len ) {
	len = 0, num[0] = 0;
	char  *end = str, *beg;
	while( *end ) ++end;
	while( ( beg = end - 8 ) >= str ) {
		int  tmp = 0;
		for( int i = 0; i < 8; ++i ) tmp = tmp * 10 + beg[i] - '0';
		num[len++] = tmp;
		end = beg;
	}
	if( (beg = str) < end ) {
		int  tmp = 0;
		for( int i = 0; i < end - beg; ++i ) tmp = tmp * 10 + beg[i] - '0';
		num[len++] = tmp;
	}
}

void  mul( LL* m1, int s1, LL* m2, int s2, LL* res, int & sr ) {
	for( int i = 0; i < s1; ++i ) {
		for( int j = 0; j < s2; ++j ) {
			res[i+j] += m1[i] * m2[j];
		}
	}
	sr = s1 + s2 - 1;
	for( int k = 0; k < sr; ++k ) {
		res[k+1] += res[k] / CARRY;
		res[k] %= CARRY;
	}
	if( res[sr] > 0 ) ++sr;
}

int main() {
	gets( buf ); parse( buf, num1, len1 );
	gets( buf ); parse( buf, num2, len2 ); 
	mul( num1, len1, num2, len2, ans, lena );
	printf( "%lld", ans[lena-1] ); 
	for( int i = lena - 2; i >= 0; --i ) printf( "%08lld", ans[i] );
	puts( "" );
	return 0;
}