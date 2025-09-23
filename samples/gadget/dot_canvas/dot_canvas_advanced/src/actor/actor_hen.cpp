#include <cmath>
#include "actor_hen.hpp"
#include "gen/anim_hen/anim_hen.h"

void ActorHen::init() {
    this->set_pos_f({8.0f, 0.0f});
    behavior_state_ = ActorHenBehaviorState::WalkLeft_1;
    anim_.set_anim_frames(anim_hen_walk_left);
    anim_.set_loop(true);
    anim_.start_animation();
    anim_.set_current_frame(this->sprite());

    auto& hitboxes = this->hitboxes();
    hitboxes[0].offset = mgc::collision::HitboxOffset(0, 0);
    hitboxes[0].size = mgc::collision::HitboxSize(4, 10);
    hitboxes[0].enabled = true;

    is_hit_ = false;
}

void ActorHen::update_anim() {
    anim_.proc();
    anim_.set_current_frame(this->sprite());
}

void ActorHen::update_behavior() {
    
    auto pos = this->pos_f();
    auto next_state = behavior_state_;

    switch ( next_state ) {
    case ActorHenBehaviorState::WalkLeft_1:
        if ( pos.x < -10.f ) {
            next_state = ActorHenBehaviorState::WalkRight;
            anim_.set_anim_frames(anim_hen_walk_right);
        }
        break;

    case ActorHenBehaviorState::WalkRight:
        if ( pos.x >= -2.0f ) {
            next_state = ActorHenBehaviorState::StandRight;
            anim_.set_anim_frames(anim_hen_stand_right);
        }
        break;

    case ActorHenBehaviorState::StandRight:
        if ( is_hit_ ) {
            next_state = ActorHenBehaviorState::WalkLeft_2;
            anim_.set_anim_frames(anim_hen_walk_left);
        }
        break;

    default:
        break;
    }

    if ( behavior_state_ != next_state ) {
        behavior_state_ = next_state;
        anim_.set_loop(true);
        anim_.start_animation();
    }

    switch ( next_state ) {
    case ActorHenBehaviorState::WalkLeft_1:
        pos.x -= 0.5f;
        break;

    case ActorHenBehaviorState::WalkRight:
        pos.x += 0.5f;
        break;

    case ActorHenBehaviorState::StandRight:
        break;

    case ActorHenBehaviorState::WalkLeft_2:
        pos.x -= 0.2f;
        break;

    default:
        break;
    }

    this->set_pos_f(pos);
}

