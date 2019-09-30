#include "scriabin/Coalescence.h"
#include "scriabin/Prob.h"
#include "scriabin/StrettoState.h"
#include "scriabin/DynamicValue.h"
#include "../test/SCRIABIN_PATH.h"
#include "mx/api/DocumentManager.h"
#include <vector>
#include <map>

#define TO_INT( x ) static_cast<int>( x )
#define TO_SZ( x ) static_cast<size_t>( x )

namespace scriabin
{
    static constexpr const int BEATS_PER_MEASURE = 12;
    static constexpr const int TIME_SIGNATURE_TOP_NUMBER = 3;
    static constexpr const int BEAT_TYPE_NUMERAL = 16;
    static constexpr const int TIME_SIGNATURE_BOTTOM_NUMBER = 4;
    static constexpr const int QUARTER_NOTE_BEAT_TYPE_NUMERAL = 4;
    static constexpr const mx::api::DurationName BEAT_TYPE_NAME = mx::api::DurationName::dur16th;
    static constexpr const int TICKS_PER_QUARTER = 16;
    static constexpr const double BEAT_TYPE_TO_QUARTER_RATIO =
            static_cast<double>( QUARTER_NOTE_BEAT_TYPE_NUMERAL ) / static_cast<double>( BEAT_TYPE_NUMERAL );
    static constexpr const int TICKS_PER_BEAT =
            static_cast<int>( ( static_cast<double>( TICKS_PER_QUARTER ) * BEAT_TYPE_TO_QUARTER_RATIO ) +
                              0.0000000001 );


    Coalescence::Coalescence( std::string inputFilepath, std::string outputFilepath )
            : myScore{}, myInFilepath{ std::move( inputFilepath ) }, myOutFilepath{ std::move( outputFilepath ) }
    {

    }


    void
    Coalescence::initSelfScore()
    {
        myScore = mx::api::ScoreData{};
        myScore = createEmptyScore( "Coalescence" );
    }


    MxNoteStreams
    Coalescence::getInputNotes() const
    {
        auto& dmgr = mx::api::DocumentManager::getInstance();
        const auto inID = dmgr.createFromFile( myInFilepath );
        const auto input = dmgr.getData( inID );
        dmgr.destroyDocument( inID );
        MxNoteStreams inputNotes;
        int partIndex = 0;

        for( const auto& part : input.parts )
        {
            for( const auto& measure : part.measures )
            {
                const auto& staff = measure.staves.at( 0 );
                const auto& voice = staff.voices.at( 0 );
                const auto& notes = voice.notes;

                for( const auto& note : notes )
                {
                    inputNotes[partIndex].push_back( note );
                }
            }
            ++partIndex;
        }

        return inputNotes;
    }


    AtomStreams
    Coalescence::extractStreams( const MxNoteStreams& inNotes )
    {
        AtomStreams streams;

        for( const auto& origPair : inNotes )
        {
            for( const auto& note : origPair.second )
            {
                Atom a;
                if( !note.isRest )
                {
                    a.setFromMx( note.pitchData );
                }

                int numNotes = 1;

                if( note.durationData.durationName == mx::api::DurationName::quarter )
                {
                    numNotes = 2;
                    if( note.durationData.durationDots == 1 )
                    {
                        numNotes = 3;
                    }
                }

                a.updateName();

                for( int i = 0; i < numNotes; ++i )
                {
                    streams[origPair.first].push_back( a );
                }
            }
        }

        // fix a problem with the viola part by copying violin 1
        // and transposing it down two octaves
        streams.at( 2 ) = streams.at( 0 );

        for( auto& note : streams.at( 2 ) )
        {
            note.setOctave( note.getOctave() - 1 );
        }

        addAccentsToInitialStreams( streams );
        return streams;
    }


    void
    Coalescence::addAccentsToInitialStreams( AtomStreams& ioStreams )
    {
        const auto& checkStreamZero = ioStreams.at( 0 );
        int indexHighest = -1;
        Atom highest;
        int indexLowest = -1;
        Atom lowest;
        int curr = 0;

        for( const auto& a : checkStreamZero )
        {
            if( indexHighest == -1 || a > highest )
            {
                highest = a;
                indexHighest = curr;
            }

            if( indexLowest == -1 || a < lowest )
            {
                lowest = a;
                indexLowest = curr;
            }

            ++curr;
        }

        for( auto& stream : ioStreams )
        {
            stream.second.at( static_cast<size_t>( indexLowest ) ).setIsAccented( true );
            stream.second.at( static_cast<size_t>( indexHighest ) ).setIsAccented( true );
        }
    }


    void
    Coalescence::reverseAtoms( Atoms& ioAtoms )
    {
        std::reverse( std::begin( ioAtoms ), std::end( ioAtoms ) );
    }


    void
    Coalescence::reverseStreams( AtomStreams& ioStreams )
    {
        for( auto& pair : ioStreams )
        {
            reverseAtoms( pair.second );
        }
    }


    void
    Coalescence::writeMusic( const Atoms& inAtomsToWrite, Atoms& ioAtomsToAppendTo, int numTimes )
    {
        for( int i = 0; i < numTimes; ++i )
        {
            std::copy(
                    std::cbegin( inAtomsToWrite ),
                    std::cend( inAtomsToWrite ),
                    std::back_inserter( ioAtomsToAppendTo )
            );
        }
    }


    void
    Coalescence::writeMusic( const AtomStreams& inStreamsToWrite, AtomStreams& ioStreamsToAppendTo, int numTimes )
    {
        if( inStreamsToWrite.size() != ioStreamsToAppendTo.size() )
        {
            throw std::runtime_error( "Coalescence::writeMusic: maps must be same size" );
        }

        auto inIter = inStreamsToWrite.cbegin();
        auto outIter = ioStreamsToAppendTo.begin();
        const auto e = inStreamsToWrite.cend();

        for( ; inIter != e; ++inIter, ++outIter )
        {
            writeMusic( inIter->second, outIter->second, numTimes );
        }
    }


    void
    Coalescence::doSomeAwesomeCoalescing(
            AtomStreams& ioPatternStreams,
            AtomStreams& ioOutputStreams,
            Prob& ioProb
    )
    {
        CoalescenceParams params;
        params.minR = 0;
        params.maxR = 0;
        params.rInc = 0;
        params.rTier = 0;

        params.minP = 1;
        params.maxP = 1;
        params.pInc = 0;
        params.pTier = 1;
        params.numLoops = 3;

        doCoalescingLoop( params, ioPatternStreams, ioOutputStreams, ioProb );
        writeMusic( ioPatternStreams, ioOutputStreams, 3 );

        params.minR = 0;
        params.maxR = 0;
        params.rInc = 0;
        params.rTier = 0;

        params.minP = 1;
        params.maxP = 1;
        params.pInc = 0;
        params.pTier = 1;
        params.numLoops = 2;

        doCoalescingLoop( params, ioPatternStreams, ioOutputStreams, ioProb );
        writeMusic( ioPatternStreams, ioOutputStreams, 2 );

        params.minR = 0;
        params.maxR = 0;
        params.rInc = 0;
        params.rTier = 0;

        params.minP = 1;
        params.maxP = 1;
        params.pInc = 0;
        params.pTier = 1;
        params.numLoops = 2;

        doCoalescingLoop( params, ioPatternStreams, ioOutputStreams, ioProb );
        writeMusic( ioPatternStreams, ioOutputStreams, 2 );

        // add a rest to viola
        int restPartIndex = 2;
        auto restIndex = findInsertIndex( ioPatternStreams.at( restPartIndex ), ioProb );
        auto restIter = ioPatternStreams.at( restPartIndex ).cbegin() + static_cast<ptrdiff_t>( restIndex );
        restIter = ioPatternStreams.at( restPartIndex ).insert( restIter, Atom{} );

        params.minR = 0;
        params.maxR = 0;
        params.rInc = 0;
        params.rTier = 0;

        params.minP = 1;
        params.maxP = 1;
        params.pInc = 0;
        params.pTier = 1;
        params.numLoops = 2;

        doCoalescingLoop( params, ioPatternStreams, ioOutputStreams, ioProb );
        writeMusic( ioPatternStreams, ioOutputStreams, 2 );

        // add a rest to violin 2
        restPartIndex = 1;
        restIndex = findInsertIndex( ioPatternStreams.at( restPartIndex ), ioProb );
        restIter = ioPatternStreams.at( restPartIndex ).cbegin() + static_cast<ptrdiff_t>( restIndex );
        restIter = ioPatternStreams.at( restPartIndex ).insert( restIter, Atom{} );

        params.minR = 0;
        params.maxR = 0;
        params.rInc = 0;
        params.rTier = 0;

        params.minP = 3;
        params.maxP = 3;
        params.pInc = 0;
        params.pTier = 1;
        params.numLoops = 2;

        doCoalescingLoop( params, ioPatternStreams, ioOutputStreams, ioProb );
        writeMusic( ioPatternStreams, ioOutputStreams, 2 );

        // add a rest to violin 1
        restPartIndex = 0;
        restIndex = findInsertIndex( ioPatternStreams.at( restPartIndex ), ioProb );
        restIter = ioPatternStreams.at( restPartIndex ).cbegin() + static_cast<ptrdiff_t>( restIndex );
        restIter = ioPatternStreams.at( restPartIndex ).insert( restIter, Atom{} );
        restIter = ioPatternStreams.at( restPartIndex ).insert( restIter, Atom{} );

        params.minR = 0;
        params.maxR = 0;
        params.rInc = 0;
        params.rTier = 0;

        params.minP = 3;
        params.maxP = 3;
        params.pInc = 0;
        params.pTier = 1;
        params.numLoops = 2;

        doCoalescingLoop( params, ioPatternStreams, ioOutputStreams, ioProb );
        // writeMusic( ioPatternStreams, ioOutputStreams, 2 );

        // add a rest to cello
        restPartIndex = 3;
        restIndex = findInsertIndex( ioPatternStreams.at( restPartIndex ), ioProb );
        restIter = ioPatternStreams.at( restPartIndex ).cbegin() + static_cast<ptrdiff_t>( restIndex );
        restIter = ioPatternStreams.at( restPartIndex ).insert( restIter, Atom{} );
        restIter = ioPatternStreams.at( restPartIndex ).insert( restIter, Atom{} );

        params.minR = 0;
        params.maxR = 0;
        params.rInc = 0;
        params.rTier = 0;

        params.minP = 10;
        params.maxP = 20;
        params.pInc = 1;
        params.pTier = 1;
        params.numLoops = 5;

        doCoalescingLoop( params, ioPatternStreams, ioOutputStreams, ioProb );
        const int NUM_EXPANSIONS_PER_PHRASE = 3;
        const int NUM_TIMES_THROUGH_THE_PHRASE = 10;

        for( int loop = 0; loop < NUM_TIMES_THROUGH_THE_PHRASE; ++loop )
        {
            for( int add = 0; add < NUM_EXPANSIONS_PER_PHRASE; ++add )
            {
                for( auto& p : ioPatternStreams )
                {
                    expandShortestReps( p.second, ioProb );
                }

            }
            writeMusic( ioPatternStreams, ioOutputStreams, 1 );
        }

        params.minR = 0;
        params.maxR = 0;
        params.rInc = 0;
        params.rTier = 0;

        params.minP = 33;
        params.maxP = 33;
        params.pInc = 0;
        params.pTier = 5;
        params.numLoops = 5;

        doCoalescingLoop( params, ioPatternStreams, ioOutputStreams, ioProb );
    }


    inline int
    chooseAtRandom(
            const std::set<int>::const_iterator beginIter,
            const std::set<int>::const_iterator endIter,
            Prob& ioProb
    )
    {
        if( beginIter == endIter )
        {
            return -1;
        }

        int escapeHatch = 0;
        std::set<int>::const_iterator it = beginIter;

        for( ; escapeHatch < 100000; ++escapeHatch )
        {
            if( ioProb.get( 30 ) )
            {
                return *it;
            }

            ++it;

            if( it == endIter )
            {
                it = beginIter;
            }
        }

        return -1;
    }


    void
    Coalescence::expandShortestReps(
            Atoms& ioPattern,
            Prob& ioProb
    )
    {
        const auto nonReps = findNonRepeatingNotes( ioPattern );

        if( !nonReps.empty() )
        {
            if( nonReps.empty() )
            {
                return;
            }

            const int rando = chooseAtRandom( std::cbegin( nonReps ), std::cend( nonReps ), ioProb );

            if( rando < 0 || rando >= static_cast<int>( ioPattern.size() ) )
            {
                throw std::runtime_error{ "not good" };
            }

            const auto randoIter = ioPattern.cbegin() + static_cast<ptrdiff_t>( rando );
            ioPattern.insert( randoIter, *randoIter );
            return;
        }

        const auto reps = findRepeatedNotes( ioPattern );
        std::vector<AtomPattern> sorted;

        for( const auto& pair : reps )
        {
            sorted.push_back( pair.second );
        }

        const auto compare = [&]( AtomPattern& l, AtomPattern& r )
        {
            if( l.patternLength < r.patternLength )
            {
                return true;
            }
            else if( l.patternLength > r.patternLength )
            {
                return false;
            }
            else if( l.firstAtomOfPattern.getOctave() < r.firstAtomOfPattern.getOctave() )
            {
                return true;
            }
            else if( l.firstAtomOfPattern.getOctave() > r.firstAtomOfPattern.getOctave() )
            {
                return false;
            }
            else if( l.firstAtomOfPattern.getStep() < r.firstAtomOfPattern.getStep() )
            {
                return true;
            }
            else if( l.firstAtomOfPattern.getStep() > r.firstAtomOfPattern.getStep() )
            {
                return false;
            }
            else if( l.firstAtomOfPattern.getAlter() < r.firstAtomOfPattern.getAlter() )
            {
                return true;
            }
            else if( l.firstAtomOfPattern.getAlter() > r.firstAtomOfPattern.getAlter() )
            {
                return false;
            }

            return false;
        };

        std::sort( std::begin( sorted ), std::end( sorted ), compare );
        const auto& first = sorted.front();
        const auto insertIndex = first.index;
        const auto insertIter = ioPattern.cbegin() + static_cast<ptrdiff_t>( insertIndex );
        ioPattern.insert( insertIter, *insertIter );
    }


    int
    Coalescence::findInsertIndex( const Atoms& inAtoms, Prob& ioProb )
    {
        // make a datastructure showing where the repetitions and rests are
        const auto repetitions = findRepeatedNotes( inAtoms );

        // find indices of all repeated notes and non-repeated notes
        std::set<int> repeatedIndices;
        std::set<int> nonRepeatedIndices;

        for( const auto& r : repetitions )
        {
            for( int x = r.second.index; x < r.second.index + r.second.patternLength; ++x )
            {
                repeatedIndices.insert( x );
            }
        }

        for( int x = 0; x < static_cast<int>( inAtoms.size() ); ++x )
        {
            if( repeatedIndices.find( x ) == repeatedIndices.cend() )
            {
                nonRepeatedIndices.insert( x );
            }
        }

        // find a non-repeated index, or if none exist, then an index where there
        // is less than 3 repitions, or if none exists then a random index
        int insertIndex = -1;

        if( repeatedIndices.size() > 0 )
        {
            const auto& collection = repeatedIndices;
            const auto begit = collection.cbegin();
            const auto endit = collection.cend();
            auto iter = begit;

            while( insertIndex < 0 )
            {
                if( ioProb.get( 1 ) )
                {
                    insertIndex = *iter;
                }

                ++iter;

                if( iter == endit )
                {
                    iter = begit;
                }
            }
        }
        else
        {
            const auto& collection = nonRepeatedIndices;
            const auto begit = collection.cbegin();
            const auto endit = collection.cend();
            auto iter = begit;

            while( insertIndex < 0 )
            {
                if( ioProb.get( 1 ) )
                {
                    insertIndex = *iter;
                }

                ++iter;

                if( iter == endit )
                {
                    iter = begit;
                }
            }
        }

        if( insertIndex < 0 || insertIndex >= static_cast<int>( inAtoms.size() ) )
        {
            throw std::runtime_error{ "index will be out of range" };
        }

        return insertIndex;
    }


    void
    Coalescence::eliminateTriplePlusAccents( AtomStreams& ioStreams )
    {
        for( auto& stream : ioStreams )
        {
            auto it = stream.second.begin();
            const auto en = stream.second.end();
            std::unique_ptr<Atom> prevAtom = nullptr;
            int accentCount = 0;

            for( ; it != en; ++it )
            {
                if( !prevAtom )
                {
                    prevAtom = std::unique_ptr<Atom>{ std::make_unique<Atom>( *it ) };
                    if( it->getIsAccented() )
                    {
                        ++accentCount;
                    }
                    continue;
                }

                if( it->getIsAccented() )
                {
                    ++accentCount;

                    if( *it == *prevAtom )
                    {
                        if( accentCount > 2 )
                        {
                            it->setIsAccented( false );
                        }
                    }
                }
                else
                {
                    accentCount = 0;
                }

                *prevAtom = *it;
            }
        }
    }


    mx::api::ScoreData
    Coalescence::doEverthing()
    {
        initSelfScore();
        const MxNoteStreams inputNotes = getInputNotes();
        const AtomStreams originalMusic = extractStreams( inputNotes );
        AtomStreams outMusic = originalMusic;
        reverseStreams( outMusic );
        const AtomStreams originalReversedMusic = outMusic;
        AtomStreams patternStreams = originalReversedMusic;
        Prob boolGen{ DIGITS_DAT_PATH() };
        doSomeAwesomeCoalescing( patternStreams, outMusic, boolGen );
        shortenStreamsToMatchLengthOfShortestStream( outMusic, BEATS_PER_MEASURE );
        reverseStreams( outMusic );
        writeMusic( originalMusic, outMusic, 32 );
//        augmentBeginning( outMusic );
        eliminateTriplePlusAccents( outMusic );
        sneakInAccents( outMusic, boolGen );
        static constexpr const int NUM_MEASURES_AT_BEGINNING = 24;
        extendTheOpening( outMusic, NUM_MEASURES_AT_BEGINNING );

        doStretto( outMusic, boolGen );

        // TODO - write the heat death


        // DONE - Write it Out
        writeStreamsToScore( outMusic, myScore );
        auto& dmgr = mx::api::DocumentManager::getInstance();
        const auto oID = dmgr.createFromScore( myScore );
        dmgr.writeToFile( oID, myOutFilepath );
        return myScore;
    }


    void
    Coalescence::extendTheOpening( AtomStreams& ioOutMusic, int inNumMeasuresAtBeginning )
    {
        for( auto& stream : ioOutMusic )
        {
            const auto repeatedNote = stream.second.front();

            for( int i = 0; i < inNumMeasuresAtBeginning * BEATS_PER_MEASURE; ++i )
            {
                stream.second.insert( stream.second.cbegin(), repeatedNote );
            }
        }
    }


    void
    Coalescence::sneakInAccents( AtomStreams& ioMusic, Prob& ioProb )
    {
        // gradual sneak-in of accents
        // find first accent after measure 240
        // leave that accent in place
        // but eliminate other accents with 90% probability
        // gradually reduce this probablity to 0 by measure 400
        const int measure400 = 400 * 6;
        const int firstDesiredAccentLoc = 200 * 6;

        auto stream0 = ioMusic.at( 0 ).begin() + static_cast<ptrdiff_t>( firstDesiredAccentLoc );
        auto stream1 = ioMusic.at( 1 ).begin() + static_cast<ptrdiff_t>( firstDesiredAccentLoc );
        auto stream2 = ioMusic.at( 2 ).begin() + static_cast<ptrdiff_t>( firstDesiredAccentLoc );
        auto stream3 = ioMusic.at( 3 ).begin() + static_cast<ptrdiff_t>( firstDesiredAccentLoc );
        const auto streamEnd = ioMusic.at( 0 ).end();
        int firstAccentLoc = 0;

        for( int i = firstDesiredAccentLoc; stream0 != streamEnd; ++i, ++stream0, ++stream1, ++stream2, ++stream3 )
        {
            if( stream0->getIsAccented() ||
                stream1->getIsAccented() ||
                stream2->getIsAccented() ||
                stream3->getIsAccented() )
            {
                firstAccentLoc = i;
                break;
            }
        }

        const double distanceBetweenProbZeroAndProb100 =
                static_cast<double>( firstAccentLoc ) - static_cast<double>( measure400 );
        const double startingProb = 80.0;
        const double probIncrement = startingProb / distanceBetweenProbZeroAndProb100;

        for( auto& stream : ioMusic )
        {
            for( size_t i = 0; i < static_cast<size_t>( firstAccentLoc ); ++i )
            {
                stream.second.at( i ).setIsAccented( false );
            }

            double prob = startingProb;
            for( size_t i = static_cast<size_t>( firstAccentLoc ) + 2; i < measure400 + 6; ++i, prob += probIncrement )
            {
                const bool doEliminate = ioProb.get( static_cast<int>( prob ) );

                if( doEliminate )
                {
                    if( stream.second.at( i ).getIsAccented() )
                    {
                        if( !stream.second.at( i - 1 ).getIsAccented() )
                        {
                            stream.second.at( i ).setIsAccented( false );
                            stream.second.at( i + 1 ).setIsAccented( false );
                        }
                    }
                }
            }
        }
    }


    void
    Coalescence::doStretto( AtomStreams& ioMusic, Prob& ioProb )
    {
        const int STRETTO_START_MEASURE_NUMBER = 699;
        const int STRETTO_LAST_MEASURE_NUMBER = 1000;
        const int STRETTO_START_MEASURE_INDEX = STRETTO_START_MEASURE_NUMBER - 1;
//        const int STRETTO_LAST_MEASURE_INDEX = STRETTO_LAST_MEASURE_NUMBER - 1;

        StrettoFacts sfacts;
        sfacts.beatsPerMeasure = BEATS_PER_MEASURE;
        sfacts.phraseLengthMeasures = 4;
        sfacts.sectionLengthMinMeasures = STRETTO_LAST_MEASURE_NUMBER - STRETTO_START_MEASURE_NUMBER;
        sfacts.topNoteIndex = 15;
        StrettoState state{ sfacts };

        const int STRETTO_START_NOTE_INDEX = STRETTO_START_MEASURE_INDEX * BEATS_PER_MEASURE;
//        const int STRETTO_LAST_NOTE_INDEX = ( STRETTO_LAST_MEASURE_NUMBER * BEATS_PER_MEASURE ) - 1;

        // chop off all repetitions after the desired amount
        for( auto& stream : ioMusic )
        {
            stream.second.resize( TO_SZ( STRETTO_START_MEASURE_INDEX * BEATS_PER_MEASURE ) );
        }

        AtomStreams tempStreams;

        // copy the last musical phrase and remove all accents
        for( auto& stream : ioMusic )
        {
            for( int n = STRETTO_START_NOTE_INDEX - state.getPhraseLengthNotes(); n < STRETTO_START_NOTE_INDEX; ++n )
            {
                auto a = stream.second.at( TO_SZ( n ) );
                if( n == STRETTO_START_NOTE_INDEX ) // ?
                {
                    a.setIsAccented( false );
                }

                tempStreams[stream.first].push_back( a );
                tempStreams[stream.first].back().setIsAccented( false );
            }
        }

        const auto proto = tempStreams;

        const std::string M1 = "Marimba 1";
        const std::string M2 = "Marimba 2";
        const std::string M3 = "Marimba 3";
        const std::string M4 = "Bass Marimba";

        const size_t M1X = 0;
        const size_t M2X = 1;
        const size_t M3X = 2;
        const size_t M4X = 3;

        AtomStreams stretto;
        stretto[M1X] = Atoms{};
        stretto[M2X] = Atoms{};
        stretto[M3X] = Atoms{};
        stretto[M4X] = Atoms{};

        const auto accent = [&]( int inPartIndex )
        {
            stretto.at( TO_SZ( inPartIndex ) ).back().setIsAccented( true );
        };

        const auto accentAll = [&]()
        {
            accent( M1X );
            accent( M2X );
            accent( M3X );
            accent( M4X );
        };

        const std::vector<int>
//                primes = { 97, 89, 83, 79, 71, 67, 61, 59, 53, 47, 43, 41, 37, 31, 29, 23, 19, 17, 13, 11, 7, 5 };
                primes = { 71, 67, 61, 59, 53, 47, 43, 41, 37, 31, 29, 23, 19, 17, 13, 11, 7, 5 };
        auto m1primesIter = primes.cbegin();
        auto m2primesIter = primes.cbegin();
        auto m3primesIter = primes.cbegin();
        auto m4primesIter = primes.cbegin();
        const auto primesEnd = primes.cend();

        state.addCounter( { M1, 24 } );
        state.getCounterMutable( M1 ).length = *m1primesIter;
//        state.getCounterMutable( M1 ).current = 5;

        state.addCounter( { M2, 24 } );
        state.getCounterMutable( M2 ).length = *m2primesIter;
//        state.getCounterMutable( M1 ).current = 7;

        state.addCounter( { M3, 24 } );
        state.getCounterMutable( M3 ).length = *m3primesIter;
//        state.getCounterMutable( M1 ).current = 11;

        state.addCounter( { M4, 24 } );
        state.getCounterMutable( M4 ).length = *m4primesIter;
//        state.getCounterMutable( M1 ).current = 13;

        const int HOW_LONG = 4000;
        const int WAIT_TRIGGER_INTERVAL = 25;

        const auto setNextPrime = [&]( const std::string& counterName )
        {
            auto iter = &m1primesIter;
            if( counterName == M2 )
            {
                iter = &m2primesIter;
            }
            else if( counterName == M3 )
            {
                iter = &m3primesIter;
            }
            else if( counterName == M4 )
            {
                iter = &m4primesIter;
            }

            if( *iter != primesEnd )
            {
                ++( *iter );
                if( ( *iter ) != primesEnd )
                {
                    const auto current = state.getCounter( counterName ).length;
                    const auto probability = std::min( current * 4, 100 );
                    const bool doDecrement = ioProb.get( probability );
                    if( doDecrement )
                    {
                        const auto newPrime = *( *iter );
                        state.getCounterMutable( counterName ).length = newPrime;
                    }
                }
            }
        };

        bool isM1Initialized = false;
        bool isM2Initialized = false;
        bool isM3Initialized = false;
        bool isM4Initialized = false;

        for( int i = 0; i < HOW_LONG; ++state, ++i )
        {
            const auto noteInPhrase = TO_SZ( state.getNoteInPhraseIndex() );
            auto atom1 = proto.at( M1X ).at( noteInPhrase );
            auto atom2 = proto.at( M2X ).at( noteInPhrase );
            auto atom3 = proto.at( M3X ).at( noteInPhrase );
            auto atom4 = proto.at( M4X ).at( noteInPhrase );
            stretto.at( M1X ).push_back( atom1 );
            stretto.at( M2X ).push_back( atom2 );
            stretto.at( M3X ).push_back( atom3 );
            stretto.at( M4X ).push_back( atom4 );

            // initialize marimbas to start at different times
            if( i == WAIT_TRIGGER_INTERVAL * 1 )
            {
                state.getCounterMutable( M1 ).current = 0;
                isM1Initialized = true;
            }

            if( i == WAIT_TRIGGER_INTERVAL * 2 )
            {
                state.getCounterMutable( M4 ).current = 0;
                isM4Initialized = true;
            }

            if( i == WAIT_TRIGGER_INTERVAL * 3 )
            {
                state.getCounterMutable( M2 ).current = 0;
                isM2Initialized = true;
            }

            if( i == WAIT_TRIGGER_INTERVAL * 4 )
            {
                state.getCounterMutable( M3 ).current = 0;
                isM3Initialized = true;
            }

            if( state.getIsFirstNoteOfPhrase() )
            {
                accentAll();
            }
            else if( state.getNoteInPhraseIndex() == sfacts.topNoteIndex )
            {
                accentAll();
            }

            if( state.getIsCounterZero( M1 ) && isM1Initialized )
            {
                accent( M1X );
                setNextPrime( M1 );
            }

            if( state.getIsCounterZero( M2 ) && isM2Initialized )
            {
                accent( M2X );
                setNextPrime( M2 );
            }

            if( state.getIsCounterZero( M3 ) && isM3Initialized )
            {
                accent( M3X );
                setNextPrime( M3 );
            }

            if( state.getIsCounterZero( M4 ) && isM4Initialized )
            {
                accent( M4X );
                setNextPrime( M4 );
            }
        }

        // write stretto to ioMusic

        for( size_t i = 0; i < 4; ++i )
        {
            const auto& atoms = stretto.at( i );
            auto& musicStream = ioMusic.at( i );
            for( const auto& atom : atoms )
            {
                musicStream.push_back( atom );
            }
        }

    } // end of function


    void
    Coalescence::doCoalescingLoop(
            const CoalescenceParams& params,
            AtomStreams& ioPatternStreams,
            AtomStreams& ioOutputStreams,
            Prob& ioProb
    )
    {
        int rCurrent = params.minR;
        int pCurrent = params.minP;

        for( int loopCounter = 0; loopCounter < params.numLoops; ++loopCounter )
        {
            for( int p = 0; p < 4; ++p )
            {
                const int restProb = rCurrent + ( params.rTier * p );
                const int repeatProb = pCurrent + ( params.pTier * p );

                for( auto it = ioPatternStreams.at( p ).begin(); it != ioPatternStreams.at( p ).end(); ++it )
                {
                    const bool doRest = ioProb.get( restProb );
                    const bool doRepeat = ioProb.get( repeatProb );

                    if( doRest )
                    {
                        const auto currentIndex = it - ioPatternStreams.at( p ).begin();
                        const auto insertIndex = findInsertIndex( ioPatternStreams.at( p ), ioProb );
                        const auto
                                insertIter = ioPatternStreams.at( p ).cbegin() + static_cast<ptrdiff_t>( insertIndex );
                        ioPatternStreams.at( p ).insert( insertIter, Atom{} );
                        it = ioPatternStreams.at( p ).begin() + currentIndex;
                    }

                    if( doRepeat )
                    {
                        it = ioPatternStreams.at( p ).insert( it, *it );
                    }
                }
            }

            writeMusic( ioPatternStreams, ioOutputStreams, 1 );

            rCurrent += params.rInc;
            pCurrent += params.pInc;

            if( rCurrent > params.maxR )
            {
                rCurrent = params.maxR;
            }

            if( pCurrent > params.maxP )
            {
                rCurrent = params.maxP;
            }
        }
    }


    void
    Coalescence::shortenStreamsToMatchLengthOfShortestStream( AtomStreams& ioStreams, int inMultipleOf )
    {
        int smallest = findIndexOfShortestStream( ioStreams );
        const int originalSizeSmallest = static_cast<int>( ioStreams.at( smallest ).size() );

        if( inMultipleOf > 0 && originalSizeSmallest > 0 && originalSizeSmallest % inMultipleOf != 0 )
        {
            const int remainder = originalSizeSmallest % inMultipleOf;
            const auto newSize = ioStreams.at( smallest ).size() - static_cast<size_t>( remainder );
            ioStreams.at( smallest ).resize( newSize );
        }

        const auto sizeOfSmallest = ioStreams.at( smallest ).size();

        // delete extra notes based on smallest
        for( auto& pair : ioStreams )
        {
            if( pair.second.size() > sizeOfSmallest )
            {
                pair.second.resize( sizeOfSmallest );
            }
        }
    }


    int
    Coalescence::findIndexOfShortestStream( const AtomStreams& inStreams )
    {
        // find the smallest stream
        int smallest = -1;
        int indexOfSmallest = 0;
        int currentIndex = 0;

        for( const auto& streamPair : inStreams )
        {
            if( smallest == -1 || static_cast<int>( streamPair.second.size() ) < smallest )
            {
                smallest = static_cast<int>( streamPair.second.size() );
                indexOfSmallest = currentIndex;
            }
            ++currentIndex;
        }

        return indexOfSmallest;
    }


    void
    Coalescence::writeStreamsToScore( const AtomStreams& inStreams, mx::api::ScoreData& ioScore )
    {
        for( int p = 0; p < static_cast<int>( inStreams.size() ); ++p )
        {
            int measureIndex = 0;
            int beatIndex = 0;
            const auto& noteStream = inStreams.at( p );
            writeStream( p, measureIndex, beatIndex, noteStream, ioScore );
        }
    }


    void
    Coalescence::writeStream(
            int partIndex,
            int startingMeasureIndex,
            int startingEighthIndex,
            const Atoms& inAtoms,
            mx::api::ScoreData& ioScore
    )
    {
        auto measureIndex = startingMeasureIndex;
        auto beatIndex = startingEighthIndex;

        for( const auto& atom : inAtoms )
        {
            auto& part = ioScore.parts.at( static_cast<size_t>( partIndex) );

            while( measureIndex > static_cast<int>( part.measures.size() ) - 1 )
            {
                appendMeasures( ioScore, 1 );
            }

            auto& measure = part.measures.at( static_cast<size_t>( measureIndex ) );
            mx::api::NoteData theNote;
            theNote.tickTimePosition = beatIndex * TICKS_PER_BEAT;
            theNote.durationData.durationTimeTicks = TICKS_PER_BEAT;
            theNote.durationData.durationName = BEAT_TYPE_NAME;

            if( atom.getStep() == -1 )
            {
                theNote.isRest = true;
            }
            else
            {
                theNote.pitchData = atom.getMxPitchData();
            }

            if( atom.getIsAccented() )
            {
                mx::api::MarkData accent{};
                accent.markType = mx::api::MarkType::accent;
                accent.tickTimePosition = theNote.tickTimePosition;
                theNote.noteAttachmentData.marks.push_back( accent );
            }

            if( atom.getHasDynamicMarking() )
            {
                mx::api::MarkData dynamic;
                dynamic.markType = mx::api::MarkType::pppppp;

                switch( atom.getDynamicValue() )
                {
                    case DynamicValue::NONE:throw "you're stupid";
                        break;
                    case DynamicValue::PP:dynamic.markType = mx::api::MarkType::pp;
                        break;
                    case DynamicValue::P:dynamic.markType = mx::api::MarkType::p;
                        break;
                    case DynamicValue::MP:dynamic.markType = mx::api::MarkType::mp;
                        break;
                    case DynamicValue::MF:dynamic.markType = mx::api::MarkType::mf;
                        break;
                    case DynamicValue::F:dynamic.markType = mx::api::MarkType::f;
                        break;
                    case DynamicValue::FF:dynamic.markType = mx::api::MarkType::ff;
                        break;
                    default:throw "you're stupid";
                        break;
                }

                theNote.noteAttachmentData.marks.push_back( dynamic );
            }

            measure.staves.at( 0 ).voices.at( 0 ).notes.push_back( theNote );

            if( ( beatIndex + 1 ) % BEATS_PER_MEASURE == 0 )
            {
                ++measureIndex;
                beatIndex = 0;
            }
            else
            {
                ++beatIndex;
            }
        }
    }


    mx::api::ScoreData
    Coalescence::createEmptyScore( const std::string& title )
    {
        mx::api::ScoreData score;
        score.ticksPerQuarter = TICKS_PER_QUARTER;
        score.workTitle = title;
        mx::api::ClefData treble;
        treble.setTreble();
        mx::api::ClefData alto;
        alto.setAlto();
        mx::api::ClefData bass;
        bass.setBass();
        addInstrument( score, "MARIMBA1", "Marimba 1", "1", mx::api::SoundID::pitchedPercussionMarimba, treble );
        addInstrument( score, "MARIMBA2", "Marimba 2", "2", mx::api::SoundID::pitchedPercussionMarimba, treble );
        addInstrument( score, "MARIMBA3", "Marimba 3", "3", mx::api::SoundID::pitchedPercussionMarimba, alto );
        addInstrument( score, "MARIMBA4", "Marimba 4", "4", mx::api::SoundID::pitchedPercussionMarimbaBass, bass );
        mx::api::PartGroupData grp;
        grp.firstPartIndex = 0;
        grp.lastPartIndex = 3;
        grp.bracketType = mx::api::BracketType::bracket;
        score.partGroups.push_back( grp );
        return score;
    }


    void
    Coalescence::addInstrument(
            mx::api::ScoreData& ioScore,
            const std::string& id,
            const std::string& name,
            const std::string& abbr,
            mx::api::SoundID soundID,
            const mx::api::ClefData clef
    )
    {
        ioScore.parts.emplace_back();
        ioScore.parts.back().uniqueId = id;
        ioScore.parts.back().name = name;
        ioScore.parts.back().abbreviation = abbr;
        ioScore.parts.back().instrumentData.uniqueId = ioScore.parts.back().uniqueId + "-I";
        ioScore.parts.back().displayName = ioScore.parts.back().name;
        ioScore.parts.back().displayAbbreviation = ioScore.parts.back().abbreviation;
        ioScore.parts.back().instrumentData.soundID = soundID;
        ioScore.parts.back().instrumentData.soloOrEnsemble = mx::api::SoloOrEnsemble::solo;

        ioScore.parts.back().measures.emplace_back();
        ioScore.parts.back().measures.back().staves.emplace_back();
        mx::api::TimeSignatureData tsd;
        tsd.beats = TIME_SIGNATURE_TOP_NUMBER;
        tsd.beatType = TIME_SIGNATURE_BOTTOM_NUMBER;
        tsd.isImplicit = false;
        ioScore.parts.back().measures.back().timeSignature = tsd;
        ioScore.parts.back().measures.back().staves.back().clefs.push_back( clef );
        ioScore.parts.back().measures.back().staves.back().voices[0] = mx::api::VoiceData{};
    }


    void
    Coalescence::appendMeasures( mx::api::ScoreData& ioScore, int numMeasures )
    {
        for( int x = 0; x < numMeasures; ++x )
        {
            for( size_t partIndex = 0; partIndex < ioScore.parts.size(); ++partIndex )
            {
                const auto lastMeasure = ioScore.parts.at( partIndex ).measures.back();
                mx::api::MeasureData prototype;
                prototype.timeSignature = lastMeasure.timeSignature;
                prototype.timeSignature.isImplicit = true;

                for( const auto& staff : lastMeasure.staves )
                {
                    prototype.staves.emplace_back();
                    for( const auto& voicePair : staff.voices )
                    {
                        prototype.staves.back().voices[voicePair.first] = mx::api::VoiceData{};
                    }
                }

                ioScore.parts.at( partIndex ).measures.push_back( prototype );
            }
        }
    }


    void
    Coalescence::augmentBeginning( AtomStreams& ioOutMusic )
    {
        std::vector<int> changeIndices;
        std::vector<Atom> previousNotes;
        std::vector<Atom> currentNotes;
        int noteIndex = 0;
        const int lastNote = static_cast<int>( ioOutMusic.at( 0 ).size() ) - 1;

        for( ; noteIndex <= lastNote && changeIndices.size() < 8; ++noteIndex )
        {
            currentNotes.clear();

            for( const auto& p : ioOutMusic )
            {
                const auto a = p.second.at( static_cast<size_t>( noteIndex) );
                currentNotes.push_back( a );
            }

            if( previousNotes.empty() )
            {
                changeIndices.push_back( noteIndex );
            }
            else
            {
                if( previousNotes.size() != currentNotes.size() )
                {
                    throw std::runtime_error{ "previousNotes.size() != currentNotes.size()" };
                }

                auto prevIter = previousNotes.cbegin();
                auto currIter = currentNotes.cbegin();
                const auto prevEnd = previousNotes.cend();

                for( ; prevIter != prevEnd; ++prevIter, ++currIter )
                {
                    if( *prevIter != *currIter )
                    {
                        changeIndices.push_back( noteIndex - 1 );
                    }
                }
            }

            previousNotes = currentNotes;
        }

        int changeInstance = static_cast<int>( changeIndices.size() );
        for( auto changeIndexIter = changeIndices.crbegin();
             changeIndexIter != changeIndices.crend();
             ++changeIndexIter, --changeInstance )
        {
            const auto changeIndex = *changeIndexIter;
            const auto notesToAdd = 18;//;changeInstance * BEATS_PER_MEASURE;

            for( auto& p : ioOutMusic )
            {
                auto insertIter = p.second.cbegin() + static_cast<ptrdiff_t>( changeIndex );

                for( int z = 0; z < notesToAdd; ++z )
                {
                    insertIter = p.second.insert( insertIter, *insertIter );
                }
            }
        }
    }
}

#undef TO_INT
#undef TO_SZ
