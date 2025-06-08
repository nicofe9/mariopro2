#include "planta.hh"
#include "utils.hh"
#include <vector>
using namespace std;

const int _ = -1;
const int n = pro2::black;
const int r = pro2::red;
const int b = pro2::white;
const int c = 0xb0fc38;
const int v = 0x028a0f;

const vector<vector<int>> Planta::planta_carnivora_sprite_ = {
    {n, b, b, b, n, _, _, _, _, _, _, n, b, b, b, n},
    {n, b, b, b, b, n, _, _, _, _, n, b, b, b, b, n},
    {_, n, b, b, b, n, _, _, _, _, n, b, b, b, n, _},
    {_, _, n, b, b, b, n, _, _, n, b, b, b, n, _, _},
    {_, n, r, n, b, b, b, n, n, b, b, b, n, r, n, _},
    {_, n, r, r, n, b, b, b, b, b, b, n, r, b, n, _},
    {n, r, b, r, r, n, b, b, b, b, n, r, r, r, r, n},
    {n, r, r, r, r, r, n, n, n, n, r, r, r, r, r, n},
    {n, r, r, r, r, r, b, b, r, r, r, r, r, r, r, n},
    {_, n, r, r, r, r, b, b, r, r, r, b, b, r, n, _},
    {_, n, b, b, r, r, r, r, r, r, r, b, b, r, n, _},
    {_, _, n, n, r, r, r, r, r, r, r, r, n, n, _, _},
    {_, _, _, _, n, n, n, n, n, n, n, n, _, _, _, _},
    {_, n, n, _, _, _, n, n, n, n, _, _, _, n, n, _},
    {n, c, c, n, n, n, n, v, n, n, _, n, n, c, v, n},
    {n, c, n, c, c, n, n, c, v, n, n, c, c, n, v, n},
    {n, c, n, v, v, c, n, c, v, n, c, v, v, n, v, n},
    {n, c, v, n, v, c, n, c, v, n, c, v, n, v, v, n},
    {_, n, v, v, n, v, n, c, v, n, v, n, v, v, n, _},
    {_, _, n, n, v, n, v, c, v, v, n, v, n, n, _, _},
    {_, _, _, _, n, n, n, c, v, n, n, n, _, _, _, _},
    {_, n, n, _, _, _, n, c, v, n, _, _, _, n, n, _},
    {n, c, c, n, n, _, n, c, v, n, _, n, n, c, v, n},
    {n, c, n, c, c, n, n, c, v, n, n, c, c, n, v, n},
    {n, c, n, v, v, c, n, c, v, n, c, v, v, n, v, n},
    {n, c, v, n, v, c, n, c, v, n, c, v, n, v, v, n},
    {_, n, v, v, n, v, n, c, v, n, v, n, v, v, n, _},
    {_, _, n, n, v, n, v, c, v, v, n, v, n, n, _, _},
    {_, _, _, _, n, n, n, c, v, n, n, n, _, _, _, _},
    {_, _, _, _, _, _, n, c, v, n, _, _, _, _, _, _},
    {_, _, _, _, _, _, n, c, v, n, _, _, _, _, _, _},
    {_, _, _, _, _, _, n, c, v, n, _, _, _, _, _, _},
};

Planta::Planta(pro2::Pt pos, int base_y, int recorregut)
    : pos_(pos), base_y_(base_y), recorregut_(recorregut), frame_offset_(0) {}

void Planta::update_animation(const pro2::Window& window) {
    int frame = window.frame_count() + frame_offset_;
    double t = (frame % 192) / 192.0;
    double pause = 0.15;
    double y;
    if (t < pause) {
        y = recorregut_;
    } else if (t < 0.5 - pause/2) {
        double t2 = (t - pause) / (0.5 - pause);
        y = recorregut_ * (1.0 - t2);
    } else if (t < 0.5 + pause/2) {
        y = 0;
    } else if (t < 1.0 - pause) {
        double t2 = (t - (0.5 + pause/2)) / (0.5 - pause);
        y = recorregut_ * t2;
    } else {
        y = recorregut_;
    }
    pos_.y = base_y_ + int(y);
}

void Planta::paint(pro2::Window& window) const {
    paint_sprite(window, pos_, planta_carnivora_sprite_, false);
}
pro2::Rect Planta::get_rect() const {
    int width = 0;
    if (!planta_carnivora_sprite_.empty()) {
        width = planta_carnivora_sprite_[0].size();
    }
    int height = planta_carnivora_sprite_.size();
    return {pos_.x, pos_.y, pos_.x + width, pos_.y + height};
}