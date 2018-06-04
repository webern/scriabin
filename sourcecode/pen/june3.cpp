#include "pen/june3.h"
#include "../test/PEN_PATH.h"
#include "mx/api/DocumentManager.h"

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
        auto input = dmgr.getData( inID );
        dmgr.destroyDocument( inID );
        
        if( input.parts.size() == 8 )
        {
            // remove the keyswitches
            input.parts.erase( input.parts.cbegin() + 7 );
            input.parts.erase( input.parts.cbegin() + 5 );
            input.parts.erase( input.parts.cbegin() + 3 );
            input.parts.erase( input.parts.cbegin() + 1 );
            input.systems.clear();
            input.layout = mx::api::LayoutData{};
            input.encoding = mx::api::EncodingData{};
            input.partGroups.clear();
            input.pageTextItems.clear();
            
            int partIndex = 0;
            for( auto& part : input.parts )
            {
                int measureIndex = 0;
                for( auto& measure : part.measures )
                {
                    if( measureIndex == 0 || measure.staves.at( 0 ).clefs.size() > 0 )
                    {
                        mx::api::ClefData clef;
                        clef.setTreble();
                        
                        if( partIndex == 2 )
                        {
                            clef.setAlto();
                        }
                        
                        if( partIndex == 3 )
                        {
                            clef.setBass();
                        }

                        if( measure.staves.at( 0 ).clefs.empty() )
                        {
                            measure.staves.at( 0 ).clefs.push_back( clef );
                        }
                        else
                        {
                            measure.staves.at( 0 ).clefs.at( 0 ) = clef;
                        }
                    }
                    
                    if( measure.staves.size() == 2 )
                    {
                        measure.staves.erase( measure.staves.cbegin() + 1 );
                    }
                    
                    for( auto& staff : measure.staves )
                    {
                        for( auto& voice : staff.voices )
                        {
                            for( auto& note: voice.second.notes )
                            {
                                if( note.pitchData.step == mx::api::Step::a )
                                {
                                    if( note.pitchData.alter == -1 )
                                    {
                                        note.pitchData.step = mx::api::Step::g;
                                        note.pitchData.alter = 1;
                                    }
                                }
                                if( note.pitchData.alter == -1 )
                                {
                                    note.pitchData.accidental = mx::api::Accidental::flat;
                                }
                                else if( note.pitchData.alter == 1 )
                                {
                                    note.pitchData.accidental = mx::api::Accidental::sharp;
                                }
                            }
                        }
                    }
                
                    ++measureIndex;
                }
                
                ++partIndex;
            }
            
            const auto resaveID = dmgr.createFromScore( input );
            dmgr.writeToFile( resaveID, inFilepath );
        }
        
        mx::api::ScoreData score = createEmptyScore( "June 3 Input" );
        appendMeasures( score, 7 );
        
        const size_t start = 114;
        
        for( size_t i = 0; i < 8; ++i )
        {
            const auto oldMeasureIndex = start + i;
            for( size_t partIndex = 0; partIndex < 4; ++partIndex )
            {
                const auto& oldPart = input.parts.at( partIndex );
                auto& newPart = score.parts.at( partIndex );
                const auto& oldMeasure = oldPart.measures.at( oldMeasureIndex );
                auto& newMeasure = newPart.measures.at( i );
                newMeasure.staves.at( 0 ).voices.at( 0 ).notes = oldMeasure.staves.at( 0 ).voices.at( 0 ).notes;
            }
        }
        
        for( auto& part : score.parts )
        {
            for( auto& measure : part.measures )
            {
                for( auto& staff : measure.staves )
                {
                    for( auto& voice : staff.voices )
                    {
                        for( auto& note: voice.second.notes )
                        {
                            if( note.pitchData.step == mx::api::Step::a )
                            {
                                if( note.pitchData.alter == -1 )
                                {
                                    note.pitchData.step = mx::api::Step::g;
                                    note.pitchData.alter = 1;
                                }
                            }
                            if( note.pitchData.alter == -1 )
                            {
                                note.pitchData.accidental = mx::api::Accidental::flat;
                            }
                            else if( note.pitchData.alter == 1 )
                            {
                                note.pitchData.accidental = mx::api::Accidental::sharp;
                            }
                        }
                    }
                }
            }
        }
        
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
