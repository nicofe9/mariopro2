#ifndef PEACH_HH
#define PEACH_HH

#include "window.hh"
#include "utils.hh"
#include <vector>

class Peach {
public:
    enum Estado { LLORANDO, FELIZ, OCULTA };
private:
    pro2::Pt pos_;
    Estado estado_ = LLORANDO;
    static const std::vector<std::vector<int>> peach_llorando_sprite_;
    static const std::vector<std::vector<int>> peach_feliz_sprite_;
public:
    Peach(pro2::Pt pos) : pos_(pos) {}

    void set_estado(Estado e) { estado_ = e; }
    Estado estado() const { return estado_; }
    pro2::Pt pos() const { return pos_; }

    void paint(pro2::Window& window) const {
        if (estado_ == OCULTA) return;
        if (estado_ == LLORANDO) {
            paint_sprite(window, {pos_.x - 8, pos_.y - 32}, peach_llorando_sprite_, false);
        } else if (estado_ == FELIZ) {
            paint_sprite(window, {pos_.x - 8, pos_.y - 32}, peach_feliz_sprite_, false);
        }
    }
};

#endif