#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define  N  100001
#define  JSPACE while( buff[j] == ' ' ) ++j
#define  READ(x) while( buff[j] >= '0' && buff[j] <= '9' ) ms[i][x] = ms[i][x] * 10 + buff[j++] - '0'

int  ms[N][2];

int  cmp( const void* a, const void* b )
{
	return  ((int*)a)[1] - ((int*)b)[1];
}

int main() {
	int  n;
	char  buff[64];
	scanf( "%d", &n ); getchar();
	if( n <= 0 ) { printf( "0\n" ); return 0; }
	for( int i = 0; i < n; ++i ) {
		gets( buff );
		int j = 0;
		JSPACE;
		READ( 0 );
		JSPACE;
		READ( 1 );
	}
	qsort( ms, n, sizeof(int)*2, cmp );
	int  sum = ms[0][0], count = 1;

	for( int j = 1; j < n; ++j ) {
		if( ms[j][1] >= sum ) {
			sum += ms[j][0];
			++count;
		}
	}
	printf( "%d\n", count );
	return 0;
}
