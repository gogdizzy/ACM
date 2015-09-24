// a * x + b * y = gcd( a, b ), we calc x, y and return gcd( a, b )
template <typename T>
T exgcd( T a, T b, T& x, T& y ) {
	if( b == 0 ) {
		x = 1; y = 0;
		return a;
	}
	T ans = exgcd( b, a % b, y, x );
	y -= a / b * x;
	return ans;
}
