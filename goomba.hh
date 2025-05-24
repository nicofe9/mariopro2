#ifndef GOOMBA_HH
#define GOOMBA_HH

#include <iostream>
#include "window.hh"
#include "platform.hh"

class Goomba{
    private:
        int extrem_esquer_ = 0;
        int extrem_dret_ = 0;

        pro2::Pt pos_;               //posició del goomba
        int speed_ = 1;              //velocitat del goomba
        bool looking_left_ = true;   //direcció en la que mira el goomba
        static const std::vector<std::vector<int>> goomba_sprite_; //matriu de colors que representa el sprite del goomba
        bool eliminat = false; //booleà que indica si el goomba ha estat eliminat
    public:
        Goomba(pro2::Pt pos) : pos_(pos) {};        //constructor del goomba

        void set_extrems(int esq, int dre) {
        extrem_esquer_ = esq;
        extrem_dret_ = dre;
    }
        void paint(pro2::Window& window) const;     //funció que pinta el goomba a la finestra
        pro2::Pt pos() const { return pos_; }       //retorna la posició del goomba
        void update_animation(const pro2::Window& window, const std::vector<Platform>& platforms); //funció que actualitza l'animació del goomba
        void move(const std::vector<Platform>& platforms); //funció que mou el goomba
        bool is_eliminat() const; //retorna si el goomba ha estat eliminat
        void eliminar(); //funció que elimina el goomba
        pro2::Rect get_rect() const {
            return {pos_.x - 6, pos_.y - 15, pos_.x + 6, pos_.y + 1};
        }
    };
    #endif





