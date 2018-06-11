#include "mx/api/PitchData.h"
#include "mx/api/DurationData.h"

namespace pen
{
    constexpr const int MIDI_NOTE_ZERO_OCTAVE = -2;
    constexpr const int MIDDLE_C_OCTAVE = 4;
    constexpr const int MIDI_NOTE_MIDDLE_C = 72;
    
    inline mx::api::PitchData
    MIDDLE_C()
    {
        mx::api::PitchData p;
        p.step = mx::api::Step::c;
        p.octave = MIDDLE_C_OCTAVE;
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
