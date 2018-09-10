#include "StrettoState.h"

namespace scriabin
{
    StrettoState::StrettoState( StrettoFacts inFacts )
    : myMeasureIndex{ 0 }
    , myNoteInMeasureIndex{ 0 }
    , myNoteInPhraseIndex{ 0 }
    , myNoteInSectionIndex{ 0 }
    , myBeatsPerMeasure{ inFacts.beatsPerMeasure }
    , mySectionLengthMeasures{ -1 }
    , myPhraseLengthMeasures{ inFacts.phraseLengthMeasures }
    , myPhraseTopNoteIndex{ inFacts.topNoteIndex }
    , mySectonLengthPhrases{ -1 }
    , myCounters{}
    {
//        auto actualLengthMeasures = inFacts.sectionLengthMinMeasures;
        auto actualLengthPhrases = inFacts.sectionLengthMinMeasures / inFacts.phraseLengthMeasures;
        
        if( inFacts.sectionLengthMinMeasures % inFacts.phraseLengthMeasures != 0 )
        {
            ++actualLengthPhrases;
        }
        mySectonLengthPhrases = actualLengthPhrases;
        mySectionLengthMeasures = actualLengthPhrases * myPhraseLengthMeasures;
    }

///////////////////////////////////////////////////////////////////
// public const ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

    int
    StrettoState::getMeasureIndex() const
    {
        return myMeasureIndex;
    }
    
    
    int
    StrettoState::getNoteInMeasureIndex() const
    {
        return myNoteInMeasureIndex;
    }
    
    
    int
    StrettoState::getNoteInPhraseIndex() const
    {
        return myNoteInPhraseIndex;
    }
    
    
    int
    StrettoState::getNoteInSectionIndex() const
    {
        return myNoteInSectionIndex;
    }


    int
    StrettoState::getBeatsPerMeasure() const
    {
        return myBeatsPerMeasure;
    }
    

    int
    StrettoState::getSectionLengthMeasures() const
    {
        return mySectionLengthMeasures;
    }
    

    int
    StrettoState::getPhraseLengthMeasures() const
    {
        return myPhraseLengthMeasures;
    }
    

    int
    StrettoState::getPhraseTopNoteIndex() const
    {
        return myPhraseTopNoteIndex;
    }
    

    int
    StrettoState::getSectionLengthNotes() const
    {
        return getSectionLengthMeasures() * getBeatsPerMeasure();
    }
    
    
    int
    StrettoState::getSectionLengthPhrases() const
    {
        const auto plm = getPhraseLengthMeasures();
        const auto slm = getSectionLengthMeasures();
        auto result = slm / plm;
        
        if( slm % plm != 0 )
        {
            ++result;
        }
        
        return result;
    }
    

    int
    StrettoState::getPhraseLengthNotes() const
    {
        return getPhraseLengthMeasures() * getBeatsPerMeasure();   
    }
    
    
    const Counter&
    StrettoState::getCounter( const std::string& inName ) const
    {
        return *findCounterConst( inName );
    }
    
    
    bool
    StrettoState::getIsCounterZero( const std::string& inName ) const
    {
        return getCounter( inName ).current == 0;
    }
    

    bool
    StrettoState::getIsFirstNoteOfPhrase() const
    {
        return getNoteInPhraseIndex() == 0;
    }
    
    
    bool
    StrettoState::getIsLastNoteOfPhrase() const
    {
        return getNoteInPhraseIndex() == ( getPhraseLengthNotes() - 1 );
    }
    
    
    bool
    StrettoState::getIsTopNoteOfPhrase() const
    {
        return getNoteInPhraseIndex() == getPhraseTopNoteIndex();
    }
 
    
    bool
    StrettoState::getIsFirstNoteOfMeasure() const
    {
        return getNoteInMeasureIndex() == 0;
    }


///////////////////////////////////////////////////////////////////
// public mutable /////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

    void
    StrettoState::addCounter( Counter inCounter )
    {
        myCounters.push_back( inCounter );
    }
    
    
    Counter&
    StrettoState::getCounterMutable( const std::string& inName )
    {
        return *findCounter( inName );
    }
    
    
    void
    StrettoState::removeCounter( const std::string& inName )
    {
        const auto it = findCounterConst( inName );
        myCounters.erase( it );
    }
    
///////////////////////////////////////////////////////////////////
// public operators ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
    
    void
    StrettoState::operator++()
    {
        ++myNoteInSectionIndex;
        
        ++myNoteInPhraseIndex;
        if( myNoteInPhraseIndex >= getPhraseLengthNotes() )
        {
            myNoteInPhraseIndex = 0;
        }
        
        ++myNoteInMeasureIndex;
        if( myNoteInMeasureIndex >= getBeatsPerMeasure() )
        {
            myNoteInMeasureIndex = 0;
        }
        
        for( auto& counter : myCounters )
        {
            ++counter.current;
            if( counter.current >= counter.length )
            {
                counter.current = 0;
                ++counter.cycleCount;
            }
        }
    }

///////////////////////////////////////////////////////////////////
// private ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

    std::vector<Counter>::iterator
    StrettoState::findCounter( const std::string& inName )
    {
        const auto lam = [&]( const Counter& inCounter )
        {
            if( inCounter.name == inName )
            {
                return true;
            }
            
            return false;
        };
        
        const auto it = std::find_if( std::begin( myCounters ), std::end( myCounters ), lam );
        
        if( it == std::end( myCounters ) )
        {
            throw std::runtime_error( "not found" );
        }
        
        return it;
    }

    
    std::vector<Counter>::const_iterator
    StrettoState::findCounterConst( const std::string& inName ) const
    {
        const auto lam = [&]( const Counter& inCounter )
        {
            if( inCounter.name == inName )
            {
                return true;
            }
            
            return false;
        };
        
        const auto it = std::find_if( std::cbegin( myCounters ), std::cend( myCounters ), lam );
        
        if( it == std::cend( myCounters ) )
        {
            throw std::runtime_error( "not found" );
        }
        
        return it;
    }
}
