#include "pen/june3.h"
#include "../test/PEN_PATH.h"
#include "mx/api/DocumentManager.h"
#include <vector>
#include <map>

namespace pen
{
    void
    June3::doEverthing()
    {
        const June3Constants c;
        auto& dmgr = mx::api::DocumentManager::getInstance();
        const auto inFilepath = MUSIC_FILES_DIRECTORY() + "/" + c.inFilename;
        const auto outFilepath = OUTPUT_DIRECTORY() + "/" + c.outFilename;
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
                    switch ( note.pitchData.step )
                    {
                        case mx::api::Step::c:
                            a.step = 0;
                            break;
                        case mx::api::Step::d:
                            a.step = 1;
                            break;
                        case mx::api::Step::e:
                            a.step = 2;
                            break;
                        case mx::api::Step::f:
                            a.step = 3;
                            break;
                        case mx::api::Step::g:
                            a.step = 4;
                            break;
                        case mx::api::Step::a:
                            a.step = 5;
                            break;
                        case mx::api::Step::b:
                            a.step = 6;
                            break;
                        default:
                            a.step = 7;
                            break;
                    }
                    a.setName();
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

        // TODO - write the notes into the score
        mx::api::ScoreData score = createEmptyScore( "June 3 Coalescence Practice" );
        appendMeasures( score, 7 );
        const auto oID = dmgr.createFromScore( score );
        dmgr.writeToFile( oID, outFilepath );
    }
    
    mx::api::ScoreData
    June3::createEmptyScore( const std::string& title )
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
    June3::addInstrument( mx::api::ScoreData& ioScore,
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
    June3::appendMeasures( mx::api::ScoreData& ioScore, int numMeasures )
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
