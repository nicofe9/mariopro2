#include "flor.hh"
#include "utils.hh"

const int _ = -1;
const int w = pro2::white;
const int a = 0x1a66cc;
const int h = 0x9eecff;
const int n = pro2::black;
const int v = 0x028a0f;
const int c = 0xb0fc38;

const std::vector<std::vector<int>> Flor::flor_sprite_ = {
    {_, _, _, _, n, n, n, n, n, n, n, n},
    {_, _, n, n, a, a, a, a, a, a, a, a, n, n},
    {_, n, a, a, h, w, w, w, w, w, w, h, a, a, n},
    {n, a, h, w, w, w, n, w, w, n, w, w, w, h, a, n},
    {n, a, h, w, w, w, n, w, w, n, w, w, w, h, a, n},
    {n, a, a, h, h, w, w, w, w, w, w, h, h, a, a, n},
    {_, n, a, a, a, h, h, h, h, h, h, a, a, a, n},
    {_, _, n, n, a, a, a, a, a, a, a, a, n, n},
    {_, _, _, _, n, n, n, n, n, n, n, n},
    {_, n, n, _, _, _, n, c, v, n, _, _, _, n, n},
    {n, c, c, n, n, _, n, c, v, n, _, n, n, c, c, n},
    {n, c, n, c, c, n, n, c, v, n, n, c, c, n, c, n},
    {n, v, v, n, c, c, n, c, v, n, c, c, n, v, v, n},
    {_, n, v, v, n, c, n, c, v, n, c, n, v, v, n},
    {_, _, n, n, v, n, c, c, v, v, n, v, n, n},
    {_, _, _, _, n, n, n, n, n, n, n, n}
};

void Flor::paint(pro2::Window& window) const {
    if (!recogida_)
        paint_sprite(window, {pos_.x - 2, pos_.y - 2}, flor_sprite_, false);
}