#ifndef MGC_GAME_INFO_HPP
#define MGC_GAME_INFO_HPP

#include "mgc/mgc.h"

namespace mgc {

enum class MainState : uint16_t {
    Tutorial = 0,
    ReadyGo,
    Playing,
    GameOver,
    MissionComplete,
};

struct GameInfo {

    GameInfo() { }
    ~GameInfo() = default;

    GameInfo(const GameInfo&) = delete;
    GameInfo& operator=(const GameInfo&) = delete;
    GameInfo(GameInfo&&) = default;
    GameInfo& operator=(GameInfo&&) = default;

    void initialize();

    MainState get_main_state() const;
    void set_main_state(MainState state);
    void update_main_state();
    void reset_main_state();
    void set_play_start();
    void set_tutorial_finished();
    void set_success();

    uint32_t get_loop_count() const;
    void increment_loop_count();

    uint32_t get_play_count() const; 
    void increment_play_count(); 

    void set_mml_cb_value(uint32_t value);
    uint32_t get_mml_cb_value() const;

    void set_countdown_value(unsigned long value_ms);
    uint32_t get_countdown_value() const;
    void start_countdown();
    void stop_countdown();
    void suspend_countdown();
    void resume_countdown();
    bool is_counting_down() const;
    void update_countdown();

    const char *get_str_score_value() const;
    const char *get_str_countdown_value() const;
    const mgc_label *get_ptr_label_countdown() const;
    const char *get_str_score_text();

private:
    MainState main_state_;
    uint32_t loop_counter_;
    uint32_t mml_cb_value_;
    uint32_t play_counter_;
    bool countdown_active_;
    unsigned long countdown_value_;
    unsigned long countdown_time_pre_;
    char str_countdown_value_[32];
    char str_score_value_[32];
    bool tutorial_finished_;
    bool play_start_;
    bool reset_main_state_;
    bool success_;
    bool suspend_countdown_;
    mgc_label label_countdown_;

    long score_;
    long score_record_[3];
    size_t new_score_idx;
    char str_score_text_[128];
};

}

#endif/*MGC_GAME_IO_HPP*/

