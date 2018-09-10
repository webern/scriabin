#pragma once
#include <string>
#include <vector>

namespace scriabin
{
    struct Counter
    {
        std::string name;
        int length;
        int current;
        int cycleCount;
        
        Counter() : name{}, length{ 1 }, current{ 0 }, cycleCount{ 0 } {}
        Counter( std::string inName, int inLength, int inCurrent = 0, int inCycleCount = 0 )
        : name{ inName }
        , length{ inLength }
        , current{ inCurrent }
        , cycleCount{ inCycleCount }
        {
            
        }
    };
    
    struct StrettoFacts
    {
        int phraseLengthMeasures = 0;
        int sectionLengthMinMeasures = 0;
        int beatsPerMeasure = 0;
        int topNoteIndex = 0;
    };
    
    class StrettoState
    {
    public:
        StrettoState( StrettoFacts inFacts );
    
    public:
        int getMeasureIndex() const;
        int getNoteInMeasureIndex() const;
        int getNoteInPhraseIndex() const;
        int getNoteInSectionIndex() const;
        int getBeatsPerMeasure() const;
        int getSectionLengthMeasures() const;
        int getPhraseLengthMeasures() const;
        int getPhraseTopNoteIndex() const;
        int getSectionLengthNotes() const;
        int getPhraseLengthNotes() const;
        int getSectionLengthPhrases() const;
        const Counter& getCounter( const std::string& inName ) const;
        bool getIsCounterZero( const std::string& inName ) const;
        bool getIsFirstNoteOfPhrase() const;
        bool getIsLastNoteOfPhrase() const;
        bool getIsTopNoteOfPhrase() const;
        bool getIsFirstNoteOfMeasure() const;
        
    public:
        void addCounter( Counter inCounter );
        Counter& getCounterMutable( const std::string& inName );
        void removeCounter( const std::string& inName );
        
    public:
        void operator++();
        
    private:
        int myMeasureIndex;
        int myNoteInMeasureIndex;
        int myNoteInPhraseIndex;
        int myNoteInSectionIndex;
        int myBeatsPerMeasure;
        int mySectionLengthMeasures;
        int myPhraseLengthMeasures;
        int myPhraseTopNoteIndex;
        int mySectonLengthPhrases;
        std::vector<Counter> myCounters;
        
    private:
        std::vector<Counter>::iterator findCounter( const std::string& inName );
        std::vector<Counter>::const_iterator findCounterConst( const std::string& inName ) const;
    };
}

