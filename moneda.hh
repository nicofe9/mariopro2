#ifndef MONEDA_HH
#define MONEDA_HH

#include <iostream>
#include "window.hh"

class Moneda{
 private:
    bool recogida_ = false;         //booleà que indica si la moneda ha estat recollida
    pro2::Pt pos_;               //posició de la moneda
    static const std::vector<std::vector<std::vector<int>>> moneda_sprites_; //vector de matrius per dibuixar els diferents sprites de la moneda
   int current_sprite_ = 0;      //comptador de cada sprite de la moneda
 public:
    Moneda(pro2::Pt pos) : pos_(pos) {};        //constructor de la moneda

    void paint(pro2::Window& window) const;     //funció que pinta la moneda a la finestra
    pro2::Pt pos() const { return pos_; }       //retorna la posició de la moneda
    bool is_recogida() const;                   //retorna si la moneda ha estat recollida   
    void recoger();                             //funció que recull la moneda
   void update_animation(const pro2::Window& window); //funció que actualitza l'animació de la moneda
};

#endif