#include "actor_chick.hpp"
#include "gen/anim_chick/anim_chick.h"

void ActorChick::init() {

    this->set_pos_f({18.0f, 0.0f});
    behavior_state_ = ActorChickBehaviorState::WalkLeft;
    anim_.set_anim_frames(anim_chick_walk_left);
    anim_.set_loop(true);
    anim_.start_animation();
    anim_.set_current_frame(this->sprite());

    auto& hitboxes = this->hitboxes();
    hitboxes[0].offset = mgc::collision::HitboxOffset(0, 0);
    hitboxes[0].size = mgc::collision::HitboxSize(6, 10);
    hitboxes[0].enabled = true;
}

void ActorChick::update_anim() {
    anim_.proc();
    anim_.set_current_frame(this->sprite());
}

void ActorChick::update_behavior() {
    auto pos = this->pos_f();
    if ( pos.x >= -12.0f ) {
        pos -= { 0.2f, 0.0f };
        this->set_pos_f(pos);
    }
}
