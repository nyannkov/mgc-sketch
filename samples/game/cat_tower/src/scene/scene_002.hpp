#ifndef MGC_SCENE_002_HPP
#define MGC_SCENE_002_HPP

#include "mgc/mgc.h"
#include "scene.hpp"
#include "actor/player.hpp"
#include "actor/static_object.hpp"

namespace mgc {

struct Scene002: SceneIf {
    Scene002(GameIO &game_io, GameInfo &game_info) : game_io_(game_io), game_info_(game_info), player_(game_io, game_info) {}
    ~Scene002() = default;
    void initialize(SceneId id_prev) override;
    SceneId get_id() const override;
    SceneId get_id_next() const override;
    bool check_trans() const override;
    void update() override;
    void draw(uint16_t screen_x0, uint16_t screen_y0, uint16_t width, uint16_t height) override;

private:
    GameIO &game_io_;
    GameInfo &game_info_;
    SceneId id_next_;
    SceneId id_prev_;
    bool scene_trans_;
    mgc_pixelbuffer pixelbuffer_;
    mgc_tilemap tilemap_;
    mgc_tilemap tilemap_bg_;
    mgc_camera camera_;
    mgc_maphit maphit_;
    mgc_sprhit sprhit_;
    Player player_;
    StaticObject gate_1_;
    StaticObject gate_2_;
    mgc_sprite text_ready_go_;
    mgc_dialoguebox dialoguebox_;
    mgc_selectbox selectbox_;
    enum class TutorialState : uint16_t {
        ID_000 = 0,
        ID_001,
        ID_010,
        ID_011,
        ID_020,
        ID_021,
        ID_022,
        ID_999,
    };
    TutorialState tutorial_state_;
    void init_components();
    bool show_tutorial();
    bool show_ready_go();
};

}

#endif/*MGC_SCENE_002_HPP*/
