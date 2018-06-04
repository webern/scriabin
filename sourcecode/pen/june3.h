#pragma once

#include "mx/api/ScoreData.h"
#include <string>
#include <vector>

namespace pen
{
    struct June3Constants
    {
        const std::string outFilename = "june3.xml";
        const std::string inFilename = "homo-sapiens-june-3-2018.large.xml";
        
    };
    
    class June3
    {
    public:
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
