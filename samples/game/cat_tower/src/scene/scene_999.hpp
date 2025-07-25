#ifndef MGC_SCENE_999_HPP
#define MGC_SCENE_999_HPP

#include "mgc/mgc.h"
#include "scene.hpp"
#include "actor/player.hpp"

namespace mgc {

struct Scene999: SceneIf {
    Scene999(GameIO &game_io, GameInfo &game_info) : game_io_(game_io), game_info_(game_info), player_(game_io, game_info) {}
    ~Scene999() = default;
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
    Player player_;
    mgc_dialoguebox dialoguebox_;
    mgc_selectbox selectbox_;
    mgc_pixelbuffer pixelbuffer_;
    void init_components();
    enum class QuestionState : uint16_t {
        ID_000 = 0,
        ID_001,
        ID_002,
        ID_003,
        ID_101,
    };
    QuestionState question_state_;
};

}

#endif/*MGC_SCENE_999_HPP*/
