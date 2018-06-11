#pragma once
#include "pen/CommandLineParser.h"
#include "pen/cmd.h"
#include "pen/InstrumentConfig.h"
#include "ezxml/ezxml.h"

namespace pen
{
    struct Program
    {
    public:
        Program()
        : parser{ std::vector<zeus::CommandLineArgumentPrototype>{} }
        , isOutfileSpecified{ false }
        , isInstrumentConfigSpecified{ false }
        , instrumentConfigPath{}
        , instrumentConfig{}
        {
            
        }
        
        Program( int argc, const char* argv[] )
        : Program{}
        {
            setParser( argc, argv );
            setOutfile();
            setInstrumentConfig();
        }
        
    public:
        zeus::CommandLineParser parser;
        bool isOutfileSpecified;
        std::string outfilePath;
        bool isInstrumentConfigSpecified;
        std::string instrumentConfigPath;
        InstrumentConfig instrumentConfig;
        
    private:
        
        inline void
        setParser(  int argc, const char* argv[] )
        {
            parser = pen::cmd( argc, argv );
        }
        
        inline void
        setFromArg( char arg, std::string& outValue, bool& outIsSet, std::string defaultValue = "unset" )
        {
            const auto& clv = parser.getCommandLineValue( arg );
            const bool isPresent = clv.getIsPresent();
            const bool isEmpty = clv.getIsEmpty();
            outIsSet = isPresent && !isEmpty;
            outValue = defaultValue;

            if( outIsSet )
            {
                const auto& values = clv.getValues();
                outValue = values.front();
            }
        }

        inline void
        setOutfile()
        {
            setFromArg( 'o', this->outfilePath, this->isOutfileSpecified, "./output.xml" );
        }
        
        inline void
        setInstrumentConfig()
        {
            setFromArg( 'n', this->instrumentConfigPath, this->isInstrumentConfigSpecified );
            if( this->isInstrumentConfigSpecified )
            {
                auto xdoc = ezxml::XFactory::makeXDoc();
                xdoc->loadFile( this->instrumentConfigPath );
                this->instrumentConfig = InstrumentConfig{ *xdoc };
            }
        }
    };
}
