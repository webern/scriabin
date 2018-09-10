#pragma once
#include <string>

namespace zeus
{
    class CommandLineArgumentPrototype
    {
    public:
        CommandLineArgumentPrototype( std::string inFullName, char inShortName, std::string inDescription );
        
        const std::string& getFullName() const;
        char getShortName() const;
        const std::string& getDescription() const;
        
    private:
        std::string myFullName;
        char myShortName;
        std::string myDescription;
    };
}
