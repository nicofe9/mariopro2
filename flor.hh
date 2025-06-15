#ifndef FLOR_HH
#define FLOR_HH

#include "window.hh"
#include <vector>

class Flor {
public:
    Flor(pro2::Pt pos) : pos_(pos) {}

    void paint(pro2::Window& window) const;
    pro2::Pt pos() const { return pos_; }
    bool is_recogida() const { return recogida_; }
    void recoger() { recogida_ = true; }

    static const std::vector<std::vector<int>> flor_sprite_;

private:
    pro2::Pt pos_;
    bool recogida_ = false;
};

#endif