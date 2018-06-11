#pragma once
#include <memory>
#include <string>

namespace pen
{
    struct InstrumentClassification
    {
        std::string kingdom;
        std::string phylum;
        std::string order;
        std::string family;
        std::string genus;
        std::string species;
    };
    
    class InstrumentSpecies;
    using InstSpecPtr = InstrumentSpecies*;
    using InstSpecUptr = std::unique_ptr<InstrumentSpecies>;

    class InstrumentSpecies
    {
    public:
        InstrumentSpecies( std::string inID );

    public:
        const std::string& id() const;
        
    public:
        std::string name;
        InstrumentClassification classification;
        int transposition;
        int lowestNote;
        int highestNote;
        
    private:
        std::string myID;
    };
    
    inline InstSpecUptr makeInstrSpec( std::string inID ){ return std::make_unique<InstrumentSpecies>( std::move( inID ) ); }
    inline InstSpecUptr makeInstrSpec( const InstSpecUptr& inOther ){ return std::make_unique<InstrumentSpecies>( *inOther ); }
    inline InstSpecUptr makeInstrSpec( const InstrumentSpecies& inOther ){ return std::make_unique<InstrumentSpecies>( inOther ); }
}
