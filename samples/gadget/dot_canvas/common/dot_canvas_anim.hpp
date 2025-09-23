#ifndef DOT_CANVAS_ANIM_H
#define DOT_CANVAS_ANIM_H

#include <Arduino.h>
#include "mgc_cpp/mgc.hpp"

namespace dot_canvas {

struct TimerArduino : mgc::platform::timer::Timer<TimerArduino, unsigned long> {
    static timestamp_t now_ms_impl() {
        return millis();
    }
};

using FrameTimer = mgc::platform::timer::FrameTimer<TimerArduino>;
using AnimController = mgc::control::anim::AnimController<FrameTimer>;
using Stopwatch = mgc::utils::Stopwatch<FrameTimer>;

} // namespace dot_canvas

#endif // DOT_CANVAS_ANIM_H

