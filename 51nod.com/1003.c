/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1003
*  �׳˺���0������
*  ˼·��ֻ��Ҫ��ȡ����5���ֵĴ����Ϳ���
*/

#include <stdio.h>

int main() {
  int  n, r = 0;
  scanf( "%d", &n );
  while( n ) {
    r += n /= 5;
  }
  printf( "%d\n", r );
  return 0;
}