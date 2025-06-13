#ifndef KEY_HH
#define KEY_HH

#include<iostream>
#include "window.hh"

class Key{
    private:
        pro2::Pt pos; // posició de la clau;
        int base_y;
        bool recogida_ = false; // booleà que indica si la clau ha estat recollida
        

    
    public:
        static const std::vector<std::vector<int>> key_sprite_;
        static const std::vector<std::vector<int>> key_sprite_black_;
        
        Key(pro2::Pt pos) : pos(pos), base_y(pos.y){}; // constructor de la clau
        void paint(pro2::Window& window) const; // funció que pinta la clau a la finestra
        pro2::Pt get_pos() const { return pos; } // retorna la posició de la clau
        bool is_recogida() const; // retorna si la clau ha estat recollida
        void recoger(); // funció que recull la clau
        pro2::Rect get_rect() const {
            return {pos.x - 6, pos.y - 15, pos.x + 6, pos.y + 1};
        }
        void set_pos(const pro2::Pt& pos);
        void update_animation(const pro2::Window& window);
        
};

#endif