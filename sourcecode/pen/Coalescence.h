#pragma once

#include "mx/api/ScoreData.h"
#include "pen/Atom.h"
#include <string>
#include <vector>
#include <sstream>

namespace pen
{
    using MxNoteStreams = std::map<int, std::vector<mx::api::NoteData>>;
    using AtomStreams = std::map<int, std::vector<Atom>>;
    
    class Coalescence
    {
    public:
        Coalescence( std::string inputFilepath, std::string outputFilepath );
        void doEverthing();
        
    private:
        mx::api::ScoreData myScore;
        std::string myInFilepath;
        std::string myOutFilepath;
        
    private:
        void initSelfScore();
        MxNoteStreams getInputNotes() const;
        
        
    private:
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
