#ifndef MGC_TEXT_DATABASE_HPP
#define MGC_TEXT_DATABASE_HPP

#include "mgc/mgc.h"

namespace mgc {
namespace textdb {

enum class Language : uint16_t {
    English,
    Japanese,
    Count,
};

enum class TextId : uint16_t {
    Id_000_Yes,
    Id_001_No,
    Id_002_NoThankyou,
    Id_100_HowToPlay,
    Id_101_HowToPlay,
    Id_102_HowToPlay,
    Id_103_HowToPlay,
    Id_104_HowToPlay,
    Id_110_WannaTryAgain,
    Count,
};

void set_language(Language language);
const char *get_text_by_id(TextId id);
const mgc_font *get_font();

}
}

#endif/*MGC_TEXT_DATABASE_HPP*/

