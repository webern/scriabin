#include "catch.hpp"
#include "pen/etude1.h"
#include "PEN_PATH.h"
#include "mx/api/DocumentManager.h"
#include "mx/api/ScoreData.h"
#include "pen/Coalescence.h"
#include "pen/Atom.h"

using namespace zeus;

TEST_CASE( "coalescence", "Comp" )
{
    const std::string outFilename = "coalescence.large.xml";
    const std::string inFilename = "coalescence.input.xml";
    const auto inFilepath = pen::MUSIC_INPUT_FILES_DIRECTORY() + "/" + inFilename;
    const auto outFilepath = pen::MUSIC_OUTPUT_FILES_DIRECTORY() + "/" + outFilename;
    pen::Coalescence coalescence{ inFilepath, outFilepath };
    const auto score = coalescence.doEverthing();
    
    const size_t minimumNumMeasures = 758;
    CHECK( score.parts.size() == 4 );
    CHECK( score.parts.at( 0 ).measures.size()>= minimumNumMeasures );
    CHECK( score.parts.at( 1 ).measures.size()>= minimumNumMeasures );
    CHECK( score.parts.at( 2 ).measures.size()>= minimumNumMeasures );
    CHECK( score.parts.at( 3 ).measures.size()>= minimumNumMeasures );
    
    size_t partIndex = 0;
    size_t measureIndex = 0;
    size_t noteIndex = 0;
    int expectedMidiNumber = 0;
    bool isAccentExpected = false;
    pen::Atom atom;
    mx::api::NoteData mxNote;
    const auto isAccented = [&]( const mx::api::NoteData& inNoteData )
    {
        if( inNoteData.noteAttachmentData.marks.size() == 0 )
        {
            return false;
        }
        
        const auto iter = std::find_if( std::cbegin( inNoteData.noteAttachmentData.marks ) , std::cend( inNoteData.noteAttachmentData.marks ), [&]( const mx::api::MarkData& inMarkData ) { return inMarkData.markType == mx::api::MarkType::accent; } );
        return iter != std::cend( inNoteData.noteAttachmentData.marks );
    };
    
    constexpr const int VIOLIN_1 = 0;
    constexpr const int VIOLIN_2 = 1;
    constexpr const int VIOLA = 2;
    constexpr const int CELLO = 3;
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 0;
    noteIndex = 0;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLA;
    expectedMidiNumber = 48;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 7;
    noteIndex = 2;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLA;
    expectedMidiNumber = 48;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 7;
    noteIndex = 3;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLA;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 13;
    noteIndex = 4;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLA;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 17;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLA;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 19;
    noteIndex = 0;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLA;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 23;
    noteIndex = 1;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLA;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 34;
    noteIndex = 2;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLIN_2;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLA;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 55;
    noteIndex = 3;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLA;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 89;
    noteIndex = 4;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLA;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = CELLO;
    expectedMidiNumber = 40;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 144;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 233;
    noteIndex = 0;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLIN_2;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = CELLO;
    expectedMidiNumber = 48;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 377;
    noteIndex = 1;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLIN_2;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLA;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = CELLO;
    expectedMidiNumber = 48;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 610;
    noteIndex = 2;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLIN_2;
    expectedMidiNumber = 77;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = VIOLA;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = CELLO;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = pen::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
}
