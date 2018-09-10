#pragma once
#include <cstdint>
#include <vector>

namespace scriabin
{
    class Prob
    {
    public:
        Prob( const std::string& inDigitsFilepath );
        
        // returns a pseudo random bool where the probability
        // of true is given by the input parameter in percent
        // from 0 to 100
        bool get( int inProbability );
        
    private:
        std::vector<int> myData;
        std::vector<int>::const_iterator myIter;
        std::vector<int>::const_iterator myEnd;
        
    private:
        void initFromFile( const std::string& inDigitsFilepath );
    };
}
