/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1018
*  ����
*  ˼·�����ÿ⺯������
*/

#include <cstdio>
#include <algorithm>

int  a[50000];

int main() {
  int  n, i;
  for( scanf( "%d", &n ), i = 0; i < n; ++i ) scanf( "%d", a + i );
  std::sort( a, a + n );
  for( i = 0; i < n; ++i ) printf( "%d\n", a[i] );
  return 0;
}