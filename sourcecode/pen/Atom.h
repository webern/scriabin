#pragma once
#include "mx/api/PitchData.h"
#include <string>
#include <sstream>
#include <cstdint>

namespace pen
{
    // step -1 indicates rest
    // step 0 is C
    // step 1 is D, etc.
    struct Atom
    {
    public:
        Atom();
        Atom( const mx::api::PitchData& inPitchData );
        
        std::string name;
        void setRest();
        void setStep( int inStep );
        int getStep() const;
        void setOctave( int inOctave );
        int getOctave() const;
        void setAlter( int inAlter );
        int getAlter() const;
        void setStep( mx::api::Step inMxStep );
        mx::api::Step getMxStep() const;
        void setFromMx( const mx::api::PitchData& inPitchData );
        mx::api::PitchData getMxPitchData() const;

    private:
        int step;
        int alter;
        int octave;

    public:
        void updateName();
    };
}
