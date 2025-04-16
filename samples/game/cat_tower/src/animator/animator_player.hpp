#ifndef MGC_ANIMATOR_PLAYER_HPP
#define MGC_ANIMATOR_PLAYER_HPP

#include "mgc/mgc.h"
#include "game_info/game_info.hpp"

namespace mgc {

enum class AnimationType {
    Invisible,
    Stop,
    Walk,
    Crouch,
    Rising,
    Falling,
    Yawn,
    GoingToSleeping,
    Sleeping,
    Standing1,
    Standing2,
    Standing3,
    FistPump,
};

enum class CharacterDirection {
    Left,
    Right,
};

struct AnimatorPlayer {
    AnimatorPlayer(GameInfo &game_info);
    const mgc_tileset_t *get_ptr_tileset() const;
    size_t get_tile_idx() const;
    void set_animation_type(AnimationType type);
    void set_direction(CharacterDirection dir);
    void update();
private:
    GameInfo &game_info_;
    AnimationType type_;
    CharacterDirection direction_;
    size_t tile_idx_;
};

}
#endif/*MGC_ANIMATOR_PLAYER_HPP*/
