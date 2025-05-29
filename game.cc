#include "game.hh"
#include "utils.hh"
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
    goomba_({150, 200}), // inicialitzem el goomba
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
          Platform(100, 300, 200, 211),
          Platform(0, 200, 250, 261),
          Platform(250, 400, 150, 161),
      },
      finished_(false) {
    for (int i = 1; i < 1000; i++) {
        platforms_.push_back(Platform(250 + i * 200, 400 + i * 200, 150, 161));
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
    for(const Platform& plat:platforms_){                                                                     
        pro2::Rect r = plat.get_rect();
        if (goomba_.pos().x >= r.left && goomba_.pos().x <= r.right && goomba_.pos().y == r.top) {
            goomba_.set_extrems(r.left, r.right);
            break;
    }
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
    mario_.update(window, platforms_);
    goomba_.update_animation(window, platforms_);

    for(Moneda& moneda : monedas_) {            // recorrem totes les monedes i fem que si el mario toca la moneda, aquesta desapareix ja que ha estat recollida
        if(!moneda.is_recogida()){
            const pro2:: Pt mario_pos = mario_.pos();
            const pro2:: Pt moneda_pos = moneda.pos();

            const int collision_distance = 15; // distància de col·lisió
            if(abs(mario_pos.x - moneda_pos.x) < collision_distance && abs(mario_pos.y - moneda_pos.y) < collision_distance) {
                moneda.recoger(); // si la moneda no ha estat recollida, la recollim
                monedas_recogidas_++;
                std::cout << "\r Monedes: " << monedas_recogidas_ << std::flush; /*mostrem el nombre de monedes recollides, 
                                                                                    amb el \r i el flush per sobreescriure la línia, 
                                                                                    ja que són de la llibreria estandard de C++
                                                                                    */ 
            }
            if(abs(mario_pos.x - goomba_.pos().x) < collision_distance && abs(mario_pos.y - goomba_.pos().y) < collision_distance) {
                if(!mario_.is_dead()) { // si el mario no ha mort, el matam
                    mario_.matar();
                    frame_mort = window.frame_count(); // guardem el frame en el que ha mort el mario
                    std::cout << "\nMario ha mort!" << std::endl;
                }
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

    if (frame_mort != -1 && window.frame_count() - frame_mort > 3 * 48) {
        finished_ = true;
    }
}

void Game::paint(pro2::Window& window) {
    window.clear(sky_blue);

    std::set<const Platform*> visibles = platforms_finder_.query(window.camera_rect()); // obtenim les plataformes visibles a la finestra
    for (const Platform* p : visibles) {    // recorrem les plataformes visibles i les pintem
        p->paint(window);   // pintem les plataformes visibles
    }

    if(mario_.is_dead()){ 
        window.clear(pro2::black);
        pro2::Pt top_left = {window.width() / 2 - (int)game_over_sprite[0].size() / 2, window.height() / 2 - (int)game_over_sprite.size() / 2};
        paint_sprite(window, top_left, game_over_sprite, false);
        return;
        
    } else {
        mario_.paint(window); // pintem el mario
    }
    goomba_.paint(window);

    std::set<const Moneda*> monedes_visibles = monedas_finder_.query(window.camera_rect()); // obtenim les monedes visibles a la finestra
    for (const Moneda* m : monedes_visibles) {      // recorrem les monedes visibles i les pintem
        if (!m->is_recogida()) {    // si la moneda no ha estat recollida, la pintem
            m->paint(window);
        }
    }
}
