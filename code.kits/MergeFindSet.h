//
// Created by 关鑫 on 2020/5/20.
//

#pragma once

/**
 * 并查集
 * 1> 查找
 * 2> 合并
 * 3> 是否在同一个集合
 * 4> 查询每个分类大小
 * 5> 查询分类数量
 */

#include <cstring>
#include <type_traits>
#include <unordered_map>

template < typename T, bool NOT_USED = std::is_integral< T >::value >
class MergeFindSet {

public:
    void Reset() {
        _father.clear();
    }

    T Find( const T &x ) {
        auto it = _father.find(x);
        if( it == _father.end() || it->second == x ) return x;
        return _father[x] = Find( it->second );
    }

    void Merge( const T &x, const T &y ) {
        auto xRoot = Find(x);
        auto yRoot = Find(y);
        if( xRoot != yRoot ) _father[yRoot] = xRoot;
    }

    bool InSameSet( const T &x, const T &y ) {
        return Find( x ) == Find( y );
    }

protected:
    std::unordered_map< T, T > _father;
};


template < typename IntType >
class MergeFindSet< IntType, true > {

public:
    // size - 数组总长度
    // zeroPos - 0的位置，可能是负数
    MergeFindSet( size_t size, ssize_t zeroPos = 0 ) {
        _size = size;
        _buf1 = new IntType[size];
        _father = _buf1 - zeroPos;
        Reset();
    }

    void Reset() {
        auto zeroPos = _buf1 - _father;
        for( ssize_t i = 0; i < _size; ++i ) {
            _buf1[i] = i + zeroPos;
        }
    }

    ~MergeFindSet() {
        if( _buf1 ) delete[] _buf1;
    }

    IntType Find( IntType x ) {
        if( _father[x] == x ) return x;
        return _father[x] = Find( _father[x] );
    }

    void Merge( IntType x, IntType y ) {
        auto xRoot = Find(x);
        auto yRoot = Find(y);
        if( xRoot != yRoot ) _father[yRoot] = xRoot;
    }

    bool InSameSet( IntType x, IntType y ) {
        return Find( x ) == Find( y );
    }

private:
    size_t   _size;
    IntType *_buf1;
    IntType *_father;
};

template < typename T, bool NOT_USED = std::is_integral< T >::value >
class MergeFindSetWithStat {

public:

    MergeFindSetWithStat() : _statOK( false ) {}

    void Reset() {
        _statOK = false;
        _father.clear();
        _count.clear();
    }

    T Find( const T &x ) {
        auto it = _father.find(x);
        if( it == _father.end() || it->second == x ) return x;
        return _father[x] = Find( it->second );
    }

    void Merge( const T &x, const T &y ) {
        auto xRoot = Find(x);
        auto yRoot = Find(y);
        if( xRoot != yRoot ) {
            _father[yRoot] = xRoot;
            _statOK = false;
        }
    }

    bool InSameSet( const T &x, const T &y ) {
        return Find( x ) == Find( y );
    }

    size_t SizeOfSet( const T &x ) {
        if( !_statOK ) Stat();
        auto root = Find( x );
        auto it = _count.find( root );
        return it == _count.end() ? 1 : it->second + 1;
    }

protected:
    void Stat() {
        _count.clear();
        for( auto &it : _father ) {
            if( it.first == it.second ) continue;
            auto root = Find( it.second );
            ++_count[root];
        }
        _statOK = true;
    }

protected:
    bool  _statOK;
    std::unordered_map< T, T > _father;
    std::unordered_map< T, size_t > _count;
};

template < typename IntType >
class MergeFindSetWithStat< IntType, true > {
public:
    // size - 数组总长度
    // zeroPos - 0的位置，可能是负数
    MergeFindSetWithStat( size_t size, ssize_t zeroPos = 0 ) {
        _statOK = false;
        _size = size;
        _buf1 = new IntType[size];
        _buf2 = new size_t[size];
        _father = _buf1 - zeroPos;
        _count = _buf2 - zeroPos;
        Reset();
    }

    ~MergeFindSetWithStat() {
        if( _buf1 ) delete[] _buf1;
        if( _buf2 ) delete[] _buf2;
    }

    void Reset() {
        _statOK = false;
        auto zeroPos = _buf1 - _father;
        for( ssize_t i = 0; i < size; ++i ) {
            _buf1[i] = i + zeroPos;
            _buf2[i] = 0;
        }
    }

    IntType Find( IntType x ) {
        if( _father[x] == x ) return x;
        return _father[x] = Find( _father[x] );
    }

    void Merge( IntType x, IntType y ) {
        auto xRoot = Find(x);
        auto yRoot = Find(y);
        if( xRoot != yRoot ) {
            _father[yRoot] = xRoot;
            _statOK = false;
        }
    }

    bool InSameSet( IntType x, IntType y ) {
        return Find( x ) == Find( y );
    }

    size_t SizeOfSet( IntType x ) {
        if( !_statOK ) Stat();
        auto root = Find( x );
        return _count[root];
    }

    size_t NumOfSet() {
        if( !_statOK ) Stat();
        return _numOfSet;
    }

protected:
    void Stat() {
        _numOfSet = 0;
        memset( _buf2, 0, sizeof( size_t ) * _size );
        auto zeroPos = _buf1 - _father;
        for( ssize_t i = 0; i < _size; ++i ) {
            auto root = Find( _buf1[i] );
            ++_count[root];
            if( root == i + zeroPos ) ++_numOfSet;
        }
        _statOK = true;
    }

private:
    bool     _statOK;
    size_t   _size;
    size_t   _numOfSet;
    IntType *_buf1;
    size_t  *_buf2;
    IntType *_father;
    size_t  *_count;
};
