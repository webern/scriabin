#include "scriabin/Atom.h"
#include "scriabin/Constants.h"

namespace scriabin
{
    Atom::Atom()
    : myStep{ -1 }
    , myAlter{ 0 }
    , myOctave{ 4 }
    , myName{ "rest" }
    , myIsAccented{ false }
    {
        
    }
    
    Atom::Atom( int inStep, int inAlter, int inOctave )
    : Atom{}
    {
        setStep( inStep );
        setAlter( inAlter );
        setOctave( inOctave );
    }
    
    
    Atom::Atom( const mx::api::PitchData& inPitchData )
    : Atom{}
    {
        setFromMx( inPitchData );
    }
    
    std::string
    Atom::getName() const
    {
        return myName;
    }
    
    
    void
    Atom::setRest()
    {
        myStep = -1;
        myOctave = 4;
        myAlter = 0;
        updateName();
    }
    
    
    void
    Atom::updateName()
    {
        std::stringstream ss;
        switch ( myStep )
        {
            case -1:
            {
                this->myName = "rest";
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
                this->myName = "rest";
                return;
            }
        }
        
        if( this->myAlter == -2 )
        {
            ss << "bb";
        }
        else if( this->myAlter == -1 )
        {
            ss << "b";
        }
        else if( this->myAlter == 1 )
        {
            ss << "#";
        }
        else if( this->myAlter == 2 )
        {
            ss << "x";
        }
        
        ss << this->myOctave;
        
        this->myName = ss.str();
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
        
        myStep = inStep;
        updateName();
    }

    
    int
    Atom::getStep() const
    {
        return myStep;
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
        
        myOctave = inOctave;
        updateName();
    }
    
    
    int
    Atom::getOctave() const
    {
        return myOctave;
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
        
        myAlter = inAlter;
        updateName();
    }
    
    
    int
    Atom::getAlter() const
    {
        return myAlter;
    }

    
    void
    Atom::setStep( mx::api::Step inMxStep)
    {
        switch ( inMxStep )
        {
            case mx::api::Step::c:
                this->myStep = 0;
                break;
            case mx::api::Step::d:
                this->myStep = 1;
                break;
            case mx::api::Step::e:
                this->myStep = 2;
                break;
            case mx::api::Step::f:
                this->myStep = 3;
                break;
            case mx::api::Step::g:
                this->myStep = 4;
                break;
            case mx::api::Step::a:
                this->myStep = 5;
                break;
            case mx::api::Step::b:
                this->myStep = 6;
                break;
            default:
                this->myStep = 7;
                break;
        }
        updateName();
    }
    
    
    mx::api::Step
    Atom::getMxStep() const
    {
        mx::api::Step outStep = mx::api::Step::unspecified;
        
        switch ( this->myStep )
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
        myAlter = inPitchData.alter;
        myOctave = inPitchData.octave;
        updateName();
    }
    
    
    mx::api::PitchData
    Atom::getMxPitchData() const
    {
        mx::api::PitchData result;
        result.step = getMxStep();
        result.octave = myOctave;
        result.alter = myAlter;
        result.showAccidental();
        return result;
    }
    
    
    bool
    Atom::getIsAccented() const
    {
        return myIsAccented;
    }
    
    
    void
    Atom::setIsAccented( bool inIsAccented )
    {
        myIsAccented = inIsAccented;
    }
    
    int
    Atom::getMidiNote() const
    {
        if( this->getStep() < 0 || this->getStep() > STEP_B )
        {
            return std::numeric_limits<int>::min();
        }
        
        const auto base = C4_MIDI_NUMBER + STEP_PITCH_CLASSES[static_cast<size_t>( getStep() )] + getAlter();
        const auto octaveAdjustment = getOctave() - ( ( C4_MIDI_NUMBER / SEMITONES_PER_OCTAVE ) - 1 );
        const auto result = base + ( octaveAdjustment * SEMITONES_PER_OCTAVE );
        return result;
    }
    
    bool operator==( const Atom& inLeft, const Atom& inRight )
    {
        return ( !( inLeft < inRight ) ) && ( !( inRight < inLeft ) );
    }
    
    
    bool operator!=( const Atom& inLeft, const Atom& inRight )
    {
        return ( inLeft < inRight ) || ( inRight < inLeft );
    }
    
    
    bool operator<( const Atom& inLeft, const Atom& inRight )
    {
        return inLeft.getMidiNote() < inRight.getMidiNote();
    }
    
    
    bool operator>( const Atom& inLeft, const Atom& inRight )
    {
        return inRight < inLeft;
    }
    
    
    bool operator<=( const Atom& inLeft, const Atom& inRight )
    {
        return ( inLeft < inRight ) || ( inLeft == inRight );
    }
    
    
    bool operator>=( const Atom& inLeft, const Atom& inRight )
    {
        return ( inRight < inLeft ) || ( inLeft == inRight );
    }
    
}
