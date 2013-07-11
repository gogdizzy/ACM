/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1019
*  逆序数
*  思路：用归并排序，每次后面的元素向前移动，就将移动步数加入结果。
*/

#include <stdio.h>
#include <string.h>

#define ULL unsigned long long
int  a[50000], b[50000];
ULL  merge_sort( int left, int right ) {
  ULL  cnt = 0;
  int  mid, i, j, k;
  if( left < right ) {
    mid = ( left + right ) / 2;
    cnt += merge_sort( left, mid ) + merge_sort( mid + 1, right );
    i = left, j = mid + 1, k = left;
    while( i <= mid && j <= right ) {
      if( a[i] <= a[j] ) b[k++] = a[i++];
      else {
        b[k++] = a[j++];
        cnt += j - k;
      }
    }
    memcpy( b + k, a + i, sizeof(int) * ( mid + 1 - i ) );
    memcpy( b + k, a + j, sizeof(int) * ( right + 1 - j ) );
    memcpy( a + left, b + left, sizeof(int) * ( right + 1 - left ) );
  }
  return cnt;
}

int main() {
  int  n, i;
  scanf( "%d", &n );
  for( i = 0; i < n; ++i ) scanf( "%d", a + i );
  printf( "%I64u\n", merge_sort( 0, n - 1 ) );
  return 0;
}