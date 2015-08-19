/*
@author gogdizzy
@date   2015-08-19
@question
	http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1000
*/

#ifdef  VER2

#include <iostream>

int main() {
	int  a, b;
	std::cin >> a >> b;
	std::cout << a + b << '\n';
	return 0;
}

#endif

#ifdef  VER1

#include <stdio.h>

int main() {
	int  a, b;
	scanf( "%d%d", &a, &b );
	printf( "%d\n", a + b );
	return 0;
}

#endif

