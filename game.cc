#include "game.hh"
#include "utils.hh"
#include "mario.hh"
using namespace pro2;

const int r = pro2::red;  //rojo
const int _ = -1; //espai en blanc
const std::vector<std::vector<int>> game_over_sprite = {
        {_, _, r, r, r, r, r, _, _, _, r, r, r, _, _, _, r, r, _, _, _, r, r, _, r, r, r, r, r, r, r},
        {_, r, r, _, _, _, _, _, _, r, r, _, r, r, _, _, r, r, r, _, r, r, r, _, r, r, _, _, _, _, _},
        {r, r, _, _, _, _, _, _, r, r, _, _, _, r, r, _, r, r, r, r, r, r, r, _, r, r, _, _, _, _, _},
        {r, r, _, _, r, r, r, _, r, r, _, _, _, r, r, _, r, r, r, r, r, r, r, _, r, r, r, r, r, _, _},
        {r, r, _, _, _, r, r, _, r, r, r, r, r, r, r, _, r, r, _, r, _, r, r, _, r, r, _, _, _, _, _},
        {_, r, r, _, _, r, r, _, r, r, _, _, _, r, r, _, r, r, _, _, _, r, r, _, r, r, _, _, _, _, _},
        {_, _, r, r, r, r, r, _, r, r, _, _, _, r, r, _, r, r, _, _, _, r, r, _, r, r, r, r, r, r, r},
        
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        {_, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _},
        
        {_, r, r, r, r, r, _, _, r, r, _, _, _, r, r, _, r, r, r, r, r, r, r, _, r, r, r, r, r, r, _},
        {r, r, _, _, _, r, r, _, r, r, _, _, _, r, r, _, r, r, _, _, _, _, _, _, r, r, _, _, _, r, r},
        {r, r, _, _, _, r, r, _, r, r, _, _, _, r, r, _, r, r, _, _, _, _, _, _, r, r, _, _, _, r, r},
        {r, r, _, _, _, r, r, _, r, r, r, _, r, r, r, _, r, r, r, r, r, _, _, _, r, r, _, _, r, r, r},
        {r, r, _, _, _, r, r, _, _, r, r, r, r, r, _, _, r, r, _, _, _, _, _, _, r, r, r, r, r, _, _},
        {r, r, _, _, _, r, r, _, _, _, r, r, r, _, _, _, r, r, _, _, _, _, _, _, r, r, _, r, r, r, _},
        {_, r, r, r ,r, r, _, _, _, _, _, r, _, _, _, _, r, r, r, r, r, r, r, _, r, r, _, _, r, r, r},
    };

Game::Game(int width, int height)
    : mario_({width / 2, 150}),
        key_({-50, 150}),
        goombas_{
            Goomba({100, 250}),
            Goomba({150, 250}),
        },
        monedas_{               // inicialitzem les primeres monedes
          Moneda({50, 250}),
          Moneda({150, 250}),
          Moneda({300, 150}),
          Moneda({350, 150}),
            Moneda({400, 150}),
            Moneda({450, 150}),
            Moneda({500, 150}), 
            Moneda({550, 150}),
        },
      platforms_{
          Platform(150, 300, 200, 211),
          Platform(40, 200, 250, 261),
          Platform(250, 400, 150, 161),
          Platform(-100, 5, 200, 210),
      },
      finished_(false) {
    for (int i = 1; i < 1000; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
    }
    for (int i = 1; i < 1000; i++){
        goombas_.push_back(Goomba({150+ i*200, 150}));
    }
    for (int i = 1; i < 1000; i++) {
        monedas_.push_back(Moneda({325 + i * 200, 125})); //fem un bucle per crear una serie de monedes
        monedas_.push_back(Moneda({275 + i * 200, 125}));
        monedas_.push_back(Moneda({375 + i * 200, 125}));
    }
    /*
    * busquem la plataforma sobre la que està el goomba i li assignem els extrems
    * per tal que el goomba es mogui sobre ella.
    * això es fa per tal que el goomba no es mogui fora de la plataforma i es pugui moure
    * correctament.
    */
    for(Goomba& goomba : goombas_){
        for(const Platform& plat:platforms_){                                                                     
            pro2::Rect r = plat.get_rect();
            if (goomba.pos().x >= r.left && goomba.pos().x <= r.right && goomba.pos().y == r.top) {
                goomba.set_extrems(r.left, r.right);
                break;
            }
        }
        goombas_finder_.add(&goomba);
    }

    for(const Platform& p : platforms_) {
        platforms_finder_.add(&p); // afegim les plataformes al finder
    }
    for(const Moneda& m : monedas_) {
        monedas_finder_.add(&m); // afegim les monedes al finder
    }
}

void Game::process_keys(pro2::Window& window) {
    if (window.is_key_down(Keys::Escape)) {
        finished_ = true;
        return;
    }
}

void Game::update_objects(pro2::Window& window) {
    if(!mario_.is_dead()){
        mario_.update(window, platforms_);
    }
    for(Goomba& goomba: goombas_){
        goomba.update_animation(window, platforms_); // actualitzem l'animació del goomba
    }
        for(Moneda& moneda : monedas_) {            // recorrem totes les monedes i fem que si el mario toca la moneda, aquesta desapareix ja que ha estat recollida
            if(!moneda.is_recogida()){
                const pro2:: Pt mario_pos = mario_.pos();
                const pro2:: Pt moneda_pos = moneda.pos();

                const int collision_distance = 15; // distància de col·lisió
                if(abs(mario_pos.x - moneda_pos.x) < collision_distance && abs(mario_pos.y - moneda_pos.y) < collision_distance) {
                    moneda.recoger(); // si la moneda no ha estat recollida, la recollim
                    monedas_recogidas_++;
                    /* mostrem el nombre de monedes recollides, 
                     amb el \r i el flush per sobreescriure la línia, 
                     ja que són de la llibreria estandard de C++ */    
                    std::cout << "\r Monedes: " << monedas_recogidas_ << std::flush;             
                }
                
            }
            moneda.update_animation(window); // actualitzem l'animació de la moneda 
        }
    if(!mario_.is_dead()){ // si el mario no està mort i el goomba no ha estat eliminat, comprovem si el mario toca el goomba
        for(Goomba& goomba : goombas_){
            if(goomba.is_eliminat()) continue; // si el goomba ha estat eliminat, no fem res
            const pro2::Pt mario_pos = mario_.pos();
            const pro2::Rect goomba_rect = goomba.get_rect();
            const pro2::Pt mario_last_pos = mario_.last_pos();

         
            if (mario_pos.x >= goomba_rect.left and mario_pos.x <= goomba_rect.right and mario_pos.y >= goomba_rect.top and mario_pos.y <= goomba_rect.bottom) { // si el mario toca el goomba
                if(mario_last_pos.y < goomba_rect.top and mario_pos.y >= goomba_rect.top) { // si el mario està per sobre del goomba, el mata
                    goomba.eliminar();
                    mario_.set_y(goomba_rect.top - 15); // el mario es posa a sobre del goomba
                    mario_.bounce(); // el mario rebota
                }else{
                    mario_.matar();
                    frame_mort = window.frame_count();
                }
            }
        }
     }
     const int limit_mapa = 600;
     if(mario_.pos().y > limit_mapa and !mario_.is_dead()){
        mario_.matar();

        frame_mort = window.frame_count();
     }
        if (!key_.is_recogida()) {
            const pro2::Pt mario_pos = mario_.pos();
            const pro2::Pt key_pos = key_.get_pos();
            const int collision_distance = 15;
            if (abs(mario_pos.x - key_pos.x) < collision_distance && abs(mario_pos.y - key_pos.y) < collision_distance) {
                key_.recoger();
                // Aquí puedes aumentar un contador de llaves recogidas si lo necesitas
            }
        }
        key_.update_animation(window);
}



void Game::update_camera(pro2::Window& window){
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

    if (frame_mort != -1 and window.frame_count() - frame_mort > 3 * 48) {
        finished_ = true;
    }
}

void Game::paint(pro2::Window& window) {
    int frames_since_death = 0;
    if (mario_.is_dead()) {
        frames_since_death = window.frame_count() - frame_mort;
    }
    // Si han pasado más de 48 frames desde la muerte, mostrar Game Over
    if (mario_.is_dead() && frames_since_death >= 48) {
        window.clear(pro2::black);
        window.set_camera_topleft({0, 0});
        pro2::Pt top_left = {
            window.width() / 2 - (int)game_over_sprite[0].size() / 2,
            window.height() / 2 - (int)game_over_sprite.size() / 2
        };
        paint_sprite(window, top_left, game_over_sprite, false);
        return;
    }

    // Pintar el mundo normalmente
    window.clear(sky_blue);
    pro2::Rect camera = window.camera_rect();
    const Color lava = 0xAB2327;
    paint_rect(window, camera.left, std::max(600, camera.top), camera.right-1, camera.bottom-1, lava);

    std::set<const Platform*> visibles = platforms_finder_.query(camera);
    for (const Platform* p : visibles) {
        p->paint(window);
    }

    // Pintar Mario (sprite muerto si está muriendo)
    mario_.paint(window, mario_.is_dead());

    if (!key_.is_recogida()) {
        key_.paint(window);
    }

    for (const Goomba& goomba : goombas_) {
        if (!goomba.is_eliminat()) {
            goomba.paint(window);
        }
    }

    std::set<const Moneda*> monedes_visibles = monedas_finder_.query(camera);
    for (const Moneda* m : monedes_visibles) {
        if (!m->is_recogida()) {
            m->paint(window);
        }
    }
}
