#include "common/dot_canvas_core.hpp"
#include "gen/tileset_chick.h"
#include "gen/tileset_hen.h"

#define PIN         A0
#define NUMPIXELS   60 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Frame buffer for the dot-matrix display (6x10)
dot_canvas::Color buffer[6*10];
dot_canvas::Framebuffer fb(buffer, 6, 10);

// Sprite used for tile rendering
mgc::parts::BasicSprite sprite;

void setup() {

    pixels.begin();

    // Register the tileset to be rendered
    //sprite.set_tileset(tileset_hen);
    sprite.set_tileset(tileset_chick);

    // Set the tile index to render
    sprite.set_tile_index(0);

    // Set the sprite position (top-left of the tile, in a Y-down coordinate system)
    sprite.set_position({0, 0});
}

void loop() {

    static size_t i = 0;

     // Clear the frame buffer before drawing
    fb.clear();

    // Update the tile index to change the rendered tile
    sprite.set_tile_index(i++%2);

    // Draw the sprite to the frame buffer
    sprite.draw(fb);

    // Flush the frame buffer to the dot-matrix display
    dot_canvas::write_dot_canvas(pixels, fb);

    // Delay between animation frames
    delay(100);
}

