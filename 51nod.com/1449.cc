//
// Created by 关鑫 on 2020/4/24.
//

// 因为每个砝码只有一个，所以从低向高看——轻的可以组合成重的，重的无法变成轻的，如果轻的无法满足，就返回false
// 对于某一层来说，如果物体边的质量大于1，那么只能在对面放上一层更重的质量

#include <stdio.h>

int main() {

    int w, m, x, c;
    bool ok = true;
    scanf( "%d%d", &w, &m );
    if( w >= 4 ) {
        c = 0;
        while( m ) {
            x = m % w; m = m / w;
            if( x + c >= w - 1 ) { c = 1; x = w - x - c; }
            else { x += c; c = 0; }
            if( x > 1 ) { ok = false; break; }
        }
    }
    puts( ok ? "YES" : "NO" );
    return 0;
}
