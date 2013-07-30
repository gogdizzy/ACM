/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1028
*  大数乘法 V2
*  思路：分治，将大的数平分成两段，复杂度O(n^1.6)
*    ( A * 10^k + B ) * ( C * 10^k + D ) = AC * 10^2k + [ ( A + B ) * ( C + D ) - AC - BD ] * 10^k + BD
*/

#include <stdio.h>
#include <string.h>

#define  LL  long long
#define  MOD  1000000000LL
#define  MAXN  100001
#define  MAXL  11120
#define  MAX( a, b )  ( (a) > (b) ? (a) : (b) )

LL  num1[MAXL], num2[MAXL], ans[MAXL*2];
int  len1, len2, lena;

char  buf[MAXN];

void  parse( char* str, LL* num, int & len ) {
	len = 0, num[0] = 0;
	char  *end = str, *beg;
	while( *end ) ++end;
	while( ( beg = end - 9 ) >= str ) {
		int  tmp = 0;
		for( int i = 0; i < 9; ++i ) tmp = tmp * 10 + beg[i] - '0';
		num[len++] = tmp;
		end = beg;
	}
	if( (beg = str) < end ) {
		int  tmp = 0;
		for( int i = 0; i < end - beg; ++i ) tmp = tmp * 10 + beg[i] - '0';
		num[len++] = tmp;
	}
}

void  add( LL* m1, int s1, LL* m2, int s2, LL* res, int & sr ) {
	if( s1 > s2 ) {  // 使左边长度不大于右边
		LL*  t1 = m1;
		m1 = m2; m2 = t1;
		int  t2 = s1;
		s1 = s2; s2 = t2;
	}
	int  i, carry = 0;
	for( i = 0; i < s1; ++i ) {
		res[i] = m1[i] + m2[i] + carry;
		carry = res[i] / MOD;
		res[i] %= MOD;
	}
	for( ; i < s2; ++i ) {
		res[i] = m2[i] + carry;
		carry = res[i] / MOD;
		res[i] %= MOD;
	}
	if( carry ) res[i++] = carry;
	sr = i;
}

void  sub( LL* m1, int s1, LL* m2, int s2, LL* res, int & sr ) {
	int  i, carry = 0;
	for( i = 0; i < s2; ++i ) {
		res[i] = m1[i] - m2[i] - carry;
		if( res[i] < 0 ) { res[i] += MOD; carry = 1; }
		else { carry = 0; }
	}
	for( ; i < s1; ++i ) {
		res[i] = m1[i] - carry;
		if( res[i] < 0 ) { res[i] += MOD; carry = 1; }
		else { carry = 0; }
	}
	for( --i; i > 0 && res[i] == 0; --i );
	sr = i + 1;
}

void  mul( LL* m1, int s1, LL* m2, int s2, LL* res, int & sr ) {
	sr = s1 + s2 - 1;
	memset( res, 0, sizeof(LL) * ( s1 + s2 ) );
	for( int i = 0; i < s1; ++i ) {
		for( int j = 0; j < s2; ++j ) {
			res[i+j] += m1[i] * m2[j];
		}
	}
	
	for( int k = 0; k < sr; ++k ) {
		res[k+1] += res[k] / MOD;
		res[k] %= MOD;
	}
	if( res[sr] > 0 ) ++sr;
}

// ( A * 10^k + B ) * ( C * 10^k + D ) = AC * 10^2k + [ ( A + B ) * ( C + D ) - AC - BD ] * 10^k + BD
void  mul2( LL* m1, int s1, LL* m2, int s2, LL* res, int & sr ) {

	int  i, j, carry;

	if( s1 <= 2 || s2 <= 2 ) mul( m1, s1, m2, s2, res, sr );
	else {
		if( s1 > s2 ) {  // 使左边长度不大于右边
			LL*  t1 = m1;
			m1 = m2; m2 = t1;
			int  t2 = s1;
			s1 = s2; s2 = t2;
		}

		int  s = ( s2 + 1 ) / 2;
		LL*  tmpm = new LL[s1+s2+10];
		int  lenm;

		if( s >= s1 ) {  // A == 0
			mul2( m1, s1, m2, s, res, sr );
			mul2( m1, s1, m2 + s, s2 - s, tmpm, lenm );
			carry = 0;
			for( i = s, j = 0; i < sr; ++i, ++j ) {
				res[i] += tmpm[j] + carry;
				carry = res[i] / MOD;
				res[i] %= MOD;
			}
			for( ; j < lenm; ++i, ++j ) {
				res[i] = tmpm[j] + carry;
				carry = res[i] / MOD;
				res[i] %= MOD;
			}
			if( carry ) res[i++] = carry;
			sr = i;
		}
		else {
			int  sr1, sr2;
			LL*  sum1 = new LL[s1+s2+10], *sum2 = new LL[s1+s2+10];
			int  lens1, lens2;

			mul2( m1, s, m2, s, res, sr1 );  // BD
			memset( res + sr1, 0, sizeof(LL) * ( 2 * s - sr1 ) );
			mul2( m1 + s, s1 - s, m2 + s, s2 - s, res + 2 * s, sr2 );  // AC
			sr = 2 * s + sr2;
			add( m1, s, m1 + s, s1 - s, sum1, lens1 ); // A + B
			add( m2, s, m2 + s, s2 - s, sum2, lens2 ); // C + D
			mul2( sum1, lens1, sum2, lens2, tmpm, lenm );  // ( A + B ) * ( C + D )
			add( res, sr1, res + 2 * s, sr2, sum1, lens1 ); // ( AC + BD )
			sub( tmpm, lenm, sum1, lens1, sum2, lens2 );  // [ ( A + B ) * ( C + D ) - AC - BD ]
			carry = 0;
			for( i = s, j = 0; j < lens2; ++i, ++j ) {
				res[i] += sum2[j] + carry;
				carry = res[i] / MOD;
				res[i] %= MOD;
			}
			for( ; carry != 0 && i < sr; ++i ) {
				res[i] += carry;
				carry = res[i] / MOD;
				res[i] %= MOD;
			}
			if( carry ) { res[i++] = carry; sr = i; }
			delete[] sum1;
			delete[] sum2;
		}

		delete[] tmpm;
	}
}

int main() {
	gets( buf ); parse( buf, num1, len1 );
	gets( buf ); parse( buf, num2, len2 ); 
	mul2( num1, len1, num2, len2, ans, lena );
	printf( "%I64d", ans[lena-1] );
	for( int i = lena - 2; i >= 0; --i ) printf( "%09I64d", ans[i] );
	puts( "" );
	return 0;
}