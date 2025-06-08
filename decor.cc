#include "decor.hh"
#include "utils.hh"
#include <vector>
using namespace std;

const int _ = -1;
const int n = pro2::black;
const int b = pro2::white;
const int g = 0xcdcdcd;
const int o = 0x474b4e;
const int v = pro2::green;

const vector<vector<int>> Decor::nubes_ = {
    {_, _, _, _, _, n, n, n, n, _, _, _, _, _},
    {_, _, _, _, n, b, b, b, b, n, _, _, _, _},
    {_, _, n, n, b, b, b, b, b, b, n, _, _, _},
    {_, n, b, b, g, b, b, b, b, b, b, n, n, _},
    {n, b, b, b, b, g, b, b, b, b, g, b, b, n},
    {n, b, b, b, b, b, b, b, b, g, b, b, b, n},
    {n, g, b, b, b, b, b, b, b, b, b, b, b, n},
    {_, n, g, b, b, b, b, b, b, b, b, b, n, _},
    {_, _, n, n, n, n, n, n, n, n, n, n, _, _},
};

const vector<vector<int>> Decor::piedras_ = {
   {_, _, n, n, n, _},
   {_, n, g, g, g, n},
   {n, g, g, o, o, n},
   {_, n, n, n, n, _},
};

const vector<vector<int>> Decor::tuberia_ = {
    {n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n ,n},
    {n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n},
    {n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n},
    {n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n},
    {n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n},
    {n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n},
    {n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n},
    {n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n},
    {n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n},
    {n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n},
    {_, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n ,_},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
    {_, _, n, v, v, v, v, v, v, v, v, v, v, v, v, v, v, n, _, _},
};

pro2::Rect Decor::get_rect() const {
    int width = sprite_.empty() ? 0 : sprite_[0].size();
    int height = sprite_.size();
    return {pos_.x, pos_.y, pos_.x + width, pos_.y + height};
}

void Decor::paint(pro2::Window& window) const {
    paint_sprite(window, pos_, sprite_, false);
}