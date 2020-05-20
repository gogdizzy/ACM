//
// Created by 关鑫 on 2020/5/15.
//

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <utility>

using namespace std;

template <typename IntType>
class MergeFindSet {
public:
    MergeFindSet() {
    }

    IntType GetRoot(IntType x) {
        auto it = father.find(x);
        if(it == father.end()) return x;
        return father[x] = GetRoot(father[x]);
    }

    void Merge(IntType x, IntType y) {
        auto xRoot = GetRoot(x);
        auto yRoot = GetRoot(y);
        father[yRoot] = xRoot;
    }

private:
    std::unordered_map<IntType, IntType> father;
};

int main() {

    ios::sync_with_stdio( false );
    cin.tie( 0 );

    int n, x, y, p;
    MergeFindSet<int> mfs;
    unordered_map< int, unordered_set< int > > mtx;

    for( cin >> n; n--; ) {
        cin >> x >> y >> p;
        auto rx = mfs.GetRoot( x );
        auto ry = mfs.GetRoot( y );
        bool ok = false;
        if( p == 1 ) {
            if( rx == ry ) {
                ok = true;
            }
            else if( !mtx[rx].count( ry ) && !mtx[ry].count( rx ) ) {
                if( mtx[rx].size() < mtx[ry].size() ) swap( rx, ry );
                for( auto z : mtx[ry] ) {
                    auto rz = mfs.GetRoot( z );
                    mtx[z].erase( ry );
                    mtx[rx].insert( rz );
                    mtx[rz].insert( rx );
                }
                mtx[ry].clear();
                mfs.Merge( rx, ry );
                ok = true;
            }
        }
        else {
            if( rx != ry ) {
                mtx[rx].insert( ry );
                mtx[ry].insert( rx );
                ok = true;
            }
        }
        puts( ok ? "YES" : "NO" );
    }

    return 0;
}
