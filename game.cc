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
        keys_{
            Key({-50, 100}),
            Key({1040, -60}),
            Key({300, 100}),
        },
        goombas_{
            Goomba({100, 250}),
            Goomba({150, 250}),
            Goomba({970, -10}),
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
          Platform(40, 200, 250, 700),
          Platform(250, 400, 150, 161),
          Platform(-100, 5, 200, 700),
          

          Platform(730, 790, 90, 100),
          Platform(800, 860, 70, 80),   // Plataforma 1
          Platform(870, 930, 30, 40),   // Plataforma 2
          Platform(940, 1000, -10, 0),  // Plataforma 3 (con Goomba)
          Platform(1010, 1070, -50, -40), // Plataforma 4 (con llave)
      },
        carnivora_({-50, 50}, 135, 100),

      
      finished_(false) {
    for (int i = 1; i < 1000; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 700));
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
    for (int i = 1; i < 1000; i++) {
        decoracions_.emplace_back(pro2::Pt{325 + i * 200, -30}, Decor::nubes_);
        decoracions_.emplace_back(pro2::Pt{275 + i * 200, 10}, Decor::nubes_);
        decoracions_.emplace_back(pro2::Pt{400 + i * 200, 0}, Decor::nubes_);
        
    }
    decoracions_.emplace_back(pro2::Pt{-52, 166}, Decor::tuberia_); 
    pro2::Rect tubo_rect = decoracions_.back().get_rect();
    platforms_.push_back(Platform(tubo_rect.left, tubo_rect.right, tubo_rect.top, tubo_rect.bottom));

    for (const Platform& plat : platforms_) {
        if(rand() % 2 == 0){
            pro2::Rect r = plat.get_rect();
            int ancho = r.right - r.left;

            if (ancho > 20) {
            int piedra1_x = r.left + rand() % (ancho - 10) + 5;
            int piedra_y = r.top - 3;
            decoracions_.emplace_back(pro2::Pt{piedra1_x, piedra_y}, Decor::piedras_);
            int piedra2_x = r.left + rand() % (ancho - 10) + 5;
            decoracions_.emplace_back(pro2::Pt{piedra2_x, piedra_y}, Decor::piedras_);
            }
        }   
    }

    for (size_t i = 0; i < platforms_.size() - 1; ++i) {
    platforms_finder_.add(&platforms_[i]);
    }
    for(const Moneda& m : monedas_) {
        monedas_finder_.add(&m); // afegim les monedes al finder
    }
    for (const Decor& decor : decoracions_) {
        decoracions_finder_.add(&decor);
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

    pro2::Rect camera = window.camera_rect();
    std::set<const Goomba*> goombas_visibles = goombas_finder_.query(camera);
    for (Goomba& goomba : goombas_) {
        if (goombas_visibles.count(&goomba) && !goomba.is_eliminat()) {
            goomba.update_animation(window, platforms_);
        }
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
            const pro2::Rect planta_rect= carnivora_.get_rect();
            const pro2::Pt mario_last_pos = mario_.last_pos();

         
            if ((mario_pos.x >= goomba_rect.left and mario_pos.x <= goomba_rect.right and mario_pos.y >= goomba_rect.top and mario_pos.y <= goomba_rect.bottom) or 
                mario_pos.x >= planta_rect.left and mario_pos.x <= planta_rect.right and mario_pos.y >= planta_rect.top and mario_pos.y <= planta_rect.bottom) { // si el mario toca el goomba o la planta
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
     carnivora_.update_animation(window);
     for(Key& key : keys_){
        if (!key.is_recogida()) {
            const pro2::Pt mario_pos = mario_.pos();
            const pro2::Pt key_pos = key.get_pos();
            const int collision_distance = 15;
            if (abs(mario_pos.x - key_pos.x) < collision_distance && abs(mario_pos.y - key_pos.y) < collision_distance) {
                key.recoger();
                // Aquí puedes aumentar un contador de llaves recogidas si lo necesitas
            }
        }
        key.update_animation(window);
     }
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

    window.clear(sky_blue);
    pro2::Rect camera = window.camera_rect();

    const Color lava = 0xAB2327;
    paint_rect(window, camera.left, std::max(600, camera.top), camera.right-1, camera.bottom-1, lava);

    carnivora_.paint(window);

    std::set<const Platform*> visibles = platforms_finder_.query(camera);
    for (const Platform* p : visibles) {
        p->paint(window);
    }
    
    mario_.paint(window, mario_.is_dead());
    

    for(const Key& key_ : keys_) {
        if (!key_.is_recogida()) {
            key_.paint(window);
        }
    }
    int total_llaves = keys_.size();
    int recogidas = 0;
    for (const Key& key : keys_) {
        if (key.is_recogida()) recogidas++;
    }
    int margen = 10;
    int separacion = 30;
    pro2::Rect cam = window.camera_rect();
    pro2::Pt cam_topleft = {cam.left, cam.top};
    int x0 = cam_topleft.x + window.width() - margen - separacion * total_llaves;
    int y0 = cam_topleft.y + margen;

    for (int i = 0; i < total_llaves; ++i) {
        pro2::Pt pos = {x0 + i * separacion, y0};
        if (i < recogidas) {
            paint_sprite(window, pos, Key::key_sprite_, false);
        } else {
            paint_sprite(window, pos, Key::key_sprite_black_, false);
        }
    }
    
    std::set<const Decor*> decoracions_visibles = decoracions_finder_.query(camera);
    for (const Decor* decor : decoracions_visibles) {
        decor->paint(window);
    }

    std::set<const Goomba*> goombas_visibles = goombas_finder_.query(camera);
    for (const Goomba* goomba : goombas_visibles) {
        if (!goomba->is_eliminat()) {
            goomba->paint(window);
        }
    }

    std::set<const Moneda*> monedes_visibles = monedas_finder_.query(camera);
    for (const Moneda* m : monedes_visibles) {
        if (!m->is_recogida()) {
            m->paint(window);
        }
    }
}
