#include "catch.hpp"
#include "pen/etude1.h"
#include "PEN_PATH.h"
#include "mx/api/DocumentManager.h"
#include "mx/api/ScoreData.h"

using namespace zeus;

TEST_CASE( "etude1", "Comp" )
{
    const auto& iConfig = pen::INSTRUMENT_CONFIG_FILEPATH();
    const auto& oDir = pen::OUTPUT_DIRECTORY();
    const std::string oPath = oDir + std::string{ "etude1.actual.xml" };
    constexpr const int argc = 5;
    const char * argv[argc] =
    {
        "/some/path/to/the/executable",
        "-o",
        oPath.c_str(),
        "--instrument-config",
        iConfig.c_str()
    };
    etude1(argc, argv);
    
    auto& dmgr = mx::api::DocumentManager::getInstance();
    const auto outDocId = dmgr.createFromFile( oPath );
    const auto actualScore = dmgr.getData( outDocId );
    dmgr.destroyDocument( outDocId );
    
    const auto inDocId = dmgr.createFromFile( pen::TEST_FILES_DIRECTORY() + std::string{ "etude1.expected.xml" } );
    const auto expectedScore = dmgr.getData( inDocId );
    dmgr.destroyDocument( inDocId );
    
    REQUIRE( expectedScore.getNumMeasures() == actualScore.getNumMeasures() );
    REQUIRE( expectedScore.getNumStavesPerSystem() == actualScore.getNumStavesPerSystem() );
    CHECK( expectedScore.arranger == actualScore.arranger );
    CHECK( expectedScore.composer == actualScore.composer );
    CHECK( expectedScore.copyright == actualScore.copyright );
    REQUIRE( expectedScore.partGroups.size() == actualScore.partGroups.size() );
    
    for( size_t i = 0; i < expectedScore.partGroups.size(); ++i )
    {
        const auto& expg = expectedScore.partGroups.at( i );
        const auto& axpg = actualScore.partGroups.at( i );
        CHECK( expg.abbreviation == axpg.abbreviation );
        CHECK( expg.bracketType == axpg.bracketType );
        CHECK( expg.displayAbbreviation == axpg.displayAbbreviation );
        CHECK( expg.displayName == axpg.displayName );
        CHECK( expg.firstPartIndex == axpg.firstPartIndex );
        CHECK( expg.lastPartIndex == axpg.lastPartIndex );
        CHECK( expg.name == axpg.name );
        CHECK( expg.number == axpg.number );
    }
    
    
    REQUIRE( expectedScore.parts.size() == actualScore.parts.size() );
    
    for( size_t i = 0; i < expectedScore.partGroups.size(); ++i )
    {
        const auto& expt = expectedScore.parts.at( i );
        const auto& acpt = actualScore.parts.at( i );
        CHECK( expt.getMaxVoice() == acpt.getMaxVoice() );
        CHECK( expt.getNumStaves() == acpt.getNumStaves() );
        CHECK( expt.abbreviation == acpt.abbreviation );
        CHECK( expt.name == acpt.name );
        CHECK( expt.displayAbbreviation == acpt.displayAbbreviation );
        CHECK( expt.displayName == acpt.displayName );
        CHECK( expt.uniqueId == acpt.uniqueId );
        REQUIRE( expt.measures.size() == acpt.measures.size() );
        
        for( size_t j = 0; j < expt.measures.size(); ++j )
        {
            const auto& expm = expt.measures.at( j );
            const auto& actm = acpt.measures.at( j );
            CHECK( expm.keys.size() == actm.keys.size() );
            CHECK( expm.number == actm.number );
            CHECK( expm.timeSignature == actm.timeSignature );
            REQUIRE( expm.staves.size() == actm.staves.size() );
            
            for( size_t k = 0; k < expm.staves.size(); ++k )
            {
                const auto& expectedStaff = expm.staves.at( k );
                const auto& actualStaff = actm.staves.at( k );
                REQUIRE( expectedStaff.clefs.size() == actualStaff.clefs.size() );
                REQUIRE( expectedStaff.clefs.size() <= 1 );
                
                if( expectedStaff.clefs.size() == 1 )
                {
                    CHECK( expectedStaff.clefs.at( 0 ) == actualStaff.clefs.at( 0 ) );
                }
                
                CHECK( expectedStaff.directions == actualStaff.directions );
                REQUIRE( expectedStaff.voices.size() == actualStaff.voices.size() );
                
                for( const auto& expectedVoicePair : expectedStaff.voices )
                {
                    const auto& expectedVoice = expectedVoicePair.second;
                    const auto& actualVoice = expectedStaff.voices.at( expectedVoicePair.first );
                    
                    REQUIRE( expectedVoice.notes.size() == actualVoice.notes.size() );
                    
                    for( size_t l = 0; l < expectedVoice.notes.size(); ++l )
                    {
                        const auto& expectedNote = expectedVoice.notes.at( l );
                        const auto& actualNote = actualVoice.notes.at( l );
                        CHECK( expectedNote == actualNote );
                    }
                }
            }
        }
    }
}
