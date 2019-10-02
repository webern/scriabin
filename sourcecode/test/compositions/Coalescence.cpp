#include "catch.hpp"
#include "scriabin/etude1.h"
#include "SCRIABIN_PATH.h"
#include "mx/api/DocumentManager.h"
#include "mx/api/ScoreData.h"
#include "scriabin/Coalescence.h"
#include "scriabin/Atom.h"

using namespace zeus;

TEST_CASE( "coalescence", "Comp" )
{
    const std::string outFilename = "coalescence.large.xml";
    const std::string inFilename = "coalescence.input.xml";
    const auto inFilepath = scriabin::MUSIC_INPUT_FILES_DIRECTORY() + "/" + inFilename;
    const auto outFilepath = scriabin::MUSIC_OUTPUT_FILES_DIRECTORY() + "/" + outFilename;
    scriabin::Coalescence coalescence{ inFilepath, outFilepath };
    const auto score = coalescence.doEverthing();
    
    const size_t minimumNumMeasures = 627;
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
    scriabin::Atom atom;
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
    
    for( int m = 0, n = 0; m < 626; m += 3, ++n )
    {
        n = n % 6;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int insideMeasureIndex = m;
        int insideNoteIndex = n;
        std::stringstream ss;
        ss.setf(std::ios_base::boolalpha);
        
        ss << "    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << std::endl;
        ss << "    measureIndex = " << insideMeasureIndex << ";" << std::endl;
        ss << "    noteIndex = " << insideNoteIndex << ";" << std::endl;
        
        partIndex = VIOLIN_1;
        mxNote = score.parts.at( partIndex ).measures.at( insideMeasureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( insideNoteIndex );
        atom = scriabin::Atom{ mxNote.pitchData };
        int insideMidiNum = atom.getMidiNote();
        bool insideIsAccent = isAccented( mxNote );
        
        ss << "" << std::endl;
        ss << "    partIndex = VIOLIN_1;" << std::endl;
        ss << "    expectedMidiNumber = " << insideMidiNum << ";" << std::endl;
        ss << "    isAccentExpected = " << insideIsAccent << ";" << std::endl;
        ss << "    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );" << std::endl;
        ss << "    atom = scriabin::Atom{ mxNote.pitchData };" << std::endl;
        ss << "" << std::endl;
        ss << "    CHECK( atom.getMidiNote() == expectedMidiNumber );" << std::endl;
        ss << "    CHECK( isAccented( mxNote ) == isAccentExpected );" << std::endl;
        
        partIndex = VIOLIN_2;
        mxNote = score.parts.at( partIndex ).measures.at( insideMeasureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( insideNoteIndex );
        atom = scriabin::Atom{ mxNote.pitchData };
        insideMidiNum = atom.getMidiNote();
        insideIsAccent = isAccented( mxNote );
        ss << "" << std::endl;
        ss << "    partIndex = VIOLIN_2;" << std::endl;
        ss << "    expectedMidiNumber = " << insideMidiNum << ";" << std::endl;
        ss << "    isAccentExpected = " << insideIsAccent << ";" << std::endl;
        ss << "    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );" << std::endl;
        ss << "    atom = scriabin::Atom{ mxNote.pitchData };" << std::endl;
        ss << "" << std::endl;
        ss << "    CHECK( atom.getMidiNote() == expectedMidiNumber );" << std::endl;
        ss << "    CHECK( isAccented( mxNote ) == isAccentExpected );" << std::endl;
        
        partIndex = VIOLA;
        mxNote = score.parts.at( partIndex ).measures.at( insideMeasureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( insideNoteIndex );
        atom = scriabin::Atom{ mxNote.pitchData };
        insideMidiNum = atom.getMidiNote();
        insideIsAccent = isAccented( mxNote );
        ss << "" << std::endl;
        ss << "    partIndex = VIOLA;" << std::endl;
        ss << "    expectedMidiNumber = " << insideMidiNum << ";" << std::endl;
        ss << "    isAccentExpected = " << insideIsAccent << ";" << std::endl;
        ss << "    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );" << std::endl;
        ss << "    atom = scriabin::Atom{ mxNote.pitchData };" << std::endl;
        ss << "" << std::endl;
        ss << "    CHECK( atom.getMidiNote() == expectedMidiNumber );" << std::endl;
        ss << "    CHECK( isAccented( mxNote ) == isAccentExpected );" << std::endl;
        
        partIndex = CELLO;
        mxNote = score.parts.at( partIndex ).measures.at( insideMeasureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( insideNoteIndex );
        atom = scriabin::Atom{ mxNote.pitchData };
        insideMidiNum = atom.getMidiNote();
        insideIsAccent = isAccented( mxNote );
        ss << "" << std::endl;
        ss << "    partIndex = CELLO;" << std::endl;
        ss << "    expectedMidiNumber = " << insideMidiNum << ";" << std::endl;
        ss << "    isAccentExpected = " << insideIsAccent << ";" << std::endl;
        ss << "    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );" << std::endl;
        ss << "    atom = scriabin::Atom{ mxNote.pitchData };" << std::endl;
        ss << "" << std::endl;
        ss << "    CHECK( atom.getMidiNote() == expectedMidiNumber );" << std::endl;
        ss << "    CHECK( isAccented( mxNote ) == isAccentExpected );" << std::endl;
        
        // uncomment to generate tests
        // std::cout << ss.str() << std::endl;
    } // end test generation loop
    
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
    measureIndex = 9;
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
    measureIndex = 12;
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
    measureIndex = 15;
    noteIndex = 5;
    
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
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 18;
    noteIndex = 0;
    
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
    measureIndex = 21;
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
    measureIndex = 24;
    noteIndex = 2;
    
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
    measureIndex = 27;
    noteIndex = 3;
    
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
    measureIndex = 30;
    noteIndex = 4;
    
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
    measureIndex = 33;
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
    measureIndex = 39;
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
    expectedMidiNumber = 58;
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
    measureIndex = 42;
    noteIndex = 2;
    
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
    measureIndex = 45;
    noteIndex = 3;
    
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
    measureIndex = 48;
    noteIndex = 4;
    
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
    measureIndex = 54;
    noteIndex = 0;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 81;
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
    measureIndex = 57;
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
    measureIndex = 60;
    noteIndex = 2;
    
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
    measureIndex = 63;
    noteIndex = 3;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 77;
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
    measureIndex = 66;
    noteIndex = 4;
    
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
    measureIndex = 69;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 70;
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
    measureIndex = 72;
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
    measureIndex = 75;
    noteIndex = 1;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
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
    measureIndex = 78;
    noteIndex = 2;
    
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
    measureIndex = 81;
    noteIndex = 3;
    
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
    measureIndex = 84;
    noteIndex = 4;
    
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
    measureIndex = 87;
    noteIndex = 5;
    
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
    measureIndex = 90;
    noteIndex = 0;
    
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
    measureIndex = 93;
    noteIndex = 1;
    
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
    measureIndex = 96;
    noteIndex = 2;
    
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
    measureIndex = 99;
    noteIndex = 3;
    
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
    measureIndex = 102;
    noteIndex = 4;
    
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
    measureIndex = 105;
    noteIndex = 5;
    
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
    expectedMidiNumber = 57;
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
    measureIndex = 108;
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
    measureIndex = 111;
    noteIndex = 1;
    
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
    measureIndex = 114;
    noteIndex = 2;
    
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
    measureIndex = 117;
    noteIndex = 3;
    
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
    expectedMidiNumber = 72;
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
    measureIndex = 120;
    noteIndex = 4;
    
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
    measureIndex = 123;
    noteIndex = 5;
    
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
    measureIndex = 126;
    noteIndex = 0;
    
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
    measureIndex = 129;
    noteIndex = 1;
    
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
    measureIndex = 132;
    noteIndex = 2;
    
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
    measureIndex = 135;
    noteIndex = 3;
    
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
    expectedMidiNumber = 48;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 138;
    noteIndex = 4;
    
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
    measureIndex = 141;
    noteIndex = 5;
    
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
    measureIndex = 147;
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
    measureIndex = 150;
    noteIndex = 2;
    
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
    measureIndex = 153;
    noteIndex = 3;
    
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
    measureIndex = 156;
    noteIndex = 4;
    
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
    measureIndex = 159;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 76;
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
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 162;
    noteIndex = 0;
    
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
    measureIndex = 165;
    noteIndex = 1;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 81;
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
    expectedMidiNumber = 55;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 168;
    noteIndex = 2;
    
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
    measureIndex = 171;
    noteIndex = 3;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
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
    measureIndex = 174;
    noteIndex = 4;
    
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
    measureIndex = 177;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 70;
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
    measureIndex = 180;
    noteIndex = 0;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 70;
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
    measureIndex = 183;
    noteIndex = 1;
    
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
    expectedMidiNumber = 58;
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
    measureIndex = 186;
    noteIndex = 2;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
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
    measureIndex = 189;
    noteIndex = 3;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
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
    measureIndex = 195;
    noteIndex = 5;
    
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
    measureIndex = 198;
    noteIndex = 0;
    
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
    measureIndex = 201;
    noteIndex = 1;
    
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
    expectedMidiNumber = 67;
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
    measureIndex = 204;
    noteIndex = 2;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
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
    measureIndex = 207;
    noteIndex = 3;
    
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
    expectedMidiNumber = 70;
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
    measureIndex = 210;
    noteIndex = 4;
    
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
    measureIndex = 213;
    noteIndex = 5;
    
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
    expectedMidiNumber = 60;
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
    measureIndex = 216;
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
    measureIndex = 219;
    noteIndex = 1;
    
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
    expectedMidiNumber = 52;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 222;
    noteIndex = 2;
    
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
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 225;
    noteIndex = 3;
    
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
    measureIndex = 228;
    noteIndex = 4;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
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
    measureIndex = 231;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 70;
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
    expectedMidiNumber = 48;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 234;
    noteIndex = 0;
    
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
    measureIndex = 237;
    noteIndex = 1;
    
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
    measureIndex = 240;
    noteIndex = 2;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 81;
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
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 243;
    noteIndex = 3;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
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
    measureIndex = 246;
    noteIndex = 4;
    
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
    measureIndex = 249;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 70;
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
    measureIndex = 252;
    noteIndex = 0;
    
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
    measureIndex = 255;
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
    measureIndex = 258;
    noteIndex = 2;
    
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
    expectedMidiNumber = 52;
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
    measureIndex = 261;
    noteIndex = 3;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 84;
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
    measureIndex = 264;
    noteIndex = 4;
    
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
    expectedMidiNumber = 41;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 267;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
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
    measureIndex = 270;
    noteIndex = 0;
    
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
    expectedMidiNumber = 64;
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
    measureIndex = 273;
    noteIndex = 1;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 64;
    isAccentExpected = false;
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
    expectedMidiNumber = 67;
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
    measureIndex = 276;
    noteIndex = 2;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
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
    expectedMidiNumber = 70;
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
    measureIndex = 279;
    noteIndex = 3;
    
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
    expectedMidiNumber = 60;
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
    measureIndex = 282;
    noteIndex = 4;
    
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
    expectedMidiNumber = 58;
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
    measureIndex = 285;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
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
    measureIndex = 288;
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
    measureIndex = 291;
    noteIndex = 1;
    
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
    expectedMidiNumber = 57;
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
    measureIndex = 294;
    noteIndex = 2;
    
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
    measureIndex = 297;
    noteIndex = 3;
    
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
    expectedMidiNumber = 53;
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
    measureIndex = 300;
    noteIndex = 4;
    
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
    expectedMidiNumber = 50;
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
    expectedMidiNumber = 60;
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
    expectedMidiNumber = 36;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 306;
    noteIndex = 0;
    
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
    measureIndex = 309;
    noteIndex = 1;
    
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
    measureIndex = 312;
    noteIndex = 2;
    
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
    measureIndex = 315;
    noteIndex = 3;
    
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
    measureIndex = 318;
    noteIndex = 4;
    
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
    measureIndex = 321;
    noteIndex = 5;
    
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
    expectedMidiNumber = 55;
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
    measureIndex = 324;
    noteIndex = 0;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
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
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 327;
    noteIndex = 1;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
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
    measureIndex = 330;
    noteIndex = 2;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 77;
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
    measureIndex = 333;
    noteIndex = 3;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
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
    expectedMidiNumber = 84;
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
    expectedMidiNumber = 62;
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
    measureIndex = 339;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
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
    expectedMidiNumber = 41;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 342;
    noteIndex = 0;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 64;
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
    expectedMidiNumber = 57;
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
    measureIndex = 345;
    noteIndex = 1;
    
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
    measureIndex = 348;
    noteIndex = 2;
    
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
    measureIndex = 351;
    noteIndex = 3;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 77;
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
    expectedMidiNumber = 60;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 354;
    noteIndex = 4;
    
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
    expectedMidiNumber = 69;
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
    noteIndex = 5;
    
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
    measureIndex = 360;
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
    measureIndex = 363;
    noteIndex = 1;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 70;
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
    measureIndex = 366;
    noteIndex = 2;
    
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
    measureIndex = 369;
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
    expectedMidiNumber = 69;
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
    measureIndex = 372;
    noteIndex = 4;
    
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
    expectedMidiNumber = 55;
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
    measureIndex = 375;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
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
    measureIndex = 378;
    noteIndex = 0;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 70;
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
    expectedMidiNumber = 53;
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
    measureIndex = 381;
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
    expectedMidiNumber = 60;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 384;
    noteIndex = 2;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
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
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 387;
    noteIndex = 3;
    
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
    expectedMidiNumber = 55;
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
    measureIndex = 390;
    noteIndex = 4;
    
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
    expectedMidiNumber = 52;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 393;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
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
    expectedMidiNumber = 48;
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
    measureIndex = 396;
    noteIndex = 0;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 72;
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
    expectedMidiNumber = 65;
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
    measureIndex = 402;
    noteIndex = 2;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 64;
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
    expectedMidiNumber = 40;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 405;
    noteIndex = 3;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
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
    expectedMidiNumber = 52;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 408;
    noteIndex = 4;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
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
    expectedMidiNumber = 58;
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
    measureIndex = 411;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
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
    expectedMidiNumber = 70;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 414;
    noteIndex = 0;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 74;
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
    expectedMidiNumber = 57;
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
    measureIndex = 417;
    noteIndex = 1;
    
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
    measureIndex = 420;
    noteIndex = 2;
    
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
    expectedMidiNumber = 52;
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
    measureIndex = 423;
    noteIndex = 3;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
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
    measureIndex = 426;
    noteIndex = 4;
    
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
    expectedMidiNumber = 57;
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
    measureIndex = 429;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
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
    measureIndex = 432;
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
    measureIndex = 435;
    noteIndex = 1;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 72;
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
    expectedMidiNumber = 57;
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
    expectedMidiNumber = 74;
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
    measureIndex = 441;
    noteIndex = 3;
    
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
    expectedMidiNumber = 57;
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
    expectedMidiNumber = 74;
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
    expectedMidiNumber = 41;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 447;
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
    expectedMidiNumber = 64;
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
    measureIndex = 450;
    noteIndex = 0;
    
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
    expectedMidiNumber = 65;
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
    measureIndex = 453;
    noteIndex = 1;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
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
    expectedMidiNumber = 43;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 456;
    noteIndex = 2;
    
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
    measureIndex = 459;
    noteIndex = 3;
    
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
    expectedMidiNumber = 67;
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
    measureIndex = 462;
    noteIndex = 4;
    
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
    measureIndex = 465;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
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
    measureIndex = 468;
    noteIndex = 0;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 81;
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
    measureIndex = 471;
    noteIndex = 1;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
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
    expectedMidiNumber = 38;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 474;
    noteIndex = 2;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
    isAccentExpected = false;
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
    measureIndex = 477;
    noteIndex = 3;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
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
    measureIndex = 480;
    noteIndex = 4;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 70;
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
    expectedMidiNumber = 46;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 486;
    noteIndex = 0;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
    isAccentExpected = false;
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
    expectedMidiNumber = 52;
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
    measureIndex = 489;
    noteIndex = 1;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 81;
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
    expectedMidiNumber = 60;
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
    measureIndex = 492;
    noteIndex = 2;
    
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
    expectedMidiNumber = 72;
    isAccentExpected = true;
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
    measureIndex = 495;
    noteIndex = 3;
    
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
    expectedMidiNumber = 53;
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
    measureIndex = 498;
    noteIndex = 4;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
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
    expectedMidiNumber = 50;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 501;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
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
    expectedMidiNumber = 48;
    isAccentExpected = true;
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
    measureIndex = 504;
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
    measureIndex = 507;
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
    measureIndex = 510;
    noteIndex = 2;
    
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
    measureIndex = 513;
    noteIndex = 3;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 81;
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
    measureIndex = 516;
    noteIndex = 4;
    
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
    measureIndex = 519;
    noteIndex = 5;
    
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
    expectedMidiNumber = 52;
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
    measureIndex = 522;
    noteIndex = 0;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 84;
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
    expectedMidiNumber = 70;
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
    measureIndex = 525;
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
    measureIndex = 528;
    noteIndex = 2;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
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
    expectedMidiNumber = 57;
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
    measureIndex = 531;
    noteIndex = 3;
    
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
    measureIndex = 534;
    noteIndex = 4;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 76;
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
    measureIndex = 537;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 64;
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
    expectedMidiNumber = 62;
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
    measureIndex = 540;
    noteIndex = 0;
    
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
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 543;
    noteIndex = 1;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 62;
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
    measureIndex = 546;
    noteIndex = 2;
    
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
    measureIndex = 549;
    noteIndex = 3;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 81;
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
    expectedMidiNumber = 70;
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
    measureIndex = 552;
    noteIndex = 4;
    
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
    measureIndex = 555;
    noteIndex = 5;
    
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
    measureIndex = 558;
    noteIndex = 0;
    
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
    measureIndex = 561;
    noteIndex = 1;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 84;
    isAccentExpected = true;
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
    expectedMidiNumber = 58;
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
    measureIndex = 564;
    noteIndex = 2;
    
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
    expectedMidiNumber = 57;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 567;
    noteIndex = 3;
    
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
    expectedMidiNumber = 72;
    isAccentExpected = true;
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
    measureIndex = 570;
    noteIndex = 4;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 79;
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
    expectedMidiNumber = 69;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 573;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 77;
    isAccentExpected = false;
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
    expectedMidiNumber = 53;
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
    measureIndex = 576;
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
    measureIndex = 579;
    noteIndex = 1;
    
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
    expectedMidiNumber = 50;
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
    measureIndex = 582;
    noteIndex = 2;
    
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
    expectedMidiNumber = 55;
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
    measureIndex = 585;
    noteIndex = 3;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 60;
    isAccentExpected = true;
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
    measureIndex = 588;
    noteIndex = 4;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 69;
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
    expectedMidiNumber = 45;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 591;
    noteIndex = 5;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
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
    expectedMidiNumber = 72;
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
    measureIndex = 594;
    noteIndex = 0;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
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
    expectedMidiNumber = 58;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    partIndex = CELLO;
    expectedMidiNumber = 60;
    isAccentExpected = true;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 597;
    noteIndex = 1;
    
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
    expectedMidiNumber = 52;
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
    measureIndex = 600;
    noteIndex = 2;
    
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
    measureIndex = 603;
    noteIndex = 3;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 72;
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
    expectedMidiNumber = 60;
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
    measureIndex = 606;
    noteIndex = 4;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 76;
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
    expectedMidiNumber = 64;
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
    measureIndex = 609;
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
    expectedMidiNumber = 52;
    isAccentExpected = false;
    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );
    atom = scriabin::Atom{ mxNote.pitchData };
    
    CHECK( atom.getMidiNote() == expectedMidiNumber );
    CHECK( isAccented( mxNote ) == isAccentExpected );
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    measureIndex = 612;
    noteIndex = 0;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 67;
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
    measureIndex = 615;
    noteIndex = 1;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 82;
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
    expectedMidiNumber = 70;
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
    measureIndex = 618;
    noteIndex = 2;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 70;
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
    measureIndex = 621;
    noteIndex = 3;
    
    partIndex = VIOLIN_1;
    expectedMidiNumber = 65;
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
    measureIndex = 624;
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
}
