#pragma once
#include "mx/api/PitchData.h"
#include <string>
#include <sstream>
#include <cstdint>

namespace pen
{
    struct Atom
    {
    public:
        Atom();
        Atom( const mx::api::PitchData& inPitchData );
        
        int step; // -1 for rest
        int alter;
        int octave;
        std::string name;
        void setStep( mx::api::Step inMxStep);
        mx::api::Step getMxStep() const;
        void setFromMx( const mx::api::PitchData& inPitchData );
        mx::api::PitchData getMxPitchData() const;
        
    public:
        void updateName();
    };
}
