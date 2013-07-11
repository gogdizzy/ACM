/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1006
*  最长公共子序列Lcs
*  思路：dp[i][j]表示第一个字符串到第i个字符，第二个字符串到第j个字符时，最长公共子序列的长度
*        转移方程 dp[i][j] = max{ dp[i-1][j-1] + ( str1[i] == str2[j] ? 1 : 0 ),  dp[i][j-1], dp[i-1][j]  }
*        如果无需记录路径，则直接用滚动数组即可，本题需要记录路径，所以无法优化空间。
*/

#include <stdio.h>
#define  MAXN  1002
char  A[MAXN];
char  B[MAXN];
char  R[MAXN];
short  mat[MAXN][MAXN];

short  max3( short a, short b, short c ) {
  if( a > b ) b = a;
  return  b > c ? b : c;
}
int main() {
  int  i, j, k;
  scanf( "%s%s", A+1, B+1 );
  for( i = 1; A[i]; ++i ) {
    for( j = 1; B[j]; ++j ) {
      mat[i][j] = max3( mat[i-1][j], mat[i][j-1], mat[i-1][j-1] + ( A[i]==B[j] ? 1 : 0 ) );
    }
  }
  --i; --j; k = MAXN - 1;
  while( i > 0 && j > 0 ) {
	if( A[i] == B[j] ) { R[--k] = A[i]; --i; --j; }
    else if( mat[i-1][j] > mat[i][j-1] ) --i;
    else  --j;
  }
  printf( "%s\n", R + k );
  return 0;
}