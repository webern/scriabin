#include "mx/api/PitchData.h"
#include "mx/api/DurationData.h"
#include <array>

namespace scriabin
{
    constexpr const int STEP_C = 0;
    constexpr const int STEP_D = 1;
    constexpr const int STEP_E = 2;
    constexpr const int STEP_F = 3;
    constexpr const int STEP_G = 4;
    constexpr const int STEP_A = 5;
    constexpr const int STEP_B = 6;
    
    constexpr const int PITCH_CLASS_C_FLAT = 11;
    constexpr const int PITCH_CLASS_C = 0;
    constexpr const int PITCH_CLASS_C_SHARP = 1;
    
    constexpr const int PITCH_CLASS_D_FLAT = PITCH_CLASS_C_SHARP;
    constexpr const int PITCH_CLASS_D = 2;
    constexpr const int PITCH_CLASS_D_SHARP = 3;
    
    constexpr const int PITCH_CLASS_E_FLAT = PITCH_CLASS_D_SHARP;
    constexpr const int PITCH_CLASS_E = 4;
    constexpr const int PITCH_CLASS_E_SHARP = 5;
    
    constexpr const int PITCH_CLASS_F_FLAT = PITCH_CLASS_E;
    constexpr const int PITCH_CLASS_F = 5;
    constexpr const int PITCH_CLASS_F_SHARP = 6;
    
    constexpr const int PITCH_CLASS_G_FLAT = PITCH_CLASS_F_SHARP;
    constexpr const int PITCH_CLASS_G = 7;
    constexpr const int PITCH_CLASS_G_SHARP = 8;
    
    constexpr const int PITCH_CLASS_A_FLAT = PITCH_CLASS_G_SHARP;
    constexpr const int PITCH_CLASS_A = 9;
    constexpr const int PITCH_CLASS_A_SHARP = 10;
    
    constexpr const int PITCH_CLASS_B_FLAT = PITCH_CLASS_A_SHARP;
    constexpr const int PITCH_CLASS_B = 11;
    constexpr const int PITCH_CLASS_B_SHARP = 0;
    
    constexpr std::array<int, 7> STEP_PITCH_CLASSES =
    {
        PITCH_CLASS_C,
        PITCH_CLASS_D,
        PITCH_CLASS_E,
        PITCH_CLASS_F,
        PITCH_CLASS_G,
        PITCH_CLASS_A,
        PITCH_CLASS_B,
    };
    
    constexpr const int MIDI_NOTE_ZERO_OCTAVE = -1;
    constexpr const int C4_OCTAVE = 4;
    constexpr const int C4_MIDI_NUMBER = 60;
    constexpr const int SEMITONES_PER_OCTAVE = 12;
    
    
    inline mx::api::PitchData
    MIDDLE_C()
    {
        mx::api::PitchData p;
        p.step = mx::api::Step::c;
        p.octave = C4_OCTAVE;
        p.alter = 0;
        p.accidental = mx::api::Accidental::none;
        return p;
    }
    
    constexpr const auto S = mx::api::DurationName::dur16th;
    constexpr const auto E = mx::api::DurationName::eighth;
    constexpr const auto Q = mx::api::DurationName::quarter;
    constexpr const auto H = mx::api::DurationName::half;
    constexpr const auto W = mx::api::DurationName::whole;
}
