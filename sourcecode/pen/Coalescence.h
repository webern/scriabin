#pragma once

#include "mx/api/ScoreData.h"
#include "pen/Atom.h"
#include <string>
#include <vector>
#include <sstream>

namespace pen
{
    using MxNoteStreams = std::map<int, std::vector<mx::api::NoteData>>;
    using Atoms = std::vector<Atom>;
    using AtomStreams = std::map<int, Atoms>;
    
    class Coalescence
    {
    public:
        Coalescence( std::string inputFilepath, std::string outputFilepath );
        void doEverthing();
        
    private:
        mx::api::ScoreData myScore;
        std::string myInFilepath;
        std::string myOutFilepath;
        std::vector<bool> myRandVec;
        std::vector<bool>::const_iterator myRandIter;
        std::vector<bool>::const_iterator myRandEnd;
        
    private:
        void initSelfScore();
        MxNoteStreams getInputNotes() const;
        bool rbool();
        
    private:
        static void reverseAtoms( Atoms& ioAtoms );
        static void reverseStreams( AtomStreams& ioStreams );
        static AtomStreams extractStreams( const MxNoteStreams& inNotes );
        static mx::api::ScoreData createEmptyScore( const std::string& title );
        static void addInstrument( mx::api::ScoreData& ioScore,
                                   const std::string& id,
                                   const std::string& name,
                                   const std::string& abbr,
                                   mx::api::SoundID soundID,
                                   const mx::api::ClefData clef );
        static void appendMeasures( mx::api::ScoreData& ioScore, int numMeasures );
    };
}
