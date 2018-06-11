#pragma once

namespace pen
{
    inline void
    addMarimbaNote( const mx::api::NoteData& NOTE_PROTO,
                    int TICKS_PER_MEASURE,
                    int index,
                    int& measureIndex,
                    int& noteCounter,
                    std::vector<mx::api::PitchData>& pattern,
                    int& patternCounter,
                    int& patternSize,
                    mx::api::PitchData &prevPatternNote,
                    mx::api::ScoreData &score,
                    int t,
                    mx::api::DurationName theDur,
                    int theTicks)
    {
        if( patternCounter == patternSize )
        {
            patternCounter = 0;
        }
        
        auto patternPitch = pattern.at( patternCounter );
        int octaveAdjust = 0;
        
        if( patternPitch == prevPatternNote )
        {
            octaveAdjust = 1;
        }
        else if( index > 15 && index % 5 == 0  && index % 7 == 0 )
        {
            octaveAdjust = 2;
        }
        else if( index > 15 && index % 5 == 0 )
        {
            octaveAdjust = 1;
        }
        else if( index > 15 && index % 7 == 0 )
        {
            octaveAdjust = -1;
        }
        
        patternPitch.octave += octaveAdjust;
        const bool isNewMeasure = ( t == 0 ) || ( t % TICKS_PER_MEASURE == 0 );
        
        if( isNewMeasure )
        {
            noteCounter = 0;
            pattern.push_back( pattern.at( measureIndex ) );
            patternSize = static_cast<int>( pattern.size() );
            ++measureIndex;
        }
        
        const bool isAccented = ( patternPitch.octave > 4 ) &&
        ( ( noteCounter == 0 ) ||
         ( noteCounter == 4 ) ||
         ( noteCounter == 6 ) ||
         ( noteCounter == 8 ) ||
         ( noteCounter == 12 ) ||
         ( noteCounter == 13 ) );
        
        measureIndex = t / TICKS_PER_MEASURE;
        const int measureTickOffset = measureIndex * TICKS_PER_MEASURE;
        const int measureRelativeTick = t - measureTickOffset;
        auto n = NOTE_PROTO;
        n.durationData.durationName = theDur;
        n.durationData.durationTimeTicks = theTicks;
        n.tickTimePosition = measureRelativeTick;
        n.pitchData = patternPitch;
        
        if( isAccented )
        {
            mx::api::MarkData md;
            md.markType = mx::api::MarkType::accent;
            n.noteAttachmentData.marks.push_back( md );
        }
        
        auto& s = score.parts.at( 1 ).measures.at( measureIndex ).staves.at( 0 );
        s.voices[0].notes.push_back( n );
        prevPatternNote = patternPitch;
    }
    
    
    inline void
    addViolinNotes( int END_TICK,
                   const mx::api::NoteData& NOTE_PROTO,
                   int TICKS_PER_MEASURE,
                   int& noteCounter,
                   mx::api::PitchData& prevPatternNote,
                   mx::api::ScoreData& score,
                   std::map<mx::api::DurationName, int>& ticks)
    {
        const auto vlnDur = S;
        const auto vlnTicks = ticks.at( vlnDur );
        prevPatternNote.octave = 0;
        prevPatternNote.alter = -100;
        noteCounter = 0;
        
        // Violin Loop
        for( int t = 0; t < END_TICK; t += vlnTicks, ++noteCounter )
        {
            addViolinNote(NOTE_PROTO, TICKS_PER_MEASURE, prevPatternNote, score, t, vlnDur, vlnTicks);
        }
    }
    
    
    inline void
    addMarimbaNotes( int END_TICK,
                     const mx::api::NoteData& NOTE_PROTO,
                     int TICKS_PER_MEASURE,
                     int& index,
                     int& measureIndex,
                     int& noteCounter,
                     std::vector<mx::api::PitchData> &pattern,
                     int& patternCounter,
                     int& patternSize,
                     mx::api::PitchData& prevPatternNote,
                     mx::api::ScoreData& score,
                     mx::api::DurationName theDur,
                     int theTicks )
    {
        for( int t = 0; t < END_TICK; t += theTicks, ++noteCounter, ++patternCounter, ++index )
        {
            addMarimbaNote(NOTE_PROTO, TICKS_PER_MEASURE, index, measureIndex, noteCounter, pattern, patternCounter, patternSize, prevPatternNote, score, t, theDur, theTicks);
        }
    }
}
