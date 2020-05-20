//
// Created by 关鑫 on 2018/11/28.
//

#pragma once

template < typename IntType = int >
class MonoStack {
public:
    enum DIR {
        LEFT_MIN,
        LEFT_MAX,
        RIGHT_MIN,
        RIGHT_MAX
    };

    MonoStack() : m_( nullptr ), stk_( nullptr ) {}
    ~MonoStack() {
        if( m_ ) delete[] m_;
        if( stk_ ) delete[] stk_;
    }

#define MONOSTACK_LEFT_LOOP( OP ) do { \
    for( IntType i = 0; i < len; ++i ) { \
        auto tmp = *( first + i ); \
        while( stk_[top] != -1 && tmp OP *( first + stk_[top] ) ) --top; \
        m_[i] = stk_[top]; \
        stk_[++top] = i; \
    } \
} while( 0 )

#define MONOSTACK_RIGHT_LOOP( OP ) do { \
    for( IntType i = len - 1; i >= 0; --i ) { \
        auto tmp = *( first + i ); \
        while( stk_[top] != len && tmp OP *( first + stk_[top] ) ) --top; \
        m_[i] = stk_[top]; \
        stk_[++top] = i; \
    } \
} while( 0 )

    template< typename _RandomAccessIterator >
    bool compute( _RandomAccessIterator first, _RandomAccessIterator last, MonoStack::DIR dir, bool includeEqual ) {
        auto len = last - first;
        if( len <= 0 ) return false;
        if( !memory_init( len ) ) return false;

        int top = -1;
        switch( dir ) {
            case DIR::LEFT_MIN: {
                stk_[++top] = -1;
                if( includeEqual ) MONOSTACK_LEFT_LOOP( >= );
                else MONOSTACK_LEFT_LOOP( > );
                break;
            }
            case DIR::LEFT_MAX: {
                stk_[++top] = -1;
                if( includeEqual ) MONOSTACK_LEFT_LOOP( <= );
                else MONOSTACK_LEFT_LOOP( < );
                break;
            }
            case DIR::RIGHT_MIN: {
                stk_[++top] = len;
                if( includeEqual ) MONOSTACK_RIGHT_LOOP( >= );
                else MONOSTACK_RIGHT_LOOP( > );
                break;
            }
            case DIR::RIGHT_MAX: {
                stk_[++top] = len;
                if( includeEqual ) MONOSTACK_RIGHT_LOOP( <= );
                else MONOSTACK_RIGHT_LOOP( < );
                break;
            }
            default:
                return false;
        }
        return true;
    }

    inline
    IntType get( size_t i ) { return m_[i]; }

    inline
    IntType operator[]( size_t i ) { return m_[i]; }

protected:
    bool memory_init( size_t need ) {
        if( m_ ) delete[] m_;
        if( stk_ ) delete[] stk_;
        m_ = new IntType[need];
        stk_ = new IntType[need + 1];
        return m_ != nullptr && stk_ != nullptr;
    }

private:
    IntType *m_;
    IntType *stk_;
};
