#include "catch.hpp"
#include "scriabin/etude1.h"
#include "SCRIABIN_PATH.h"
#include "mx/api/DocumentManager.h"
#include "mx/api/ScoreData.h"
#include "scriabin/Coalescence.h"
#include "scriabin/Atom.h"

//using namespace zeus;

TEST_CASE( "coalescence lock", "Comp" )
{
    const std::string outFilename = "coalescence.large.xml";
    const std::string inFilename = "coalescence.input.xml";
    const auto inFilepath = scriabin::MUSIC_INPUT_FILES_DIRECTORY() + "/" + inFilename;
    const auto outFilepath = scriabin::MUSIC_OUTPUT_FILES_DIRECTORY() + "/" + outFilename;
    scriabin::Coalescence coalescence{ inFilepath, outFilepath };
    const auto score = coalescence.doEverthing();

    const size_t expectedNumMeasures = 547;
    CHECK( score.parts.size() == 4 );
    CHECK( score.parts.at( 0 ).measures.size() == expectedNumMeasures );
    CHECK( score.parts.at( 1 ).measures.size() == expectedNumMeasures );
    CHECK( score.parts.at( 2 ).measures.size() == expectedNumMeasures );
    CHECK( score.parts.at( 3 ).measures.size() == expectedNumMeasures );

    size_t partIndex = 0;
    size_t measureIndex = 0;
    size_t noteIndex = 0;
    int expectedMidiNumber = 0;
    bool isAccentExpected = false;
    scriabin::Atom atom;
    mx::api::NoteData mxNote;
    const auto isAccented = [&]( const mx::api::NoteData& inNoteData )
    {
        if( inNoteData.noteAttachmentData.marks.size() == 0 )
        {
            return false;
        }

        const auto iter = std::find_if(
                std::cbegin( inNoteData.noteAttachmentData.marks ),
                std::cend( inNoteData.noteAttachmentData.marks ),
                [&]( const mx::api::MarkData& inMarkData )
                {
                    return inMarkData.markType == mx::api::MarkType::accent;
                }
        );
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
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 48;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 3;
    noteIndex = 1;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 48;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 6;
    noteIndex = 2;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 9;
    noteIndex = 3;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 12;
    noteIndex = 4;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 15;
    noteIndex = 5;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 18;
    noteIndex = 6;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 21;
    noteIndex = 7;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 24;
    noteIndex = 8;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 27;
    noteIndex = 9;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 30;
    noteIndex = 10;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 33;
    noteIndex = 11;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 72;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 76;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 40;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 36;
    noteIndex = 0;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 77;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 41;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 39;
    noteIndex = 1;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 38;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 42;
    noteIndex = 2;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 40;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 45;
    noteIndex = 3;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 36;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 48;
    noteIndex = 4;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 84;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 41;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 51;
    noteIndex = 5;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 46;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 54;
    noteIndex = 6;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 52;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 57;
    noteIndex = 7;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 81;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 60;
    noteIndex = 8;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 72;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 63;
    noteIndex = 9;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 66;
    noteIndex = 10;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 48;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 69;
    noteIndex = 11;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 46;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 72;
    noteIndex = 0;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 75;
    noteIndex = 1;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 78;
    noteIndex = 2;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 81;
    noteIndex = 3;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 84;
    noteIndex = 4;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 87;
    noteIndex = 5;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 72;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 76;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 52;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 90;
    noteIndex = 6;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 93;
    noteIndex = 7;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 96;
    noteIndex = 8;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 40;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 99;
    noteIndex = 9;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 41;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 102;
    noteIndex = 10;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 40;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 105;
    noteIndex = 11;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 41;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 108;
    noteIndex = 0;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 111;
    noteIndex = 1;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 114;
    noteIndex = 2;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 117;
    noteIndex = 3;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 46;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 120;
    noteIndex = 4;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 81;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 77;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 52;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 123;
    noteIndex = 5;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 72;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 126;
    noteIndex = 6;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 129;
    noteIndex = 7;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 76;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 48;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 132;
    noteIndex = 8;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 38;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 135;
    noteIndex = 9;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 41;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 138;
    noteIndex = 10;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 141;
    noteIndex = 11;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 46;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 144;
    noteIndex = 0;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 72;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 147;
    noteIndex = 1;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 150;
    noteIndex = 2;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 41;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 153;
    noteIndex = 3;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 72;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 48;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 52;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 156;
    noteIndex = 4;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 159;
    noteIndex = 5;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 40;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 162;
    noteIndex = 6;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 76;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 165;
    noteIndex = 7;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 168;
    noteIndex = 8;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 38;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 171;
    noteIndex = 9;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 72;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 174;
    noteIndex = 10;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 81;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 48;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 177;
    noteIndex = 11;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 84;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 36;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 180;
    noteIndex = 0;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 77;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 183;
    noteIndex = 1;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 186;
    noteIndex = 2;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 36;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 189;
    noteIndex = 3;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 192;
    noteIndex = 4;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 195;
    noteIndex = 5;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 52;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 198;
    noteIndex = 6;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 201;
    noteIndex = 7;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 36;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 204;
    noteIndex = 8;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 77;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 207;
    noteIndex = 9;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 72;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 210;
    noteIndex = 10;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 213;
    noteIndex = 11;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 216;
    noteIndex = 0;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 36;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 219;
    noteIndex = 1;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 222;
    noteIndex = 2;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 40;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 225;
    noteIndex = 3;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 48;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 228;
    noteIndex = 4;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 52;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 231;
    noteIndex = 5;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 234;
    noteIndex = 6;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 237;
    noteIndex = 7;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 240;
    noteIndex = 8;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 243;
    noteIndex = 9;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 48;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 246;
    noteIndex = 10;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 249;
    noteIndex = 11;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 252;
    noteIndex = 0;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 46;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 255;
    noteIndex = 1;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 258;
    noteIndex = 2;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 84;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 57;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 261;
    noteIndex = 3;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 264;
    noteIndex = 4;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 267;
    noteIndex = 5;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 72;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 72;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 270;
    noteIndex = 6;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 273;
    noteIndex = 7;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 276;
    noteIndex = 8;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 76;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 38;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 279;
    noteIndex = 9;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 282;
    noteIndex = 10;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 77;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 285;
    noteIndex = 11;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 40;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 288;
    noteIndex = 0;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 291;
    noteIndex = 1;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 81;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 41;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 294;
    noteIndex = 2;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 48;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 297;
    noteIndex = 3;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 76;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 300;
    noteIndex = 4;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 41;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 303;
    noteIndex = 5;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 306;
    noteIndex = 6;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 41;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 309;
    noteIndex = 7;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 312;
    noteIndex = 8;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 52;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 40;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 315;
    noteIndex = 9;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 72;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 48;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 318;
    noteIndex = 10;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 38;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 321;
    noteIndex = 11;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 324;
    noteIndex = 0;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 327;
    noteIndex = 1;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 41;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 330;
    noteIndex = 2;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 333;
    noteIndex = 3;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 336;
    noteIndex = 4;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 76;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 339;
    noteIndex = 5;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 76;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 342;
    noteIndex = 6;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 345;
    noteIndex = 7;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 348;
    noteIndex = 8;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 52;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 40;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 351;
    noteIndex = 9;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 72;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 48;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 354;
    noteIndex = 10;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 38;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 357;
    noteIndex = 11;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 360;
    noteIndex = 0;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 363;
    noteIndex = 1;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 41;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 366;
    noteIndex = 2;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 369;
    noteIndex = 3;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 372;
    noteIndex = 4;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 76;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 375;
    noteIndex = 5;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 76;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 55;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 378;
    noteIndex = 6;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 381;
    noteIndex = 7;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 384;
    noteIndex = 8;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 52;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 40;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 387;
    noteIndex = 9;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 72;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 69;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 48;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 390;
    noteIndex = 10;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 38;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 393;
    noteIndex = 11;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 396;
    noteIndex = 0;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 399;
    noteIndex = 1;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 62;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 41;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 402;
    noteIndex = 2;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 405;
    noteIndex = 3;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 408;
    noteIndex = 4;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 76;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 411;
    noteIndex = 5;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 76;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 414;
    noteIndex = 6;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 417;
    noteIndex = 7;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 420;
    noteIndex = 8;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 52;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 40;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 423;
    noteIndex = 9;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 72;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 48;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 426;
    noteIndex = 10;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 38;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 429;
    noteIndex = 11;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 432;
    noteIndex = 0;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 435;
    noteIndex = 1;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 41;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 438;
    noteIndex = 2;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 441;
    noteIndex = 3;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 444;
    noteIndex = 4;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 76;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 447;
    noteIndex = 5;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 76;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 450;
    noteIndex = 6;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 453;
    noteIndex = 7;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 79;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 456;
    noteIndex = 8;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 52;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 40;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 459;
    noteIndex = 9;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 72;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 48;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 462;
    noteIndex = 10;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 38;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 465;
    noteIndex = 11;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 468;
    noteIndex = 0;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 471;
    noteIndex = 1;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 62;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 53;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 41;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 474;
    noteIndex = 2;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 477;
    noteIndex = 3;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 62;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 480;
    noteIndex = 4;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 76;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 483;
    noteIndex = 5;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 76;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 486;
    noteIndex = 6;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 489;
    noteIndex = 7;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 79;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 70;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 492;
    noteIndex = 8;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 64;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 495;
    noteIndex = 9;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 72;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 48;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 498;
    noteIndex = 10;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 501;
    noteIndex = 11;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 65;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 504;
    noteIndex = 0;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 64;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 507;
    noteIndex = 1;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 53;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 510;
    noteIndex = 2;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 513;
    noteIndex = 3;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 50;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 516;
    noteIndex = 4;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 519;
    noteIndex = 5;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 76;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 522;
    noteIndex = 6;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 525;
    noteIndex = 7;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 528;
    noteIndex = 8;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 52;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 531;
    noteIndex = 9;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 534;
    noteIndex = 10;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 58;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 537;
    noteIndex = 11;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 540;
    noteIndex = 0;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 543;
    noteIndex = 1;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 546;
    noteIndex = 2;

    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLIN_2;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = VIOLA;
    expectedMidiNumber = 55;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );

    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };

    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
}