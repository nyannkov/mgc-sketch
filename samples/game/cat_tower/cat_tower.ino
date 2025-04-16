#include "mgc/mgc.h"
#include "game_io/game_io.hpp"
#include "scene/scene.hpp"
#include "resources/mml/mml_list.h"
#include "resources/text/text_database.hpp"

namespace {

mgc::GameInfo game_info;

mgc::GameIO game_io(
    display_SSD1331_handler,
    sound_mml_psg,
    gamepad_tiny
);

uint16_t display_width;
uint16_t display_height;
std::unique_ptr<mgc::SceneIf> scene;

uint32_t mml_cb_data;
void mml_callback(uint8_t ch, int32_t param) {
    mml_cb_data = param;
}

}

void setup() {

    game_info.initialize();

    game_io.initialize();

    game_io.sound.set_BGM_table(mml_bgm_list, MML_BGM_LIST_COUNT);
    game_io.sound.set_SE_table(mml_se_list, MML_SE_LIST_COUNT);

    mml_cb_data = 0;
    sound_mml_psg__set_BGM_callback(mml_callback);

    display_width = game_io.display.get_width();
    display_height = game_io.display.get_height();

    mgc::textdb::set_language(mgc::textdb::Language::English);
    //mgc::textdb::set_language(mgc::textdb::Language::Japanese);

    scene = mgc::make_scene(mgc::SceneId::ID_001, game_io, game_info);

    if ( scene ) {
        scene->initialize(mgc::SceneId::ID_000);
    }
}

void loop() {

    game_io.gamepad.proc();
    
    game_info.update_countdown();

    game_info.increment_loop_count();

    noInterrupts();
    game_info.set_mml_cb_value(mml_cb_data);
    interrupts();
    
    game_info.update_main_state();

    mgc::update_scene_state();

    if ( scene ) {
        scene->update();
        scene->draw(0, 0, display_width, display_height);
#ifdef MGC_SSD1331_USE_FRAME_BUFFER
        display_SSD1331_transfer_frame();
#endif
        if ( scene->check_trans() ) {
            mgc::SceneId id_prev = scene->get_id();
            mgc::SceneId id_next = scene->get_id_next();

            scene.reset();
            scene = make_scene(id_next, game_io, game_info);
            if ( scene ) {
                scene->initialize(id_prev);
            }
        }
    }
}

