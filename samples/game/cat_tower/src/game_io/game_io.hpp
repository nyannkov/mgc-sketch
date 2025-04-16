#ifndef MGC_GAME_IO_HPP
#define MGC_GAME_IO_HPP

#include "game_io_config.hpp"

namespace mgc {

struct GameIO {
    GameIO(const mgc_display_if_t &display_handler, const mgc_sound_mml_if_t &sound_handler, const mgc_gamepad_if_t &gamepad_handler)
        : display(display_handler), sound(sound_handler), gamepad(gamepad_handler) {}

    void initialize() {
        display.init();
        sound.init();
        gamepad.init();
    }
    const mgc_display_if_t &display;
    const mgc_sound_mml_if_t &sound;
    const mgc_gamepad_if_t &gamepad;
};

}

#endif/*MGC_GAME_IO_HPP*/

