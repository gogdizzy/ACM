/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1435

@solution
	因为各个数位阶乘的乘积是固定值的时候，又不包括0和1，那么每个数字尽
	可能小，使得总的位数最长

	然后发现对于质数的阶乘，只能维持原样，而对于合数，可以将其包含最大
	的质数的阶乘提取，剩下的组成小数字阶乘

	所以对每个数字进行替换，然后总体排一下序即可
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {

	const string t[10] = { "", "", "2", "3", "322",
		"5", "53", "7", "7222", "7332" };
	int  n;
	string  s, ans;

	cin >> n >> s;
	for( auto c : s ) {
		ans += t[c-'0'];
	}
	sort( ans.begin(), ans.end(), []( const char& a, const char& b ) { return a > b; } );

	cout << ans << '\n';

	return 0;
}
