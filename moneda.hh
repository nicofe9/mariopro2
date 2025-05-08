#ifndef MONEDA_HH
#define MONEDA_HH

#include <iostream>
#include "window.hh"

class Moneda{
 private:
    bool recogida_ = false;
    pro2::Pt pos_;
    static const std::vector<std::vector<int>> moneda_;

 public:
    Moneda(pro2::Pt pos) : pos_(pos) {};

    void paint(pro2::Window& window) const;
    pro2::Pt pos() const { return pos_; }
    bool is_recogida() const;
    void recoger();
};

#endif