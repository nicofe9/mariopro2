#include "utils.hh"
#include "moneda.hh"
#include <vector>
using namespace std;
using namespace pro2;
   
    bool recogida_ = false;

    const int y = 0xf7d547;     //amarillo comun
    const int _ = -1;
    const int n = 0x30302e;     //negro grisaceo
    const int b = 0xfafbfd;     //blanco
    const int a = 0xecab0f;     //amarillo fuerte
    const int c = 0xfff099;    //amarillo crema


    const vector<vector<int>> Moneda::moneda_texture_ ={
        {_, _, b, b, n, n, _, _},
        {_, b, y, c, c, c, n, _},
        {b, y, y, a, a, y, c, n},
        {n, y, a, y, y, c, y, n},
        {n, y, a, y, y, c, y, n},
        {n, a, y, c, c, y, y, n},
        {_, n, a, a, a, y, n, _},
        {_, _, n, n, n, n, _, _},
    };

     void Moneda::paint(pro2::Window& window) const {
        const Pt top_left = {pos_.x - 6, pos_.y - 15};
        paint_sprite(window, top_left, moneda_texture_, false);
    }

    bool Moneda::is_recogida() const {
        return recogida_;
    }

    void Moneda::recoger() {
        recogida_ = true;
    }