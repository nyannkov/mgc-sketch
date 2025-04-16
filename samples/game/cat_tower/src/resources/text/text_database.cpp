#include "text_database.hpp"
#include "resources/generated/font/misaki_gothic.h"

namespace mgc {
namespace textdb {

static Language lang;

struct TextLocalized {
    const char *text[static_cast<uint16_t>(Language::Count)];
};

static const TextLocalized text_database[static_cast<uint16_t>(TextId::Count)] = {
    // Id_000_Yes
    {
        "Yes",
        "はい",
    },
    // Id_001_No
    {
        "No",
        "いいえ",
    },
    // Id_002_NoThankyou
    {
        "No,thanks",
        "結構です",
    },
    // Id_100_HowToPlay
    {
        "How to play:",
        "遊び方：",
    },
    // Id_101_HowToPlay
    {
        "Catch the fish \non top of the \ntower before \ntime runs out!",
        "時間がなくなる前に、塔の上にいる魚をつかまえよう！",
    },
    // Id_102_HowToPlay
    {
        "The more time \nyou have left, \nthe higher \nyour score will be!",
        "時間がたくさん残っているほど、得点がアップするよ！",
    },
    // Id_103_HowToPlay
    {
        "Ready to go?",
        "準備はいいですか?",
    },
    // Id_104_HowToPlay
    {
        "Good luck!",
        "頑張ってね！",
    },
    // Id_110_WannaTryAgain
    {
        "Wanna try again?",
        "もう一回やる？",
    },
};


void set_language(Language language) {
    lang = language;
}

const char *get_text_by_id(TextId id) {

    uint16_t index = static_cast<uint16_t>(id);
    if ( index < static_cast<uint16_t>(TextId::Count) ) {
        return text_database[index].text[static_cast<uint16_t>(lang)];
    } else {
        return "";
    }
}

const mgc_font *get_font() {
    switch (lang) {
    case Language::English:
    case Language::Japanese:
        return &misaki_gothic;
    default:
        return &misaki_gothic;
    }
}

}
}
