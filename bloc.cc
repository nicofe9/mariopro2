#include "bloc.hh"

using namespace std;

const int _ = -1;
const int n = pro2::black;
const int b = pro2::white;
const int o = 0xe1b002;
const int m = 0xf2c201;
const int a = 0xffd404;

const vector<vector<int>> Bloc::bloc_sprite_ = {
    {_, _, n, n, n, n, n, n, n, n, n, n, n, n, _, _},
    {_, n, b, b, b, m, m, m, m, m, m, m, m, o, n, _},
    {n, b, b, a, n, n, n, n, n, n, n, a, m, m, o, n},
    {n, b, a, n, b, b, b, b, b, b, b, n, a, m, o, n},
    {n, b, n, b, b, b, b, b, b, b, b, b, n, m, o, n},
    {n, m, n, b, b, b, n, n, n, b, b, b, n, m, o, n},
    {n, b, a, n, n, n, n, n, n, b, b, b, n, m, o, n},
    {n, m, a, a, a, n, b, b, b, b, b, n, a, m, o, n},
    {n, m, a, a, a, n, b, b, b, n, n, a, a, m, o, n},
    {n, m, a, a, a, a, n, n, n, a, a, a, a, m, o, n},
    {n, m, a, a, a, n, b, b, b, n, a, a, a, m, o, n},
    {n, m, a, a, a, n, b, b, b, n, a, a, a, m, o, n},
    {n, m, m, a, a, a, n, n, n, a, a, a, m, m, o, n},
    {n, o, m, m, m, m, m, m, m, m, m, m, m, o, o, n},
    {_, n, o, o, o, o, o, o, o, o, o, o, o, o, n, _},
    {_, _, n, n, n, n, n, n, n, n, n, n, n, n, _, _},
};