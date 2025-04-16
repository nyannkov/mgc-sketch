#ifndef MGC_SCENE_003_HPP
#define MGC_SCENE_003_HPP

#include "mgc/mgc.h"
#include "scene.hpp"
#include "actor/player.hpp"
#include "actor/static_object.hpp"

namespace mgc {

struct Scene003: SceneIf {
    Scene003(GameIO &game_io, GameInfo &game_info) : game_io_(game_io), game_info_(game_info), player_(game_io, game_info) {}
    ~Scene003() = default;
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
    mgc_camera camera_;
    mgc_maphit maphit_;
    mgc_sprhit sprhit_;
    Player player_;
    StaticObject gate_1_;
    StaticObject gate_2_;
    void init_components();
};

}

#endif/*MGC_SCENE_003_HPP*/
