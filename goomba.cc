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


const vector<vector<int>> Goomba::goomba_sprite_ = {
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

void Goomba::paint(pro2::Window& window) const {
    if(eliminat) return;
    const Pt top_left = {pos_.x - 6, pos_.y - 15};
    paint_sprite(window, top_left, goomba_sprite_, looking_left_);
}

bool Goomba::is_eliminat() const {
    return eliminat;
}
void Goomba::eliminar() {
    eliminat = true;
}

void Goomba::update_animation(const pro2::Window& window, const std::vector<Platform>& platforms) {
    if (eliminat) {
        return; // Si el goomba ha sido eliminado, no hacemos nada
    }
    move(platforms);
}
void Goomba::move(const std::vector<Platform>& platforms) {
    if (eliminat) {
        return; // Si el goomba ha sido eliminado, no hacemos nada
    }
    int velocidad;
    if (looking_left_) {
        velocidad = -speed_;
    } else {
        velocidad = speed_;
    }

    pro2::Pt next_pos = pos_;
    next_pos.x = pos_.x + velocidad;

    // Limita el movimiento a los extremos
    if (next_pos.x < extrem_esquer_) {
        next_pos.x = extrem_esquer_;
        looking_left_ = false; // Cambia de dirección a la derecha
    } else {
        if (next_pos.x > extrem_dret_) {
            next_pos.x = extrem_dret_;
            looking_left_ = true; // Cambia de dirección a la izquierda
        }
    }

    pos_ = next_pos;
}


