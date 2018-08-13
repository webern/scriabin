#include "StrettoState.h"

namespace pen
{
    StrettoState::StrettoState()
    : myMeasureIndex{ 0 }
    , myBeatsPerMeasure{ 0 }
    , mySectionLengthMeasures{ 0 }
    , myPhraseLengthMeasures{ 0 }
    , myPhraseTopNoteIndex{ 0 }
    {
        
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
    StrettoState::getPhraseLengthNotes() const
    {
        return getPhraseLengthMeasures() * getBeatsPerMeasure();   
    }

///////////////////////////////////////////////////////////////////
// public mutable /////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

    void
    StrettoState::setMeasureIndex( int inMeasureIndex )
    {
        myMeasureIndex = inMeasureIndex;
    }


    void
    StrettoState::setBeatsPerMeasure( int inValue )
    {
        myBeatsPerMeasure = inValue;
    }
    

    void
    StrettoState::setSectionLengthMeasures( int inValue )
    {
        mySectionLengthMeasures = inValue;
    }
    

    void
    StrettoState::setPhraseLengthMeasures( int inValue )
    {
        myPhraseLengthMeasures = inValue;
    }
    

    void
    StrettoState::setPhraseTopNoteIndex( int inValue )
    {
        myPhraseTopNoteIndex = inValue;
    }

///////////////////////////////////////////////////////////////////
// public operators ///////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
    
    void
    StrettoState::operator++()
    {
        
    }

///////////////////////////////////////////////////////////////////
// private ////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

    void
    StrettoState::priv()
    {

    }

}
