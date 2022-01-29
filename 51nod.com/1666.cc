//
// Created by 关鑫 on 2021/4/12.
//

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#define MAXL 100001

char l[MAXL];
char r[MAXL];
char k[MAXL];
uint64_t p;
int presum[MAXL];
uint64_t coe[MAXL];
int posInGroup[MAXL];

uint64_t gcd(uint64_t a, uint64_t b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {

    uint64_t ans = 0;
    scanf("%s%s%s%llu", l, r, k, &p);
    uint64_t llen = strlen(l);
    uint64_t rlen = strlen(r);
    uint64_t klen = strlen(k);

    if( llen == rlen ) {
        uint64_t groupCount = gcd(rlen, klen);
        uint64_t groupSize = klen / groupCount;
        uint64_t lcm = (uint64_t)rlen / groupCount * klen;

        for( int group = 0; group < groupCount; ++group) {
            int pos = 0;
            presum[group] = (k[group] - '0');
            posInGroup[group] = pos++;
            int prev = group;
            for(int cur = (prev + rlen) % klen; cur != group; cur = (prev + rlen) % klen) {
                presum[cur] = presum[prev] + (k[cur] - '0');
                posInGroup[cur] = pos++;
                prev = cur;
            }
        }

        uint64_t tmp = 0;
        for(int i = 0; i < rlen; ++i) {
            uint64_t fullLoopCount = ( p - i ) / lcm;
            uint64_t partLoopSize = (( p - i ) % lcm + rlen - 1) / rlen;
            int group = i % groupCount;
            int curPosInGroup = posInGroup[i % klen];
            int fullLoop = presum[(group + rlen * (groupSize - 1)) % klen];
            int partLoop = 0;
            if(i == 28857) {
                int z = 2;
            }
            if(curPosInGroup + partLoopSize > groupSize) {
                partLoop = fullLoop - presum[(group + rlen * (curPosInGroup - 1)) % klen] +
                        presum[(group + rlen * ((curPosInGroup + partLoopSize) % groupSize - 1)) % klen];
            }
            else {
                partLoop = presum[(group + rlen * (curPosInGroup + partLoopSize - 1)) % klen] -
                        (curPosInGroup == 0 ? 0 : presum[(group + rlen * (curPosInGroup - 1)) % klen]);
            }
            coe[i] = (uint64_t)fullLoop * fullLoopCount + partLoop;
            tmp += coe[i] * 9;
            ans += coe[i] * (r[i] - '0');
        }

        int notEqualPos = rlen;
        for(int i = 0; i < rlen; ++i) {
            if(l[i] != r[i]) {
                notEqualPos = i;
                break;
            }
            tmp -= coe[i] * (9 - (r[i] - '0'));
        }

        for(int i = notEqualPos; i < rlen; ++i) {
            int digit = r[i] - '0' - 1;
            if(digit < 0) {
                tmp -= coe[i] * 9;
                continue;
            }
            tmp -= coe[i] * (9 - digit);
            if(tmp > ans) ans = tmp;
            tmp += coe[i];
        }
    }
    else {
        uint64_t totalSum = 0, partSum = 0;
        uint64_t rem = p % klen;
        for(int i = 0; i < klen; ++i) {
            int x = k[i] - '0';
            if( i < rem ) partSum += x;
            totalSum += x;
        }
        ans = ( p / klen * totalSum + partSum ) * 9;
    }

    printf( "%llu\n", ans );

    return 0;
}
