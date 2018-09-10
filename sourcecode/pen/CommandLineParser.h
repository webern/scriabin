#pragma once
#include <map>

#include "scriabin/CommandLineValue.h"

namespace zeus
{
    class CommandLineParser
    {
    public:
        CommandLineParser( const std::vector<CommandLineArgumentPrototype>& inPrototypes );
        CommandLineParser( const CommandLineParser& other );
        CommandLineParser( CommandLineParser&& other );
        CommandLineParser& operator=( const CommandLineParser& other );
        CommandLineParser& operator=( CommandLineParser&& other );
        
    public:
        bool parse( int argc, const char* argv[] );
        void clearValues();
        const CommandLineValue& getCommandLineValue( const std::string& inLongName ) const;
        const CommandLineValue& getCommandLineValue( const char inShortName ) const;
        const std::string& getExecutablePath() const;
        
    private:
        std::vector<std::string> myArgs;
        std::map<std::string, std::unique_ptr<CommandLineValue>> myValues;
        std::map<char, CommandLineValue*> myShortLookup;
        std::string myExecutablePath;
        
    private:
        CommandLineParser();
        CommandLineValue* getCommandLineValuePtr( const std::string& inLongName );
        CommandLineValue* getCommandLineValuePtr( const char inShortName );
        const CommandLineValue* getCommandLineValueConstPtr( const std::string& inLongName ) const;
        const CommandLineValue* getCommandLineValueConstPtr( const char inShortName ) const;
        void copyState( const CommandLineParser& other );
        void moveState( CommandLineParser&& other );
    };
}
