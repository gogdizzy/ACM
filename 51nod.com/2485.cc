//
// Created by 关鑫 on 2021/5/17.
//

#include <cstdio>

int C[256];

int main() {

    int x, tot = 0;

    while((x = getchar()) != 0) {
        ++C[x];
        ++tot;
    }

    bool ok = true;
    for(x = 'a'; x <= 'z'; ++x) {
        if(C[x] * 2 > tot + 1) {
            ok = false;
            break;
        }
    }
    puts(ok ? "Possible" : "Impossible");

    return 0;
}