#include "scene_004.hpp"
#include "resources/generated/tileset/tileset_map_elements.h"
#include "resources/generated/tileset/tileset_static_objects.h"
#include "resources/generated/map/map_scene_004.h"
#include "resources/text/text_database.hpp"
#include "resources/mml/mml_list.h"

namespace mgc {

void Scene004::initialize(SceneId id_prev) {
    id_next_ = SceneId::ID_004;
    id_prev_ = id_prev;
    scene_trans_ = false;
    set_scene_state(SceneState::Showing);

    init_components();

    camera_update(&pixelbuffer_, &camera_, player_.get_ptr_sprite());
}

SceneId Scene004::get_id() const {
    return SceneId::ID_004;
}

SceneId Scene004::get_id_next() const {
    return id_next_;
}

bool Scene004::check_trans() const {
    return scene_trans_;
}

void Scene004::update() {

    fish_.update();

    SceneState scene_state = get_scene_state();
    if ( scene_state == SceneState::Shown ) {
        switch ( game_info_.get_main_state() ) {
        case MainState::Playing:
            player_.update();
            check_hit_tilemap(&player_, maphit_, tilemap_);
            if ( check_hit_sprite(&player_, sprhit_, *gate_1_.get_ptr_sprite()) ) {
                id_next_ = SceneId::ID_003;
                set_scene_state(SceneState::Closing);
            } else if ( check_hit_sprite(&player_, sprhit_, *fish_.get_ptr_sprite()) ) {
                game_io_.sound.play_BGM(MML_BGM_3);
                fish_.hide();
                game_info_.set_success();
                game_info_.suspend_countdown();
            } else {
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
        case MainState::MissionComplete:
            check_hit_tilemap(&player_, maphit_, tilemap_);
            camera_update(&pixelbuffer_, &camera_, player_.get_ptr_sprite());
            if ( player_.victory() ) {
                id_next_ = SceneId::ID_999;
                set_scene_state(SceneState::Closing);
            }
            break;
        default:
            break;
        }
    } else if ( scene_state == SceneState::Closed ) {
        scene_trans_ = true;
    } else {
    }
}

void Scene004::cell_draw_and_transfer(uint16_t screen_x0, uint16_t screen_y0, uint16_t width, uint16_t height) {
    for ( int16_t y = 0; y < height; y += MGC_CELL2PIXEL(1)) {
        for ( int16_t x = 0; x < width; x += MGC_CELL2PIXEL(1)) {
            tilemap_apply_cell_blending(&tilemap_, &pixelbuffer_, x, y);
            label_apply_cell_blending(game_info_.get_ptr_label_countdown(), &pixelbuffer_, x, y);
            sprite_apply_cell_blending(gate_1_.get_ptr_sprite(), &pixelbuffer_, x, y);
            sprite_apply_cell_blending(fish_.get_ptr_sprite(), &pixelbuffer_, x, y);
            sprite_apply_cell_blending(player_.get_ptr_sprite(), &pixelbuffer_, x, y);
            sprite_apply_cell_blending(player_.get_ptr_sprite_item(), &pixelbuffer_, x, y);

            filter_scene_cell(&pixelbuffer_, MGC_COLOR_BLACK);
            pixelbuffer_draw_cell(&pixelbuffer_, &game_io_.display, screen_x0+x, screen_y0+y);
        }
    }
}

void Scene004::draw(mgc_framebuffer_t& fb) {

    mgc_point_t camera_pos;
    camera_get_position(&camera_, &camera_pos);

    framebuffer_clear(&fb, MGC_COLOR(0.0, 1.0, 1.0));

    tilemap_draw(&tilemap_, &fb, &camera_pos, nullptr);
    label_draw(game_info_.get_ptr_label_countdown(), &fb, &camera_pos, nullptr);
    sprite_draw(gate_1_.get_ptr_sprite(), &fb, &camera_pos, nullptr);
    sprite_draw(fish_.get_ptr_sprite(), &fb, &camera_pos, nullptr);
    sprite_draw(player_.get_ptr_sprite(), &fb, &camera_pos, nullptr);
    sprite_draw(player_.get_ptr_sprite_item(), &fb, &camera_pos, nullptr);

    filter_scene(&fb, MGC_COLOR_BLACK);
}

void Scene004::init_components() {

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
    gate_1_.set_tile_idx(3);

    // tilemap
    tilemap_init(&tilemap_, 1, &map_scene_004, &tileset_map_elements);
    tilemap_set_position(&tilemap_, MGC_CELL2PIXEL(0), MGC_CELL2PIXEL(0));
    tilemap_set_r_cell_offset(&tilemap_, 1, 1);
    tilemap_set_enabled(&tilemap_, true);

    // player
    player_.init(0, MGC_CELL2PIXEL(2), MGC_CELL2PIXEL(38));
    player_.set_animation(AnimationType::Stop, CharacterDirection::Right);

    // fish
    fish_.init(0, MGC_CELL2PIXEL(4), MGC_CELL2PIXEL(8));
    fish_.set_speed(2);
    fish_.set_x_range(MGC_CELL2PIXEL(4), MGC_CELL2PIXEL(33));
    fish_.show();

    // camera
    camera_init(&camera_);
    camera_set_x_follow_settings(&camera_, MGC_CELL2PIXEL(2), MGC_CELL2PIXEL(map_scene_004.map_width), MGC_CELL2PIXEL(1));
    camera_set_y_follow_settings(&camera_, MGC_CELL2PIXEL(2), MGC_CELL2PIXEL(map_scene_004.map_height), MGC_CELL2PIXEL(1)/2);
    camera_set_x_follow_enabled(&camera_, true);
    camera_set_y_follow_enabled(&camera_, true);
}

}
