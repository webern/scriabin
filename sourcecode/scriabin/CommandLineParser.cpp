#include "scriabin/CommandLineParser.h"

namespace zeus
{
    CommandLineParser::CommandLineParser( const std::vector<CommandLineArgumentPrototype>& inPrototypes )
    : CommandLineParser{}
    {
        for( const auto& proto : inPrototypes )
        {
            std::unique_ptr<CommandLineValue> v{ std::make_unique<CommandLineValue>( proto ) };
            myValues.emplace( proto.getFullName(), std::move( v ) );
            myShortLookup.emplace( proto.getShortName(), myValues.at( proto.getFullName() ).get() );
        }
    }
    
    
    CommandLineParser::CommandLineParser( const CommandLineParser& other )
    : CommandLineParser{}
    {
        copyState( other );
    }
    
    
    CommandLineParser::CommandLineParser( CommandLineParser&& other )
    : CommandLineParser{}
    {
        moveState( std::move( other ) );
    }
    
    
    CommandLineParser& CommandLineParser::operator=( const CommandLineParser& other )
    {
        copyState( other );
        return *this;
    }
    
    
    CommandLineParser& CommandLineParser::operator=( CommandLineParser&& other )
    {
        moveState( std::move( other ) );
        return *this;
    }
    
    
    bool
    CommandLineParser::parse( int argc, const char* argv[] )
    {
        clearValues();
        
        for( int i = 0; i < argc; ++i )
        {
            myArgs.emplace_back( std::string{ argv[i] } );
        }
        
        std::string currentSwitch;
        bool isExecutablePath = true;
        
        for( const auto& arg : myArgs )
        {
            if( arg.empty() )
            {
                continue;
            }
            else if( isExecutablePath )
            {
                myExecutablePath = arg;
                isExecutablePath = false;
                continue;
            }
            else if( arg.length() >= 3 && arg.substr(0, 2) == "--" )
            {
                const auto& longName = arg.substr( 2 );
                
                const auto ptr = getCommandLineValuePtr( longName );
                
                if( ptr == nullptr )
                {
                    return false;
                }
                
                ptr->setIsPresent( true );
                currentSwitch = longName;
            }
            else if( arg.length() == 2 && arg.substr(0, 1) == "-" )
            {
                const auto& shortNameStr = arg.substr( 1 );
                const auto shortName = shortNameStr[0];
                const auto ptr = getCommandLineValuePtr( shortName );
                
                if( ptr == nullptr )
                {
                    return false;
                }
                
                ptr->setIsPresent( true );
                currentSwitch = ptr->getPrototype().getFullName();
            }
            else if( !currentSwitch.empty() )
            {
                const auto ptr = getCommandLineValuePtr( currentSwitch );
                
                if( ptr == nullptr )
                {
                    return false;
                }
                
                ptr->addValue( arg );
            }
            else
            {
                // problem
            }
        }
        
        return true;
    }
    
    
    void
    CommandLineParser::clearValues()
    {
        myArgs.clear();
        
        for( auto& pair : myValues )
        {
            pair.second->clearValues();
        }
    }
    
    
    const CommandLineValue&
    CommandLineParser::getCommandLineValue( const std::string& inLongName ) const
    {
        const CommandLineValue* ptr = getCommandLineValueConstPtr( inLongName );
        
        if( ptr == nullptr )
        {
            throw std::runtime_error{ "null pointer encountered" };
        }
        
        return *ptr;
    }
    
    
    const CommandLineValue&
    CommandLineParser::getCommandLineValue( const char inShortName ) const
    {
        const CommandLineValue* ptr = getCommandLineValueConstPtr( inShortName );
        
        if( ptr == nullptr )
        {
            throw std::runtime_error{ "null pointer encountered" };
        }
        
        return *ptr;
    }
    
    
    const std::string&
    CommandLineParser::getExecutablePath() const
    {
        return myExecutablePath;
    }
    
    // PRIVATE
    
    CommandLineParser::CommandLineParser()
    : myArgs{}
    , myValues{}
    , myShortLookup{}
    , myExecutablePath{}
    {
        
    }
    
    CommandLineValue*
    CommandLineParser::getCommandLineValuePtr( const std::string& inLongName )
    {
        const auto iter = myValues.find( inLongName );
        
        if( iter == myValues.cend() )
        {
            return nullptr;
        }
        
        return ( iter->second ).get();
    }
    
    
    CommandLineValue*
    CommandLineParser::getCommandLineValuePtr( const char inShortName )
    {
        const auto iter = myShortLookup.find( inShortName );
        
        if( iter == myShortLookup.cend() )
        {
            return nullptr;
        }
        
        return iter->second;
    }
    
    
    const CommandLineValue*
    CommandLineParser::getCommandLineValueConstPtr( const std::string& inLongName ) const
    {
        const auto iter = myValues.find( inLongName );
        
        if( iter == myValues.cend() )
        {
            return nullptr;
        }
        
        return ( iter->second ).get();
    }
    
    
    const CommandLineValue*
    CommandLineParser::getCommandLineValueConstPtr( const char inShortName ) const
    {
        const auto iter = myShortLookup.find( inShortName );
        
        if( iter == myShortLookup.cend() )
        {
            return nullptr;
        }
        
        return iter->second;
    }
    
    
    void
    CommandLineParser::copyState( const CommandLineParser& other )
    {
        myArgs = std::move( other.myArgs );

        myValues.clear();
        myShortLookup.clear();
        
        for( const auto& o : other.myValues )
        {
            std::unique_ptr<CommandLineValue> temp{ std::make_unique<CommandLineValue>( *o.second ) };
            auto ptr = temp.get();
            myValues.emplace( o.first, std::move( temp ) );
            myShortLookup.emplace( o.second->getPrototype().getShortName(), ptr );
        }
        
        myExecutablePath = std::move( other.myExecutablePath );
    }
    
    
    void
    CommandLineParser::moveState( CommandLineParser&& other )
    {
        myArgs = std::move( other.myArgs );
        myValues = std::move( other.myValues );
        myShortLookup = std::move( other.myShortLookup );
        myExecutablePath = std::move( other.myExecutablePath );
    }
}
