#include "game.hh"
using namespace pro2;

Game::Game(int width, int height)
    : mario_({width / 2, 150}),
        monedas_{               // inicialitzem les primeres monedes
          Moneda({50, 250}),
          Moneda({150, 250}),
          Moneda({300, 150}),
          Moneda({350, 150}),
        },
      platforms_{
          Platform(100, 300, 200, 211),
          Platform(0, 200, 250, 261),
          Platform(250, 400, 150, 161),
      },
      finished_(false) {
    for (int i = 1; i < 20; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
    }
    for (int i = 1; i < 20; i++) {
        monedas_.push_back(Moneda({325 + i * 200, 125})); //fem un bucle per crear una serie de monedes
        monedas_.push_back(Moneda({275 + i * 200, 125}));
        monedas_.push_back(Moneda({375 + i * 200, 125}));
    }
    
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }
}

void Game::update_objects(pro2::Window& window) {
    mario_.update(window, platforms_);

    for(Moneda& moneda : monedas_) {            // recorrem totes les monedes i fem que si el mario toca la moneda, aquesta desapareix ja que ha estat recollida
        if(!moneda.is_recogida()){
            const pro2:: Pt mario_pos = mario_.pos();
            const pro2:: Pt moneda_pos = moneda.pos();

            const int collision_distance = 10; // distància de col·lisió
            if(abs(mario_pos.x - moneda_pos.x) < collision_distance && abs(mario_pos.y - moneda_pos.y) < collision_distance) {
                moneda.recoger(); // si la moneda no ha estat recollida, la recollim
                monedas_recogidas_++;
                std::cout << "\r Monedes: " << monedas_recogidas_ << std::flush; /*mostrem el nombre de monedes recollides, 
                                                                                    amb el \r i el flush per sobreescriure la línia, 
                                                                                    ja que són de la llibreria estandard de C++
                                                                                    */ 
            }
        }
        moneda.update_animation(window); // Actualitzem l'animació de la moneda 
    }
}

void Game::update_camera(pro2::Window& window) {
    const Pt pos = mario_.pos();
    const Pt cam = window.camera_center();

    const int left = cam.x - window.width() / 4;
    const int right = cam.x + window.width() / 4;
    const int top = cam.y - window.height() / 4;
    const int bottom = cam.y + window.height() / 4;

    int dx = 0, dy = 0;
    if (pos.x > right) {
        dx = pos.x - right;
    } else if (pos.x < left) {
        dx = pos.x - left;
    }
    if (pos.y < top) {
        dy = pos.y - top;
    } else if (pos.y > bottom) {
        dy = pos.y - bottom;
    }

    window.move_camera({dx, dy});
}

void Game::update(pro2::Window& window) {
    process_keys(window);
    update_objects(window);
    update_camera(window);
}

void Game::paint(pro2::Window& window) {
    window.clear(sky_blue);
    for (const Platform& p : platforms_) {
        p.paint(window);
    }
    mario_.paint(window);
    for (const Moneda& m : monedas_) {      // si la moneda no ha estat recollida, la pintem
        if (!m.is_recogida()) {
            m.paint(window);
        }
    }
}