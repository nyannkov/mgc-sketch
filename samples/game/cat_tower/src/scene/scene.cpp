#include "scene.hpp"
#include "scene_001.hpp"
#include "scene_002.hpp"
#include "scene_003.hpp"
#include "scene_004.hpp"
#include "scene_999.hpp"

namespace mgc {

static SceneState scene_state;
static int16_t cell_mask;

std::unique_ptr<SceneIf> make_scene(SceneId id, GameIO &game_io, GameInfo &game_info) {
    switch (id) {
    case SceneId::ID_001:
        return std::make_unique<Scene001>(game_io, game_info);
    case SceneId::ID_002:
        return std::make_unique<Scene002>(game_io, game_info);
    case SceneId::ID_003:
        return std::make_unique<Scene003>(game_io, game_info);
    case SceneId::ID_004:
        return std::make_unique<Scene004>(game_io, game_info);
    case SceneId::ID_999:
        return std::make_unique<Scene999>(game_io, game_info);
    default:
        return nullptr;
    }
}

SceneState get_scene_state() {
    return scene_state;
}

void set_scene_state(SceneState state) {

    switch (state) {
    case SceneState::WaitClose:
    case SceneState::Closing:
    case SceneState::Shown:
        cell_mask = 0;
        break;

    case SceneState::Closed:
    case SceneState::Showing:
        cell_mask = MGC_CELL_LEN*-1;
        break;

    default:
        break;
    }

    scene_state = state;
}

void update_scene_state() {
    switch (scene_state) {
    case SceneState::Closing:
        cell_mask++;
        if ( cell_mask >= MGC_CELL_LEN ) {
            cell_mask = MGC_CELL_LEN;
            scene_state = SceneState::Closed;
        }
        break;

    case SceneState::Showing:
        cell_mask++;
        if ( cell_mask >= 0 ) {
            cell_mask = 0;
            scene_state = SceneState::Shown;
        }
        break;

    default:
        break;
    }
}

void filter_scene_cell(mgc_pixelbuffer *pixelbuffer, mgc_color_t color) {
    if ( scene_state != SceneState::Shown ) {
        pixelbuffer_fill_partial_with_color(pixelbuffer, color, cell_mask, cell_mask);
    }
}

void filter_scene(mgc_framebuffer *framebuffer, mgc_color_t color) {
    if ( scene_state != SceneState::Shown ) {
        mgc_color_t* buffer = framebuffer_get_buffer_mut(framebuffer);
        uint16_t width = framebuffer_get_width(framebuffer);
        uint16_t height = framebuffer_get_height(framebuffer);

        if ( cell_mask >= 0 ) {
            uint16_t rows = (uint16_t)((height * (float)cell_mask / MGC_CELL_LEN) + 0.5f);
            for ( uint16_t y = 0; y < rows; y++ ) {
                for ( uint16_t x = 0; x < width; x++ ) {
                    buffer[x + y * width] = MGC_COLOR_SWAP(color);
                }
            }
        } else {
            uint16_t rows = (uint16_t)((height * (float)cell_mask*-1 / MGC_CELL_LEN) + 0.5f);
            for ( int32_t y = rows-1; y >= 0; y-- ) {
                for ( int32_t x = width-1; x >= 0; x-- ) {
                    buffer[x + y * width] = MGC_COLOR_SWAP(color);
                }
            }
        }
    }
}


}
