/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1422

@solution
	根据题目所给数据，总的序列长度最大应该在10^14左右，用long long足够
	只需要保存构造序列的步骤，还有每步之后序列达到的长度
	查询时逆推回去即可，通过二分查找跳回到步骤几，只要逆推到操作1，
	就可以知道该数字是多少
*/

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int MAXM = 100000;

struct OP {
	int  type;
	int  arg1, arg2;
};

OP  ops[MAXM];
LL  pos[MAXM+1];

int main() {

	ios::sync_with_stdio( false );

	int  m, n, i, p;
	LL   q;

	pos[0] = 0;
	cin >> m;
	for( i = 0; i < m; ++i ) {
		cin >> ops[i].type;
		if( ops[i].type == 1 ) {
			cin >> ops[i].arg1;
			pos[i+1] = pos[i] + 1;
		}
		else {
			cin >> ops[i].arg1 >> ops[i].arg2;
			pos[i+1] = pos[i] + (LL)ops[i].arg1 * ops[i].arg2;
		}
	}

	cin >> n;
	for( i = 0; i < n; ++i ) {
		cin >> q; --q;
		do {
			p = lower_bound( pos, pos + m + 1, q + 1 ) - pos - 1;
			if( ops[p].type == 1 ) break;
			else q = ( q - pos[p] ) % ops[p].arg1;
		} while( 1 );
		cout << ops[p].arg1 << ( i == n - 1 ? '\n' : ' ' );
	}

	return 0;
}
