#include <Arduino.h>
#include "game_info.hpp"
#include "resources/text/text_database.hpp"

namespace mgc {

void GameInfo::initialize() {
    main_state_ = MainState::Tutorial;
    loop_counter_ = 0;
    mml_cb_value_ = 0;
    play_counter_ = 0;
    countdown_active_ = false;
    countdown_value_ = 0;
    countdown_time_pre_ = 0;
    snprintf(str_countdown_value_, sizeof(str_countdown_value_), "---");
    str_score_text_[0] = '\0';

    tutorial_finished_ = false;
    play_start_ = false;
    reset_main_state_ = false;
    success_ = false;
    suspend_countdown_ = false;
    
    score_ = 0;
   
    for ( auto &record : score_record_ ) {
        record = -1;
    }

    // label_countdown_
    label_init(&label_countdown_, 0, textdb::get_font(), true);
    label_set_position(&label_countdown_, MGC_CELL2PIXEL(0), MGC_CELL2PIXEL(0));
    label_set_r_cell_offset(&label_countdown_, 0, 0);
    label_set_size(&label_countdown_, 8*10*2, 12*2);
    label_set_text(&label_countdown_, str_countdown_value_);
    label_set_fore_color(&label_countdown_, MGC_COLOR(1.0, 1.0, 1.0));
    label_set_enabled(&label_countdown_, true);
}

MainState GameInfo::get_main_state() const {
    return main_state_;
}

void GameInfo::update_main_state() {
    switch (main_state_) {
    case MainState::Tutorial:
        if ( tutorial_finished_ ) {
            tutorial_finished_ = false;
            main_state_ = MainState::ReadyGo;
        }
        break;

    case MainState::ReadyGo:
        if ( play_start_ ) {
            play_start_ = false;
            success_ = false;
            main_state_ = MainState::Playing;
        }
        break;

    case MainState::Playing:
        if ( success_ ) {
            main_state_ = MainState::MissionComplete;
        } else if ( mml_cb_value_ == 0x21 ) {
            main_state_ = MainState::GameOver;
        } else {
        }
        break;

    case MainState::GameOver:
    case MainState::MissionComplete:
        if ( reset_main_state_ ) {
            reset_main_state_ = false;
            main_state_ = MainState::ReadyGo;
        }
        break;

    default:
        break;
    }

}

uint32_t GameInfo::get_loop_count() const {
    return loop_counter_;
}

void GameInfo::increment_loop_count() {
    loop_counter_++;
}

uint32_t GameInfo::get_play_count() const {
    return play_counter_;
}

void GameInfo::increment_play_count() {
    play_counter_++;
}

void GameInfo::set_mml_cb_value(uint32_t value) {
    mml_cb_value_ = value;
}

uint32_t GameInfo::get_mml_cb_value() const {
    return mml_cb_value_;
}

void GameInfo::set_countdown_value(unsigned long value_ms) {
    countdown_value_ = value_ms;
}

uint32_t GameInfo::get_countdown_value() const {
    return countdown_value_;
}

void GameInfo::suspend_countdown() {
    suspend_countdown_ = true;
}

void GameInfo::resume_countdown() {
    suspend_countdown_ = false;
}

void GameInfo::start_countdown() {
    countdown_time_pre_ = millis();
    countdown_active_ = true;
    suspend_countdown_ = false;
}

void GameInfo::stop_countdown() {
    countdown_active_ = false;
}

bool GameInfo::is_counting_down() const {
    return countdown_active_;
}

const mgc_label *GameInfo::get_ptr_label_countdown() const {
    return &label_countdown_;
}

void GameInfo::update_countdown() {
    if ( countdown_active_ ) {
        unsigned long time_now = millis();
        unsigned long time_elapsed = time_now - countdown_time_pre_;
        unsigned long time_sec;

        countdown_time_pre_ = time_now;

        if ( !suspend_countdown_ ) {
            if ( countdown_value_ > time_elapsed ) {
                countdown_value_ -= time_elapsed;
            } else {
                countdown_value_ = 0;
            }
        }

        time_sec = countdown_value_ / 1000;

        snprintf(str_countdown_value_, sizeof(str_countdown_value_), "%03d", time_sec);

    } else {
        snprintf(str_countdown_value_, sizeof(str_countdown_value_), "---");
    }
}

const char *GameInfo::get_str_countdown_value() const {
    return str_countdown_value_;
}

const char *GameInfo::get_str_score_value() const {
    return str_score_value_;
}

void GameInfo::set_play_start() {
    play_start_ = true;
}

void GameInfo::set_tutorial_finished() {
    tutorial_finished_ = true;
}
void GameInfo::set_success() {
    score_ = countdown_value_/10;
    size_t score_index = 0;
    bool new_record = false;
    if ( score_ > 99999 ) {
        score_ = 99999;
    }
    for ( score_index = 0; score_index < countof(score_record_); score_index++ ) {
        if ( score_ > score_record_[score_index] ) {
            new_record = true;
            break;
        }
    }
    new_score_idx = score_index;

    if ( new_record ) {
        for ( size_t i = countof(score_record_) - 1; i > new_score_idx; i-- ) {
            score_record_[i] = score_record_[i-1];
        }
        score_record_[new_score_idx] = score_;
    }

    snprintf(str_score_value_, sizeof(str_score_value_), "SCORE: %d%s", score_, new_record ? " (NEW!)" : "");
    success_ = true;
}

const char *GameInfo::get_str_score_text() {
    snprintf(str_score_text_,
            sizeof(str_score_text_),
            "[SCORE]\n1. %5d\n2. %5d\n3. %5d",
            score_record_[0],
            score_record_[1],
            score_record_[2]
    );
    return str_score_text_;
}

void GameInfo::reset_main_state() {
    stop_countdown();
    reset_main_state_ = true;
}
void GameInfo::set_main_state(MainState state) {
    main_state_ = state;
}

}
