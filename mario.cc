#include "mario.hh"
#include "utils.hh"
using namespace std;
using namespace pro2;

bool dead = false;

const int _ = -1;
const int r = pro2::red;  //rojo
const int w = pro2::white; //blanco
const int n = pro2::black;  //negro
const int p = 0xFFC8C8; //rosa claro
const int o = 0xFF8080; //rosa oscuro
const int m = 0xB97A57; //marrón claro
const int k = 0x6F4E37; //marrón oscuro
const int b = 0xF8E3B7; //beige
const int a = 0xFFD700; //amarillo

// clang-format off
const vector<vector<int>> Mario::mario_sprite_normal_ = {
   {_, _, _, _, _, _, _, _, n, n, n, n, n, _, _, _, _},
   {_, _, _, _, _, _, n, n, w, w, a, w, w, n, _, _, _},
   {_, _, _, _, _, n, w, w, b, a, a, w, b, n, _, _, _},
   {_, _, _, _, n, w, b, b, n, n, n, n, n, n, n, _, _},
   {_, _, _, n, w, b, n, n, n, n, n, n, n, n, n, n, _},
   {_, _, n, b, b, n, n, n, n, n, n, n, n, n, n, n, _},
   {_, _, n, b, b, n, n, o, w, w, o, w, w, n, n, _, _},
   {_, _, o, p, n, n, o, o, w, n, p, n, w, _, _, _, _},
   {_, o, m, p, n, n, o, p, w, n, p, n, w, p, m, _, _},
   {_, o, m, o, o, n, n, p, p, o, o, p, p, p, m, _, _},
   {_, _, o, o, o, n, p, p, n, m, o, o, o, o, m, _, _},
   {_, _, n, n, o, o, o, n, n, n, n, n, n, n, n, n, _},
   {_, _, _, n, n, o, o, p, p, n, n, n, n, n, n, _, _},
   {_, _, n, n, n, m, o, o, o, o, o, o, m, m, m, m, _},
   {_, n, b, b, b, b, b, b, m, m, m, m, m, w, m, w, m},
   {_, n, b, w, w, w, w, k, k, w, w, k, w, m, w, w, m},
   {_, n, b, m, m, m, b, b, r, r, b, b, r, m, w, w, m},
   {_, n, m, w, w, m, m, k, k, r, r, k, k, r, m, m, _},
   {_, m, w, w, w, w, w, m, r, w, w, r, r, w, k, _, _},
   {_, m, w, w, w, w, w, m, r, w, w, r, r, k, m, m, _},
   {_, _, m, w, w, w, m, r, r, r, r, r, k, m, a, m, n},
   {_, n, m, m, m, m, r, r, r, r, r, k, m, m, m, n, n},
   {n, m, m, m, k, k, r, r, r, r, r, k, m, m, m, n, n},
   {n, m, m, m, k, k, k, k, k, k, k, k, m, m, n, n, n,},
   {n, m, m, a, m, m, k, k, _, _, _, _, m, n, n, n, _},
   {_, n, m, m, n, n, _, _, _, _, _, _, n, n, n, _, _},
   {_, _, n, n, _, _, _, _, _, _, _, _, _, n, _, _, _},
   
};
// clang-format on

void Mario::paint(pro2::Window& window) const {
    const Pt top_left = {pos_.x - 8, pos_.y - 26};
    paint_sprite(window, top_left, mario_sprite_normal_, looking_left_);
}

void Mario::apply_physics_() {
    if (grounded_) {
        speed_.y = 0;
        accel_.y = 0;
    }

    const int gravity = 1; 
    speed_.y += gravity;

    if (accel_time_ > 0) {
        speed_.y += accel_.y;
        accel_time_--;
    }

    pos_.x += speed_.x;
    pos_.y += speed_.y;
}

void Mario::jump() {
    if (grounded_) {
        accel_.y = -6;
        grounded_ = false;
        accel_time_ = 2;
    }
}

bool Mario::is_dead()const{
        return dead;
    }

    void Mario::matar(){
        dead = true;
    }

void Mario::update(pro2::Window& window, const vector<Platform>& platforms) {
    last_pos_ = pos_;
    if (window.is_key_down(Keys::Space)) {
        jump();
    }

    speed_.x = 0; 
    if (window.is_key_down(Keys::Left)) {
        speed_.x = -4;
    } else if (window.is_key_down(Keys::Right)) {
        speed_.x = 4;
    }
    if (speed_.x != 0) {
        looking_left_ = speed_.x < 0;
    }
    
    apply_physics_();

    set_grounded(false);

    for (const Platform& platform : platforms) {
        if (platform.has_crossed_floor_downwards(last_pos_, pos_)) {
            set_grounded(true);
            set_y(platform.top());
        }
        
    }


}