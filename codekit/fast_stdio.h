/*
@author gogdizzy
@date   2015-10-25
@ref
	http://ideone.com/fOK6CW
@desc
	There's no error format handle, you should give good input data.
	!!! float and double type maybe not so precise !!!
*/

#pragma once

#include <stdio.h>
#include <string>

#ifdef _POSIX_SOURCE
  #define GCFAST getchar_unlocked
  #define PCFAST( c ) putchar_unlocked( c )
#else
  #define GCFAST getchar
  #define PCFAST( c ) putchar( c )
#endif

#ifdef _GNU_SOURCE
  #define PUTSFAST( s ) fputs_unlocked( s, stdout )
#else
  #define PUTSFAST( s ) fputs( s, stdout )
#endif

class FastStdin {

public:
	typedef char       *cstring;
	typedef std::string cppstring;

	FastStdin() : cur_( 0 ), bak_( 0 ) {}

	inline operator bool() { return !( cur_ == EOF && bak_ == 0 ); }

	inline FastStdin& operator >>( char &c ) { c = next(); return *this; }
	inline FastStdin& operator >>( signed char &c ) { c = next(); return *this; }
	inline FastStdin& operator >>( unsigned char &c ) { c = next(); return *this; }
	inline FastStdin& operator >>( cstring str ) {
		if( skip_space() ) {
			do { *str++ = static_cast<char>( next() ); } while( peek() > 0x20 );
			str[-1] = 0;
			unget();
		}
		return *this;
	}
	inline FastStdin& operator >>( cppstring &str ) {
		// i'm not sure how fast std::string push_back is, though it's
		// amortized constant, so i use a buffer
		char tmp[1024];
		int  idx = 0;
		if( skip_space() ) {
			str.clear();
			do {
				tmp[idx++] = next();
				if( idx == sizeof tmp ) {
					if( peek() <= 0x20 ) { tmp[--idx] = 0; unget(); }
					str.append( tmp, tmp + idx );
					idx = 0;
				}
			} while( peek() > 0x20 );
			if( idx > 0 ) {
				tmp[--idx] = 0;
				unget();
				str.append( tmp, tmp + idx );
			}
		}
		return *this;
	}


#define DEF_SINT_FUNC( type ) \
	inline FastStdin& operator >>( type &i ) { \
		if( skip_space() ) { \
			type ans = 0, sign = -1; \
			if( next() == '-' ) sign = -sign; \
			else if( peek() == '+' ) {} \
			else { ans = '0' - peek(); } \
			while( next() > 0 ) { \
				if( '0' <= peek() && peek() <= '9' ) { \
					ans = ans * 10 + ( '0' - peek() ); \
				} \
				else { \
					break; \
				} \
			} \
			unget(); \
			i = sign * ans; \
		} \
		return *this; \
	}

	DEF_SINT_FUNC( short )
	DEF_SINT_FUNC( int )
	DEF_SINT_FUNC( long )
	DEF_SINT_FUNC( long long )

#undef DEF_SINT_FUNC

#define DEF_UINT_FUNC( type ) \
	inline FastStdin& operator >>( type &i ) { \
		if( skip_space() ) { \
			type ans = 0; \
			if( next() == '+' ) {} \
			else { ans = peek() - '0'; } \
			while( next() > 0 ) { \
				if( '0' <= peek() && peek() <= '9' ) { \
					ans = ans * 10 + ( peek() - '0' ); \
				} \
				else { \
					break; \
				} \
			} \
			unget(); \
			i = ans; \
		} \
		return *this; \
	}

	DEF_UINT_FUNC( unsigned short )
	DEF_UINT_FUNC( unsigned int )
	DEF_UINT_FUNC( unsigned long )
	DEF_UINT_FUNC( unsigned long long )

#undef DEF_UINT_FUNC

	// only read double that digit not too long
	inline FastStdin& operator >>( double &x ) {
		if( skip_space() ) {
			int sign = 1;
			double ipart = 0.0, dpart = 0.0, depth = 10.0;
			if( next() == '-' ) { sign = -sign; }
			else if( peek() == '+' ) {}
			else if( peek() == '.' ) { goto READ_DPART; }
			else { ipart = peek() - '0'; }

			while( next() > 0 ) {
				if( '0' <= peek() && peek() <= '9' ) {
					ipart = ipart * 10.0 + ( peek() - '0' );
				}
				else {
					break;
				}
			}
READ_DPART:
			if( peek() == '.' ) {
				while( next() > 0 ) {
					if( '0' <= peek() && peek() <= '9' ) {
						dpart += ( peek() - '0' ) / depth;
						depth *= 10.0;
					}
					else {
						break;
					}
				}
			}
			unget();
			x = sign * ( ipart + dpart );
		}
		return *this;
	}
	inline FastStdin& operator >>( float &x ) {
		double d;
		(*this) >> d;
		x = static_cast<float>( d );
		return *this;
	}

protected:
	inline int peek() { return cur_; }

	inline void unget() { bak_ = cur_; }
	inline int next() {
		return bak_ ? bak_ = 0, cur_ : cur_ = GCFAST();
	}

	inline static bool is_space( int c ) {
		// the libc function isspace defines as follows, but i change it
		// 0x20 0x09 0x0a  0x0d 0x0c 0x0b
		// return c == ' ' || c == '\t' || c == '\n' || c == '\r'
		//		|| c == '\f' || c == '\v';
		return c > 0 && c <= 0x20;
	}
	inline bool skip_space() {
		while( is_space( next() ) );
		if( cur_ != EOF ) unget();
		return peek() != EOF;
	}

private:
	int cur_;
	int bak_;
};

class FastStdout {

public:
	typedef const char *cstring;
	typedef const std::string cppstring;

	FastStdout() : precision_(6) {}

	inline FastStdout& operator <<( char c ) { PCFAST( c ); return *this; }
	inline FastStdout& operator <<( signed char c ) { PCFAST( c ); return *this; }
	inline FastStdout& operator <<( unsigned char c ) { PCFAST( c ); return *this; }

	inline FastStdout& operator <<( cstring str ) {
		PUTSFAST( str );
		return *this;
	}
	inline FastStdout& operator <<( cppstring &str ) {
		PUTSFAST( str.c_str() );
		return *this;
	}

#define DEF_SINT_FUNC( type ) \
	inline FastStdout& operator <<( type i ) { \
		if( i == 0 ) { PCFAST( '0' ); return *this; } \
		long long z = i; \
		unsigned long long x; \
		if( i < 0 ) { PCFAST( '-' ); x = -z; } \
		else { x = z; } \
		char tmp[32], *p = tmp + 32; \
		while( x ) { \
			*--p = '0' + x % 10; \
			x /= 10; \
		} \
		while( p < tmp + 32 ) PCFAST( *p++ ); \
		return *this; \
	}

	DEF_SINT_FUNC( short )
	DEF_SINT_FUNC( int )
	DEF_SINT_FUNC( long )
	DEF_SINT_FUNC( long long )

#undef DEF_SINT_FUNC

#define DEF_UINT_FUNC( type ) \
	inline FastStdout& operator <<( type i ) { \
		if( i == 0 ) { PCFAST( '0' ); return *this; } \
		unsigned long long x = i; \
		char tmp[32], *p = tmp + 32; \
		while( x ) { \
			*--p = '0' + x % 10; \
			x /= 10; \
		} \
		while( p < tmp + 32 ) PCFAST( *p++ ); \
		return *this; \
	}

	DEF_UINT_FUNC( unsigned short )
	DEF_UINT_FUNC( unsigned int )
	DEF_UINT_FUNC( unsigned long )
	DEF_UINT_FUNC( unsigned long long )

#undef DEF_UNIT_FUNC

	inline FastStdout& set_precision( int precision ) {
		precision_ = precision;
		return *this;
	}

	// only write double that digit not too long
	// integral part not exceed long long
	// truncate mode
	inline FastStdout& operator <<( double d ) {
		long long b, c = 1;
		(*this) << static_cast<long long>( d );

		if( precision_ > 0 ) PCFAST( '.' );

		for( int i = 0; i < precision_; ++i ) c *= 10;
		b = static_cast<long long>( d * c ) % c;
		c /= 10;
		while( b < c ) { PCFAST( '0' ); c /= 10; }
		if( b > 0 ) (*this) << b;
		return *this;
	}
	inline FastStdout& operator <<( float f ) {
		return (*this) << static_cast<double>( f );
	}

private:
	// must less than 18
	int precision_;
};

#undef GCFAST
#undef PCFAST
#undef PUTSFAST

