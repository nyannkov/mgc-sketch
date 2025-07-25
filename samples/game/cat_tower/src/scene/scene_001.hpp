#ifndef MGC_SCENE_001_HPP
#define MGC_SCENE_001_HPP

#include "mgc/mgc.h"
#include "scene.hpp"

namespace mgc {

struct Scene001: SceneIf {
    Scene001(GameIO &game_io, GameInfo &game_info) : game_io_(game_io), game_info_(game_info) {}
    ~Scene001() = default;
    void initialize(SceneId id_prev) override;
    SceneId get_id() const override;
    SceneId get_id_next() const override;
    bool check_trans() const override;
    void update() override;
    void cell_draw_and_transfer(uint16_t screen_x0, uint16_t screen_y0, uint16_t width, uint16_t height) override;
    void draw(mgc_framebuffer_t& fb) override;

private:
    GameIO &game_io_;
    GameInfo &game_info_;
    SceneId id_next_;
    SceneId id_prev_;
    bool scene_trans_;
    mgc_pixelbuffer pixelbuffer_;
    mgc_sprite sprite_title_;
    mgc_selectbox selectbox_menu_;
    mgc_dialoguebox dialoguebox_;
    bool is_score_shown_;
    void init_components();
};

}

#endif/*MGC_SCENE_001_HPP*/
