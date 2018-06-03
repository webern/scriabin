#pragma once
#include "pen/util.h"
#include "mx/api/DocumentManager.h"
#include "mx/api/ScoreData.h"
#include <iostream>
#include <map>
#include "pen/Etude.h"
#include "pen/Program.h"
#include "pen/addViolinNotes.h"
#include "pen/addMarimbaNotes.h"


int inline etude1( int argc, const char* argv[] )
{
    using namespace mx::api;
    using namespace etude;
    Program program{ argc, argv };
    
    Etude etude{ program.instrumentConfig };
    etude.addPart( "species.violin" );
    etude.addPart( "species.marimba.4.3" );

    auto& score = etude.getScore();
    score.workTitle = "C++ Etude";
    score.composer = "Matthew James Briggs";

    const int measCount = 16;
    const int tpq = 4 * 4 * 4;
    score.ticksPerQuarter = tpq;

    // TODO - put this in a singleton
    std::map<DurationName, int> ticks = {
        { etude::Q, tpq },
        { etude::H, tpq * 2 },
        { etude::W, tpq * 4 },
        { etude::E, tpq / 2 },
        { etude::S, tpq / 4 },
    };
    
    // TODO - put this in a singleton
    std::map<int, DurationName> timeSignatureDenominatorDurationName = {
        { 4, etude::Q },
        { 2, etude::H },
        { 1, etude::W },
        { 8, etude::E },
        { 16, etude::S },
    };
    
    const int BEATS_PER_MEASURE = 4;
    const int TS_DENOMINATOR = 4;
    const auto TS_DENOMINATOR_DURATION_NAME = timeSignatureDenominatorDurationName.at( TS_DENOMINATOR );
    const int TICKS_PER_TS_BEAT = ticks.at( TS_DENOMINATOR_DURATION_NAME );
    const auto TICKS_PER_MEASURE = BEATS_PER_MEASURE * TICKS_PER_TS_BEAT;
    const auto END_TICK = TICKS_PER_MEASURE * measCount;
    const auto NOTE_PROTO = getNotePrototype( tpq );
    bool isFirstMeasure = true;
    TimeSignatureData ts;
    ts.beats = BEATS_PER_MEASURE;
    ts.beatType = TS_DENOMINATOR;
    ts.isImplicit = false;
    TempoData td;
    td.beatsPerMinute.beatsPerMinute = 72;
    td.tempoType = TempoType::beatsPerMinute;
    td.beatsPerMinute.durationName = DurationName::quarter;
    
    for( int i = 0; i < measCount; ++i )
    {
        const int mbaPartIndex = 1;
        const int mbaStaffIndex = 0;
        const int measureIndex = i;
        score.parts.at( static_cast<size_t>( mbaPartIndex) ).measures.emplace_back();
        score.parts.at( static_cast<size_t>( mbaPartIndex) ).measures.at( measureIndex ).staves.emplace_back();
        score.parts.at( static_cast<size_t>( mbaPartIndex) ).measures.at( measureIndex ).staves.emplace_back();
        
        if( isFirstMeasure )
        {
            score.parts.at( static_cast<size_t>( mbaPartIndex) ).measures.rbegin()->timeSignature = ts;
            ClefData clef;
            clef.setTreble();
            score.parts.at( static_cast<size_t>( mbaPartIndex) ).measures.rbegin()->staves.at( mbaStaffIndex ).clefs.push_back( clef );
        }
        
        if( isFirstMeasure )
        {
            score.parts.at( static_cast<size_t>( mbaPartIndex) ).measures.rbegin()->timeSignature = ts;
            ClefData clef;
            clef.setBass();
            score.parts.at( static_cast<size_t>( mbaPartIndex) ).measures.rbegin()->staves.at( 1 ).clefs.push_back( clef );
        }
        
        const int vlnPartIndex = 0;
        const int vlnStaffIndex = 0;
        score.parts.at( static_cast<size_t>( vlnPartIndex) ).measures.emplace_back();
        score.parts.at( static_cast<size_t>( vlnPartIndex) ).measures.at( measureIndex ).staves.emplace_back();
        
        if( isFirstMeasure )
        {
            score.parts.at( static_cast<size_t>( vlnPartIndex) ).measures.rbegin()->timeSignature = ts;
            ClefData clef;
            clef.setTreble();
            score.parts.at( static_cast<size_t>( vlnPartIndex) ).measures.rbegin()->staves.at( vlnStaffIndex ).clefs.push_back( clef );
            DirectionData dir;
            dir.tempos.push_back( td );
            score.parts.at( static_cast<size_t>( vlnPartIndex) ).measures.rbegin()->staves.at( vlnStaffIndex ).directions.push_back( dir );
        }
        
        isFirstMeasure = false;
    }
    
    std::vector<PitchData> pattern;
    PitchData p;
    p.step = Step::a;
    p.alter = 0;
    p.accidental= Accidental::none;
    p.octave = 3;
    pattern.push_back( p );

    p.step = Step::e;
    p.alter = 0;
    p.accidental= Accidental::none;
    p.octave = 4;
    pattern.push_back( p );

    p.step = Step::f;
    p.alter = 1;
    p.accidental= Accidental::sharp;
    p.octave = 4;
    pattern.push_back( p );

    p.step = Step::b;
    p.alter = -1;
    p.accidental= Accidental::flat;
    p.octave = 3;
    pattern.push_back( p );

    p.step = Step::d;
    p.alter = 0;
    p.accidental= Accidental::none;
    p.octave = 4;
    pattern.push_back( p );

    p.step = Step::b;
    p.alter = 0;
    p.accidental= Accidental::natural;
    p.octave = 3;
    pattern.push_back( p );
    
    p.step = Step::c;
    p.alter = 0;
    p.accidental= Accidental::natural;
    p.octave = 4;
    pattern.push_back( p );
    
    p.step = Step::g;
    p.alter = 1;
    p.accidental= Accidental::sharp;
    p.octave = 3;
    pattern.push_back( p );
    
    const auto theDur = S;
    const auto theTicks = ticks.at( theDur );
    int noteCounter = 0;
    int patternCounter = 0;
    int patternSize = static_cast<int>( pattern.size() );
    int measureIndex = 0;
    mx::api::PitchData prevPatternNote;
    prevPatternNote.octave = 0;
    prevPatternNote.alter = -100;
    int index = 0;
    
    addMarimbaNotes(END_TICK, NOTE_PROTO, TICKS_PER_MEASURE, index, measureIndex, noteCounter, pattern, patternCounter, patternSize, prevPatternNote, score, theDur, theTicks);
    addViolinNotes(END_TICK, NOTE_PROTO, TICKS_PER_MEASURE, noteCounter, prevPatternNote, score, ticks);

    auto& dmgr = DocumentManager::getInstance();
    const auto docid = dmgr.createFromScore( score );
    dmgr.writeToFile( docid, program.outfilePath );
    return 0;
}
