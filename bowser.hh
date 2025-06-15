#ifndef BOWSER_HH
#define BOWSER_HH

#include <vector>
#include "window.hh"
#include "utils.hh"
#include "geometry.hh"

struct Fireball {
    pro2::Pt pos;
    pro2::Pt speed;
    bool active = true;
    int frame = 0;
    int base_y = 0;
    static const std::vector<std::vector<int>> fireball_sprite_;

    Fireball(pro2::Pt p, pro2::Pt s)
        : pos(p), speed(s), base_y(p.y) {}

    void update() {
        frame++;
        pos.x += speed.x;
        pos.y = base_y + int(10 * std::sin(frame / 8.0)) + speed.y;
    }
    void paint(pro2::Window& window) const {
        if (active)
            paint_sprite(window, {pos.x-4, pos.y-4}, fireball_sprite_, false);
    }
};

class Bowser {
private:
    pro2::Pt pos_;
    bool alive_ = true;
    int frame_offset_ = 0;
    int vidas_ = 3;
    int vidas_max_ = 3;
    std::vector<Fireball> fireballs_;
    int fireball_cooldown_ = 0;
    static const std::vector<std::vector<int>> bowser_sprite_;
    static const std::vector<std::vector<int>> bowser_dead;

    int parpadeo_frames_ = 0;
    int parpadeos_totales_ = 0;
    static constexpr int PARPADEOS_MAX_ = 8;
    int frame_bowser_muerto_ = -1;
public:
    Bowser(pro2::Pt pos) : pos_(pos) {}

    void paint(pro2::Window& window) const {
        bool pintar = true;
        if(parpadeo_frames_ > 0){
            pintar = (parpadeo_frames_ % 2 == 0);
        }

        if (alive_ and pintar) {
        paint_sprite(window, pos_, bowser_sprite_, false);
        int bar_width = 40;
        int bar_height = 5;
        int x = pos_.x;
        int y = pos_.y - 10;
        int vidas_actuales = std::max(vidas_, 0);
        int vidas_maximas = vidas_max_;
        int filled = (bar_width * vidas_actuales) / vidas_maximas;
        paint_rect(window, x, y, x + bar_width, y + bar_height, 0xAA2222);
        paint_rect(window, x, y, x + filled, y + bar_height, 0x22CC22);
        for (int i = 0; i < bar_width; ++i) {
            window.set_pixel({x + i, y}, pro2::black);
            window.set_pixel({x + i, y + bar_height - 1}, pro2::black);
        }
        for (int i = 0; i < bar_height; ++i) {
            window.set_pixel({x, y + i}, pro2::black);
            window.set_pixel({x + bar_width - 1, y + i}, pro2::black);
        }
        for (const auto& f : fireballs_) f.paint(window);
        }
        else if (frame_bowser_muerto_ != -1) {
            int frames = window.frame_count() - frame_bowser_muerto_;
            if (frames < 96) {
                paint_sprite(window, pos_, bowser_dead, false);
            }
        }
    }

    void update(const pro2::Pt& mario_pos) {
        if (!alive_) return;
        if(parpadeo_frames_ > 0) parpadeo_frames_--;
        if (fireball_cooldown_ > 0) fireball_cooldown_--;
        else {
            int distancia = std::abs(mario_pos.x - pos_.x);
            if (distancia < 300) {
                lanzar_bola(mario_pos);
                fireball_cooldown_ = 60;
            }
        }
        for (auto& f : fireballs_) {
            if (f.active) f.update();
        }
    }

    void lanzar_bola(const pro2::Pt& mario_pos) {
        if (!alive_) return;
        pro2::Pt dir = {mario_pos.x - pos_.x, mario_pos.y - (pos_.y+7)};
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len == 0) len = 1;
        pro2::Pt speed = { (int)(dir.x / len * 3), (int)(dir.y / len * 2) };
        fireballs_.emplace_back(pro2::Pt{pos_.x + 20, pos_.y + 30}, speed);
    }

    void recibir_danio(pro2::Window& window) {
        if (!alive_) return;
        vidas_--;
        if (vidas_ <= 0) {
            alive_ = false;
            frame_bowser_muerto_ = window.frame_count();
        }
        parpadeo_frames_ = PARPADEOS_MAX_;
        parpadeos_totales_ = 0;
    }

    int vidas_max() const { return vidas_max_; }
    int vidas() const { return vidas_; }
    bool is_alive() const { return alive_; }
    pro2::Pt pos() const { return pos_; }
    pro2::Rect get_rect() const { return {pos_.x, pos_.y, pos_.x + 40, pos_.y+40}; }
    std::vector<Fireball>& fireballs() { return fireballs_; }
    void kill() { alive_ = false; }
};

#endif