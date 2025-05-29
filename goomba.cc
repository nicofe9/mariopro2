#include<iostream>
#include<vector>
#include "goomba.hh"
#include "utils.hh"
#include "platform.hh"

using namespace std;
using namespace pro2;

bool eliminat = false;

const int _ = -1;
const int n = pro2::black;
const int b = 0xE0CD95;
const int m = 0x45322E;


const vector<vector<int>> Goomba::goomba_sprite_ = {                /*he fet un nou objecte que es mou sobre una plataforma
                                                                    on més endevant aquest sera un enemic del mario al joc.
                                                                    actualment nomes forma part del mon del mario al joc i es mou per sobre
                                                                    de la plataforma*/
    {_, _, _, _, _, _, n, n, n, n, _, _, _, _, _, _},
    {_, _, _, _, n, n, m, m, m, m, n, n, _, _, _, _},
    {_, _, _, n, n, n, n, m, m, n, n, n, n, _, _, _},
    {_, _, _, _, n, b, n, m, m, n, b, n, _, _, _, _},
    {_, _, _, n, m, b, b, n, n, b, b, m, n, _, _, _},
    {_, n, n, m, m, b, n, m, m, n, b, m, m, n, n, _},
    {n, m, m, m, m, b, n, m, m, n, b, m, m, m, m, n},
    {n, m, m, m, m, m, m, m, m, m, m, m, m, m, m, n},
    {n, m, m, b, n, n, n, n, n, n, n, n, b, m, m, n},
    {_, n, m, b, m, m, m, m, m, m, m, m, b, m, n, _},
    {_, _, n, n, n, n, n, n, n, n, n, n, n, n, _, _},
    {_, _, _, _, n, b, b, b, b, b, b, n, _, _, _, _},
    {_, _, _, n, m, b, b, b, b, b, b, b, n, n, n, _},
    {_, n, n, n, n, m, b, b, b, b, b, n, n, n, n, _},
    {n, n, n, n, n, n, m, m, m, m, m, n, n, n, n, n},
    {n, n, n, n, n, n, n, _, _, _ , n, n, n, n, n, n},
};

void Goomba::paint(pro2::Window& window) const {                    // pinta el goomba a la finestra
    if(eliminat) return;
    const Pt top_left = {pos_.x - 6, pos_.y - 15};
    paint_sprite(window, top_left, goomba_sprite_, looking_left_);
}

bool Goomba::is_eliminat() const {               // retorna si el goomba ha estat eliminat (funció futura)
    return eliminat;
}
void Goomba::eliminar() {           // funció que elimina el goomba (funció futura)
    eliminat = true;
}

void Goomba::update_animation(const pro2::Window& window, const std::vector<Platform>& platforms) {     // funció que actualitza l'animació del goomba
    if (eliminat) {
        return;
    }
    move(platforms);
}
void Goomba::move(const std::vector<Platform>& platforms) {       // funció que mou el goomba
    if (eliminat) {            
        return;
    }
    int velocidad;                                  
    if (looking_left_) {              // si el goomba mira a l'esquerra, la velocitat es negativa
        velocidad = -speed_;
    } else {
        velocidad = speed_;
    }

    pro2::Pt next_pos = pos_;
    next_pos.x = pos_.x + velocidad;

    if (next_pos.x < extrem_esquer_) {      // si el goomba es mou a l'esquerra i arriba al extrem esquerre, canvia de direcció
        next_pos.x = extrem_esquer_;
        looking_left_ = false;
    } else {
        if (next_pos.x > extrem_dret_) {    // si el goomba es mou a la dreta i arriba al extrem dret, canvia de direcció
            next_pos.x = extrem_dret_;
            looking_left_ = true;
        }
    }

    pos_ = next_pos;
}


