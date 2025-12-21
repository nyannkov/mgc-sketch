#ifndef ACTOR_CHICKEN_HPP
#define ACTOR_CHICKEN_HPP

#include "common/dot_canvas_anim.hpp"

// Enumeration of the Hen actor's behavior states
enum class ActorHenBehaviorState {
    WalkLeft_1,
    WalkRight,
    StandRight,
    WalkLeft_2,
};

// Forward declaration of ActorChick
struct ActorChick;

// ActorHen class representing a hen in the scene
// Inherits from ActorImpl<ActorHen, 1>, where 1 is the number of hitboxes
struct ActorHen : mgc::entities::ActorImpl<ActorHen, 1> {

    // Constructor: initialize animation controller, behavior state, position, and hit flag
    explicit ActorHen(const dot_canvas::FrameTimer& frame_timer) 
    : anim_(frame_timer),
      behavior_state_(ActorHenBehaviorState::WalkLeft_1),
      is_hit_(false) { }

    // Initialize actor state
    // - Set initial position and behavior state
    // - Setup animation frames and start animation
    // - Configure hitboxes
    void init();

    // Update the animation controller and apply the current frame to the sprite
    void update_anim();

    // Update actor behavior (state machine)
    // - Changes behavior state based on position and collision (is_hit_)
    // - Adjusts position according to behavior
    void update_behavior();

    // Collision handler for box-to-box collisions
    // If colliding with ActorChick, mark as hit
    template <typename Other>
    void on_hit_box_to_box_impl(
            const Other& other,
            const mgc::collision::BoxCollisionInfo& info
    ) { 
        if constexpr (std::is_same_v<Other, ActorChick>) {
            is_hit_ = true;
        }
    }

private:
    dot_canvas::AnimController anim_;       // Controls sprite animation frames
    ActorHenBehaviorState behavior_state_;  // Current behavior state
    bool is_hit_;                           // Flag set when hit by a chick
};

#endif // ACTOR_CHICKEN_HPP

