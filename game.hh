#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include "mario.hh"
#include "platform.hh"
#include "window.hh"
#include "moneda.hh"

class Game {
    Mario                 mario_;
    std::vector<Platform> platforms_;
    std::vector<Moneda>   monedas_;

    bool finished_;
    int monedas_recogidas_ = 0;

    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);

 public:
    Game(int width, int height);

    void update(pro2::Window& window);
    void paint(pro2::Window& window);

    bool is_finished() const {
        return finished_;
    }

 private:
    static constexpr int sky_blue = 0x5c94fc;
};

#endif