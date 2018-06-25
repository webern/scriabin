#include "pen/Coalescence.h"
#include "../test/PEN_PATH.h"
#include "mx/api/DocumentManager.h"
#include <vector>
#include <map>

namespace pen
{
    Coalescence::Coalescence()
    : myScore{}
    {
        
    }
    
    
    void
    Coalescence::doEverthing()
    {
        const CoalescenceConsts c;
        auto& dmgr = mx::api::DocumentManager::getInstance();
        const auto inFilepath = MUSIC_INPUT_FILES_DIRECTORY() + "/" + c.inFilename;
        const auto outFilepath = MUSIC_OUTPUT_FILES_DIRECTORY() + "/" + c.outFilename;
        const auto inID = dmgr.createFromFile( inFilepath );
        const auto input = dmgr.getData( inID );
        dmgr.destroyDocument( inID );
        
        int partIndex = 0;
        std::map<int, std::vector<mx::api::NoteData>> partNoteStreams;
        for( const auto& part : input.parts )
        {
            for( const auto& measure : part.measures )
            {
                const auto& staff = measure.staves.at( 0 );
                const auto& voice = staff.voices.at( 0 );
                const auto& notes = voice.notes;
                
                for( const auto& note : notes )
                {
                    partNoteStreams[partIndex].push_back( note );
                }
            }
            ++partIndex;
        }
        
        std::map<int, std::vector<Atom>> partAtomsStreams;
        
        for( const auto& origPair : partNoteStreams )
        {
            for( const auto& note : origPair.second )
            {
                Atom a;
                if( !note.isRest )
                {
                    a.octave = note.pitchData.octave;
                    a.alter = note.pitchData.alter;
                    a.setStep( note.pitchData.step );
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
                
                for( int i = 0; i < numNotes; ++i )
                {
                    partAtomsStreams[origPair.first].push_back( a );
                }
            }
        }
        
        // fix a problem
        partAtomsStreams.at( 2 ) = partAtomsStreams.at( 0 );
        
        for( auto& note : partAtomsStreams.at( 2 ) )
        {
            note.octave = note.octave - 1;
        }
        
        // reverse the stream
        for( auto& pair : partAtomsStreams )
        {
            std::reverse(std::begin( pair.second ), std::end( pair.second ) );
        }

        const std::vector<bool> randVec = { true, true, false, false, true, false, true, false, false, false, true, true, true, true, false, true, true, false, false, false, false, false, true, false, false, false, false, true, true, true, false, false, false, true, true, true, false, false, true, true, false, false, true, false, false, true, true, true, true, true, true, false, true, false, true, false, true, false, false, true, true, false, false, true, false, true, false, false, false, false, false, false, true, false, true };
        auto randIter = std::cbegin( randVec );
        const auto randEnd = std::cend( randVec );

        const auto rand = [&]()
        {
            const bool val = *randIter;
            if( randIter == randEnd )
            {
                randIter = std::cbegin( randVec );
            }
            else
            {
                ++randIter;
            }
            
            return val;
        };
        
        int masterIndex = 0;
        
        for( auto& pair : partAtomsStreams )
        {
            auto& stream = pair.second;
            decltype( pair.second ) writer;
            std::copy( std::cbegin( stream ), std::cend( stream ), std::back_inserter( writer ) );
            
            // final repeats, eight times
            for( int i = 0; i < 7; ++i, ++masterIndex )
            {
                std::copy( std::begin( writer ), std::end( writer ), std::back_inserter( stream ) );
            }

            // eight times with increasing rests
            for( int i = 0; i < 8; ++i, ++masterIndex )
            {
                for( auto& note : writer )
                {
                    if( masterIndex % 37 == 0 && rand() )
                    {
                        note.alter = 0;
                        note.octave = 0;
                        note.step = -1;
                        note.name = "rest";
                    }
                    
                    ++masterIndex;
                    std::copy( std::begin( writer ), std::end( writer ), std::back_inserter( stream ) );
                }
            }
            
            // eight times with increasing augmentation
            for( int i = 0; i < 8; ++i, ++masterIndex )
            {
                for( auto noteIter = writer.begin(); noteIter != writer.end(); ++noteIter, ++masterIndex )
                {
                    if( masterIndex % 3 == 0 && rand() )
                    {
                        auto reps = ( masterIndex % ( i + 2 ) + 1 );
                        const auto note = *noteIter;
                        for( int j = 0; j < reps; ++j )
                        {
                            noteIter = writer.insert( noteIter, note );
                            ++noteIter;
                            
                            if( noteIter == writer.end() )
                            {
                                break;
                            }
                        }
                    }
                }
                std::copy( std::begin( writer ), std::end( writer ), std::back_inserter( stream ) );
            }
        }
        
        // find the smallest stream
        int smallest = -1;
        
        for( const auto& pait : partAtomsStreams )
        {
            if( smallest == -1 || pait.second.size() < smallest )
            {
                smallest = pait.second.size();
            }
        }
        
        // delete extra notes based on smallest
        for( auto& pair : partAtomsStreams )
        {
            if( pair.second.size() > smallest )
            {
                pair.second.resize( smallest );
            }
        }
        
        // reverse the again to put it back into frontwards order stream
        for( auto& pair : partAtomsStreams )
        {
            std::reverse(std::begin( pair.second ), std::end( pair.second ) );
        }

        myScore = mx::api::ScoreData{};
        mx::api::ScoreData myScore = createEmptyScore( "June 3 Coalescence Practice" );
        appendMeasures( myScore, 7 );
        
        // write notes into score
        
        for( int partIndex = 0; partIndex < partAtomsStreams.size(); ++partIndex )
        {
            int measureIndex = 0;
            int eighthIndex = 0;
            const auto& noteStream = partAtomsStreams.at( partIndex );
            auto& outPart = myScore.parts.at( partIndex );
            
            for( const auto& note : noteStream )
            {
                while( measureIndex > outPart.measures.size() - 1 )
                {
                    appendMeasures( myScore, 1 );
                }
                
                auto& measure = outPart.measures.at( measureIndex );
                mx::api::NoteData theNote;
                theNote.tickTimePosition = eighthIndex * ( myScore.ticksPerQuarter / 2 );
                theNote.durationData.durationTimeTicks = myScore.ticksPerQuarter / 2;
                theNote.durationData.durationName = mx::api::DurationName::eighth;
                
                if( note.step == -1 )
                {
                    theNote.isRest = true;
                }
                else
                {
                    theNote.pitchData.alter = note.alter;
                    theNote.pitchData.octave = note.octave;
                    theNote.pitchData.step = note.getMxStep();
                    
                    if( note.alter < 0 )
                    {
                        theNote.pitchData.accidental = mx::api::Accidental::flat;
                    }
                    else if ( note.alter > 0 )
                    {
                        theNote.pitchData.accidental = mx::api::Accidental::sharp;
                    }
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
        
        const auto oID = dmgr.createFromScore( myScore );
        dmgr.writeToFile( oID, outFilepath );
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
