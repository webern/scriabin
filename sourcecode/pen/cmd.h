#pragma once
#include "pen/CommandLineParser.h"

namespace scriabin
{
    inline const zeus::CommandLineParser
    cmd( int argc, const char* argv[] )
    {
        std::vector<zeus::CommandLineArgumentPrototype> switches;
        switches.emplace_back( zeus::CommandLineArgumentPrototype{ "help", 'h', "Display help options" } );
        switches.emplace_back( zeus::CommandLineArgumentPrototype{ "output", 'o', "The path to the desired output file" } );
        switches.emplace_back( zeus::CommandLineArgumentPrototype{ "instrument-config", 'n', "The path to the instrument configuration xml file" } );
        zeus::CommandLineParser parser{ switches };
        parser.parse( argc, argv );
        return parser;
    }
}
