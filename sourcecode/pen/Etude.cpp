#include "pen/Etude.h"

namespace scriabin
{
    Etude::Etude()
    : myConfig{}
    , myScore{}
    {
        
    }
    
    
    Etude::Etude( InstrumentConfig inConfig )
    : myConfig{ std::move( inConfig ) }
    , myScore{}
    {
        
    }
    
    
    void
    Etude::addPart( const std::string inSpecies )
    {
        const auto& spec = myConfig.getSpecies( inSpecies );
        mx::api::PartData p;
        p.name = spec.name;
        p.displayName = spec.name;
        p.uniqueId = spec.id() + std::string{ "." } + std::to_string( myScore.parts.size() );
        
        p.instrumentData.uniqueId = std::string{ "si." } + p.uniqueId;
        p.instrumentData.name = p.name;

        if( inSpecies == "species.violin" )
        {
            // TODO - fix this hack
            p.instrumentData.soundID = mx::api::SoundID::stringsViolin;
        }
        else if( inSpecies == "species.marimba.4.3" )
        {
            // TODO - fix this hack
            p.instrumentData.soundID = mx::api::SoundID::pitchedPercussionMarimba;
        }
        
        myScore.parts.push_back( p );
        
        if( inSpecies == "species.marimba.4.3" )
        {
            // TODO - fix this hack
            const auto index = myScore.parts.size() - 1;
            mx::api::PartGroupData pg;
            pg.firstPartIndex = static_cast<int>( index );
            pg.lastPartIndex = static_cast<int>( index );
            pg.bracketType = mx::api::BracketType::brace;
            pg.name = p.uniqueId;
            pg.displayName = p.name;
            myScore.partGroups.push_back( pg );
        }
    }
    
    
    mx::api::ScoreData&
    Etude::getScore()
    {
        return myScore;
    }
    
    
    const mx::api::ScoreData&
    Etude::getScoreConst() const
    {
        return myScore;
    }
}
