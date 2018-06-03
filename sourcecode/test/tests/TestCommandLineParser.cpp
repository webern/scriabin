#include "catch.hpp"
#include "pen/CommandLineParser.h"

using namespace zeus;

TEST_CASE( "CommandLineParser test001", "CommandLineParser" )
{
    std::vector<CommandLineArgumentPrototype> protos;
    protos.emplace_back( CommandLineArgumentPrototype{ "help", 'h', "Display help options" } );
    protos.emplace_back( CommandLineArgumentPrototype{ "output", 'o', "The path to the desired output file" } );
    
    constexpr const int argc = 2;
    const char * argv[argc] = {
        "/some/path/to/the/executable",
        "-h",
    };
        
    CommandLineParser clp{ protos };
    clp.parse( argc, argv );
    CHECK( "/some/path/to/the/executable" == clp.getExecutablePath() );
    CHECK( clp.getCommandLineValue( "help" ).getIsPresent() );
    CHECK( !clp.getCommandLineValue( "output" ).getIsPresent() );
    clp.clearValues();
    CHECK( !clp.getCommandLineValue( "help" ).getIsPresent() );
    CHECK( !clp.getCommandLineValue( "output" ).getIsPresent() );
}

TEST_CASE( "CommandLineParser test002", "CommandLineParser" )
{
    std::vector<CommandLineArgumentPrototype> protos;
    protos.emplace_back( CommandLineArgumentPrototype{ "help", 'h', "Display help options" } );
    protos.emplace_back( CommandLineArgumentPrototype{ "output", 'o', "The path to the desired output file" } );
    
    constexpr const int argc = 2;
    const char * argv[argc] = {
        "/some/path/to/the/executable",
        "--help",
    };
    
    CommandLineParser clp{ protos };
    clp.parse( argc, argv );
    CHECK( "/some/path/to/the/executable" == clp.getExecutablePath() );
    CHECK( clp.getCommandLineValue( "help" ).getIsPresent() );
    CHECK( !clp.getCommandLineValue( "output" ).getIsPresent() );
    clp.clearValues();
    CHECK( !clp.getCommandLineValue( "help" ).getIsPresent() );
    CHECK( !clp.getCommandLineValue( "output" ).getIsPresent() );
}

TEST_CASE( "CommandLineParser test003", "CommandLineParser" )
{
    std::vector<CommandLineArgumentPrototype> protos;
    protos.emplace_back( CommandLineArgumentPrototype{ "help", 'h', "Display help options" } );
    protos.emplace_back( CommandLineArgumentPrototype{ "output", 'o', "The path to the desired output file" } );
    
    constexpr const int argc = 4;
    const char * argv[argc] = {
        "/some/path/to/the/executable",
        "--output",
        "some/file/path.xml",
        "some/file/other/path.xml",
    };
    
    CommandLineParser clp{ protos };
    clp.parse( argc, argv );
    CHECK( "/some/path/to/the/executable" == clp.getExecutablePath() );
    CHECK( !clp.getCommandLineValue( "help" ).getIsPresent() );
    CHECK( clp.getCommandLineValue( "output" ).getIsPresent() );
    const auto& o = clp.getCommandLineValue( "output" );
    CHECK( 2 == o.getValues().size() );
    CHECK( "some/file/path.xml" == o.getValues().at(0) );
    CHECK( "some/file/other/path.xml" == o.getValues().at(1) );
    clp.clearValues();
    CHECK( !clp.getCommandLineValue( "help" ).getIsPresent() );
    CHECK( !clp.getCommandLineValue( "output" ).getIsPresent() );
}
