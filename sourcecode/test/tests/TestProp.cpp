#include "catch.hpp"
#include "PEN_PATH.h"
#include "pen/Prob.h"

using namespace pen;

TEST_CASE( "Prob test001", "Prob" )
{
    Prob prob{ DIGITS_DAT_PATH() };
    CHECK( prob.get( 100 ) );
    CHECK( !prob.get( 0 ) );
    
    int probability = 50;
    int trueCount = 0;
    int falseCount = 0;
    
    for( int i = 0; i < 100000; ++i )
    {
        if( prob.get( probability ) )
        {
            ++trueCount;
        }
        else
        {
            ++falseCount;
        }
    }
    
    auto pctTrue = static_cast<double>( trueCount ) / ( static_cast<double>( trueCount ) + static_cast<double>( falseCount ) );
    double expected = static_cast<double>( probability ) / 100.0;
    CHECK( pctTrue == Approx( expected ).epsilon( 0.01 ) );
    
    probability = 75;
    trueCount = 0;
    falseCount = 0;
    
    for( int i = 0; i < 100000; ++i )
    {
        if( prob.get( probability ) )
        {
            ++trueCount;
        }
        else
        {
            ++falseCount;
        }
    }
    
    pctTrue = static_cast<double>( trueCount ) / ( static_cast<double>( trueCount ) + static_cast<double>( falseCount ) );
    expected = static_cast<double>( probability ) / 100.0;
    CHECK( pctTrue == Approx( expected ).epsilon( 0.01 ) );
    
    probability = 25;
    trueCount = 0;
    falseCount = 0;
    
    for( int i = 0; i < 100000; ++i )
    {
        if( prob.get( probability ) )
        {
            ++trueCount;
        }
        else
        {
            ++falseCount;
        }
    }
    
    pctTrue = static_cast<double>( trueCount ) / ( static_cast<double>( trueCount ) + static_cast<double>( falseCount ) );
    expected = static_cast<double>( probability ) / 100.0;
    CHECK( pctTrue == Approx( expected ).epsilon( 0.02 ) );
}
