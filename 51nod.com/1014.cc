/**
*  http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1014
*  X^2 Mod P
*  ˼·��ö�٣�ö�ٵ���һ��ֹͣ
*        ��x�ǵ�һ����������������y�ǵڶ������� ( y^2 - x^2 ) = k * p����( y + x ) * ( y - x ) = k * p
*        ��Ϊx��y����ȣ�����[0,p]���䣬����y - x < p��0 < y + x < 2p������y + x = p
*        Ҳ����˵��Ҫôû�д𰸣�Ҫô�ҵ�x��ֱ�����x��p-x����
*/

#include <stdio.h>

int main() {
  int  a, p, x, z = 1;

  scanf( "%d%d", &p, &a );
  for( x = 1; x <= p; ++x )
    if( (long long)x * (long long)x % p == a ) { z = 0; break; }

  if( z ) puts( "No Solution" );
  else printf( "%d %d\n", x, p - x );
  return 0;
}