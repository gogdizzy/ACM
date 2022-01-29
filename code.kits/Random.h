//
// Created by 关鑫 on 2021/9/2.
//

#pragma once

#include <random>

struct RandomInt {

    RandomInt(int beg, int end) :
        _distribution(beg, end)
    {
        _rng.seed(std::random_device()());
    }

    int get() {
        return _distribution(_rng);
    }

private:
    std::mt19937 _rng;
    std::uniform_int_distribution<std::mt19937::result_type> _distribution;
};
