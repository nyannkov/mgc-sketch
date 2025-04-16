#include "mml_list.h"

mgc_mml_record_t mml_se_list[MML_SE_LIST_COUNT] = {
    {
        MML_SE_0,
        "$P-60$B60L4O5F#"
    },
    {
        MML_SE_1,
        "T140L16V13O6 Q2A"
    }
};

mgc_mml_record_t mml_bgm_list[MML_BGM_LIST_COUNT] = {
    {
        MML_BGM_0,
        "T140"
        "$P-720$B60I0"
        "O2[4 F#8 R8 F#8 R8 F#8 R8 F#8 R8]"
        "@C(0x01)O2[0 [2 V15F#8 V13H64R16.. V15F#8 V13H64R16.. V15F#8 V13H64R16.. V15F#8 V13H64R16..] ]"
    },
    {
        MML_BGM_1,
        "T140"
        "$P-720$B60I0 O2"
        "@C(0x11)V15F#8 V13H64R16.. V15F#8 V13H64R16.. @C(0x12)V15F#8 V13H64R16.. V15F#8 V13H64R16.."
        "@C(0x13)V15F#8 V13H64R16.. V15F#8 V13H64R16.. @C(0x14)V15F#8 R8"
    },
    {
        MML_BGM_2,
        // CH A
        "T140"
        "$P-30$B60"
        "$E1$A0$H40$D100$S80$F2000"
        "[2 L4O5 D#8C#8<F#>F#F#]"
        "L4O5 D#8C#8<F#>F#<D#>F#<C#>FF"
        "[2 L4O5 D#8C#8<C#>FF]"
        "L4O5 D#8C#8<C#>F<D#>F<F#>F#F#"

        "[2 L4O5 D#8C#8A#F#F#]"
        "L4O5 D#8C#8A#F#>C#<F#>D#<FF"
        "[2 L4O5 D#8C#8>D#<FF]"
        "L4O5 D#8C#8>D#<F>C#<FA#F#F#"

        "L4O5 D#8C#8<F#>F#<C#>F#<F#>F#<C#>F# <F#FF#GG# >FF"
        "L4O5 D#8C#8<G#>F <D#>F <G#>F <D#>F  <G#GG#AA# >F#F#"

        "[2 L4O5 D#8C#8<F#>F#F#]"
        "L4O5 D#8C#8<F#>F#<D#>F#<C#>FF"
        "[2 L4O5 D#8C#8<C#>FF]"
        "L4O5 D#8C#8<C#>F<D#>F<F#>F#$P-60F#2$P-30"

        "L4O5 @C(0x21) F# C#8C#8D C#2 @C(0x22) F$P-60 @C(0x23) F#2R2@C(0x24)"
        ","
        // CH B
        "T140V15"
        "$P-720$B60I0"
        "R4"
        "O2[32 V15F#8 V13H64R16.. V15F#8 V13H64R16.. V15F#8 V13H64R16.. V15F#8 V13H64R16..]"
        ","
        // CH C 
        "T140"
        "$P-30$B60"
        "$E1$A0$H40$D100$S80$F2000"
        "[2"
            "[2 L4O4 R2 A#A#]"
            "L4O4 R2 A# R A# R BB"
            "[2 L4O4 R2 BB]"
            "L4O4 R2 B  R B  R A#A#"
        "]"
        "L4O4 R2 A# R A# R A# R A# R1 R B  B"
        "L4O4 R2 B  R B  R B  R B  R1 R A# A#"

        "[2 L4O4 R2 A#A#]"
        "L4O4 R2 A# R A# R BB"
        "[2 L4O4 R2 BB]"
        "L4O4 R2 B  R B  R A#$P-60A#2$P-30"

        "L4O4 A# R1 B $P-60A#2"
    },
    {
        MML_BGM_3,
        // CH A
        "T140"
        "$B90"
        "$E1$A0$H40$D100$S80$F2000"
        "R1"
        "L4O5 F# C#8C#8D C#2 F F#2R2"
        ","
        // CH B
        "T140V15"
        "$P-720$B90I0"
        "@C(0x30)V13 [4 H64R64 R8.. ]"
        "[6 @C(0x31)V15F#8 @C(0x32)V13H64R16..]"
        "@C(0x33)V15 F#8R2..@C(0x34)"
        ","
        // CH C 
        "T140"
        "$B90"
        "$E1$A0$H40$D100$S80$F2000"
        "R1"
        "L4O4 A# R1 B A#2R2"
    }
};
