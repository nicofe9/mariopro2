#ifndef MARIO_HH
#define MARIO_HH

#include <iostream>
#include <vector>
#include "platform.hh"
#include "window.hh"

class Mario {
 private:
    pro2::Pt pos_, last_pos_;
    pro2::Pt speed_ = {0, 0};
    pro2::Pt accel_ = {0, 0};
    int      accel_time_ = 0;

    bool grounded_ = false;
	bool looking_left_ = false;
    bool dead = false; //boolea que indica si el mario(nosaltres) ha mort per un enemic

	void apply_physics_();
	
 public:
    Mario(pro2::Pt pos) : pos_(pos), last_pos_(pos) {}

    void paint(pro2::Window& window, bool dead_sprite = false) const;

    pro2::Pt pos() const {
        return pos_;
    }
    pro2::Pt last_pos() const {
        return last_pos_;
    }

    void set_y(int y) {
        pos_.y = y;
    }

    bool is_grounded() const {
        return grounded_;
    }

    void set_grounded(bool grounded) {
        grounded_ = grounded;
        if (grounded_) {
            speed_.y = 0;
        }
    }

    void toggle_grounded() {
        set_grounded(!grounded_);
    }

    void jump();
    void bounce();

    void update(pro2::Window& window, const std::vector<Platform>& platforms);

    void matar();
    bool is_dead() const;
    pro2::Pt speed() const { return speed_; }

 private:
    static const std::vector<std::vector<int>> mario_sprite_normal_;
    static const std::vector<std::vector<int>> mario_sprite_dead_;
};

#endif