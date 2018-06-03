#include "pen/InstrumentSpecies.h"

namespace pen
{
    InstrumentSpecies::InstrumentSpecies( std::string inID )
    : myID{ std::move( inID ) }
    , name{}
    , transposition{ 0 }
    , lowestNote{ 0 }
    , highestNote{ 0 }
    {
        
    }
    
    
    const std::string&
    InstrumentSpecies::id() const
    {
        return myID;
    }
}
