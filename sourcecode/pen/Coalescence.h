#pragma once

#include "mx/api/ScoreData.h"
#include "pen/Atom.h"
#include <string>
#include <vector>
#include <sstream>

namespace pen
{
    struct CoalescenceConsts
    {
        const std::string outFilename = "coalescence.large.xml";
        const std::string inFilename = "coalescence.input.xml";
        
    };
    
    class Coalescence
    {
    public:
        Coalescence();
        void doEverthing();
        
    private:
        mx::api::ScoreData myScore;
        
    private:
        static mx::api::ScoreData createEmptyScore( const std::string& title );
        static void addInstrument( mx::api::ScoreData& ioScore,
                                   const std::string& id,
                                   const std::string& name,
                                   const std::string& abbr,
                                   mx::api::SoundID soundID,
                                   const mx::api::ClefData clef );
        static void appendMeasures( mx::api::ScoreData& ioScore, int numMeasures );
    };
}
