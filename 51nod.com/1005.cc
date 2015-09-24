/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1005

@solution
	简单的模拟
*/

#define VER2

#ifdef  VER2


#ifndef  __BINT_BASE10_H__
#define  __BINT_BASE10_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>

template< int ARR_SIZE = 32, int ELE_MOD = 1000000000, int ELE_WIDTH = 9 >
class BintBase10 {

public:
	BintBase10() : sign_(0), size_(0) {}

bool  read() {
	char  buf[4096];
	int  c, n;

	// jmp space or tab or return
	while( ( c = getchar() ) != EOF ) {
		if( c >= '-' ) break;
	}
	if( c == EOF ) return false;

	n = 0;
	do {
		buf[n++] = c;
	} while( ( c = getchar() ) != EOF && '0' <= c && c <= '9' );
	if( n == 0 ) return false;
	else buf[n] = 0;
	return  read( buf, n );
}

bool  read( const char* p, int w = -1 ) {
	if( p == NULL ) return false;
	while( *p != 0 && *p < '-' ) { ++p; --w; }
	if( *p == 0 ) return false;
	if( *p == '-' ) { ++p; --w; sign_ = 1; }

	if( w < 0 ) w = strlen( p );
	if( w <= 0 ) return false;

	const char* tail = p + w - ELE_WIDTH;
	int64_t  tmp;
	while( tail > p ) {
		tmp = 0;
		for( int i = 0; i < ELE_WIDTH; ++i ) tmp = tmp * 10 + tail[i] - '0';
		data_[ size_ ++ ] = tmp;

		tail -= ELE_WIDTH;
	}
	tmp = 0;
	for( int i = 0; i < ( tail + ELE_WIDTH - p ); ++i ) tmp = tmp * 10 + p[i] - '0';
	data_[ size_ ++ ] = tmp;

	return true;
}

int  write() {
	int  ret = 0;
	if( size_ == 0 || ( size_ == 1 && data_[0] == 0 ) ) { putchar( '0' ); return 1; }
	if( sign_ ) { putchar( '-' ); ++ret; }
	char  dig[ELE_WIDTH];

	// first data
	int  i;
	int64_t  tmp = data_[size_ - 1];
	for( i = 0; tmp > 0; ++i ) {
		dig[i] = tmp % 10;
		tmp /= 10;
	}
	ret += i;
	for( --i; i >= 0; --i ) putchar( dig[i] + '0' );

	// other data
	for( int pos = size_ - 2; pos >= 0; --pos ) {
		tmp = data_[pos];
		for( i = 0; i < ELE_WIDTH; ++i ) {
			dig[i] = tmp % 10;
			tmp /= 10;
		}
		ret += ELE_WIDTH;
		for( --i; i >= 0; --i ) putchar( dig[i] + '0' );
	}
	return ret;
}

int  write( char* p0 ) {

	char* p = p0;
	if( size_ == 0 ) { *p++ = '0'; return 1; }
	if( sign_ ) { *p++ = '-'; }
	char  dig[ELE_WIDTH];

	// first data
	int  i;
	int64_t  tmp = data_[size_ - 1];
	for( i = 0; tmp > 0; ++i ) {
		dig[i] = tmp % 10;
		tmp /= 10;
	}
	for( --i; i >= 0; --i ) *p++ = dig[i] + '0';

	// other data
	for( int pos = size_ - 2; pos >= 0; --pos ) {
		tmp = data_[pos];
		for( i = 0; i < ELE_WIDTH; ++i ) {
			dig[i] = tmp % 10;
			tmp /= 10;
		}
		for( --i; i >= 0; --i ) *p++ = dig[i] + '0';
	}

	return p - p0;
}

BintBase10 &  add( BintBase10& v ) {
	if( sign_ == v.sign_ ) add0( *this, v );
	else {
		int s = sub0( *this, v );
		if( s < 0 ) sign_ = 1 - sign_;
	}
}

static void add0( BintBase10& a, BintBase10& b ) {
	int  carry = 0;
	int  i;
	int  e1 = a.size_ < b.size_ ? a.size_ : b.size_;
	int  e2 = a.size_ > b.size_ ? a.size_ : b.size_;
	for( i = 0; i < e1; ++i ) {
		a.data_[i] += b.data_[i] + carry;
		if( a.data_[i] >= ELE_MOD ) { a.data_[i] -= ELE_MOD; carry = 1; }
		else carry = 0;
	}

	for( ; i < a.size_; ++i ) {
		if( carry == 0 ) return;
		a.data_[i] += carry;
		if( a.data_[i] >= ELE_MOD ) { a.data_[i] -= ELE_MOD; carry = 1; }
		else return;
	}

	for( ; i < b.size_; ++i ) {
		a.data_[i] = b.data_[i] + carry;
		if( a.data_[i] >= ELE_MOD ) { a.data_[i] -= ELE_MOD; carry = 1; }
		else carry = 0;
	}

	if( carry == 1 ) a.data_[i++] = 1;
	a.size_ = i;
}

static int sub0( BintBase10& a, BintBase10& b ) {
	int  r = cmp0( a, b );
	if( r == 0 ) {
		a.size_ = 1;
		a.data_[0] = 0;
		a.sign_ = 0;
		return 0;
	}

	int  carry = 0;
	int  i;
	if( r < 0 ) {
		for( i = 0; i < a.size_; ++i ) {
			a.data_[i] = b.data_[i] - a.data_[i] - carry;
			if( a.data_[i] < 0 ) { a.data_[i] += ELE_MOD; carry = 1; }
			else carry = 0;
		}
		for( ; i < b.size_; ++i ) {
			a.data_[i] = b.data_[i] - carry;
			if( a.data_[i] < 0 ) { a.data_[i] += ELE_MOD; carry = 1; }
			else carry = 0;
		}
	}
	else {
		for( i = 0; i < b.size_; ++i ) {
			a.data_[i] -= b.data_[i] + carry;
			if( a.data_[i] < 0 ) { a.data_[i] += ELE_MOD; carry = 1; }
			else carry = 0;
		}
		for( ; i < a.size_ && carry == 1; ++i ) {
			a.data_[i] -= carry;
			if( a.data_[i] < 0 ) { a.data_[i] += ELE_MOD; carry = 1; }
		}
	}

	for( --i; a.data_[i] == 0; --i );
	a.size_ = i + 1;
}

static int cmp0( BintBase10& a, BintBase10& b ) {
	if( a.size_ < b.size_ ) return -1;
	if( a.size_ > b.size_ ) return 1;
	for( int i = a.size_ - 1; i >= 0; --i ) {
		if( a.data_[i] < b.data_[i] ) return -1;
		if( a.data_[i] > b.data_[i] ) return 1;
	}
	return 0;
}

private:
	int      sign_;  // 0 for pos, 1 for neg
	int      size_;
	int64_t  data_[ARR_SIZE];
};


#endif



int main() {
	BintBase10< 1112, 1000000000, 9 >  b1, b2;
	b1.read();
	b2.read();
	b1.add( b2 );
	b1.write(); putchar( '\n' );
	return 0;
}

#endif


#ifdef  VER1

#include <stdio.h>
#include <string.h>

#define  MAXN  10005

char  A[MAXN];
char  B[MAXN];

void  check( char* num, int* sign, int* len, char** end ) {
	*len = strlen( num );
	*end = num + *len;
	if( *num == '-' ) { *sign = 1; --*len; }
	else *sign = 0;
}

char*  add( char* enda, int lena, char* endb, int lenb, char* endc ) {
	int  len1, len2, carry = 0;
	char *end1, *end2, *stop;

	if( lena > lenb ) { end1 = enda; len1 = lena; end2 = endb; len2 = lenb; }
	else { end1 = endb; len1 = lenb; end2 = enda; len2 = lena; }

	stop = end2 - len2;
	while( end2 > stop ) {
		*--endc = (*--end1) - '0' + (*--end2) + carry;
		if( *endc > '9' ) { *endc -= 10; carry = 1; }
		else  carry = 0;
	}

	stop = end1 + len2 - len1;
	while( end1 > stop ) {
		*--endc = (*--end1) + carry;
		if( *endc > '9' ) { *endc -= 10; carry = 1; }
		else  carry = 0;
	}
	if( carry == 1 ) *--endc = '1';
	
	return  endc;
}

char*  sub( char* enda, int lena, char* endb, int lenb, char* endc ) {
	int   carry = 0;
	char  *endc0 = endc, *stop = endb - lenb;
	
	while( endb > stop ) {
		*--endc = (*--enda) - (*--endb) + '0' - carry;
		if( *endc < '0' ) { *endc += 10; carry = 1; }
		else carry = 0;
	}

	stop = enda + lenb - lena;
	while( enda > stop ) {
		*--endc = (*--enda) - carry; 
		if( *endc < '0' ) { *endc += 10; carry = 1; }
		else carry = 0;
	}
	
	while( *endc == '0' ) ++endc;
	
	return  endc == endc0 ? endc - 1 : endc;
}


int main() {  
	char  *a, *b, *r; 
	int   sa, sb, la, lb;

	scanf( "%s%s", A, B ); 
	check( A, &sa, &la, &a );
	check( B, &sb, &lb, &b );
	
	if( sa == sb ) { 
		r = add( a, la, b, lb, B + 10003 );
		if( sa == 1 ) *--r = '-';
	}
	else if( la > lb || ( la == lb && memcmp( a - la, b - lb, la ) > 0 ) ) {
		r = sub( a, la, b, lb, B + 10003 );
		if( sa == 1 ) *--r = '-';
	}
	else {  
		r = sub( b, lb, a, la, B + 10003 );
		if( sb == 1 ) *--r = '-';
	}
	
	if( r[0] == '-' && r[1] == '0' ) ++r;
	puts( r );
	
	return 0;
}

#endif
