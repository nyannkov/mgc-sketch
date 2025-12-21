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
};

#endif // ACTOR_CHICK_HPP

