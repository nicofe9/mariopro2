#ifndef BLOC_HH
#define BLOC_HH

#include <iostream>
#include <vector>
#include "window.hh"
#include "utils.hh"

class Bloc {
    pro2::Pt pos_;
    bool destruido_ = false;
public:
    static const std::vector<std::vector<int>> bloc_sprite_;
    Bloc(pro2::Pt pos) : pos_(pos) {}
    pro2::Pt pos() const { return pos_; }
    bool destruido() const { return destruido_; }
    void destruir() { destruido_ = true; }
    pro2::Rect get_rect() const {
        return {pos_.x, pos_.y, pos_.x + 16, pos_.y + 16};
    }
    void paint(pro2::Window& window) const {
        if (!destruido_) {
            paint_sprite(window, pos_, bloc_sprite_, false);
        }
    }
};

#endif