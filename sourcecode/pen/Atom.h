#pragma once
#include <string>
#include <sstream>
#include <cstdint>

namespace pen
{
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
        
        void setStep( mx::api::Step inMxStep)
        {
            switch ( inMxStep )
            {
                case mx::api::Step::c:
                    this->step = 0;
                    break;
                case mx::api::Step::d:
                    this->step = 1;
                    break;
                case mx::api::Step::e:
                    this->step = 2;
                    break;
                case mx::api::Step::f:
                    this->step = 3;
                    break;
                case mx::api::Step::g:
                    this->step = 4;
                    break;
                case mx::api::Step::a:
                    this->step = 5;
                    break;
                case mx::api::Step::b:
                    this->step = 6;
                    break;
                default:
                    this->step = 7;
                    break;
            }
            setName();
        }
        
        mx::api::Step getMxStep() const
        {
            mx::api::Step outStep = mx::api::Step::unspecified;
            
            switch ( this->step )
            {
                case 0:
                    outStep = mx::api::Step::c;
                    break;
                case 1:
                    outStep = mx::api::Step::d;
                    break;
                case 2:
                    outStep = mx::api::Step::e;
                    break;
                case 3:
                    outStep = mx::api::Step::f;
                    break;
                case 4:
                    outStep = mx::api::Step::g;
                    break;
                case 5:
                    outStep = mx::api::Step::a;
                    break;
                case 6:
                    outStep = mx::api::Step::b;
                    break;
                default:
                    outStep = mx::api::Step::c;
                    break;
            }
            
            return outStep;
        }
    };
}
