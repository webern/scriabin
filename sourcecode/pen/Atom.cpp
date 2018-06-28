#include "Atom.h"

namespace pen
{
    Atom::Atom()
    : step{ -1 }
    , alter{ 0 }
    , octave{ 4 }
    , name{ "rest" }
    {
        
    }
    
    
    Atom::Atom( const mx::api::PitchData& inPitchData )
    : Atom{}
    {
        setFromMx( inPitchData );
    }
    
    
    void
    Atom::setRest()
    {
        step = -1;
        octave = 4;
        alter = 0;
        updateName();
    }
    
    
    void
    Atom::updateName()
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
        
        if( this->alter == -2 )
        {
            ss << "bb";
        }
        else if( this->alter == -1 )
        {
            ss << "b";
        }
        else if( this->alter == 1 )
        {
            ss << "#";
        }
        else if( this->alter == 2 )
        {
            ss << "x";
        }
        
        ss << this->octave;
        
        this->name = ss.str();
    }
    
    
    void
    Atom::setStep( int inStep )
    {
        if( inStep < -1 )
        {
            throw std::runtime_error("Atom::setStep out of range, < -1");
        }
        else if( inStep > 6 )
        {
            throw std::runtime_error("Atom::setStep out of range, > 6");
        }
        
        step = inStep;
        updateName();
    }

    
    int
    Atom::getStep() const
    {
        return step;
    }
    
    
    void
    Atom::setOctave( int inOctave )
    {
        if( inOctave < -2 )
        {
            throw std::runtime_error("Atom::setOctave out of range, < -2");
        }
        else if( inOctave > 9 )
        {
            throw std::runtime_error("Atom::setOctave out of range, > 9");
        }
        
        octave = inOctave;
        updateName();
    }
    
    
    int
    Atom::getOctave() const
    {
        return octave;
    }
    
    
    void
    Atom::setAlter( int inAlter )
    {
        if( inAlter < -2 )
        {
            throw std::runtime_error("Atom::setAlter out of range, < -2");
        }
        else if( inAlter > 2 )
        {
            throw std::runtime_error("Atom::setAlter out of range, > 2");
        }
        
        alter = inAlter;
        updateName();
    }
    
    
    int
    Atom::getAlter() const
    {
        return alter;
    }

    
    void
    Atom::setStep( mx::api::Step inMxStep)
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
        updateName();
    }
    
    
    mx::api::Step
    Atom::getMxStep() const
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
    
    
    void
    Atom::setFromMx( const mx::api::PitchData& inPitchData )
    {
        setStep( inPitchData.step );
        alter = inPitchData.alter;
        octave = inPitchData.octave;
        updateName();
    }
    
    
    mx::api::PitchData
    Atom::getMxPitchData() const
    {
        mx::api::PitchData result;
        result.step = getMxStep();
        result.octave = octave;
        result.alter = alter;
        result.showAccidental();
        return result;
    }
}
