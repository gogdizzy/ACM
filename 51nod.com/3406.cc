//
// Created by 关鑫 on 2021/7/27.
//

#include <iostream>
#include <string>
#include <algorithm>

const int N = 10000;

struct Student {
    int id;
    int chinese;
    int math;
    int english;
};

std::string name[N];
Student s[N];
int result[N];

int main() {
    int n, k;
    std::cin >> n;
    for(int i = 0; i < n; ++i) {
        s[i].id = i;
        std::cin >> name[i] >> s[i].chinese >> s[i].math >> s[i].english;
    }

    std::sort(s, s + n, [](const Student &a, const Student &b) {
        return a.chinese < b.chinese;
    });

    int minc, maxc, minm, maxm, mine, maxe;
    std::cin >> k;
    for(int i = 0; i < k; ++i) {
        int len = 0;
        std::cin >> minc >> maxc >> minm >> maxm >> mine >> maxe;
        for(auto pos = std::lower_bound(s, s + n, minc, [](const Student &a, int v) { return a.chinese < v; }) - s;
            pos < n;
            ++pos) {
            if(s[pos].chinese <= maxc && minm <= s[pos].math && s[pos].math <= maxm && mine <= s[pos].english && s[pos].english <= maxe) {
                result[len++] = s[pos].id;
            }
        }
        std::sort(result, result + len);
        for(int z = 0; z < len; ++z) {
            std::cout << name[result[z]] << '\n';
        }
    }

    return 0;
}