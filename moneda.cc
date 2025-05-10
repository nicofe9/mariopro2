#include "utils.hh"
#include "moneda.hh"
#include <vector>
#include <cmath>
using namespace std;
using namespace pro2;
   
    bool recogida_ = false;

    const int y = 0xf7d547;     //amarillo comun
    const int _ = -1;
    const int n = 0x30302e;     //negro grisaceo
    const int b = 0xfafbfd;     //blanco
    const int a = 0xecab0f;     //amarillo fuerte
    const int c = 0xfff099;    //amarillo crema


    const vector<vector<vector<int>>> Moneda::moneda_sprites_ ={        //vector dels diferents sprites
        {   {_, _, b, b, n, n, _, _},
            {_, b, y, c, c, c, n, _},
            {b, y, y, a, a, y, c, n},
            {n, y, a, y, y, c, y, n},
            {n, y, a, y, y, c, y, n},
            {n, a, y, c, c, y, y, n},
            {_, n, a, a, a, y, n, _},
            {_, _, n, n, n, n, _, _},
        },
        {
            {_, _, _, n, n, _, _, _},
            {_, _, n, y, b, b, _, _},
            {_, n, y, b, b, c, n, _},
            {_, n, b, b, c, y, n, _},
            {_, b, b, a, c, y, n, _},
            {_, b, a, y, y, y, n, _},
            {_, _, n, a, y, n, _, _},
            {_, _, _, n, n, _, _, _},
        },
        {
            {_, _, _, n, n, _, _, _},
            {_, _, n, a, c, n, _, _},
            {_, _, n, a, c, n, _, _},
            {_, _, n, a, c, b, _, _},
            {_, _, n, a, b, b, _, _},
            {_, _, n, b, b, n, _, _},
            {_, _, b, b, c, n, _, _},
            {_, _, _, n, n, _, _, _},
        },
        {
            {_, _, _, n, n, _, _, _},
            {_, _, n, c, y, n, _, _},
            {_, n, c, y, y, y, n, _},
            {_, n, y, c, a, y, n, _},
            {_, n, y, a, a, y, b, _},
            {_, n, y, y, y, a, b, _},
            {_, _, n, y, a, b, _, _},
            {_, _, _, b, b, _, _, _},
        }
    };

     void Moneda::paint(pro2::Window& window) const {                   // pinta la moneda a la finestra
        const Pt top_left = {pos_.x - 6, pos_.y - 15};
        paint_sprite(window, top_left, moneda_sprites_[current_sprite_], false);
    }

    bool Moneda::is_recogida() const {      //retorna si la moneda ha estat recollida
        return recogida_;
    }

    void Moneda::recoger() {
        recogida_ = true;        //la moneda ha estat recollida
    }

    void Moneda::update_animation(const pro2::Window& window){      //funció que actualitza l'animació de la moneda
        if(recogida_) return;

        int frame_counter = window.frame_count();
        current_sprite_ = (frame_counter / 10) % moneda_sprites_.size();
    }