#include "common/dot_canvas_core.hpp"
#include "src/actor/actor_chick.hpp"
#include "src/actor/actor_hen.hpp"

#define PIN         A0
#define NUMPIXELS   60 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Frame buffer for the dot-matrix display (6x10)
dot_canvas::Color buffer[6*10];
dot_canvas::Framebuffer fb(buffer, 6, 10);

// Timer and stopwatch for controlling animation and behavior updates
dot_canvas::FrameTimer frame_timer;
dot_canvas::Stopwatch sw(frame_timer);

// Actor instances for the chick and hen
ActorChick chick(frame_timer);
ActorHen hen(frame_timer);

using mgc::collision::CollisionDetectorBoxToBox;

void setup() {

    pixels.begin();

    // Initialize actors
    chick.init();
    hen.init();

    // Reset frame timer and start stopwatch
    frame_timer.reset();
    sw.start();
}

void loop() {

    // Advance the frame timer
    frame_timer.tick();

    // Update behaviors at a fixed interval (100 ms)
    if (sw.elapsed_ms() > 100 ) {
        sw.restart();

        // Detect collision between hen and chick
        CollisionDetectorBoxToBox::detect(hen, chick);
        
        // Update behavior for each actor
        chick.update_behavior();
        hen.update_behavior();
    }

    // Update animation frames (can run every loop iteration)
    hen.update_anim();
    chick.update_anim();

     // Clear the frame buffer before drawing
    fb.clear();

    // Draw actors to the frame buffer
    hen.draw(fb);
    chick.draw(fb);

    // Flush the frame buffer to the dot-matrix display
    dot_canvas::write_dot_canvas(pixels, fb, 3);
}

