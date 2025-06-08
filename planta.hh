#ifndef PLANTA_HH
#define PLANTA_HH

#include <vector>
#include "window.hh"

class Planta{
    public:
        Planta(pro2::Pt pos, int base_y, int recorregut);

        void update_animation(const pro2::Window& window);
        void paint(pro2::Window& window) const;
        pro2::Rect get_rect() const;

    private:
    pro2::Pt pos_;
    int base_y_;
    int recorregut_;
    int frame_offset_;
    static const std::vector<std::vector<int>> planta_carnivora_sprite_;
};

#endif