#include "scene_999.hpp"
#include "resources/text/text_database.hpp"

namespace mgc {

void Scene999::initialize(SceneId id_prev) {
    id_next_ = SceneId::ID_999;
    id_prev_ = id_prev;
    scene_trans_ = false;
    set_scene_state(SceneState::Showing);
    question_state_ = QuestionState::ID_000;

    init_components();
}

SceneId Scene999::get_id() const {
    return SceneId::ID_999;
}

SceneId Scene999::get_id_next() const {
    return id_next_;
}

bool Scene999::check_trans() const {
    return scene_trans_;
}

void Scene999::update() {

    SceneState scene_state = get_scene_state();

    if ( scene_state == SceneState::Shown ) {
        switch (question_state_) {
        case QuestionState::ID_000:

            if ( game_info_.get_main_state() == MainState::MissionComplete ) {
                dialoguebox_set_text(&dialoguebox_, game_info_.get_str_score_value());
                dialoguebox_set_enabled(&dialoguebox_, true);
                question_state_ = QuestionState::ID_101;
            } else {
                dialoguebox_set_text(&dialoguebox_, textdb::get_text_by_id(textdb::TextId::Id_110_WannaTryAgain));
                dialoguebox_set_enabled(&dialoguebox_, true);
                question_state_ = QuestionState::ID_001;
            }

            break;

        case QuestionState::ID_001:
            if ( dialoguebox_get_display_text_state(&dialoguebox_) == MGC_DISPLAY_TEXT_STATE_TEXT_END ) {
                selectbox_set_enabled(&selectbox_, true);
                question_state_ = QuestionState::ID_002;
            }
            break;
        case QuestionState::ID_002:
            if ( game_io_.gamepad.is_key_on_edge(GAMEPAD_TINY_KEY_0) ) {
                selectbox_change_selected_idx(&selectbox_, false);

            } else if ( game_io_.gamepad.is_key_on_edge(GAMEPAD_TINY_KEY_1) ) {
                selectbox_change_selected_idx(&selectbox_, true);

            } else if ( game_io_.gamepad.is_key_on_edge(GAMEPAD_TINY_KEY_2) ) {
                switch ( selectbox_.selected_idx ) {
                case 0:
                    id_next_ = SceneId::ID_002;
                    set_scene_state(SceneState::Closing);
                    player_.set_animation(AnimationType::GoingToSleeping, CharacterDirection::Left);
                    break;
                case 1:
                default:
                    id_next_ = SceneId::ID_001;
                    set_scene_state(SceneState::Closing);
                    break;
                }
                question_state_ = QuestionState::ID_003;
                selectbox_set_enabled(&selectbox_, false);

            } else {
            }
            break;

        case QuestionState::ID_003:
            break;

        case QuestionState::ID_101:
            if ( dialoguebox_get_display_text_state(&dialoguebox_) == MGC_DISPLAY_TEXT_STATE_TEXT_END ) {
                if ( game_io_.gamepad.is_key_on_edge(GAMEPAD_TINY_KEY_2) ) {
                    dialoguebox_set_text(&dialoguebox_, textdb::get_text_by_id(textdb::TextId::Id_110_WannaTryAgain));
                    question_state_ = QuestionState::ID_001;
                }
            }
            break;
        }

        dialoguebox_display_update(&dialoguebox_);

    } else if ( scene_state == SceneState::Closed ) { 
        game_info_.reset_main_state();
        scene_trans_ = true;

    } else {
    }

    player_.update_animation();
}

void Scene999::draw(uint16_t screen_x0, uint16_t screen_y0, uint16_t width, uint16_t height) {
    for ( int16_t y = 0; y < height; y += MGC_CELL2PIXEL(1)) {
        for ( int16_t x = 0; x < width; x += MGC_CELL2PIXEL(1)) {
            sprite_apply_cell_blending(player_.get_ptr_sprite(), &pixelbuffer_, x, y);
            dialoguebox_apply_cell_blending(&dialoguebox_, &pixelbuffer_, x, y);
            selectbox_apply_cell_blending(&selectbox_, &pixelbuffer_, x, y);

            filter_scene_cell(&pixelbuffer_, MGC_COLOR_BLACK);
            pixelbuffer_draw_cell(&pixelbuffer_, &game_io_.display, screen_x0+x, screen_y0+y);
        }
    }
}

void Scene999::init_components() {

    // pixelbuffer
    pixelbuffer_init(&pixelbuffer_);
    pixelbuffer_set_back_color(&pixelbuffer_, MGC_COLOR_BLACK);

    // player
    player_.init(0, MGC_CELL2PIXEL(1)/2, MGC_CELL2PIXEL(3));
    player_.set_animation(AnimationType::Sleeping, CharacterDirection::Left);

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
    dialoguebox_set_text(&dialoguebox_, textdb::get_text_by_id(textdb::TextId::Id_110_WannaTryAgain));
    dialoguebox_set_r_cell_offset(&dialoguebox_, 0, 0);
    dialoguebox_set_enabled(&dialoguebox_, false);

    // Initialize the selectbox.
    selectbox_init(&selectbox_, 0, textdb::get_font(), false);
    selectbox_append_item(&selectbox_, textdb::get_text_by_id(textdb::TextId::Id_000_Yes));
    selectbox_append_item(&selectbox_, textdb::get_text_by_id(textdb::TextId::Id_002_NoThankyou));
    selectbox_set_width(&selectbox_, 4*14);
    selectbox_set_position(&selectbox_, MGC_CELL2PIXEL(2), MGC_CELL2PIXEL(2));
    selectbox_set_r_cell_offset(&selectbox_, 0, 0);
    selectbox_set_enabled(&selectbox_, false);
}

}
