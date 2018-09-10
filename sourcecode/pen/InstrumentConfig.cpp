#include "pen/InstrumentConfig.h"
#include "ezxml/ezxml.h"
#include "pen/constants.h"

namespace scriabin
{
    InstrumentConfig::InstrumentConfig()
    : mySpecies{}
    {
        
    }
    
    
    const InstrumentSpecies& 
    InstrumentConfig::getSpecies( const std::string& inId ) const
    {
        return *mySpecies.at( inId );
    }
    
    
    
    InstrumentConfig::InstrumentConfig( const InstrumentConfig& other )
    : InstrumentConfig{}
    {
        copyState( other );
    }
    
    
    InstrumentConfig::InstrumentConfig( InstrumentConfig&& other )
    : InstrumentConfig{}
    {
        moveState( std::move( other ) );
    }
    
    
    InstrumentConfig&
    InstrumentConfig::operator=( const InstrumentConfig& other )
    {
        copyState( other );
        return *this;
    }
    
    
    InstrumentConfig&
    InstrumentConfig::operator=( InstrumentConfig&& other )
    {
        moveState( std::move( other ) );
        return *this;
    }

    
    template < typename ITER, typename STR >
    bool is( const ITER& i, const STR& s )
    {
        const bool isTrue = i->getName() == s;
        return isTrue;
    }
    
    template < typename ITER, typename STR >
    ITER child( const ITER& i, const STR& s )
    {
        auto iter = i->begin();
        const auto e = iter->end();
        
        for( ; iter != e; ++iter )
        {
            if( is( iter, s ) )
            {
                return iter;
            }
        }
        
        throw std::runtime_error{ std::string{ s } + " not found" };
    }
    
    template < typename ITER, typename STR >
    std::string sval( const ITER& i, const STR& s )
    {
        const auto c = child( i, s );
        return c->getValue();
    }
    
    
    template < typename ITER >
    std::string name( const ITER& i )
    {
        return sval( i, "name" );
    }
    
    InstrumentConfig::InstrumentConfig( const ezxml::XDoc& inConfig )
    : InstrumentConfig{}
    {
        int middleC = C4_MIDI_NUMBER;
        int middleCOcttave = C4_MIDI_NUMBER;
        
        const auto& r = inConfig.getRoot();
        
        auto i = r->begin();
        auto e = r->end();
        
        for( ; i != e; ++i )
        {
            if( is( i, "middle-c-note-number" ) )
            {
                const auto c4str = i->getValue();
                const int c4parsed = std::stoi( c4str );
                middleC = c4parsed;
            }
            else if( is( i, "middle-c-octave" ) )
            {
                const auto octStr = i->getValue();
                const int octParsed = std::stoi( octStr );
                middleCOcttave = octParsed;
            }
            else if( is( i, "kingdom" ) )
            {
                parseKingdom( i );
            }
        }
    }
    
    void
    InstrumentConfig::parseGeneric( const ezxml::XElementIterator& root, InstrumentClassification& ioCls, std::string& ioIdField, const char* const inElementName, func inFunc )
    {
        auto i = root->begin();
        auto e = root->end();
        ioIdField = sval( root, "id" );
        
        for( ; i != e; ++i )
        {
            if( is( i, inElementName ) )
            {
                (this->*inFunc)( i, ioCls );
            }
        }
    }
    
    void
    InstrumentConfig::parseKingdom( const ezxml::XElementIterator& root )
    {
        InstrumentClassification cls;
        parseGeneric( root, cls, cls.kingdom, "phylum", &InstrumentConfig::parsePhylum );
    }
    
    void
    InstrumentConfig::parsePhylum( const ezxml::XElementIterator& root, InstrumentClassification& cls )
    {
        parseGeneric( root, cls, cls.phylum, "order", &InstrumentConfig::parseOrder );
    }
    
    void
    InstrumentConfig::parseOrder( const ezxml::XElementIterator& root, InstrumentClassification& cls )
    {
        parseGeneric( root, cls, cls.order, "family", &InstrumentConfig::parseFamily );
    }
    
    void
    InstrumentConfig::parseFamily( const ezxml::XElementIterator& root, InstrumentClassification& cls )
    {
        parseGeneric( root, cls, cls.family, "genus", &InstrumentConfig::parseGenus );
    }
    
    void
    InstrumentConfig::parseGenus( const ezxml::XElementIterator& root, InstrumentClassification& cls )
    {
        parseGeneric( root, cls, cls.genus, "species", &InstrumentConfig::parseSpecies );
    }
    
    void
    InstrumentConfig::parseSpecies( const ezxml::XElementIterator& root, InstrumentClassification& cls )
    {
        const std::string id = sval( root, "id" );
        InstSpecUptr inst{ makeInstrSpec( id ) };
        inst->classification = cls;
        inst->name = name( root );
        cls.species = id;
        
        mySpecies.emplace( inst->id(), std::move( inst ) );
        inst = nullptr;
    }
    
    void
    InstrumentConfig::copyState( const InstrumentConfig& other )
    {
        this->mySpecies.clear();
        
        for( const auto& pair : other.mySpecies )
        {
            this->mySpecies.emplace( pair.first, makeInstrSpec( *pair.second ) );
        }
    }
    
    
    void
    InstrumentConfig::moveState(  InstrumentConfig&& other )
    {
        mySpecies = std::move( other.mySpecies );
    }
    
//Phylum: Winds - Strings - Percussion
//Order: Woodwinds
//Family: Double Reeds
//Genus: Bassoons
//Species: Contra Bassoon
    
}
