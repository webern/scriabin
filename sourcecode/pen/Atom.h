#pragma once
#include "mx/api/PitchData.h"
#include <string>
#include <sstream>
#include <cstdint>
#include <vector>
#include <map>
#include <set>

namespace pen
{
    // step -1 indicates rest
    // step 0 is C
    // step 1 is D, etc.
    struct Atom
    {
    public:
        Atom();
        Atom( const mx::api::PitchData& inPitchData );
        
        std::string name;
        void setRest();
        void setStep( int inStep );
        int getStep() const;
        void setOctave( int inOctave );
        int getOctave() const;
        void setAlter( int inAlter );
        int getAlter() const;
        void setStep( mx::api::Step inMxStep );
        mx::api::Step getMxStep() const;
        void setFromMx( const mx::api::PitchData& inPitchData );
        mx::api::PitchData getMxPitchData() const;

    private:
        int step;
        int alter;
        int octave;

    public:
        void updateName();
    };
    
    inline bool operator==( const Atom& inLeft, const Atom& inRight )
    {
        if( inLeft.getStep() < 0 && inRight.getStep() < 0 )
        {
            return true;
        }
        else if( inLeft.getStep() != inRight.getStep() )
        {
            return false;
        }
        else if( inLeft.getOctave() != inRight.getOctave() )
        {
            return false;
        }
        else if( inLeft.getAlter() != inRight.getAlter() )
        {
            return false;
        }
        
        return true;
    }
    
    enum class AtomPatternType
    {
        Pitch,
        Rest
    };
    
    struct AtomPattern
    {
        int index = -1;
        int repitions = 1;
        int patternLength = 1;
        Atom firstAtomOfPattern;
        AtomPatternType type = AtomPatternType::Pitch;
    };
    
    using AtomPatterns = std::map<int, AtomPattern>;
    using Atoms = std::vector<Atom>;
    
    inline AtomPatterns findRepeatedNotes( const Atoms& inAtoms )
    {
        AtomPatterns patterns;
        bool isRepeating = false;
        int repititionStartIndex = -1;
        std::unique_ptr<Atom> lastAtom = nullptr;
        int currentIndex = 0;

        for( const auto& atom : inAtoms )
        {
            const bool equalsPrevious = !!lastAtom && atom == *lastAtom && atom.getStep() >= 0;
            
            if( !isRepeating )
            {
                if( equalsPrevious )
                {
                    isRepeating = true;
                    repititionStartIndex = currentIndex - 1;
                }
                else
                {
                    // pedantic - not necessary
                    isRepeating = false;
                    repititionStartIndex = -1;
                }
            }
            else
            {
                if( equalsPrevious )
                {
                    // pedantic - nothing to do
                    isRepeating = true;
                }
                else
                {
                    // the repetition stopped with the previous atom, finalize
                    const int finalIndex = currentIndex - 1;
                    AtomPattern pattern;
                    pattern.index = repititionStartIndex;
                    pattern.patternLength = finalIndex - repititionStartIndex + 1;
                    pattern.type = AtomPatternType::Pitch;
                    pattern.firstAtomOfPattern = *lastAtom;
                    patterns.emplace( pattern.index, pattern );
                    repititionStartIndex = -1;
                    isRepeating = false;
                }
            }
            
            if( !lastAtom )
            {
                lastAtom = std::unique_ptr<Atom>{ std::make_unique<Atom>() };
            }

            *lastAtom = atom;
            ++currentIndex;

        }
        
        if( isRepeating && repititionStartIndex >= 0 )
        {
            // the final notes where repeating
            const int finalIndex = currentIndex - 1;
            AtomPattern pattern;
            pattern.index = repititionStartIndex;
            pattern.patternLength = finalIndex - repititionStartIndex + 1;
            pattern.type = AtomPatternType::Pitch;
            pattern.firstAtomOfPattern = *lastAtom;
            patterns.emplace( pattern.index, pattern );
            repititionStartIndex = -1;
            isRepeating = false;
        }
        
        return patterns;
    }
    
    inline std::set<int> findNonRepeatingNotes( const Atoms& inAtoms )
    {
        if( inAtoms.empty() )
        {
            return std::set<int>{};
        }
        
        const auto reps = findRepeatedNotes( inAtoms );
        std::set<int> repeatedIndices;
        
        for( const auto& r : reps )
        {
            int c = r.second.index;
            int e = c + r.second.patternLength;
            
            for( ; c < e; ++c )
            {
                repeatedIndices.insert( c );
            }
        }
        
        std::set<int> nonRepeatedIndices;
        const int len = static_cast<int>( inAtoms.size() );
        
        for( int x = 0; x < len; ++ x )
        {
            const bool isRepeated = repeatedIndices.find( x ) != std::cend( repeatedIndices );
            
            if( !isRepeated )
            {
                const auto& theNote = inAtoms.at( static_cast<size_t>( x ) );
                
                if( theNote.getStep() >= 0 )
                {
                    nonRepeatedIndices.insert( x );
                }
            }
        }
        
        return nonRepeatedIndices;
    }
}
