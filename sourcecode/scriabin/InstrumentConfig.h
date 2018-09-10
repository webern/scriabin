#pragma once
#include "scriabin/InstrumentSpecies.h"
#include <vector>
#include <map>

namespace ezxml
{
    class XDoc;
    class XElementIterator;
}

namespace scriabin
{
    class InstrumentConfig
    {
    public:
        InstrumentConfig();
        InstrumentConfig( const ezxml::XDoc& inConfig );
        InstrumentConfig( const InstrumentConfig& other );
        InstrumentConfig( InstrumentConfig&& other );
        InstrumentConfig& operator=( const InstrumentConfig& other );
        InstrumentConfig& operator=( InstrumentConfig&& other );
    
    public:
        const InstrumentSpecies& getSpecies( const std::string& inId ) const;
        
    private:
        using InstSpecMap = std::map<const std::string, InstSpecUptr>;
        InstSpecMap mySpecies;

    private:
        typedef void (InstrumentConfig::*func)( const ezxml::XElementIterator& root, InstrumentClassification& cls );
        void parseGeneric( const ezxml::XElementIterator& root, InstrumentClassification& ioCls, std::string& ioIdField, const char* const inElementName, func inFunc );
        void parseKingdom( const ezxml::XElementIterator& root );
        void parsePhylum( const ezxml::XElementIterator& root, InstrumentClassification& cls );
        void parseOrder( const ezxml::XElementIterator& root, InstrumentClassification& cls );
        void parseFamily( const ezxml::XElementIterator& root, InstrumentClassification& cls );
        void parseGenus( const ezxml::XElementIterator& root, InstrumentClassification& cls );
        void parseSpecies( const ezxml::XElementIterator& root, InstrumentClassification& cls );
        void copyState( const InstrumentConfig& other );
        void moveState(  InstrumentConfig&& other );
    };
}
