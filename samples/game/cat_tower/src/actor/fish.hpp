#ifndef MGC_FISH_HPP
#define MGC_FISH_HPP

#include "mgc/mgc.h"
#include "mgc/utils/jumpctrl/jumpctrl.h"
#include "actor_if.hpp"
#include "game_info/game_info.hpp"

namespace mgc {

struct Fish : ActorIf {
    Fish(GameInfo &game_info) : game_info_(game_info) {}
    void init(mgc_id_t id, int16_t x, int16_t y) override;
    void update() override;
    const mgc_sprite *get_ptr_sprite() const override;
    void set_x_range(int16_t min, int16_t max);
    void set_speed(int8_t vx);
    void show();
    void hide();

private:
    GameInfo &game_info_;
    int8_t vx_;
    int16_t height_;
    int16_t min_x_;
    int16_t max_x_;
    mgc_sprite sprite_;
    mgc_hitbox hitbox_;
};

}
#endif/*MGC_FISH_HPP*/
