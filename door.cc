#include "door.hh"
#include "utils.hh"

const int _ = -1;
const int n = pro2::black;
const int m = 0x8b5e20;
const int a = 0xdfa420;
const int v = 0xfcd53f;

const int g = 0x3a3a3a;

const std::vector<std::vector<int>> Door::door_sprite_ = {
    {_, _, _, _, _, n, n, n, n, n, n, _, _, _, _, _},
    {_, _, _, n, n, a, a, m, m, a, a, n, n, _, _, _},
    {_, _, n, a, a, a, a, m, m, a, a, a, a, n, _, _},
    {_, n, a, a, m, m, a, m, m, a, m, m, a, a, n, _},
    {_, n, a, m, a, v, a, m, m, a, m, a, v, a, n, _},
    {n, a, a, m, a, v, a, m, m, a, m, a, v, a, a, n},
    {n, a, m, a, a, v, a, m, m, a, m, a, a, v, a, n},
    {n, a, m, a, a, v, a, m, m, a, m, a, a, v, a, n},
    {n, a, m, a, a, v, a, m, m, a, m, a, a, v, a, n},
    {n, a, m, a, a, v, a, m, m, a, m, a, a, v, a, n},
    {n, a, m, a, a, v, a, m, m, a, m, a, a, v, a, n},
    {n, a, m, a, a, v, a, m, m, a, m, a, a, v, a, n},
    {n, a, v, v, v, v, a, m, m, a, v, v, v, v, a, n},
    {n, a, a, a, a, a, a, m, m, a, a, a, a, a, a, n},
    {n, a, m, m, m, m, a, m, m, a, m, m, m, m, a, n},
    {n, a, m, a, a, v, a, m, m, a, m, a, a, v, a, n},
    {n, a, m, a, a, n, n, m, m, n, n, a, a, v, a, n},
    {n, a, m, a, n, v, a, n, n, v, a, n, a, v, a, n},
    {n, a, m, a, n, a, a, n, n, a, a, n, a, v, a, n},
    {n, a, m, a, m, n, n, m, m, n, n, m, a, v, a, n},
    {n, a, m, a, a, m, m, m, m, m, m, a, a, v, a, n},
    {n, a, v, v, v, v, a, m, m, a, v, v, v, v, a, n},
    {n, a, a, a, a, a, a, m, m, a, a, a, a, a, a, n},
    {n, a, m, m, m, m, a, m, m, a, m, m, m, m, a, n},
    {n, a, m, a, a, v, a, m, m, a, m, a, a, v, a, n},
    {n, a, m, a, a, v, a, m, m, a, m, a, a, v, a, n},
    {n, a, m, a, a, v, a, m, m, a, m, a, a, v, a, n},
    {n, a, m, a, a, v, a, m, m, a, m, a, a, v, a, n},
    {n, a, m, a, a, v, a, m, m, a, m, a, a, v, a, n},
    {n, a, m, a, a, v, a, m, m, a, m, a, a, v, a, n},
    {n, a, v, v, v, v, a, m, m, a, v, v, v, v, a, n},
    {n, a, a, a, a, a, a, m, m, a, a, a, a, a, a, n},
    {n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n},
};

const std::vector<std::vector<int>> Door::door_sprite_open_ = {
   {_, _, _, _, _, n, n, n, n, n, n, _, _, _, _, _},
    {_, _, _, n, n, g, g, g, g, g, g, n, n, _, _, _},
    {_, _, n, g, g, g, g, g, g, g, g, g, g, n, _, _},
    {_, n, g, g, g, g, g, g, g, g, g, g, g, g, n, _},
    {_, n, g, g, g, g, g, g, g, g, g, g, g, g, n, _},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, g, g, g, g, g, g, g, g, g, g, g, g, g, g, n},
    {n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n}
};

void Door::paint(pro2::Window& window) const {
    pro2::Pt top_left = {pos_.x - 3, pos_.y - 30}; // Ajusta según el sprite
    if (abierta_) {
        paint_sprite(window, top_left, door_sprite_open_, false);
    } else {
        paint_sprite(window, top_left, door_sprite_, false);
    }
}