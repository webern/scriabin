#pragma once
#include <string>

// TODO - replace with something dynamic
constexpr const char* const PEN_PATH = "/Users/mjb/Documents/repos/pen/";

inline const std::string INSTRUMENT_CONFIG_FILEPATH()
{
    static const std::string& result = std::string{ PEN_PATH } + std::string{ "sourcecode/instrument-config/instrument-config.xml" };
    return result;
}

inline const std::string& OUTPUT_DIRECTORY()
{
    static const std::string& result = std::string{ PEN_PATH } + std::string{ "out/" };
    return result;
}

inline const std::string INPUT_DIRECTORY()
{
    static const std::string& result = std::string{ PEN_PATH } + std::string{ "in/" };
    return result;
}

inline const std::string TEST_FILES_DIRECTORY()
{
    static const std::string& result = INPUT_DIRECTORY() + std::string{ "test-files/" };
    return result;
}
