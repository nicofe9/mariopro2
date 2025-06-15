#ifndef DOOR_HH
#define DOOR_HH

#include "window.hh"
#include <vector>

class Door {
private:
    pro2::Pt pos_;
    bool abierta_ = false;
    static const std::vector<std::vector<int>> door_sprite_;
    static const std::vector<std::vector<int>> door_sprite_open_;

public:
    Door(pro2::Pt pos) : pos_(pos) {}

    void abrir() { abierta_ = true; }
    void cerrar() { abierta_ = false; }
    bool is_abierta() const { return abierta_; }
    pro2::Pt get_pos() const { return pos_; }

    pro2::Rect get_rect() const {
        // Ajusta el tamaño según el sprite
        return {pos_.x - 10, pos_.y - 30, pos_.x + 10, pos_.y + 1};
    }

    void paint(pro2::Window& window) const;

};

#endif