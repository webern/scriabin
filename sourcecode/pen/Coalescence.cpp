#include "pen/Coalescence.h"
#include "pen/Prob.h"
#include "../test/PEN_PATH.h"
#include "mx/api/DocumentManager.h"
#include <vector>
#include <map>

namespace pen
{
    Coalescence::Coalescence( std::string inputFilepath, std::string outputFilepath )
    : myScore{}
    , myInFilepath{ std::move( inputFilepath ) }
    , myOutFilepath{ std::move( outputFilepath ) }
    , myRandVec{ true, true, false, false, true, false, true, false, false, false, true, true, true, true, false, true, true, false, false, false, false, false, true, false, false, false, false, true, true, true, false, false, false, true, true, true, false, false, true, true, false, false, true, false, false, true, true, true, true, true, true, false, true, false, true, false, true, false, false, true, true, false, false, true, false, true, false, false, false, false, false, false, true, false, true }
    , myRandIter{}
    , myRandEnd{}
    {
        myRandIter = myRandVec.cbegin();
        myRandEnd = myRandVec.cend();
    }
    
    
    void
    Coalescence::initSelfScore()
    {
        myScore = mx::api::ScoreData{};
        myScore = createEmptyScore( "Coalescence" );
    }
    
    
    MxNoteStreams
    Coalescence::getInputNotes() const
    {
        auto& dmgr = mx::api::DocumentManager::getInstance();
        const auto inID = dmgr.createFromFile( myInFilepath );
        const auto input = dmgr.getData( inID );
        dmgr.destroyDocument( inID );
        MxNoteStreams inputNotes;
        int partIndex = 0;
        
        for( const auto& part : input.parts )
        {
            for( const auto& measure : part.measures )
            {
                const auto& staff = measure.staves.at( 0 );
                const auto& voice = staff.voices.at( 0 );
                const auto& notes = voice.notes;
                
                for( const auto& note : notes )
                {
                    inputNotes[partIndex].push_back( note );
                }
            }
            ++partIndex;
        }
        
        return inputNotes;
    }
    
    
    AtomStreams
    Coalescence::extractStreams( const MxNoteStreams& inNotes )
    {
        AtomStreams streams;
        
        for( const auto& origPair : inNotes )
        {
            for( const auto& note : origPair.second )
            {
                Atom a;
                if( !note.isRest )
                {
                    a.setFromMx( note.pitchData );
                }
                
                int numNotes = 1;
                
                if( note.durationData.durationName == mx::api::DurationName::quarter )
                {
                    numNotes = 2;
                    if( note.durationData.durationDots == 1 )
                    {
                        numNotes = 3;
                    }
                }
                
                a.updateName();
                
                for( int i = 0; i < numNotes; ++i )
                {
                    streams[origPair.first].push_back( a );
                }
            }
        }
        
        // fix a problem with the viola part by copying violin 1
        // and transposing it down two octaves
        streams.at( 2 ) = streams.at( 0 );
        
        for( auto& note : streams.at( 2 ) )
        {
            note.setOctave( note.getOctave() - 1 );
        }
        
        return streams;
    }
    
    
    void
    Coalescence::reverseAtoms( Atoms& ioAtoms )
    {
        std::reverse(std::begin( ioAtoms ), std::end( ioAtoms ) );
    }
    
    
    void
    Coalescence::reverseStreams( AtomStreams& ioStreams )
    {
        for( auto& pair : ioStreams )
        {
            reverseAtoms( pair.second );
        }
    }
    
    
    bool
    Coalescence::rbool()
    {
        const bool val = *myRandIter;
        ++myRandIter;
        
        if( myRandIter == myRandEnd )
        {
            myRandIter = std::cbegin( myRandVec );
        }
        
        return val;
    }
    
    
    void
    Coalescence::writeMusic( const Atoms& inAtomsToWrite, Atoms& ioAtomsToAppendTo, int numTimes )
    {
        for( int i = 0; i < numTimes; ++i )
        {
            std::copy( std::cbegin( inAtomsToWrite ), std::cend( inAtomsToWrite ), std::back_inserter( ioAtomsToAppendTo ) );
        }
    }
    
    
    void
    Coalescence::writeMusic( const AtomStreams& inStreamsToWrite, AtomStreams& ioStreamsToAppendTo, int numTimes )
    {
        if( inStreamsToWrite.size() != ioStreamsToAppendTo.size() )
        {
            std::runtime_error( "Coalescence::writeMusic: maps must be same size" );
        }
        
        auto inIter = inStreamsToWrite.cbegin();
        auto outIter = ioStreamsToAppendTo.begin();
        const auto e = inStreamsToWrite.cend();
        
        for( ; inIter != e; ++inIter, ++outIter )
        {
            writeMusic( inIter->second, outIter->second, numTimes );
        }
    }
    
    
    void
    Coalescence::doPenultimateCoalescing( AtomStreams& ioPatternStreams, AtomStreams& ioOutputStreams )
    {
        // add one rest to the cello
        {
            const int pidx = 3;
            const auto insertLoc = ioPatternStreams.at( pidx ).cbegin();
            ioPatternStreams.at( pidx ).insert( insertLoc, Atom{} );
        }
        
        writeMusic( ioPatternStreams, ioOutputStreams, 2 );
        
        // add two rests to the first violin
        {
            const int pidx = 0;
            auto insertLoc = ioPatternStreams.at( pidx ).cbegin();
            insertLoc = ioPatternStreams.at( pidx ).insert( insertLoc, Atom{} );
            insertLoc = ioPatternStreams.at( pidx ).insert( insertLoc, Atom{} );
        }
        
        writeMusic( ioPatternStreams, ioOutputStreams, 2 );
        
        // add three rests to the second violin
        {
            const int pidx = 1;
            auto insertLoc = ioPatternStreams.at( pidx ).cbegin();
            insertLoc = ioPatternStreams.at( pidx ).insert( insertLoc, Atom{} );
            insertLoc = ioPatternStreams.at( pidx ).insert( insertLoc, Atom{} );
            insertLoc = ioPatternStreams.at( pidx ).insert( insertLoc, Atom{} );
        }
        
        writeMusic( ioPatternStreams, ioOutputStreams, 2 );
        
        // add four rests to the viola
        {
            const int pidx = 2;
            auto insertLoc = ioPatternStreams.at( pidx ).cbegin();
            insertLoc = ioPatternStreams.at( pidx ).insert( insertLoc, Atom{} );
            insertLoc = ioPatternStreams.at( pidx ).insert( insertLoc, Atom{} );
            insertLoc = ioPatternStreams.at( pidx ).insert( insertLoc, Atom{} );
            insertLoc = ioPatternStreams.at( pidx ).insert( insertLoc, Atom{} );
        }
        
        writeMusic( ioPatternStreams, ioOutputStreams, 2 );
    }
    
    
    void
    Coalescence::doEverthing()
    {
        initSelfScore();
        const MxNoteStreams inputNotes = getInputNotes();
        const AtomStreams originalMusic = extractStreams( inputNotes );
        AtomStreams outMusic = originalMusic;
        reverseStreams( outMusic );
        const AtomStreams originalReversedMusic = outMusic;
        AtomStreams patternStreams = originalReversedMusic;
        doPenultimateCoalescing( patternStreams, outMusic );

        Prob boolGen{ DIGITS_DAT_PATH() };
        CoalescenceParams params;
        params.minR = 0;
        params.maxR = 1;
        params.rInc = 1;
        params.rTier = 0;
        
        params.minP = 0;
        params.maxP = 25;
        params.pInc = 1;
        params.pTier = 2;
        params.numLoops = 8;
        
        doCoalescingLoop( params, patternStreams, outMusic, boolGen );
        
        shortenStreamsToMatchLengthOfShortestStream( outMusic );
        reverseStreams( outMusic );
        writeMusic( originalMusic, outMusic, 32 );
        writeStreamsToScore( outMusic, myScore );
        auto& dmgr = mx::api::DocumentManager::getInstance();
        const auto oID = dmgr.createFromScore( myScore );
        dmgr.writeToFile( oID, myOutFilepath );
    }
    
    
    void
    Coalescence::doCoalescingLoop( const CoalescenceParams& params,
                                   AtomStreams& ioPatternStreams,
                                   AtomStreams& ioOutputStreams,
                                   Prob& ioProb )
    {
        int rCurrent = params.minR;
        int pCurrent = params.minP;
        
        for( int loopCounter = 0; loopCounter < params.numLoops; ++loopCounter )
        {
            for( int p = 0; p < 4; ++p )
            {
                const int restProb = rCurrent + ( params.rTier * p );
                const int repeatProb = pCurrent + ( params.pTier * p );
                
                for( auto it = ioPatternStreams.at( p ).begin(); it != ioPatternStreams.at( p ).end(); ++it )
                {
                    const bool doRest = ioProb.get( restProb );
                    const bool doRepeat = ioProb.get( repeatProb );
                    
                    if( doRest )
                    {
                        *it = Atom{};
                    }
                    
                    if( doRepeat )
                    {
                        it = ioPatternStreams.at( p ).insert( it, *it );
                    }
                }
            }
            
            writeMusic( ioPatternStreams, ioOutputStreams, 1 );
            
            rCurrent += params.rInc;
            pCurrent += params.pInc;
            
            if( rCurrent > params.maxR )
            {
                rCurrent = params.maxR;
            }
            
            if( pCurrent > params.maxP )
            {
                rCurrent = params.maxP;
            }
        }
    }
    
    void
    Coalescence::shortenStreamsToMatchLengthOfShortestStream( AtomStreams& ioStreams )
    {
        int smallest = findIndexOfShortestStream( ioStreams );
        
        // delete extra notes based on smallest
        for( auto& pair : ioStreams )
        {
            if( static_cast<int>( pair.second.size() ) > smallest )
            {
                pair.second.resize( static_cast<size_t>( smallest ) );
            }
        }
    }
    
    
    int
    Coalescence::findIndexOfShortestStream( const AtomStreams& inStreams )
    {
        // find the smallest stream
        int smallest = -1;
        
        for( const auto& streamPair : inStreams )
        {
            if( smallest == -1 || static_cast<int>( streamPair.second.size() ) < smallest )
            {
                smallest = static_cast<int>( streamPair.second.size() );
            }
        }
        
        return smallest;
    }
    
    
    void
    Coalescence::writeStreamsToScore( const AtomStreams& inStreams, mx::api::ScoreData& ioScore )
    {
        for( int p = 0; p < static_cast<int>( inStreams.size() ); ++p )
        {
            int measureIndex = 0;
            int eighthIndex = 0;
            const auto& noteStream = inStreams.at( p );
            writeStream( p, measureIndex, eighthIndex, noteStream, ioScore );
        }
    }
    
    
    void
    Coalescence::writeStream( int partIndex,
                              int startingMeasureIndex,
                              int startingEighthIndex,
                              const Atoms& inAtoms,
                              mx::api::ScoreData& ioScore )
    {
        auto measureIndex = startingMeasureIndex;
        auto eighthIndex = startingEighthIndex;
        
        for( const auto& atom : inAtoms )
        {
            auto& part = ioScore.parts.at( static_cast<size_t>( partIndex) );
            
            while( measureIndex > static_cast<int>( part.measures.size() ) - 1 )
            {
                appendMeasures( ioScore, 1 );
            }
            
            auto& measure = part.measures.at( static_cast<size_t>( measureIndex ) );
            mx::api::NoteData theNote;
            theNote.tickTimePosition = eighthIndex * ( ioScore.ticksPerQuarter / 2 );
            theNote.durationData.durationTimeTicks = ioScore.ticksPerQuarter / 2;
            theNote.durationData.durationName = mx::api::DurationName::eighth;
            
            if( atom.getStep() == -1 )
            {
                theNote.isRest = true;
            }
            else
            {
                theNote.pitchData = atom.getMxPitchData();
            }
            
            measure.staves.at( 0 ).voices.at( 0 ).notes.push_back( theNote );
            
            if( ( eighthIndex + 1 ) % 6 == 0 )
            {
                ++measureIndex;
                eighthIndex = 0;
            }
            else
            {
                ++eighthIndex;
            }
        }
    }
    
    
    mx::api::ScoreData
    Coalescence::createEmptyScore( const std::string& title )
    {
        mx::api::ScoreData score;
        score.workTitle = title;
        mx::api::ClefData treble;
        treble.setTreble();
        mx::api::ClefData alto;
        alto.setAlto();
        mx::api::ClefData bass;
        bass.setBass();
        addInstrument( score, "VN1", "Violin 1", "Vln 1", mx::api::SoundID::stringsViolin, treble );
        addInstrument( score, "VN2", "Violin 2", "Vln 2", mx::api::SoundID::stringsViolin, treble );
        addInstrument( score, "VLA", "Viola", "Vla", mx::api::SoundID::stringsViola, alto );
        addInstrument( score, "VLC", "Cello", "Vlc", mx::api::SoundID::stringsCello, bass );
        mx::api::PartGroupData grp;
        grp.firstPartIndex = 0;
        grp.lastPartIndex = 3;
        grp.bracketType = mx::api::BracketType::bracket;
        score.partGroups.push_back( grp );
        return score;
    }
    
    
    void
    Coalescence::addInstrument( mx::api::ScoreData& ioScore,
                          const std::string& id,
                          const std::string& name,
                          const std::string& abbr,
                          mx::api::SoundID soundID,
                          const mx::api::ClefData clef  )
    {
        ioScore.parts.emplace_back();
        ioScore.parts.back().uniqueId = id;
        ioScore.parts.back().name = name;
        ioScore.parts.back().abbreviation = abbr;
        ioScore.parts.back().instrumentData.uniqueId = ioScore.parts.back().uniqueId + "-I";
        ioScore.parts.back().displayName = ioScore.parts.back().name;
        ioScore.parts.back().displayAbbreviation = ioScore.parts.back().abbreviation;
        ioScore.parts.back().instrumentData.soundID = soundID;
        ioScore.parts.back().instrumentData.soloOrEnsemble = mx::api::SoloOrEnsemble::solo;
        
        ioScore.parts.back().measures.emplace_back();
        ioScore.parts.back().measures.back().staves.emplace_back();
        mx::api::TimeSignatureData tsd;
        tsd.beats = 6;
        tsd.beatType = 8;
        tsd.isImplicit = false;
        ioScore.parts.back().measures.back().timeSignature = tsd;
        ioScore.parts.back().measures.back().staves.back().clefs.push_back( clef );
        ioScore.parts.back().measures.back().staves.back().voices[0] = mx::api::VoiceData{};
    }
    
    
    void
    Coalescence::appendMeasures( mx::api::ScoreData& ioScore, int numMeasures )
    {
        for( int x = 0; x < numMeasures; ++x )
        {
            for( size_t partIndex = 0; partIndex < ioScore.parts.size(); ++partIndex )
            {
                const auto lastMeasure = ioScore.parts.at( partIndex ).measures.back();
                mx::api::MeasureData prototype;
                prototype.timeSignature = lastMeasure.timeSignature;
                prototype.timeSignature.isImplicit = true;
                
                for( const auto& staff : lastMeasure.staves )
                {
                    prototype.staves.emplace_back();
                    for( const auto& voicePair : staff.voices )
                    {
                        prototype.staves.back().voices[voicePair.first] = mx::api::VoiceData{};
                    }
                }
                
                ioScore.parts.at( partIndex ).measures.push_back( prototype );
            }
        }
    }
}
