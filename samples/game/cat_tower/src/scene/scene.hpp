#ifndef MGC_SCENE_HPP
#define MGC_SCENE_HPP

#include <memory>
#include "mgc/mgc.h"
#include "game_io/game_io.hpp"
#include "game_info/game_info.hpp"

namespace mgc {

enum class SceneId : uint16_t {
    ID_000 = 0,
    ID_001,
    ID_002,
    ID_003,
    ID_004,
    ID_999,
};

enum class SceneState {
    WaitClose,
    Closing,
    Closed,
    Showing,
    Shown,
};

struct SceneIf {
    virtual ~SceneIf() = default;
    virtual void initialize(SceneId id_prev) = 0;
    virtual SceneId get_id() const = 0;
    virtual SceneId get_id_next() const = 0;
    virtual bool check_trans() const = 0;
    virtual void update() = 0;
    virtual void cell_draw_and_transfer(uint16_t screen_x0, uint16_t screen_y0, uint16_t width, uint16_t height) = 0;
    virtual void draw(mgc_framebuffer_t& fb) = 0;
};

extern std::unique_ptr<SceneIf> make_scene(SceneId id, GameIO &game_io, GameInfo &game_info);
extern void update_scene_state();

extern SceneState get_scene_state();
extern void set_scene_state(SceneState state);
extern void filter_scene_cell(mgc_pixelbuffer *pixelbuffer, mgc_color_t color);
extern void filter_scene(mgc_framebuffer *framebuffer, mgc_color_t color);

}
#endif/*MGC_SCENE_HPP*/
