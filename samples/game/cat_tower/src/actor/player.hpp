#ifndef MGC_PLAYER_HPP
#define MGC_PLAYER_HPP

#include "mgc/mgc.h"
#include "mgc/utils/jumpctrl/jumpctrl.h"
#include "actor_if.hpp"
#include "animator/animator_player.hpp"
#include "game_io/game_io.hpp"
#include "game_info/game_info.hpp"

namespace mgc {

struct Player : ActorIf {
    Player(GameIO &game_io, GameInfo &game_info) : game_io_(game_io), game_info_(game_info), animator_(game_info){}
    void init(mgc_id_t id, int16_t x, int16_t y) override;
    void update() override;
    const mgc_sprite *get_ptr_sprite() const override;
    void on_hit_tilemap(const mgc_hitbox &hitbox, int16_t map_x, int16_t map_y) override;
    void set_animation(AnimationType type, CharacterDirection dir);
    void update_animation();
    bool gameover();
    bool victory();
    const mgc_sprite *get_ptr_sprite_item() const;
private:
    GameIO &game_io_;
    GameInfo &game_info_;
    int16_t mark_x_;
    int16_t mark_y_;
    int8_t vx_;
    int8_t vy_;
    bool foot_hit_;
    mgc_sprite sprite_;
    mgc_sprite sprite_item_;
    enum hitbox_id {
        HITBOX_ID_BODY = 0,
        HITBOX_ID_HEAD,
        HITBOX_ID_FOOT,
        NUM_OF_HITBOX_ID
    };
    mgc_hitbox hitbox_array_[NUM_OF_HITBOX_ID];
    mgc_jumpctrl jumpctrl_;
    AnimatorPlayer animator_;
    void set_position(int16_t x, int16_t y);
    void mark_current_position();
    void jump_proc(bool jump_button_pressed);
};

}
#endif/*MGC_PLAYER_HPP*/
