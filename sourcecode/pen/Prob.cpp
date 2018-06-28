#include "Prob.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace pen
{
    Prob::Prob( const std::string& inDigitsFilepath )
    : myData{}
    , myIter{}
    , myEnd{}
    {
        initFromFile( inDigitsFilepath );
    }
    
    
    bool
    Prob::get( int inProbability )
    {
        const auto val = *myIter;
        ++myIter;
        
        if( myIter == myEnd )
        {
            myIter = myData.cbegin();
        }
        
        return val < inProbability;
    }
    
    
    void
    Prob::initFromFile( const std::string& inDigitsFilepath )
    {
        std::ifstream ifile{ inDigitsFilepath };
        if( !ifile.is_open() )
        {
            std::stringstream ss;
            ss << "Prob::initFromFile: cannot read file '" << inDigitsFilepath << "'";
            throw std::runtime_error{ ss.str() };
        }
        
        char c;
        while ( ifile >> c )
        {
            if( c >= '0' && c <= '9' )
            {
                int firstDigit = static_cast<int>( ( c - '0' ) * 10 );
                
                if( ifile >> c )
                {
                    int secondDigit = static_cast<int>( ( c - '0' ) );
                    int val = firstDigit + secondDigit;
                    myData.push_back( val );
                }
            }
        }
        
        if( myData.empty() )
        {
            throw std::runtime_error{ "data file had no digits" };
        }
        
        myIter = myData.cbegin();
        myEnd = myData.cend();
    }
}
