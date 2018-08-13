#pragma once

namespace pen
{
    class StrettoState
    {
    public:
        StrettoState();
    
    public:
        int getMeasureIndex() const;
    
    public:
        void setMeasureIndex( int inVal );
    
    public:
        void operator++();
        
    private:
        int myMeasureIndex;
    
    private:
        void priv();
    };
}
