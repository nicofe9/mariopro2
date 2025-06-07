#ifndef DECOR_HH
#define DECOR_HH

#include <iostream>
#include <vector>
#include "window.hh"

class Decor{
public:
Decor(pro2::Pt pos, const std::vector<std::vector<int>>& sprite)
        : pos_(pos), sprite_(sprite) {}

    void paint(pro2::Window& window) const;
    pro2::Rect get_rect() const;
    static const std::vector<std::vector<int>> nubes_;
    static const std::vector<std::vector<int>> piedras_;

private:
    pro2::Pt pos_;
    const std::vector<std::vector<int>>& sprite_;
    
    
};

#endif