
#pragma once

template <typename IntType, int Size>
class UnionSet {
public:
    UnionSet(int offset = 0) {
        for(int i = 0; i < Size; ++i) {
            data[i] = i - offset;
            data2[i] = 0;
        }
        father = data + offset;
        count = data2 + offset;
    }

    IntType GetRoot(IntType x) {
        if(father[x] == x) return x;
        return father[x] = GetRoot(father[x]);
    }

    void Merge(IntType x, IntType y) {
        auto xRoot = GetRoot(x);
        auto yRoot = GetRoot(y);
        father[yRoot] = xRoot;
    }

    void StatCount() {
        for(int i = 0; i < Size; ++i) {
            ++count[data[i]];
        }
    }

    IntType GetCount(IntType x) {
        return count[GetRoot(x)];
    }

private:
    IntType data[Size];
    IntType *father;
    IntType data2[Size];
    IntType *count;
};
