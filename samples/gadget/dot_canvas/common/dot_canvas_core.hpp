#ifndef DOT_CANVAS_CORE_H
#define DOT_CANVAS_CORE_H

#include <Adafruit_NeoPixel.h>
#include "mgc_cpp/mgc.hpp"

namespace dot_canvas {

using Framebuffer = mgc::graphics::Framebuffer;
using Color = mgc::graphics::Color;

void write_dot_canvas(
    Adafruit_NeoPixel& pixels,
    const Framebuffer& fb,
    uint8_t brightness = 5
) {
    const Color* data = fb.data();
    uint16_t canvas_width = fb.width();
    uint16_t canvas_height = fb.height();

    if ( !data ) return;

    pixels.setBrightness(brightness);

    for ( size_t i = 0; i < canvas_width; ++i ) {
        for ( size_t j = 0; j < canvas_height; ++j ) {
            size_t index = i + canvas_width * j;
            auto color = MGC_COLOR_SWAP(data[index]);
            // Although RGB888 configuration is normally possible, MGC currently supports
            // only RGB565, which is why this conversion is required. Future support for
            // RGB888 is planned.
            uint8_t r = 255 * (float)((color >> 11) & 0x1F)/0x1F;
            uint8_t g = 255 * (float)((color >>  5) & 0x3F)/0x3F;
            uint8_t b = 255 * (float)((color >>  0) & 0x1F)/0x1F;
            pixels.setPixelColor(index, pixels.Color(r, g, b));
        }
    }
    pixels.show();
}

} // namespace dot_canvas

#endif // DOT_CANVAS_CORE_H

