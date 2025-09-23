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
      pos_f_({0.0f, 0.0f}),
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
    mgc::math::Vec2f pos_f_;                // Floating-point position for smooth movement
    bool is_hit_;                           // Flag set when hit by a chick

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

#endif // ACTOR_CHICKEN_HPP

