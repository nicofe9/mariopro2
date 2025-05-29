#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include "mario.hh"
#include "platform.hh"
#include "window.hh"
#include "moneda.hh"
#include "finder.hh"
#include "goomba.hh"

class Game {
    Mario                 mario_;
    Goomba              goomba_; //goomba que es mou per la pantalla
    std::vector<Platform> platforms_;
    std::vector<Moneda>   monedas_;     //vector de monedes
    Finder<Platform> platforms_finder_;     //finder per les plataformes
    Finder<Moneda> monedas_finder_;     //finder per les plataformes i les monedes

    bool finished_;

    int frame_mort = -1;
    int monedas_recogidas_ = 0;         //comptador de monedes recollides

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