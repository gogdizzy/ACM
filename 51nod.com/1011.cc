/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1011
*  ���Լ��GCD
*  ˼·��ŷ�����շת���
*/

#include <stdio.h>

int main() {
  int  a, b, t;
  scanf( "%d%d", &a, &b );
  while( b != 0 ) {
    t = a % b;
    a = b;
    b = t;
  }
  printf( "%d\n", a );
  return 0;
}