#pragma once

namespace pen
{
    class StrettoState
    {
    public:
        StrettoState();
    
    public:
        int getMeasureIndex() const;
        int getBeatsPerMeasure() const;
        int getSectionLengthMeasures() const;
        int getPhraseLengthMeasures() const;
        int getPhraseTopNoteIndex() const;
        int getSectionLengthNotes() const;
        int getPhraseLengthNotes() const;
    
    public:
        void setMeasureIndex( int inVal );
        void setBeatsPerMeasure( int inValue );
        void setSectionLengthMeasures( int inValue );
        void setPhraseLengthMeasures( int inValue );
        void setPhraseTopNoteIndex( int inValue );

    public:
        void operator++();
        
    private:
        int myMeasureIndex;
        int myBeatsPerMeasure;
        int mySectionLengthMeasures;
        int myPhraseLengthMeasures;
        int myPhraseTopNoteIndex;
        
    private:
        void priv();
    };
}

