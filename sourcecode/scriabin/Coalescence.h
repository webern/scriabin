#pragma once

#include "mx/api/ScoreData.h"
#include "scriabin/Atom.h"
#include "scriabin/Prob.h"
#include <string>
#include <vector>
#include <sstream>

namespace scriabin
{
    using MxNoteStreams = std::map<int, std::vector<mx::api::NoteData>>;
    using Atoms = std::vector<Atom>;
    using AtomStreams = std::map<int, Atoms>;
    
    struct CoalescenceParams
    {
        // rest probabilities
        
        // the starting probability that a note will become a rest
        int minR = 0;
        
        // the maximum probability that a note will become a rest
        int maxR = 1;
        
        // the amount that we will increment the rest probability
        // on each iteration of the coalescing loop
        int rInc = 1;
        
        // the amount that we will add to the rest probability
        // for each subsequent part in the inner loop
        int rTier = 0;
        
        // repeat probabilities
        
        // the starting probability that a note will be repeated
        int minP = 0;
        
        // the maximum probability that a note will be repeated
        int maxP = 25;
        
        // the amount that we will increment the repeat probability
        // on each iteration of the coalescing loop
        int pInc = 1;
        
        // the amout that we will add to the repeat probability
        // for each subsequent part in the inner loop
        int pTier = 2;
        
        // number of times to run the coalescing procedure
        int numLoops = 0;
    };
    
    class Coalescence
    {
    public:
        Coalescence( std::string inputFilepath, std::string outputFilepath );
        
        // saves the score to disk but also returns it for inspection
        mx::api::ScoreData doEverthing();
        
    private:
        mx::api::ScoreData myScore;
        std::string myInFilepath;
        std::string myOutFilepath;
        
    private:
        void initSelfScore();
        MxNoteStreams getInputNotes() const;
        
    private:
        static void doSomeAwesomeCoalescing( AtomStreams& ioPatternStreams,
                                             AtomStreams& ioOutputStreams,
                                             Prob& ioProb );
        
        static void expandShortestReps( Atoms& ioPattern,
                                        Prob& ioProb );
        
        static void doCoalescingLoop( const CoalescenceParams& p,
                                      AtomStreams& ioPatternStreams,
                                      AtomStreams& ioOutputStreams,
                                      Prob& ioProb );
        
        static void writeMusic( const AtomStreams& inStreamsToWrite, AtomStreams& ioStreamsToAppendTo, int numTimes );
        static void writeMusic( const Atoms& inAtomsToWrite, Atoms& ioAtomsToAppendTo, int numTimes );
        static void reverseAtoms( Atoms& ioAtoms );
        static void reverseStreams( AtomStreams& ioStreams );
        static AtomStreams extractStreams( const MxNoteStreams& inNotes );
        static void addAccentsToInitialStreams( AtomStreams& ioStreams );
        static mx::api::ScoreData createEmptyScore( const std::string& title );
        static void addInstrument( mx::api::ScoreData& ioScore,
                                   const std::string& id,
                                   const std::string& name,
                                   const std::string& abbr,
                                   mx::api::SoundID soundID,
                                   const mx::api::ClefData clef );
        static void appendMeasures( mx::api::ScoreData& ioScore, int numMeasures );
        static void writeStream( int partIndex,
                                 int startingMeasureIndex,
                                 int startingEighthIndex,
                                 const Atoms& inAtoms,
                                 mx::api::ScoreData& ioScore );
        static void writeStreamsToScore( const AtomStreams& inStreams, mx::api::ScoreData& ioScore );
        static int findIndexOfShortestStream( const AtomStreams& inStreams );
        static void shortenStreamsToMatchLengthOfShortestStream( AtomStreams& ioStreams, int inMultipleOf = -1 );
        static void sneakInAccents( AtomStreams& ioMusic, Prob& ioProb );
        static void doStretto( AtomStreams& ioMusic );
        static int findInsertIndex( const Atoms& inAtoms, Prob& ioProb );
        static void augmentBeginning( AtomStreams& ioOutMusic );
        static void eliminateTriplePlusAccents( AtomStreams& ioStreams );
    };
}
