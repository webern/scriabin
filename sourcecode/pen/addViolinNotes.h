#pragma once
#include "pen/util.h"
#include "mx/api/DocumentManager.h"
#include "mx/api/ScoreData.h"
#include <iostream>
#include <map>
#include "pen/Etude.h"
#include "pen/Program.h"

namespace etude
{
    inline void
    addViolinNote( const mx::api::NoteData& NOTE_PROTO,
                   int TICKS_PER_MEASURE,
                   mx::api::PitchData& prevPatternNote,
                   mx::api::ScoreData& score,
                   int t,
                   mx::api::DurationName vlnDur,
                   int vlnTicks )
    {
        const int measureIndex = t / TICKS_PER_MEASURE;
        const int measureTickOffset = measureIndex * TICKS_PER_MEASURE;
        const int measureRelativeTick = t - measureTickOffset;
        const auto& marimbaMeasure = score.parts.at( 1 ).measures.at( measureIndex );
        const auto& marimbaStaff0Notes = marimbaMeasure.staves.at( 0 ).voices.at( 0 ).notes;
        
        const auto findLambda = [&]( const mx::api::NoteData& inNote )
        {
            if( inNote.tickTimePosition == measureRelativeTick )
            {
                return true;
            }
            
            return false;
        };
        
        const auto staff0Iter = std::find_if( marimbaStaff0Notes.cbegin(), marimbaStaff0Notes.cend(), findLambda );
        auto tempNote = NOTE_PROTO;
        
        if( staff0Iter != marimbaStaff0Notes.cend() )
        {
            tempNote = *staff0Iter;
        }
        
        const auto marimbaNote = tempNote;
        //const auto marimbaMidi = getMidiNote( marimbaNote.pitchData );
        
        mx::api::PitchData LOWEST_PITCH;
        LOWEST_PITCH.octave = 3;
        LOWEST_PITCH.step = mx::api::Step::g;
        LOWEST_PITCH.alter = 0;
        const int LOWEST_MIDI_NOTE = getMidiNote( LOWEST_PITCH );
        
        mx::api::PitchData HIGHEST_PITCH;
        HIGHEST_PITCH.octave = 7;
        HIGHEST_PITCH.step = mx::api::Step::c;
        HIGHEST_PITCH.alter = 0;
        const int HIGHEST_MIDI_NOTE = getMidiNote( HIGHEST_PITCH );
        
        const auto marimbaPc = getPitchClass( marimbaNote.pitchData );
        std::set<int> directions = { -4, -3, 4, 4 };
        std::set<int> pcs;
        
        for( const auto d : directions )
        {
            auto newPc = marimbaPc + d;
            
            while( newPc > 12 )
            {
                newPc -= 12;
            }
            
            while( newPc < 0 )
            {
                newPc += 12;
            }
            
            pcs.insert( newPc );
        }
        
        std::set<int> possibleMidiNotes;
        
        for( const auto pcval : pcs )
        {
            for(int octave = 3; octave <= 7; ++octave)
            {
                auto tempPitchData = getPitchDataFromPitchClass( pcval );
                tempPitchData.octave = octave;
                const auto newMidiVal = getMidiNote( tempPitchData );
                possibleMidiNotes.insert( newMidiVal );
            }
        }
        
        auto vlnPitch = getPitchDataFromPitchClass( *pcs.cbegin() );
        vlnPitch.octave = -1;
        
        auto vlnMidiNote = 0;
        
        if( prevPatternNote.alter == -100 )
        {
            // this is the first note of the piece, choose lowest possible pitch
            auto m = 0;
            
            for( const auto val : possibleMidiNotes )
            {
                m = val;
                if( m >= LOWEST_MIDI_NOTE )
                {
                    break;
                }
            }
            
            
        }
        else // this is not the first note
        {
            const auto prevMidiNote = getMidiNote( prevPatternNote );
            int theMidiNote = 0;
            int distanceFromPrevNote = std::numeric_limits<int>::max();
            
            for( const auto possibleMidiNote : possibleMidiNotes )
            {
                const auto dist = std::abs( possibleMidiNote - prevMidiNote );
                
                if( dist < distanceFromPrevNote )
                {
                    distanceFromPrevNote = dist;
                    theMidiNote = possibleMidiNote;
                }
                else if( dist == distanceFromPrevNote )
                {
                    if( theMidiNote > prevMidiNote )
                    {
                        theMidiNote = prevMidiNote;
                    }
                }
            }
            vlnMidiNote = theMidiNote;
        }
        
        if( vlnMidiNote > HIGHEST_MIDI_NOTE - 24 )
        {
            vlnMidiNote -= 12;
        }
        
        while( vlnMidiNote < LOWEST_MIDI_NOTE )
        {
            vlnMidiNote += 12;
        }
        
        mx::api::NoteData vlnNote;
        vlnNote.tickTimePosition = marimbaNote.tickTimePosition;
        vlnNote.pitchData = getPitchDataFromMidiNote( vlnMidiNote );
        vlnNote.durationData.durationName = vlnDur;
        vlnNote.durationData.durationTimeTicks = vlnTicks;
        vlnNote.beams.clear();
        
        score.parts.at( 0 ).measures.at( measureIndex ).staves.at( 0 ).voices[0].notes.push_back( vlnNote );
        prevPatternNote = vlnNote.pitchData;
    }
}
