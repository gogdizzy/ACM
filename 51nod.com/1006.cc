/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1006
*  �����������Lcs
*  ˼·��dp[i][j]��ʾ��һ���ַ�������i���ַ����ڶ����ַ�������j���ַ�ʱ������������еĳ���
*        ת�Ʒ��� dp[i][j] = max{ dp[i-1][j-1] + ( str1[i] == str2[j] ? 1 : 0 ),  dp[i][j-1], dp[i-1][j]  }
*        ��������¼·������ֱ���ù������鼴�ɣ�������Ҫ��¼·���������޷��Ż��ռ䡣
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