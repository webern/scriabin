#pragma once
#include <string>

namespace pen
{
    // TODO - replace with something dynamic
    constexpr const char* const PEN_PATH = "/Users/mjb/Documents/repos/pen/";

    inline const std::string& INSTRUMENT_CONFIG_FILEPATH()
    {
        static const std::string result = std::string{ PEN_PATH } + std::string{ "sourcecode/instrument-config/instrument-config.xml" };
        return result;
    }

    inline const std::string& OUTPUT_DIRECTORY()
    {
        static const std::string result = std::string{ PEN_PATH } + std::string{ "out/" };
        return result;
    }

    inline const std::string& INPUT_DIRECTORY()
    {
        static const std::string result = std::string{ PEN_PATH } + std::string{ "in/" };
        return result;
    }

    inline const std::string& TEST_FILES_DIRECTORY()
    {
        static const std::string result = INPUT_DIRECTORY() + std::string{ "test-files/" };
        return result;
    }

    inline const std::string& MUSIC_INPUT_FILES_DIRECTORY()
    {
        static const std::string result = INPUT_DIRECTORY() + std::string{ "music-files/" };
        return result;
    }
    
    inline const std::string& MUSIC_OUTPUT_FILES_DIRECTORY()
    {
        static const std::string result = OUTPUT_DIRECTORY() + std::string{ "comp/" };
        return result;
    }
    
    inline const std::string& DIGITS_DAT_PATH()
    {
        static const std::string result = INPUT_DIRECTORY() + std::string{ "digits.dat" };
        return result;
    }
}
