#pragma once

#include "mx/api/ScoreData.h"
#include <string>
#include <vector>
#include <sstream>

namespace pen
{
    struct June3Constants
    {
        const std::string outFilename = "coalescence.large.xml";
        const std::string inFilename = "coalescence.input.xml.xml";
        
    };
    
    class June3
    {
    public:
        void doEverthing();
        
    private:
        struct Atom
        {
            int step = -1; // -1 for rest
            int alter = 0;
            int octave = 4;
            std::string name = "rest";
            void setName()
            {
                std::stringstream ss;
                switch ( step )
                {
                    case -1:
                    {
                        this->name = "rest";
                        return;
                    }
                    case 0:
                    {
                        ss << "C";
                        break;
                    }
                    case 1:
                    {
                        ss << "D";
                        break;
                    }
                    case 2:
                    {
                        ss << "E";
                        break;
                    }
                    case 3:
                    {
                        ss << "F";
                        break;
                    }
                    case 4:
                    {
                        ss << "G";
                        break;
                    }
                    case 5:
                    {
                        ss << "A";
                        break;
                    }
                    case 6:
                    {
                        ss << "B";
                        break;
                    }
                    default:
                    {
                        this->name = "rest";
                        return;
                    }
                }
                
                if( alter == -1 )
                {
                    ss << "b";
                }
                else if( alter == 1 )
                {
                    ss << "#";
                }
                ss << octave;
                this->name = ss.str();
            }
        };
        
    private:
        static mx::api::ScoreData createEmptyScore( const std::string& title );
        static void addInstrument( mx::api::ScoreData& ioScore,
                                   const std::string& id,
                                   const std::string& name,
                                   const std::string& abbr,
                                   mx::api::SoundID soundID,
                                   const mx::api::ClefData clef );
        static void appendMeasures( mx::api::ScoreData& ioScore, int numMeasures );
    };
}
