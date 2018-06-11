#pragma once
#include "mx/api/ScoreData.h"
#include "pen/InstrumentConfig.h"

namespace pen
{
    class Etude
    {
    public:
        Etude();
        Etude( InstrumentConfig inConfig );
        
    public:
        void addPart( const std::string inSpecies );
        mx::api::ScoreData& getScore();
        const mx::api::ScoreData& getScoreConst() const;
        
    private:
        InstrumentConfig myConfig;
        mx::api::ScoreData myScore;
    };
}
