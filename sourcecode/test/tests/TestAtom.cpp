#include "catch.hpp"
#include "pen/Atom.h"
#include "pen/Constants.h"
#include <limits>

using namespace scriabin;

TEST_CASE( "getMidiNote rest", "Atom" )
{
    const std::string expectedName = "rest";
    const int expectedMidiNote = std::numeric_limits<int>::min();
    const int step = -1;
    const int alter = 0;
    const int octave = 4;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}

TEST_CASE( "getMidiNote C4 60", "Atom" )
{
    const std::string expectedName = "C4";
    const int expectedMidiNote = 60;
    const int step = STEP_C;
    const int alter = 0;
    const int octave = 4;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}

TEST_CASE( "getMidiNote C#4 61", "Atom" )
{
    const std::string expectedName = "C#4";
    const int expectedMidiNote = 61;
    const int step = STEP_C;
    const int alter = 1;
    const int octave = 4;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}

TEST_CASE( "getMidiNote D4 62", "Atom" )
{
    const std::string expectedName = "D4";
    const int expectedMidiNote = 62;
    const int step = STEP_D;
    const int alter = 0;
    const int octave = 4;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote D#4 63", "Atom" )
{
    const std::string expectedName = "D#4";
    const int expectedMidiNote = 63;
    const int step = STEP_D;
    const int alter = 1;
    const int octave = 4;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote B-2 -1", "Atom" )
{
    const std::string expectedName = "B-2";
    const int expectedMidiNote = -1;
    const int step = STEP_B;
    const int alter = 0;
    const int octave = -2;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote Cb-1 -1", "Atom" )
{
    const std::string expectedName = "Cb-1";
    const int expectedMidiNote = -1;
    const int step = STEP_C;
    const int alter = -1;
    const int octave = -1;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote Ax-2 -1", "Atom" )
{
    const std::string expectedName = "Ax-2";
    const int expectedMidiNote = -1;
    const int step = STEP_A;
    const int alter = 2;
    const int octave = -2;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote Bb-2 -2", "Atom" )
{
    const std::string expectedName = "Bb-2";
    const int expectedMidiNote = -2;
    const int step = STEP_B;
    const int alter = -1;
    const int octave = -2;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote A3 57", "Atom" )
{
    const std::string expectedName = "A3";
    const int expectedMidiNote = 57;
    const int step = STEP_A;
    const int alter = 0;
    const int octave = 3;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote G#3 56", "Atom" )
{
    const std::string expectedName = "G#3";
    const int expectedMidiNote = 56;
    const int step = STEP_G;
    const int alter = 1;
    const int octave = 3;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote Bb3 58", "Atom" )
{
    const std::string expectedName = "Bb3";
    const int expectedMidiNote = 58;
    const int step = STEP_B;
    const int alter = -1;
    const int octave = 3;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote Ab2 44", "Atom" )
{
    const std::string expectedName = "Ab2";
    const int expectedMidiNote = 44;
    const int step = STEP_A;
    const int alter = -1;
    const int octave = 2;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote E5 76", "Atom" )
{
    const std::string expectedName = "E5";
    const int expectedMidiNote = 76;
    const int step = STEP_E;
    const int alter = 0;
    const int octave = 5;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote G#1 32", "Atom" )
{
    const std::string expectedName = "G#1";
    const int expectedMidiNote = 32;
    const int step = STEP_G;
    const int alter = 1;
    const int octave = 1;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote A0 21", "Atom" )
{
    const std::string expectedName = "A0";
    const int expectedMidiNote = 21;
    const int step = STEP_A;
    const int alter = 0;
    const int octave = 0;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote B3 59", "Atom" )
{
    const std::string expectedName = "B3";
    const int expectedMidiNote = 59;
    const int step = STEP_B;
    const int alter = 0;
    const int octave = 3;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote Cb4 59", "Atom" )
{
    const std::string expectedName = "Cb4";
    const int expectedMidiNote = 59;
    const int step = STEP_C;
    const int alter = -1;
    const int octave = 4;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote Fx7 103", "Atom" )
{
    const std::string expectedName = "Fx7";
    const int expectedMidiNote = 103;
    const int step = STEP_F;
    const int alter = 2;
    const int octave = 7;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote Ab6 92", "Atom" )
{
    const std::string expectedName = "Ab6";
    const int expectedMidiNote = 92;
    const int step = STEP_A;
    const int alter = -1;
    const int octave = 6;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote B#6 96", "Atom" )
{
    const std::string expectedName = "B#6";
    const int expectedMidiNote = 96;
    const int step = STEP_B;
    const int alter = 1;
    const int octave = 6;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote Dbb7 96", "Atom" )
{
    const std::string expectedName = "Dbb7";
    const int expectedMidiNote = 96;
    const int step = STEP_D;
    const int alter = -2;
    const int octave = 7;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote Abb-1 7", "Atom" )
{
    const std::string expectedName = "Abb-1";
    const int expectedMidiNote = 7;
    const int step = STEP_A;
    const int alter = -2;
    const int octave = -1;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote Fx-1 7", "Atom" )
{
    const std::string expectedName = "Fx-1";
    const int expectedMidiNote = 7;
    const int step = STEP_F;
    const int alter = 2;
    const int octave = -1;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote G-1 7", "Atom" )
{
    const std::string expectedName = "G-1";
    const int expectedMidiNote = 7;
    const int step = STEP_G;
    const int alter = 0;
    const int octave = -1;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote B#-2 0", "Atom" )
{
    const std::string expectedName = "B#-2";
    const int expectedMidiNote = 0;
    const int step = STEP_B;
    const int alter = 1;
    const int octave = -2;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote Eb-2 -9", "Atom" )
{
    const std::string expectedName = "Eb-2";
    const int expectedMidiNote = -9;
    const int step = STEP_E;
    const int alter = -1;
    const int octave = -2;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}


TEST_CASE( "getMidiNote F#-2 -6", "Atom" )
{
    const std::string expectedName = "F#-2";
    const int expectedMidiNote = -6;
    const int step = STEP_F;
    const int alter = 1;
    const int octave = -2;
    const Atom atom{ step, alter, octave };
    CHECK( atom.getName() == expectedName );
    CHECK( atom.getMidiNote() == expectedMidiNote );
}
