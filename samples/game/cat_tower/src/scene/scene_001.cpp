#include "scene_001.hpp"
#include "resources/generated/tileset/tileset_map_elements.h"
#include "resources/generated/tileset/tileset_player.h"
#include "resources/generated/tileset/tileset_title.h"
#include "resources/mml/mml_list.h"
#include "resources/text/text_database.hpp"

namespace mgc {

void Scene001::initialize(SceneId id_prev) {
    id_next_ = SceneId::ID_001;
    id_prev_ = id_prev;
    scene_trans_ = false;
    is_score_shown_ = false;
    set_scene_state(SceneState::Shown);

    init_components();
}

SceneId Scene001::get_id() const {
    return SceneId::ID_001;
}

SceneId Scene001::get_id_next() const {
    return id_next_;
}

bool Scene001::check_trans() const {
    return scene_trans_;
}

void Scene001::update() {

    SceneState scene_state = get_scene_state();

    if ( scene_state == SceneState::Shown ) {
        if ( !selectbox_menu_.visible ) {

            if ( game_io_.gamepad.is_key_on_edge(GAMEPAD_TINY_KEY_2) ) {
                selectbox_set_visible(&selectbox_menu_, true);
            }

        } else {

            if ( !is_score_shown_ ) {

                if ( game_io_.gamepad.is_key_on_edge(GAMEPAD_TINY_KEY_0) ) {
                    selectbox_change_selected_idx(&selectbox_menu_, false);

                } else if ( game_io_.gamepad.is_key_on_edge(GAMEPAD_TINY_KEY_1) ) {
                    selectbox_change_selected_idx(&selectbox_menu_, true);

                } else if ( game_io_.gamepad.is_key_on_edge(GAMEPAD_TINY_KEY_2) ) {
                    switch ( selectbox_menu_.selected_idx ) {
                    case 0:
                        id_next_ = SceneId::ID_002;
                        game_io_.sound.play_SE(MML_SE_0);
                        set_scene_state(SceneState::WaitClose);
                        break;
                    case 1:
                        is_score_shown_ = true;
                        dialoguebox_set_text(&dialoguebox_, game_info_.get_str_score_text());
                        dialoguebox_set_enabled(&dialoguebox_, true);
                        break;

                    default:
                        break;
                    }
                } else {
                }
            } else {
                if ( game_io_.gamepad.is_key_on_edge(GAMEPAD_TINY_KEY_2) ) {
                    is_score_shown_ = false;
                    dialoguebox_set_enabled(&dialoguebox_, false);
                }
                dialoguebox_display_update(&dialoguebox_);
            }
        }
    } else if ( scene_state == SceneState::WaitClose ) {
        if ( game_io_.sound.is_SE_done() ) {
            set_scene_state(SceneState::Closing);
        }
    } else if ( scene_state == SceneState::Closed ) {
        scene_trans_ = true;
    } else {
    }
}

void Scene001::draw(uint16_t screen_x0, uint16_t screen_y0, uint16_t width, uint16_t height) {
    for ( int16_t y = 0; y < height; y += MGC_CELL2PIXEL(1)) {
        for ( int16_t x = 0; x < width; x += MGC_CELL2PIXEL(1)) {

            sprite_apply_cell_blending(&sprite_title_, &pixelbuffer_, x, y);
            selectbox_apply_cell_blending(&selectbox_menu_, &pixelbuffer_, x, y);
            dialoguebox_apply_cell_blending(&dialoguebox_, &pixelbuffer_, x, y);

            filter_scene_cell(&pixelbuffer_, MGC_COLOR_BLACK);
            pixelbuffer_draw_cell(&pixelbuffer_, &game_io_.display, screen_x0+x, screen_y0+y);
        }
    }
}

void Scene001::init_components() {
    // pixelbuffer
    pixelbuffer_init(&pixelbuffer_);

    // sprite_title_
    sprite_init(&sprite_title_, 0);
    sprite_set_tileset(&sprite_title_, &tileset_title);
    sprite_set_tile_idx(&sprite_title_, 0);
    sprite_set_r_cell_offset(&sprite_title_, 0, 0);
    sprite_set_position(&sprite_title_, MGC_CELL2PIXEL(2), MGC_CELL2PIXEL(0));
    sprite_set_enabled(&sprite_title_, true);

    // selectbox_menu_
    selectbox_init(&selectbox_menu_, 0, textdb::get_font(), false);
    selectbox_append_item(&selectbox_menu_, "START");
    selectbox_append_item(&selectbox_menu_, "SCORE");
    selectbox_set_width(&selectbox_menu_, 4*11);
    selectbox_set_position(&selectbox_menu_, MGC_CELL2PIXEL(2), MGC_CELL2PIXEL(2));
    selectbox_set_enabled(&selectbox_menu_, false);

    // dialoguebox_score_
    dialoguebox_init(&dialoguebox_, 0, textdb::get_font(), false);
    dialoguebox_set_position(&dialoguebox_, MGC_CELL2PIXEL(1)/2, MGC_CELL2PIXEL(1)/2);
    dialoguebox_set_width(&dialoguebox_, MGC_CELL2PIXEL(5));
    dialoguebox_set_height(&dialoguebox_, 8*6);
    dialoguebox_set_cursor_speed(&dialoguebox_, 8);
    dialoguebox_set_scroll_speed(&dialoguebox_, 8);
    dialoguebox_set_scroll_line(&dialoguebox_, 6);
    dialoguebox_set_line_spacing(&dialoguebox_, 0);
    dialoguebox_set_text(&dialoguebox_, game_info_.get_str_score_text());
    dialoguebox_set_r_cell_offset(&dialoguebox_, 0, 0);
    dialoguebox_set_enabled(&dialoguebox_, false);
    
}

}
