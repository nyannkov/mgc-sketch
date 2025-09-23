#ifndef ACTOR_CHICK_HPP
#define ACTOR_CHICK_HPP

#include <cmath>
#include "common/dot_canvas_anim.hpp"

// Enumeration of the Chick actor's behavior states
enum class ActorChickBehaviorState {
    WalkLeft
};

// ActorChick class representing a chick in the scene
// Inherits from ActorImpl<ActorChick, 1>, where 1 is the number of hitboxes
struct ActorChick : mgc::entities::ActorImpl<ActorChick, 1> {

    // Constructor: initialize animation controller, position, and behavior state
    explicit ActorChick(const dot_canvas::FrameTimer& frame_timer) 
    : anim_(frame_timer),
      pos_f_({0.0f, 0.0f}),
      behavior_state_(ActorChickBehaviorState::WalkLeft) { }

    // Initialize actor state
    // - Set initial position and behavior state
    // - Setup animation frames and start animation
    // - Configure hitboxes
    void init();

    // Update the animation controller and apply the current frame to the sprite
    void update_anim();

    // Update actor behavior (state machine)
    // - Currently, only walking left
    void update_behavior();

private:
    dot_canvas::AnimController anim_;            // Controls sprite animation frames
    ActorChickBehaviorState behavior_state_;     // Current behavior state
    mgc::math::Vec2f pos_f_;                     // Floating-point position for smooth movement

    // Getter for the internal float position
    mgc::math::Vec2f pos_f() const {
        return pos_f_;
    }

    // Setter for internal position
    // - Updates sprite position for rendering
    // - Floors coordinates to integer before casting to int16_t
    void set_pos_f(const mgc::math::Vec2f& pos_f) {
        pos_f_ = pos_f;

        auto temp = pos_f_;
        temp.x = std::floor(temp.x);
        temp.y = std::floor(temp.y);

        this->sprite().set_position(temp.template cast_to<int16_t>());
    }
};

#endif // ACTOR_CHICK_HPP

