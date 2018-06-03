#include "pen/CommandLineArgumentPrototype.h"

namespace zeus
{
    CommandLineArgumentPrototype::CommandLineArgumentPrototype( std::string inFullName, char inShortName, std::string inDescription )
    : myFullName{ std::move( inFullName ) }
    , myShortName{ inShortName }
    , myDescription{ std::move( inDescription ) }
    {
        
    }
    
    
    const std::string&
    CommandLineArgumentPrototype::getFullName() const
    {
        return myFullName;
    }
    
    
    char
    CommandLineArgumentPrototype::getShortName() const
    {
        return myShortName;
    }
    
    
    const std::string&
    CommandLineArgumentPrototype::getDescription() const
    {
        return myDescription;
    }
}
