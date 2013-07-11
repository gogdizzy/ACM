/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1001
*  数组中和等于K的数对
*  思路：先排序，然后双指针搜索
*/

#include <cstdio>
#include <algorithm>
using namespace std;

int  a[50000];

int main() {
  int  K, N, i, j, ans = 0;
  scanf( "%d%d", &K, &N );
  for( i = 0; i < N; ++i ) scanf( "%d", &a[i] );
  sort( a, a + N );
  for( i = 0, j = N - 1; i < j; ++i ) {
    while( i < j && a[i] + a[j] > K ) --j;
    if( i < j && a[i] + a[j] == K ) {
      printf( "%d %d\n", a[i], a[j] );
      ans++;
    }
  }
  if( !ans ) puts( "No Solution" );
  return 0;
}