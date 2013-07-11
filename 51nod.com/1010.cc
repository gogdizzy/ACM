/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1010
*  ֻ��������2 3 5����
*  ˼·�������ݷ�Χ10^18�������61��2���ӣ���39��3���ӣ���27��5����
*        �����Ƚ����еĿ������ֶ������������Ȼ����ֲ��ҡ�
*/

#include <cstdio>
#include <algorithm>

#define ULL  unsigned long long
#define  MAXN  1500000000000000000ULL
#define  P2  61
#define  P3  39
#define  P5  27
ULL  tbl[P2*P3*P5+5];
int  cnt = 0;

int main() {
  int  t, i, j, k;
  ULL  x, m1, m2, m3;
  for( i = 0, m1 = 1; m1 < MAXN && i < P2; ++i, m1 *= 2 ) {
    for( j = 0, m2 = m1; m2 < MAXN && j < P3; ++j, m2 *= 3 ) {
      for( k = 0, m3 = m2; m3 < MAXN && k < P5; ++k, m3 *= 5 ) {
        tbl[cnt++] = m3;
      }
    }
  }
  std::sort( tbl, tbl + cnt );

  scanf( "%d", &t );
  while( t-- ) {
    scanf( "%I64u", &x );
    printf( "%I64u\n", *std::lower_bound( tbl + 1, tbl + cnt, x ) );
  }
  return 0;
}