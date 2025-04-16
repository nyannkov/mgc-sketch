#include "animator_player.hpp"
#include "resources/generated/tileset/tileset_player.h"

namespace mgc {

enum anim_idx {
    idx_invisible = 0,
    idx_walk0_l = 1,
    idx_walk1_l = 2,
    idx_walk0_r = 3,
    idx_walk1_r = 4,
    idx_crouch_l = 5,
    idx_rising_l = 6,
    idx_falling_l = 7,
    idx_crouch_r = 8,
    idx_rising_r = 9,
    idx_falling_r = 10,
    idx_yawn_1_l = 11,
    idx_yawn_2_l = 12,
    idx_going_to_sleeping_l = 13,
    idx_sleeping_1_l = 14,
    idx_sleeping_2_l = 15,
    idx_yawn_1_r = 16,
    idx_yawn_2_r = 17,
    idx_going_to_sleeping_r = 18,
    idx_sleeping_1_r = 19,
    idx_sleeping_2_r = 20,
    idx_standing_1 = 21,
    idx_standing_2 = 22,
    idx_fist_pump = 23,
    idx_standing_3 = 24,
};

AnimatorPlayer::AnimatorPlayer(GameInfo &game_info) : game_info_(game_info) {
    type_ = AnimationType::Invisible;
    tile_idx_ = idx_invisible;
}

const mgc_tileset_t *AnimatorPlayer::get_ptr_tileset() const {
    return &tileset_player;
}

size_t AnimatorPlayer::get_tile_idx() const {
    if ( tile_idx_ >= tileset_player.tile_count ) {
        MGC_WARN("Out of tile_idx");
        return idx_invisible;
    }
    return tile_idx_;
}

void AnimatorPlayer::set_animation_type(AnimationType type) {
    type_ = type;
}

void AnimatorPlayer::set_direction(CharacterDirection dir) {
    direction_ = dir;
}

void AnimatorPlayer::update() {
    switch (type_) {
    case AnimationType::Invisible:
        tile_idx_ = idx_invisible;
        break;
    case AnimationType::Stop:
        tile_idx_ = (direction_ == CharacterDirection::Left) ? idx_walk0_l : idx_walk0_r;
        break;
    case AnimationType::Walk:
        if ( direction_ == CharacterDirection::Left ) {
            if ( tile_idx_ == idx_walk0_l ) {
                tile_idx_ = idx_walk1_l;
            } else {
                tile_idx_ = idx_walk0_l;
            }
        } else {
            if ( tile_idx_ == idx_walk0_r ) {
                tile_idx_ = idx_walk1_r;
            } else {
                tile_idx_ = idx_walk0_r;
            }
        }
        break;
    case AnimationType::Crouch:
        tile_idx_ = (direction_ == CharacterDirection::Left) ? idx_crouch_l : idx_crouch_r;
        break;
    case AnimationType::Rising:
        tile_idx_ = (direction_ == CharacterDirection::Left) ? idx_rising_l : idx_rising_r;
        break;
    case AnimationType::Falling:
        tile_idx_ = (direction_ == CharacterDirection::Left) ? idx_falling_l : idx_falling_r;
        break;
    case AnimationType::Yawn:
        if ( (game_info_.get_loop_count()&0x8) == 0 ) {
            tile_idx_ = (direction_ == CharacterDirection::Left) ? idx_yawn_1_l : idx_yawn_1_r;
        } else {
            tile_idx_ = (direction_ == CharacterDirection::Left) ? idx_yawn_2_l : idx_yawn_2_r;
        }
        break;
    case AnimationType::GoingToSleeping:
        tile_idx_ = (direction_ == CharacterDirection::Left) ? idx_going_to_sleeping_l : idx_going_to_sleeping_r;
        break;
    case AnimationType::Sleeping:
        if ( (game_info_.get_loop_count()&0x10) == 0 ) {
            tile_idx_ = (direction_ == CharacterDirection::Left) ? idx_sleeping_1_l : idx_sleeping_1_r;
        } else {
            tile_idx_ = (direction_ == CharacterDirection::Left) ? idx_sleeping_2_l : idx_sleeping_2_r;
        }
        break;
    case AnimationType::Standing1:
        tile_idx_ = idx_standing_1;
        break;
    case AnimationType::Standing2:
        tile_idx_ = idx_standing_2;
        break;
    case AnimationType::Standing3:
        tile_idx_ = idx_standing_3;
        break;
    case AnimationType::FistPump:
        tile_idx_ = idx_fist_pump;
        break;
    default:
        MGC_WARN("Invalid AnimationType");
        tile_idx_ = idx_invisible;
        break;
    }
}

}
