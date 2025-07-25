#include "scene_002.hpp"
#include "resources/generated/tileset/tileset_map_elements.h"
#include "resources/generated/tileset/tileset_static_objects.h"
#include "resources/generated/tileset/tileset_char.h"
#include "resources/generated/map/map_scene_002.h"
#include "resources/generated/map/map_scene_002_bg.h"
#include "resources/mml/mml_list.h"
#include "resources/text/text_database.hpp"

namespace mgc {

void Scene002::initialize(SceneId id_prev) {
    id_next_ = SceneId::ID_002;
    id_prev_ = id_prev;
    scene_trans_ = false;

    set_scene_state(SceneState::Showing);

    init_components();

    if ( id_prev != SceneId::ID_003 ) {
        if ( game_info_.get_main_state() == MainState::Tutorial ) {
            game_io_.sound.play_BGM(MML_BGM_0);
            tutorial_state_ = TutorialState::ID_000;
            dialoguebox_set_enabled(&dialoguebox_, true);
        } else {
            game_io_.sound.play_BGM(MML_BGM_1);
            tutorial_state_ = TutorialState::ID_999;
            dialoguebox_set_enabled(&dialoguebox_, false);
            sprite_set_tile_idx(&text_ready_go_, 1);
        }
    } else {
        tutorial_state_ = TutorialState::ID_999;
        dialoguebox_set_enabled(&dialoguebox_, false);
        sprite_set_tile_idx(&text_ready_go_, 0);
    }
    camera_update(&pixelbuffer_, &camera_, player_.get_ptr_sprite());
}

SceneId Scene002::get_id() const {
    return SceneId::ID_002;
}

SceneId Scene002::get_id_next() const {
    return id_next_;
}

bool Scene002::check_trans() const {
    return scene_trans_;
}

void Scene002::update() {

    SceneState scene_state = get_scene_state();

    if ( scene_state == SceneState::Shown ) {
        switch ( game_info_.get_main_state() ) {
        case MainState::Tutorial:
            if ( show_tutorial() ) {
                game_info_.set_tutorial_finished();
            }
            break;

        case MainState::ReadyGo:
            if ( show_ready_go() ) {
                game_info_.set_play_start();
            }
            break;

        case MainState::Playing:
            player_.update();
            check_hit_tilemap(&player_, maphit_, tilemap_);
            if ( check_hit_sprite(&player_, sprhit_, *gate_2_.get_ptr_sprite()) ) {
                id_next_ = SceneId::ID_003;
                set_scene_state(SceneState::Closing);
            }
            camera_update(&pixelbuffer_, &camera_, player_.get_ptr_sprite());
            player_.update_animation();
            break;

        case MainState::GameOver:
            check_hit_tilemap(&player_, maphit_, tilemap_);
            camera_update(&pixelbuffer_, &camera_, player_.get_ptr_sprite());
            if ( player_.gameover() ) {
                id_next_ = SceneId::ID_999;
                set_scene_state(SceneState::Closing);
            }
            break;
        }
    } else if ( scene_state == SceneState::Closed ) {
        scene_trans_ = true;
    } else {
    }
}

void Scene002::cell_draw_and_transfer(uint16_t screen_x0, uint16_t screen_y0, uint16_t width, uint16_t height) {
    for ( int16_t y = 0; y < height; y += MGC_CELL2PIXEL(1)) {
        for ( int16_t x = 0; x < width; x += MGC_CELL2PIXEL(1)) {
            tilemap_apply_cell_blending(&tilemap_bg_, &pixelbuffer_, x, y);
            tilemap_apply_cell_blending(&tilemap_, &pixelbuffer_, x, y);
            sprite_apply_cell_blending(gate_1_.get_ptr_sprite(), &pixelbuffer_, x, y);
            sprite_apply_cell_blending(gate_2_.get_ptr_sprite(), &pixelbuffer_, x, y);
            sprite_apply_cell_blending(player_.get_ptr_sprite(), &pixelbuffer_, x, y);
            sprite_apply_cell_blending(&text_ready_go_, &pixelbuffer_, x, y);
            label_apply_cell_blending(game_info_.get_ptr_label_countdown(), &pixelbuffer_, x, y);
            dialoguebox_apply_cell_blending(&dialoguebox_, &pixelbuffer_, x, y);
            selectbox_apply_cell_blending(&selectbox_, &pixelbuffer_, x, y);

            filter_scene_cell(&pixelbuffer_, MGC_COLOR_BLACK);
            pixelbuffer_draw_cell(&pixelbuffer_, &game_io_.display, screen_x0+x, screen_y0+y);
        }
    }
}

void Scene002::draw(mgc_framebuffer_t& fb) {

    mgc_point_t camera_pos;
    camera_get_position(&camera_, &camera_pos);

    framebuffer_clear(&fb, MGC_COLOR(0.0, 1.0, 1.0));

    tilemap_draw(&tilemap_bg_, &fb, &camera_pos, nullptr);
    tilemap_draw(&tilemap_, &fb, &camera_pos, nullptr);
    sprite_draw(gate_1_.get_ptr_sprite(), &fb, &camera_pos, nullptr);
    sprite_draw(gate_2_.get_ptr_sprite(), &fb, &camera_pos, nullptr);
    sprite_draw(player_.get_ptr_sprite(), &fb, &camera_pos, nullptr);
    sprite_draw(&text_ready_go_, &fb, &camera_pos, nullptr);
    label_draw(game_info_.get_ptr_label_countdown(), &fb, &camera_pos, nullptr);
    dialoguebox_draw(&dialoguebox_, &fb, &camera_pos, nullptr);
    selectbox_draw(&selectbox_, &fb, &camera_pos, nullptr);

    filter_scene(&fb, MGC_COLOR_BLACK);
}

void Scene002::init_components() {

    // pixelbuffer
    pixelbuffer_init(&pixelbuffer_);
    pixelbuffer_set_back_color(&pixelbuffer_, MGC_COLOR(0.0, 1.0, 1.0));

    // maphit
    maphit_init(&maphit_);

    // sprhit
    sprhit_init(&sprhit_);

    // gate_1
    gate_1_.init(0, MGC_CELL2PIXEL(1), MGC_CELL2PIXEL(38));
    gate_1_.init_hitbox(0, 2, 2, 12, 12);
    gate_1_.set_tileset(tileset_static_objects);
    gate_1_.set_tile_idx(4);

    // gate_2
    gate_2_.init(1, MGC_CELL2PIXEL(1), MGC_CELL2PIXEL(2));
    gate_2_.init_hitbox(0, 2, 2, 12, 12);
    gate_2_.set_tileset(tileset_static_objects);
    gate_2_.set_tile_idx(3);

    // text_ready_go
    sprite_init(&text_ready_go_, 0);
    sprite_set_tileset(&text_ready_go_, &tileset_char);
    sprite_set_tile_idx(&text_ready_go_, 0);
    sprite_set_r_cell_offset(&text_ready_go_, 0, 0);
    sprite_set_position(&text_ready_go_, MGC_CELL2PIXEL(2), MGC_CELL2PIXEL(0));

    // tilemap
    tilemap_init(&tilemap_, 1, &map_scene_002, &tileset_map_elements);
    tilemap_set_position(&tilemap_, MGC_CELL2PIXEL(0), MGC_CELL2PIXEL(0));
    tilemap_set_r_cell_offset(&tilemap_, 1, 1);
    tilemap_set_enabled(&tilemap_, true);

    // tilemap (background)
    tilemap_init(&tilemap_bg_, 1, &map_scene_002_bg, &tileset_map_elements);
    tilemap_set_position(&tilemap_bg_, MGC_CELL2PIXEL(-2), MGC_CELL2PIXEL(5));
    tilemap_set_r_cell_offset(&tilemap_bg_, 8, 8);
    tilemap_set_enabled(&tilemap_bg_, true);

    // Initialize the dialoguebox.
    dialoguebox_init(&dialoguebox_, 0, textdb::get_font(), false);
    dialoguebox_set_position(&dialoguebox_, 2, 2);
    dialoguebox_set_width(&dialoguebox_, 92);
    dialoguebox_set_height(&dialoguebox_, 8*2);
    dialoguebox_set_cursor_speed(&dialoguebox_, 2);
    dialoguebox_set_scroll_speed(&dialoguebox_, 2);
    dialoguebox_set_scroll_line(&dialoguebox_, 2);
    dialoguebox_set_line_spacing(&dialoguebox_, 4);
    dialoguebox_adjust_height(&dialoguebox_);
    dialoguebox_set_text(&dialoguebox_, "");
    dialoguebox_set_r_cell_offset(&dialoguebox_, 0, 0);
    dialoguebox_set_enabled(&dialoguebox_, false);

    // Initialize the selectbox.
    selectbox_init(&selectbox_, 0, textdb::get_font(), false);
    selectbox_append_item(&selectbox_, textdb::get_text_by_id(textdb::TextId::Id_000_Yes));
    selectbox_append_item(&selectbox_, textdb::get_text_by_id(textdb::TextId::Id_001_No));
    selectbox_set_width(&selectbox_, 4*11);
    selectbox_set_position(&selectbox_, MGC_CELL2PIXEL(3), MGC_CELL2PIXEL(2));
    selectbox_set_r_cell_offset(&selectbox_, 0, 0);
    selectbox_set_enabled(&selectbox_, false);

    // player
    if ( id_prev_ == SceneId::ID_003 ) {
        player_.init(0, MGC_CELL2PIXEL(2), MGC_CELL2PIXEL(2));
        player_.set_animation(AnimationType::Stop, CharacterDirection::Right);
    } else {
        player_.init(0, MGC_CELL2PIXEL(2), MGC_CELL2PIXEL(38));
        player_.set_animation(AnimationType::Stop, CharacterDirection::Right);
    }

    // camera
    camera_init(&camera_);
    camera_set_x_follow_settings(&camera_, MGC_CELL2PIXEL(2), MGC_CELL2PIXEL(map_scene_002.map_width), MGC_CELL2PIXEL(1));
    camera_set_y_follow_settings(&camera_, MGC_CELL2PIXEL(2), MGC_CELL2PIXEL(map_scene_002.map_height), MGC_CELL2PIXEL(1)/2);
    camera_set_x_follow_enabled(&camera_, true);
    camera_set_y_follow_enabled(&camera_, true);
}

bool Scene002::show_tutorial() {

    switch (tutorial_state_) {
    case TutorialState::ID_000:
        dialoguebox_set_text(&dialoguebox_, textdb::get_text_by_id(textdb::TextId::Id_100_HowToPlay));
        tutorial_state_ = TutorialState::ID_001;
        break;
    case TutorialState::ID_001:
        if ( dialoguebox_get_display_text_state(&dialoguebox_) == MGC_DISPLAY_TEXT_STATE_TEXT_END ) {
            if ( game_io_.gamepad.is_key_on_edge(GAMEPAD_TINY_KEY_2) ) {
                dialoguebox_set_text(&dialoguebox_, textdb::get_text_by_id(textdb::TextId::Id_101_HowToPlay));

                tutorial_state_ = TutorialState::ID_010;
            }
        }

        break;
    case TutorialState::ID_010:
        if ( dialoguebox_get_display_text_state(&dialoguebox_) == MGC_DISPLAY_TEXT_STATE_TEXT_END ) {
            if ( game_io_.gamepad.is_key_on_edge(GAMEPAD_TINY_KEY_2) ) {
                dialoguebox_set_text(&dialoguebox_, textdb::get_text_by_id(textdb::TextId::Id_102_HowToPlay));
                tutorial_state_ = TutorialState::ID_011;
            }
        } else {
            game_io_.sound.play_SE(MML_SE_1);
        }
        break;
    case TutorialState::ID_011:
        if ( dialoguebox_get_display_text_state(&dialoguebox_) == MGC_DISPLAY_TEXT_STATE_TEXT_END ) {
            if ( game_io_.gamepad.is_key_on_edge(GAMEPAD_TINY_KEY_2) ) {
                dialoguebox_set_text(&dialoguebox_, textdb::get_text_by_id(textdb::TextId::Id_103_HowToPlay));
                tutorial_state_ = TutorialState::ID_020;
            }
        } else {
            game_io_.sound.play_SE(MML_SE_1);
        }
        break;
    case TutorialState::ID_020:
        if ( dialoguebox_get_display_text_state(&dialoguebox_) == MGC_DISPLAY_TEXT_STATE_TEXT_END ) {
            selectbox_clear_items(&selectbox_);
            selectbox_append_item(&selectbox_, textdb::get_text_by_id(textdb::TextId::Id_000_Yes));
            selectbox_append_item(&selectbox_, textdb::get_text_by_id(textdb::TextId::Id_001_No));
            selectbox_set_enabled(&selectbox_, true);
            selectbox_set_selected_idx(&selectbox_, 0);
            tutorial_state_ = TutorialState::ID_021;
        } else {
            game_io_.sound.play_SE(MML_SE_1);
        }
        break;
    case TutorialState::ID_021:
        if ( game_io_.gamepad.is_key_on_edge(GAMEPAD_TINY_KEY_0) ) {
            selectbox_change_selected_idx(&selectbox_, false);
        } else if ( game_io_.gamepad.is_key_on_edge(GAMEPAD_TINY_KEY_1) ) {
            selectbox_change_selected_idx(&selectbox_, true);
        } else if ( game_io_.gamepad.is_key_on_edge(GAMEPAD_TINY_KEY_2) ) {
            switch ( selectbox_.selected_idx ) {
            case 0:
                tutorial_state_ = TutorialState::ID_022;
                dialoguebox_set_cursor_speed(&dialoguebox_, 10);
                dialoguebox_set_text(&dialoguebox_, textdb::get_text_by_id(textdb::TextId::Id_104_HowToPlay));
                sound_mml_psg__finish_primary_loop(true);
                break;
            case 1:
                tutorial_state_ = TutorialState::ID_000;
                break;
            default:
                break;
            }
            selectbox_set_enabled(&selectbox_, false);

        } else {
        }
        break;

    case TutorialState::ID_022:
        if ( game_io_.sound.is_BGM_done() ) {
            dialoguebox_set_enabled(&dialoguebox_, false);
            game_io_.sound.play_BGM(MML_BGM_1);
            tutorial_state_ = TutorialState::ID_999;
        }
        break;
    case TutorialState::ID_999:
        break;
    default:
        break;
    }

    if ( tutorial_state_ != TutorialState::ID_999 ) {
        dialoguebox_display_update(&dialoguebox_);
    }

    return (tutorial_state_ == TutorialState::ID_999);
}

bool Scene002::show_ready_go() {
    uint32_t mml_cb_data = game_info_.get_mml_cb_value();
    switch (mml_cb_data) {
    case 0x11:
        sprite_set_tile_idx(&text_ready_go_, 1);
        break;
    case 0x12:
        sprite_set_tile_idx(&text_ready_go_, 2);
        break;
    case 0x13:
        sprite_set_tile_idx(&text_ready_go_, 3);
        break;
    case 0x14:
        sprite_set_tile_idx(&text_ready_go_, 4);
        break;
    default:
        break;
    }
    if ( game_io_.sound.is_BGM_done() ) {
        sprite_set_tile_idx(&text_ready_go_, 0);
        game_info_.set_countdown_value(55*1000);
        game_info_.start_countdown();
        game_io_.sound.play_BGM(MML_BGM_2);
        return true;
    } else {
        return false;
    }
}
}
