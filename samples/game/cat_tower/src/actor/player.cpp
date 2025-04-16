#include "player.hpp"
#include "resources/generated/tileset/tileset_items.h"

namespace mgc {

void Player::init(mgc_id_t id, int16_t x, int16_t y) {
    hitbox_init(&hitbox_array_[HITBOX_ID_BODY], HITBOX_ID_BODY, 2,  2, 12, 12);
    hitbox_init(&hitbox_array_[HITBOX_ID_HEAD], HITBOX_ID_HEAD, 2,  0, 12,  1);
    hitbox_init(&hitbox_array_[HITBOX_ID_FOOT], HITBOX_ID_FOOT, 2, 15, 12,  1);
    sprite_init(&sprite_, id);
    sprite_set_position(&sprite_, x, y);
    sprite_set_hitbox_array(&sprite_, hitbox_array_, NUM_OF_HITBOX_ID);
    sprite_set_tileset(&sprite_, animator_.get_ptr_tileset());
    sprite_set_tile_idx(&sprite_, 0);
    sprite_set_enabled(&sprite_, true);

    sprite_init(&sprite_item_, 0);
    sprite_set_tileset(&sprite_item_, &tileset_items);
    sprite_set_tile_idx(&sprite_item_, 0);
    sprite_set_enabled(&sprite_item_, true);

    jumpctrl_init(&jumpctrl_);

    mark_x_ = sprite_.x;
    mark_y_ = sprite_.y;
    vx_ = 0;
    vy_ = 0;
    foot_hit_ = false;
}

void Player::update() {
    bool key_0_state = game_io_.gamepad.get_key_state(GAMEPAD_TINY_KEY_0); // key left
    bool key_1_state = game_io_.gamepad.get_key_state(GAMEPAD_TINY_KEY_1); // key right
    bool key_2_state = game_io_.gamepad.get_key_state(GAMEPAD_TINY_KEY_2);
    
    if ( key_0_state ) {
        vx_ = -4;
    } else if ( key_1_state ) {
        vx_ = 4;
    } else {
        vx_ = 0;
    }

    jump_proc(key_2_state);

}

bool Player::gameover() {

    bool r = false;

    vx_ = 0;

    jump_proc(false);

    switch (game_info_.get_mml_cb_value()) {
    case 0x21:
        animator_.set_animation_type(AnimationType::Yawn);
        break;
    case 0x22:
        animator_.set_animation_type(AnimationType::GoingToSleeping);
        break;
    case 0x23:
        animator_.set_animation_type(AnimationType::Sleeping);
        break;
    case 0x24:
        r = true;
        break;
    default:
        break;
    }

    animator_.update();
    sprite_set_tile_idx(&sprite_, animator_.get_tile_idx());

    return r;
}

bool Player::victory() {

    bool r = false;

    vx_ = 0;

    jump_proc(false);

    switch (game_info_.get_mml_cb_value()) {
    case 0x30:
    case 0x31:
        animator_.set_animation_type(AnimationType::Standing2);
        break;
    case 0x32:
        animator_.set_animation_type(AnimationType::Standing1);
        break;
    case 0x33:
        animator_.set_animation_type(AnimationType::FistPump);
        sprite_set_tile_idx(&sprite_item_, 1);
        sprite_set_position(&sprite_item_, sprite_.x+9, sprite_.y-14);
        break;
    case 0x34:
        r = true;
        break;
    default:
        break;
    }
    animator_.update();
    sprite_set_tile_idx(&sprite_, animator_.get_tile_idx());

    return r;
}


void Player::set_animation(AnimationType type, CharacterDirection dir) {
    animator_.set_animation_type(type);
    animator_.set_direction(dir);
    animator_.update();
    sprite_set_tile_idx(&sprite_, animator_.get_tile_idx());
}

void Player::update_animation() {
    if ( vx_ < 0 ) {
        animator_.set_direction(CharacterDirection::Left);
    } else if ( vx_ > 0 ) {
        animator_.set_direction(CharacterDirection::Right);
    } else {
        // No changed.
    }

    if ( foot_hit_ ) {
        if ( vx_ == 0 ) {
            animator_.set_animation_type(AnimationType::Stop);
        } else {
            animator_.set_animation_type(AnimationType::Walk);
        }
    } else {
        if ( vy_ > 0 ) {
            animator_.set_animation_type(AnimationType::Falling);
        } else if ( vy_ < 0 ) {
            animator_.set_animation_type(AnimationType::Rising);
        } else {
            // No changed.
        }
    }

    animator_.update();
    sprite_set_tile_idx(&sprite_, animator_.get_tile_idx());
}

void Player::set_position(int16_t x, int16_t y) {
    sprite_set_position(&sprite_, x, y);
}

void Player::mark_current_position() {
    mark_x_ = sprite_.x;
    mark_y_ = sprite_.y;
}

void Player::jump_proc(bool jump_button_pressed) {
    mark_current_position();
    jumpctrl_update_jump_state(&jumpctrl_, jump_button_pressed, foot_hit_);
    foot_hit_ = false;
    if ( jumpctrl_get_jump_state(&jumpctrl_) == MGC_JUMP_STATE_FLOATING ) {
        vy_ = -10;
    } else {
        vy_++;
        if ( vy_ > 14 ) {
            vy_ = 14;
        } else if ( vy_ < -14 ) {
            vy_ = -14;
        } else {
        }
    }
    set_position(sprite_.x + vx_, sprite_.y + vy_);
}

const mgc_sprite *Player::get_ptr_sprite() const {
    return &sprite_;
}

const mgc_sprite *Player::get_ptr_sprite_item() const {
    return &sprite_item_;
}

void Player::on_hit_tilemap(const mgc_hitbox &hitbox, int16_t map_x, int16_t map_y) {
    int16_t temp_x, temp_y;
    int16_t prev_x, prev_y;

    temp_x = sprite_.x + hitbox.x0_ofs;
    temp_y = sprite_.y + hitbox.y0_ofs;
    prev_x = mark_x_ + hitbox.x0_ofs;
    prev_y = mark_y_ + hitbox.y0_ofs;

    switch (hitbox.id) {
    case HITBOX_ID_BODY:
        if ( ( (prev_y + hitbox.height) > map_y ) && ( prev_y < (map_y + MGC_CELL_LEN) ) ||
             ( (map_y <= temp_y) && ((temp_y + hitbox.height) <= (map_y + MGC_CELL_LEN)) )
        ) {
            if ( vx_ > 0 ) {
                temp_x = map_x - hitbox.width;
            } else if ( vx_ < 0 ) {
                temp_x = map_x + MGC_CELL_LEN;
            } else {
            }
            vx_ = 0;
        }
        break;

    case HITBOX_ID_HEAD:
        if ( vy_ < 0 ) {
            temp_y = map_y + MGC_CELL_LEN;
            vy_ = 0;
        }
        break;

    case HITBOX_ID_FOOT:
        if ( vy_ > 0 ) {
            temp_y = map_y - hitbox.height;
            vy_ = 0;
        }
        foot_hit_ = true;
        break;

    default:
        MGC_WARN("Unexpected hitbox id");
        break;
    }

    set_position(temp_x - hitbox.x0_ofs, temp_y - hitbox.y0_ofs);
}

}

