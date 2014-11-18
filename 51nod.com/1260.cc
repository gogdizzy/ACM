#include <stdio.h>

#define  P  1000000007
#define  LL  long long


LL solve( int n ) {
	if( n == 1 ) return 1;
	LL  ans = 0, tmp;
	for( int i = 1; i < n / 2; ++i ) {
		ans = ( ans + solve( i ) * solve( n - i ) ) % P;
	}
	tmp = solve( n / 2 ) * solve( n - n / 2 );
	return  ( ans + ans + ( ( n & 1 ) + 1 ) * tmp ) % P;
}

int main() {
	int  n;
	scanf( "%d", &n );
	printf( "%d\n", (int)solve( n ) );
	return 0;
}
