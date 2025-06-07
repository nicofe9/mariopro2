#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include "mario.hh"
#include "platform.hh"
#include "window.hh"
#include "moneda.hh"
#include "finder.hh"
#include "goomba.hh"
#include "key.hh"
#include "decor.hh"

class Game {
    Mario                 mario_;
    
    std::vector<Goomba> goombas_;
    std::vector<Platform> platforms_;
    std::vector<Moneda>   monedas_;     //vector de monedes
    std::vector<Key>     keys_;
    std::vector<Decor> decoracions_;
    Finder<Platform> platforms_finder_;     //finder per les plataformes
    Finder<Moneda> monedas_finder_;     //finder per les plataformes i les monedes
    Finder<Goomba> goombas_finder_;     //finder per els goombas
    Finder<Decor> decoracions_finder_; //finder per les decoracions

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