#include "key.hh"
#include "utils.hh"
#include <vector>

using namespace std;
using namespace pro2;


const int y = 0xFFF52D;
const int o = 0xFFA460;
const int _ = -1;
const int n = pro2::black;
const int b = pro2::white;

const vector<vector<int>> Key::key_sprite_ = {
    {_, _, _, _, _, _, _, _, _, _, n, n, n, n, _, _, _, _},
    {_, _, _, _, _, _, _, _, _, n, b, y, y, y, n, _, _, _},
    {_, _, _, _, _, _, _, _, n, b, y, n, n, y, y, n, _, _},
    {_, _, _, _, _, _, _, _, n, b, n, _, _, n, y, y, n, _},
    {_, _, _, _, _, _, _, n, b, y, n, _, _, _, n, y, o, n},
    {_, _, _, _, _, _, _, n, b, y, n, _, _, _, _, n, o, n},
    {_, _, _, _, _, _, _, _, n, b, y, n, _, _, _, n, o, n},
    {_, _, _, _, _, _, _, _, n, b, y, y, n, n, n, y, o, n},
    {_, _, _, _, _, _, _, n, b, y, o, o, y, y, o, o, n, _},
    {_, _, n, n, n, _, n, b, y, o, n, n, o, o, n, n, _, _},
    {_, _, n, b, b, n, b, y, o, n, _, _, n, n, _, _, _, _},
    {n, n, n, y, y, b, y, o, n, _, _, _, _, _, _, _, _, _},
    {n, b, b, y, y, y, o, n, _, _, _, _, _, _, _, _, _, _},
    {n, y, y, y, y, o, n, _, _, _, _, _, _, _, _, _, _, _},
    {_, n, o, y, o, n, _, _, _, _, _, _, _, _, _, _, _, _},
    {_, _, n, o, n, _, _, _, _, _, _, _, _, _, _, _, _, _},
    {_, _, _, n, _, _, _, _, _, _, _, _, _, _, _, _, _, _},

};

void Key::paint(pro2::Window& window) const {                   // pinta la moneda a la finestra
        const Pt top_left = {pos.x - 6, pos.y - 15};
        paint_sprite(window, top_left, key_sprite_, false);
    }

bool Key::is_recogida() const{
    return recogida_;
}

void Key::recoger(){
    recogida_ = true;
}

void Key::update_animation(const pro2::Window& window) {
    if (recogida_) return;
    int frame = window.frame_count();
    pos.y = base_y + int(8 * sin(frame / 12.0));
}