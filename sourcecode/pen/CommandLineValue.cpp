
#include "pen/CommandLineValue.h"

namespace zeus
{
    CommandLineValue::CommandLineValue( CommandLineArgumentPrototype inPrototype )
    : myPrototype{ std::move( inPrototype ) }
    , myIsPresent{ false }
    , myValues{}
    {
        
    }
    
    const CommandLineArgumentPrototype&
    CommandLineValue::getPrototype() const
    {
        return myPrototype;
    }


    const std::vector<std::string>&
    CommandLineValue::getValues() const
    {
        return myValues;
    }
    
    
    bool
    CommandLineValue::getIsEmpty() const
    {
        const auto isEmpty = myValues.empty();
        return isEmpty;
    }
    
    
    bool
    CommandLineValue::getIsPresent() const
    {
        return myIsPresent;
    }
    
    
    void
    CommandLineValue::setIsPresent( bool inIsPresent )
    {
        myIsPresent = inIsPresent;
    }


    void
    CommandLineValue::setValues( std::vector<std::string> inValues )
    {
        myValues = std::move( inValues );
    }

    
    void
    CommandLineValue::addValue( std::string inValue )
    {
        myValues.emplace_back( std::move( inValue ) );
    }

    
    void
    CommandLineValue::clearValues()
    {
        myValues.clear();
        myIsPresent = false;
    }
}
