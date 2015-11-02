// https://en.wikipedia.org/wiki/Prime-counting_function


#pragma once

#include <stdint.h>
#include <math.h>
#include <string.h>

class PrimeTable {

public:
	PrimeTable( int maxn ) {
		maxn_ = maxn;
		if( maxn_ < 10 ) maxn_ = 10;
		pmcount_ = static_cast< int >( 1.25506 * maxn_ / log( maxn_ ) + 1 );
		bits_ = new uint64_t[maxn_/64+1];
		primes_ = new uint32_t[pmcount_];
		pcount_ = 0;
		memset( bits_, 0, sizeof( uint64_t ) * (maxn_/64+1) );

		uint32_t  rt = (uint32_t)sqrt( (double)maxn_ ) + 1;

		for( uint32_t i = 2; i <= maxn_; ++i ) {
			if( !test_bit( i ) ) {
				primes_[pcount_++] = i;
				if( i < rt ) {
					for( uint32_t j = i * i; j <= maxn_; j += i ) {
						set_bit( j );
					}
				}
			}
		}
	}
	~PrimeTable() {
		if( bits_ ) { delete[] bits_; bits_ = nullptr; }
		if( primes_ ) { delete[] primes_; primes_ = nullptr; }
	}

	inline
	bool is_prime( int x ) { return !test_bit( x ); }

	inline
	uint32_t* begin() { return primes_; }

	inline
	uint32_t* end() { return primes_ + pcount_; }

protected:
	inline
	bool test_bit( uint32_t i ) {
		return bits_[i>>6] & (1ULL << (i & 63));
	}

	inline
	void set_bit( uint32_t i ) {
		bits_[i>>6] |= (1ULL << (i & 63));
	}

private:
	int maxn_;
	int pcount_;
	int pmcount_;
	uint64_t *bits_;
	uint32_t *primes_;
};
