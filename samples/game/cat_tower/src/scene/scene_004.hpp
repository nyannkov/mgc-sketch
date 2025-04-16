#ifndef MGC_SCENE_004_HPP
#define MGC_SCENE_004_HPP

#include "mgc/mgc.h"
#include "scene.hpp"
#include "actor/player.hpp"
#include "actor/static_object.hpp"
#include "actor/fish.hpp"

namespace mgc {

struct Scene004: SceneIf {
    Scene004(GameIO &game_io, GameInfo &game_info) : 
        game_io_(game_io),
        game_info_(game_info),
        player_(game_io, game_info),
        fish_(game_info) 
    { }
    ~Scene004() = default;
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
    Fish fish_;
    StaticObject gate_1_;
    void init_components();
};

}

#endif/*MGC_SCENE_004_HPP*/
