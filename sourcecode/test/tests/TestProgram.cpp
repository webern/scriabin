#include "catch.hpp"
#include "pen/Program.h"
#include "PEN_PATH.h"

using namespace zeus;

TEST_CASE( "Program test001", "Program" )
{
    const std::string opath = "/my/path.xml";
    const std::string ipath = pen::INSTRUMENT_CONFIG_FILEPATH();
    
    constexpr const int argc = 5;
    const char* argv[argc] = {
        "/some/path/to/the/executable",
        "-o",
        opath.c_str(),
        "--instrument-config",
        ipath.c_str(),
    };
    
    pen::Program program{ argc, argv };
    CHECK( program.isOutfileSpecified );
    CHECK( opath == program.outfilePath.c_str() );
    CHECK( program.isInstrumentConfigSpecified );
    CHECK( ipath == program.instrumentConfigPath.c_str() );
    
//    std::vector<CommandLineArgumentPrototype> protos;
//    protos.emplace_back( CommandLineArgumentPrototype{ "help", 'h', "Display help options" } );
//    protos.emplace_back( CommandLineArgumentPrototype{ "output", 'o', "The path to the desired output file" } );
//

//
//    CommandLineParser clp{ protos };
//    clp.parse( argc, argv );
//    CHECK_EQUAL( "/some/path/to/the/executable", clp.getExecutablePath() );
//    CHECK( clp.getCommandLineValue( "help" ).getIsPresent() )
//    CHECK( !clp.getCommandLineValue( "output" ).getIsPresent() )
//    clp.clearValues();
//    CHECK( !clp.getCommandLineValue( "help" ).getIsPresent() )
//    CHECK( !clp.getCommandLineValue( "output" ).getIsPresent() )
}

