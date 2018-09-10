#pragma once

#include "mx/api/ScoreData.h"
#include "scriabin/Constants.h"

namespace scriabin
{
    inline mx::api::MeasureData&
    getMeasure( mx::api::ScoreData& score, int partIndex, int measureIndex )
    {
        auto& part = *( score.parts.begin() + static_cast<size_t>( partIndex ) );
        auto& measure = *( part.measures.begin() + static_cast<size_t>( measureIndex ) );
        return measure;
    }
    
    
    inline mx::api::StaffData&
    getStaff( mx::api::ScoreData& score, int partIndex, int measureIndex, int staffIndex )
    {
        auto& measure = getMeasure( score, partIndex, measureIndex );
        return *( measure.staves.begin() + static_cast<size_t>( staffIndex ) );
    }
    
    
    inline mx::api::VoiceData&
    getVoice( mx::api::ScoreData& score, int partIndex, int measureIndex, int staffIndex, int voiceIndex )
    {
        auto& staff = getStaff( score, partIndex, measureIndex, staffIndex );
        
        if( staff.voices.find( voiceIndex ) == staff.voices.end() )
        {
            staff.voices.emplace( voiceIndex, mx::api::VoiceData{} );
        }
        
        auto& voice = ( staff.voices.find( voiceIndex ) )->second;
        return voice;
    }
    
    
    inline mx::api::MeasureData&
    addAndGetMeasure( mx::api::ScoreData& score, int partIndex )
    {
        mx::api::PartData& part = score.parts.at( static_cast<size_t>( partIndex) );
        part.measures.emplace_back();
        mx::api::MeasureData& measure = *( part.measures.rbegin() );
        return measure;
    }
    
    
    inline mx::api::StaffData&
    addAndGetStaff( mx::api::MeasureData& ioMeasure )
    {
        ioMeasure.staves.emplace_back();
        auto& staff = *( ioMeasure.staves.rbegin() );
        return staff;
    }
    
    
    inline mx::api::NoteData
    getNotePrototype( int ticksPerQuarter )
    {
        mx::api::NoteData n;
        n.durationData.durationName = mx::api::DurationName::whole;
        n.durationData.durationTimeTicks = ticksPerQuarter * 4;
        n.pitchData.step = mx::api::Step::b;
        n.pitchData.octave = 4;
        n.pitchData.alter = -1;
        return n;
    }
    
    
    inline int
    getPitchClass( const mx::api::PitchData& inPitchData )
    {
        int pc = 0;
        
        switch ( inPitchData.step )
        {
            case mx::api::Step::c:
                pc = 0;
                break;
            case mx::api::Step::d:
                pc = 2;
                break;
            case mx::api::Step::e:
                pc = 4;
                break;
            case mx::api::Step::f:
                pc = 5;
                break;
            case mx::api::Step::g:
                pc = 7;
                break;
            case mx::api::Step::a:
                pc = 9;
                break;
            case mx::api::Step::b:
                pc = 11;
                break;
            case mx::api::Step::unspecified:
            default:
                break;
        }
        
        pc += inPitchData.alter;

        while( pc < 0 )
        {
            pc += 12;
        }
        
        if( pc >= 12 )
        {
            pc = pc % 12;
        }
        
        return pc;
    }
    
    
    inline int getMidiNote( const mx::api::PitchData& inPitchData )
    {
        const auto pc = getPitchClass( inPitchData );
        const auto octave = inPitchData.octave;
        const auto octaveStartsAt = 12 * ( octave - MIDI_NOTE_ZERO_OCTAVE );
        const auto midiNote = octaveStartsAt + pc;
        return midiNote;
    }
    
    
    inline mx::api::PitchData
    getPitchDataFromPitchClass( int inPitchClass, const std::vector<mx::api::PitchData>& inSpellingPreferences )
    {
        const auto finder = [&]( const mx::api::PitchData& inPitchData )
        {
            const auto pc = getPitchClass( inPitchData );
            
            if( pc == inPitchClass )
            {
                return true;
            }
            
            return false;
        };
        
        const auto iter = std::find_if( inSpellingPreferences.cbegin(), inSpellingPreferences.cend(), finder );
        
        if( iter != inSpellingPreferences.cend() )
        {
            return *iter;
        }
        
        mx::api::PitchData result;
        
        const auto pcCheckAndSet = [&]( mx::api::Step step, int alter )
        {
            result.step = step;
            result.alter = alter;
            const auto pc = getPitchClass( result );
            
            if( pc == inPitchClass )
            {
                return true;
            }
            
            return false;
        };
        
        if( pcCheckAndSet( mx::api::Step::c, 0 ) )
        {
            return result;
        }
        else if( pcCheckAndSet( mx::api::Step::c, 1 ) )
        {
            return result;
        }
        else if( pcCheckAndSet( mx::api::Step::d, 0 ) )
        {
            return result;
        }
        else if( pcCheckAndSet( mx::api::Step::e, -1 ) )
        {
            return result;
        }
        else if( pcCheckAndSet( mx::api::Step::e, 0 ) )
        {
            return result;
        }
        else if( pcCheckAndSet( mx::api::Step::f, 0 ) )
        {
            return result;
        }
        else if( pcCheckAndSet( mx::api::Step::f, 1 ) )
        {
            return result;
        }
        else if( pcCheckAndSet( mx::api::Step::g, 0 ) )
        {
            return result;
        }
        else if( pcCheckAndSet( mx::api::Step::a, -1 ) )
        {
            return result;
        }
        else if( pcCheckAndSet( mx::api::Step::a, 0 ) )
        {
            return result;
        }
        else if( pcCheckAndSet( mx::api::Step::b, -1 ) )
        {
            return result;
        }
        else if( pcCheckAndSet( mx::api::Step::b, 0 ) )
        {
            return result;
        }
        
        return result;
    }
    
    
    inline mx::api::PitchData
    getPitchDataFromPitchClass( int inPitchClass )
    {
        std::vector<mx::api::PitchData> defaultSpellingPreferences;
        mx::api::PitchData p;
        p.step = mx::api::Step::c;
        p.alter = 0;
        p.accidental = mx::api::Accidental::natural;
        defaultSpellingPreferences.push_back( p );
        
        p.step = mx::api::Step::c;
        p.alter = 1;
        p.accidental = mx::api::Accidental::sharp;
        defaultSpellingPreferences.push_back( p );
        
        p.step = mx::api::Step::d;
        p.alter = 0;
        p.accidental = mx::api::Accidental::natural;
        defaultSpellingPreferences.push_back( p );
        
        p.step = mx::api::Step::e;
        p.alter = -1;
        p.accidental = mx::api::Accidental::flat;
        defaultSpellingPreferences.push_back( p );
        
        p.step = mx::api::Step::e;
        p.alter = 0;
        p.accidental = mx::api::Accidental::natural;
        defaultSpellingPreferences.push_back( p );
        
        p.step = mx::api::Step::f;
        p.alter = 0;
        p.accidental = mx::api::Accidental::natural;
        defaultSpellingPreferences.push_back( p );
        
        p.step = mx::api::Step::f;
        p.alter = 1;
        p.accidental = mx::api::Accidental::sharp;
        defaultSpellingPreferences.push_back( p );
        
        p.step = mx::api::Step::g;
        p.alter = 0;
        p.accidental = mx::api::Accidental::natural;
        defaultSpellingPreferences.push_back( p );
        
        p.step = mx::api::Step::a;
        p.alter = -1;
        p.accidental = mx::api::Accidental::flat;
        defaultSpellingPreferences.push_back( p );
        
        p.step = mx::api::Step::a;
        p.alter = 0;
        p.accidental = mx::api::Accidental::natural;
        defaultSpellingPreferences.push_back( p );
        
        p.step = mx::api::Step::b;
        p.alter = -1;
        p.accidental = mx::api::Accidental::flat;
        defaultSpellingPreferences.push_back( p );
        
        p.step = mx::api::Step::b;
        p.alter = 0;
        p.accidental = mx::api::Accidental::natural;
        defaultSpellingPreferences.push_back( p );
        
        return getPitchDataFromPitchClass( inPitchClass, defaultSpellingPreferences );
    }
    
    
    inline int
    getMidiNoteFromPitchClass( int inPitchClass, int octave )
    {
        auto pd = getPitchDataFromPitchClass( inPitchClass );
        pd.octave = octave;
        const auto midiNote = getMidiNote( pd );
        return midiNote;
    }
    
    
    // collapses any number of semitones down to fitting in one
    // octave. for example 13 => 1, 12 => 0, -1 => 11, -13 => 11
    inline int
    collapse( int inNumberOfSemitones )
    {
        auto result = inNumberOfSemitones;
        
        while( result >= 12 )
        {
            result -= 12;
        }
        
        while( result < 0 )
        {
            result += 12;
        }
        
        return result;
    }
    
    
    inline int
    getPitchClassFromMidiNote( int inMidiNote )
    {
        const auto middleC = getMidiNote( MIDDLE_C() );
        auto diff = inMidiNote - middleC;
        const auto result = collapse( diff );
        return result;
    }
    
    
    inline mx::api::PitchData
    getPitchDataFromMidiNote( int inMidiNote )
    {
        auto pc = getPitchClassFromMidiNote( inMidiNote );
        auto pd = getPitchDataFromPitchClass( pc );
        
        for(int octave = MIDI_NOTE_ZERO_OCTAVE; octave < 9; ++octave )
        {
            pd.octave = octave;
            
            const auto mn = getMidiNote( pd );
            if( mn == inMidiNote )
            {
                return pd;
            }
        }
        
        return pd;
    }
}
