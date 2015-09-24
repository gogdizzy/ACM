/*
@author gogdizzy
@date   2015-08-19

@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1009

@solution
	首先考察不同位数以内的所有整数出现1的次数，例如四位数以内[0,9999]，个十百千位均有可能出现1，
	出现1的时候，其它三个位均可以是0~9，所以假设固定一个位为1，另外三个位的可能性是10*10*10
	所以总共出现4*10*10*10 = 4000次1，所以一个完整的k位数中包含1的个数是k * 10^(k-1)

	对于一个数字n，可以将十进制拆成[p1][p2...pk]的形式，
	如果p1==0，n = [p2...pk] = [p2][p3...pk]，转化为子问题
	如果p1==1，这时包含了三种情况
		  1> p1位=0时，后边k-1位包含 (k-1) * 10^(k-2)个1
		  2> p1位=1时，p1位重复了[p2...pk] + 1 个1
		  3> p1位=1时，[p2...pk]出现1的次数（这是一个子问题，可以递归）
	如果p1 > 1，这时包含了三种情况
		  1> p1位=0,1...p1-1时（共p1个可能），后面k-1位包含 (k-1) * 10^(k-2)个1
		  2> p1位=1时，p1位重复了10^(k-1)个1
		  3> p1位=p1时，[p2...pk]出现1的次数（这是一个子问题，可以递归）

	代码是根据这个原理从后往前累加的
*/

#include <stdio.h>
typedef  unsigned int   uint32_t;

uint32_t  count1( uint32_t N ) {
	const uint32_t  lkp[] = { 0, 1, 20, 300, 4000, 50000, 600000,
		7000000, 80000000, 900000000 };
	uint32_t  result = 0;
	uint32_t  len = 0;
	uint32_t  digit = 0;
	uint32_t  radix = 1;
	uint32_t  tail = 0;
	while( N != 0 ) {
		digit = N % 10;
		N /= 10;
		++len;
		 
		if( digit > 1 ) {
			result += radix + digit * lkp[len-1];
		}
		else if( digit == 1 ) {
			result += tail + 1 + lkp[len-1];
		}
 
		tail += digit * radix;
		radix *= 10;
	}
	return  result;
}

int main() {
	uint32_t  n;
	scanf( "%u", &n );
	printf( "%u\n", count1( n ) );
	return 0;
}
