#include <stdio.h>

int main() {
  int  n, x, i = 0, j = 31622, c = 0;
  scanf( "%d", &n );
  while( i <= j ) {
    x = n - i * i;
    while( i < j && j * j > x ) --j;
    if( j * j == x ) { printf( "%d %d\n", i, j ); c = 1; }
    ++i;
  }
  if( !c ) puts( "No Solution" );
  return 0;
}
