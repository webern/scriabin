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

    for( int m = 0, n = 0; m < 626; m += 3, ++n )
    {
        n = n % 6;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int insideMeasureIndex = m;
        int insideNoteIndex = n;
        std::stringstream ss;
        ss.setf( std::ios_base::boolalpha );

        ss << "    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////"
           << std::endl;
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
        ss << "    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );"
           << std::endl;
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
        ss << "    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );"
           << std::endl;
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
        ss << "    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );"
           << std::endl;
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
        ss << "    mxNote = score.parts.at( partIndex ).measures.at( measureIndex ).staves.at( 0 ).voices.at( 0 ).notes.at( noteIndex );"
           << std::endl;
        ss << "    atom = scriabin::Atom{ mxNote.pitchData };" << std::endl;
        ss << "" << std::endl;
        ss << "    CHECK( atom.getMidiNote() == expectedMidiNumber );" << std::endl;
        ss << "    CHECK( isAccented( mxNote ) == isAccentExpected );" << std::endl;

        // uncomment to generate tests
        // std::cout << ss.str() << std::endl;
    } // end test generation loop


}
