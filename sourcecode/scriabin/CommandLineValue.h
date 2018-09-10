#pragma once

#include "scriabin/CommandLineArgumentPrototype.h"
#include <string>
#include <vector>

namespace zeus
{
    class CommandLineValue
    {
    public:
        CommandLineValue( CommandLineArgumentPrototype inPrototype );
        
        const CommandLineArgumentPrototype& getPrototype() const;
        const std::vector<std::string>& getValues() const;
        bool getIsEmpty() const;
        bool getIsPresent() const;
        void setIsPresent( bool inIsPresent );
        void setValues( std::vector<std::string> inValues );
        void addValue( std::string inValue );
        void clearValues();
        
    private:
        CommandLineArgumentPrototype myPrototype;
        bool myIsPresent;
        std::vector<std::string> myValues;
    };
}
