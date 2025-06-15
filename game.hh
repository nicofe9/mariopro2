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
#include "bloc.hh"
#include "planta.hh"
#include "door.hh"
#include "bowser.hh"
#include "peach.hh"
#include "flor.hh"

class Game {
    Mario                 mario_;
    Planta                carnivora_;
    Bloc bloc_{pro2::Pt{300, 84}};
    Bloc bloc_flor_{pro2::Pt{0, 0}};
    Door puerta_{pro2::Pt{1125, 150}};
    Bowser bowser_{pro2::Pt{1300, 150-39}};
    Peach peach_{pro2::Pt{1350, 150-32}};

    bool llave_animando_ = false;
    int llave_anim_frame_ = 0;
    int llave_anim_max_frames_ = 20;
    int llave_y_inicial_ = 100;
    int llave_y_animada_ = 100;
    bool llave_oculta_ = true;
    bool puerta_visible_ = false;
    bool esperando_transicion_puerta_ = false;
    bool en_nuevo_mapa_ = false;
    bool nuevo_mapa_inicializado_ = false;
    int frame_entrada_nuevo_mapa_ = -1;
    bool peach_rescatada_ = false; // booleà que indica si la princesa ha estat rescatada
    int frame_peach_rescatada_ = -1; // frame en el que la princesa ha estat rescatada
    bool flor_visible_ = false; // booleà que indica si la flor està visible
    bool flor_recogida_ = false; // booleà que indica si la flor ha estat recollida
    bool flor_animando_ = false;
    int flor_anim_frame_ = 0;
    const int flor_anim_max_frames_ = 20;
    int flor_y_inicial_ = 0;
    double flor_y_animada_ = 0;
    int flor_base_y_ = 0;
    pro2::Pt flor_pos_ = {1200, 170};
    int frame_flor_aparece_ = -1;

    bool transicion_nuevo_mapa_ = false; // booleà que indica si estem en una transició al nou mapa
    int frame_transicion_ = -1; // frame en el que estem de la transició al nou mapa
    
    std::vector<Goomba> goombas_;
    std::vector<Platform> platforms_;
    std::vector<Moneda>   monedas_;     //vector de monedes
    std::vector<Key>     keys_;
    std::vector<Decor> decoracions_;
    std::vector<Platform> plataformas_nuevo_mapa_;
    std::vector<Iceball> iceballs_;
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