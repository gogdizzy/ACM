/**
*  http://51nod.com/onlineJudge/questionCode.html#!problemId=1159
*  ѹ���㷨�ľ���
*  �ο��𰸣�http://51nod.com/question/index.html#!questionId=45
*  ˼·�������һ�зŵ���һ�У���ô�൱��ÿ���ַ���������ѭ��1λ���γɵķ����ԭ���ķ���ֻ��
*        ĳЩ�е�˳��ͬ�����������������ô��Ϊ��һ����������λ�����Ժ͵�һ���Լ�������һ���ġ�
*        ��һ���Լ��ź���Ӧ���γ��˺�ԭʼ����һ���Ľ�����������һ����֪���ˡ�
*        �ظ�������衣
*  ????1    1????    0???1    10???    00??1    100??    001?1    1001?    00101
*  ????1    1????    0???1    10???    01??1    101??    010?1    1010?    01001
*  ????0 => 0???? => 0???0 => 00??? => 01??0 => 001?? => 010?0 => 0010? => 01010
*  ????0    0????    1???0    01???    10??0    010??    100?0    0100?    10010
*  ????0    0????    1???0    01???    10??0    010??    101?0    0101?    10100
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int  count1( char* str ) {
	int  cnt = 0;
	while( *str ) cnt += *str++ - '0';
	return  cnt;
}

bool  cmp( const char* a, const char* b ) {
	return  strcmp( a, b ) < 0;
}

int main() {
	char  x, strs[100][101], *pstr[100];
	char  input[101];
	int  i, j, n;

	scanf( "%*d%s", input );
	n = strlen( input );

	for( i = 0; i < n; ++i ) {
		strs[i][100] = 0;
		pstr[i] = &strs[i][100];
	}

	for( j = n; j > 0; --j ) {
		for( i = 0; i < n; ++i ) {
			*--(pstr[i]) = input[i];
		}
		sort( pstr, pstr + n, cmp );
	}

	if( count1( input ) != count1( pstr[0] ) ) puts( "No Solution" );
	else puts( pstr[0] );

	return 0;
}