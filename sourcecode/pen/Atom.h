#pragma once
#include "mx/api/PitchData.h"
#include <string>
#include <sstream>
#include <cstdint>

namespace pen
{
    struct Atom
    {
        int step = -1; // -1 for rest
        int alter = 0;
        int octave = 4;
        std::string name = "rest";
        void updateName();
        void setStep( mx::api::Step inMxStep);
        mx::api::Step getMxStep() const;
    };
}
