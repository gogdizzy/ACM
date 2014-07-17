// 
// http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1005
//

#ifdef  VER2

#include "BintBase10.h"

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

