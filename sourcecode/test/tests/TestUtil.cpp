#include "catch.hpp"
#include "pen/util.h"

using namespace scriabin;

TEST_CASE( "util test001", "util" )
{
    mx::api::PitchData p;
    p.step = mx::api::Step::c;
    p.alter = -1;
    p.accidental = mx::api::Accidental::flat;
    const auto pitchClass = getPitchClass( p );
    const auto pitchData = getPitchDataFromPitchClass( pitchClass );
    CHECK( pitchData.step == mx::api::Step::b );
    CHECK( pitchData.accidental == mx::api::Accidental::natural );
    CHECK( 0 == pitchData.alter );
}

TEST_CASE( "util test002", "util" )
{
    mx::api::PitchData p;
    p.step = mx::api::Step::e;
    p.alter = 1;
    p.accidental = mx::api::Accidental::sharp;
    const auto pitchClass = getPitchClass( p );
    const auto pitchData = getPitchDataFromPitchClass( pitchClass );
    CHECK( pitchData.step == mx::api::Step::f );
    CHECK( pitchData.accidental == mx::api::Accidental::natural );
    CHECK( 0 == pitchData.alter );
}

TEST_CASE( "util test003", "util" )
{
    const int midiNote = 0;
    const int actual = getPitchClassFromMidiNote( midiNote );
    const int expected = 0;
    CHECK( expected == actual );
}

TEST_CASE( "util test004", "util" )
{
    const int midiNote = 1;
    const int actual = getPitchClassFromMidiNote( midiNote );
    const int expected = 1;
    CHECK( expected == actual );
}

TEST_CASE( "util test005", "util" )
{
    const int midiNote = 11;
    const int actual = getPitchClassFromMidiNote( midiNote );
    const int expected = 11;
    CHECK( expected == actual );
}

TEST_CASE( "util test006", "util" )
{
    const int midiNote = 12;
    const int actual = getPitchClassFromMidiNote( midiNote );
    const int expected = 0;
    CHECK( expected == actual );
}

TEST_CASE( "util test007", "util" )
{
    const int midiNote = 13;
    const int actual = getPitchClassFromMidiNote( midiNote );
    const int expected = 1;
    CHECK( expected == actual );
}

TEST_CASE( "util test008", "util" )
{
    const int midiNote = 0 + ( 12 * 6 );
    const int actual = getPitchClassFromMidiNote( midiNote );
    const int expected = 0;
    CHECK( expected == actual );
}

TEST_CASE( "util test009", "util" )
{
    const int midiNote = 1 + ( 12 * 6 );
    const int actual = getPitchClassFromMidiNote( midiNote );
    const int expected = 1;
    CHECK( expected == actual );
}

TEST_CASE( "util test010", "util" )
{
    const int midiNote = 11 + ( 12 * 6 );
    const int actual = getPitchClassFromMidiNote( midiNote );
    const int expected = 11;
    CHECK( expected == actual );
}

TEST_CASE( "util test011", "util" )
{
    const int midiNote = 12 + ( 12 * 6 );
    const int actual = getPitchClassFromMidiNote( midiNote );
    const int expected = 0;
    CHECK( expected == actual );
}

TEST_CASE( "util test012", "util" )
{
    const int midiNote = 13 + ( 12 * 6 );
    const int actual = getPitchClassFromMidiNote( midiNote );
    const int expected = 1;
    CHECK( expected == actual );
}

TEST_CASE( "util test013", "util" )
{
    const int midiNote = -1 + ( 12 * 6 );
    const int actual = getPitchClassFromMidiNote( midiNote );
    const int expected = 11;
    CHECK( expected == actual );
}
