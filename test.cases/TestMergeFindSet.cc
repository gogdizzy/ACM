//
// Created by 关鑫 on 2020/8/14.
//

#include <cassert>
#include <string>

#include "MergeFindSet.h"

void testInt() {
    // use array
    {
        const int N = 100;
        MergeFindSet< int > mfs( N );
        assert( mfs.Find( 0 ) == 0 );
        assert( mfs.Find( N - 1 ) == N - 1 );
        mfs.Merge( 2, 3 );
        mfs.Merge( 3, 4 );
        assert( mfs.InSameSet( 2, 4 ) );
        mfs.Reset();
        assert( !mfs.InSameSet( 2, 4 ) );
    }
    // use unordered_map
    {
        const int N = 100;
        MergeFindSet< int, false > mfs;
        assert( mfs.Find( 0 ) == 0 );
        assert( mfs.Find( N - 1 ) == N - 1 );
        mfs.Merge( 2, 3 );
        mfs.Merge( 3, 4 );
        assert( mfs.InSameSet( 2, 4 ) );
        mfs.Reset();
        assert( !mfs.InSameSet( 2, 4 ) );
    }
}

void testString() {
    // use unordered_map
    {
        const int N = 100;
        MergeFindSet< std::string > mfs;
        assert( mfs.Find( "hello" ) == "hello" );
        assert( mfs.Find( "world" ) == "world" );
        mfs.Merge( "good", "child" );
        mfs.Merge( "bad", "boy" );
        assert( !mfs.InSameSet( "good", "bad" ) );
        mfs.Merge( "child", "boy" );
        assert( mfs.InSameSet( "good", "bad" ) );
        mfs.Reset();
        assert( !mfs.InSameSet( "good", "bad" ) );
    }
}

void testIntWithStat() {
    // use array
    {
        const int N = 100;
        MergeFindSetWithStat< int > mfs( N );
        assert( mfs.Find( 0 ) == 0 );
        assert( mfs.Find( N - 1 ) == N - 1 );
        mfs.Merge( 2, 3 );
        mfs.Merge( 3, 4 );
        assert( mfs.InSameSet( 2, 4 ) );
        assert( mfs.NumOfSet() == N - 2 );
        assert( mfs.SizeOfSet( 2 ) == 3 );
        mfs.Reset();
        assert( !mfs.InSameSet( 2, 4 ) );
        assert( mfs.SizeOfSet( 2 ) == 1 );
    }
    // use unordered_map
    {
        const int N = 100;
        MergeFindSetWithStat< int, false > mfs;
        assert( mfs.Find( 0 ) == 0 );
        assert( mfs.Find( N - 1 ) == N - 1 );
        mfs.Merge( 2, 3 );
        mfs.Merge( 3, 4 );
        assert( mfs.InSameSet( 2, 4 ) );
        assert( mfs.SizeOfSet( 2 ) == 3 );
        mfs.Reset();
        assert( !mfs.InSameSet( 2, 4 ) );
        assert( mfs.SizeOfSet( 2 ) == 1 );
    }
}

void testStringWithStat() {
// use unordered_map
    {
        const int N = 100;
        MergeFindSetWithStat< std::string > mfs;
        assert( mfs.Find( "hello" ) == "hello" );
        assert( mfs.Find( "world" ) == "world" );
        mfs.Merge( "good", "child" );
        mfs.Merge( "bad", "boy" );
        assert( !mfs.InSameSet( "good", "bad" ) );
        mfs.Merge( "child", "boy" );
        assert( mfs.InSameSet( "good", "bad" ) );
        assert( mfs.SizeOfSet( "good" ) == 4 );
        mfs.Reset();
        assert( !mfs.InSameSet( "good", "bad" ) );
    }
}

struct A {
    int x, y;

    A() {}
    A(int x, int y) : x(x), y(y) {}
    bool operator==(const A& other) const { return x == other.x && y == other.y; }
    bool operator!=(const A& other) const { return !(*this == other); }
};

struct HashA {
    size_t operator()(const A &a) const {
        return size_t(a.x << 16) | a.y;
    }
};

void testAWithStat() {
// use unordered_map
    {
        const int N = 100;
        MergeFindSetWithStat< A, false, HashA > mfs;
        assert( mfs.Find( {1, 2} ) == A(1, 2) );
        assert( mfs.Find( {3, 4} ) == A(3, 4) );
        mfs.Merge( {1, 2}, {10, 20} );
        mfs.Merge( {3, 4}, {30, 40} );
        assert( !mfs.InSameSet( {1, 2}, {3, 4} ) );
        mfs.Merge( {10, 20}, {30, 40} );
        assert( mfs.InSameSet( {1, 2}, {3, 4} ) );
        assert( mfs.SizeOfSet( {1, 2} ) == 4 );
        mfs.Reset();
        assert( !mfs.InSameSet( {1, 2}, {3, 4} ) );
    }
}

int main() {

    testInt();
    testString();
    testIntWithStat();
    testStringWithStat();
    testAWithStat();

    return 0;
}