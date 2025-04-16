#include "fish.hpp"
#include "resources/generated/tileset/tileset_fish.h"

namespace mgc {

void Fish::init(mgc_id_t id, int16_t x, int16_t y) {

    hitbox_init(&hitbox_, 0, 1,  1, 15, 15);

    sprite_init(&sprite_, id);
    sprite_set_position(&sprite_, x, y);
    sprite_set_tileset(&sprite_, &tileset_fish);
    sprite_set_hitbox_array(&sprite_, &hitbox_, 1);
    sprite_set_tile_idx(&sprite_, 0);
    sprite_set_enabled(&sprite_, true);

    min_x_ = 0;
    max_x_ = 0;
    vx_ = 0;
    height_ = y;
}

void Fish::set_speed(int8_t vx) {

    vx_ = vx;
}

void Fish::set_x_range(int16_t min, int16_t max) {
    min_x_ = min;
    max_x_ = max;
}

void Fish::show() {

    sprite_set_enabled(&sprite_, true);
}

void Fish::hide() {

    sprite_set_enabled(&sprite_, false);
}

void Fish::update() {
    
    int16_t dy = 0;
    switch ( game_info_.get_loop_count() % 3 ) {
    case 0:
        sprite_set_tile_idx(&sprite_, (vx_ >= 0) ? 1 : 4);
        dy = 0;
        break;
    case 1:
        sprite_set_tile_idx(&sprite_, (vx_ >= 0) ? 2 : 5);
        dy = 1;
        break;
    case 2:
        sprite_set_tile_idx(&sprite_, (vx_ >= 0) ? 3 : 6);
        dy = -1;
        break;
    default:
        break;
    }

    if ( vx_ > 0 ) {
        if ( (sprite_.x + vx_) > max_x_ ) {
            vx_ *= -1;
        }
    } else if ( vx_ < 0 ) {
        if ( (sprite_.x + vx_) < min_x_ ) {
            vx_ *= -1;
        }
    } else {
    }

    sprite_set_position(&sprite_, sprite_.x + vx_, height_ + dy);
}

const mgc_sprite *Fish::get_ptr_sprite() const {
    return &sprite_;
}

}

