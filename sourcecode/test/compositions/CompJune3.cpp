#include "catch.hpp"
#include "pen/etude1.h"
#include "PEN_PATH.h"
#include "mx/api/DocumentManager.h"
#include "mx/api/ScoreData.h"

using namespace zeus;

TEST_CASE( "etude1", "Comp" )
{
    const auto& iConfig = pen::INSTRUMENT_CONFIG_FILEPATH();
    const auto& oDir = pen::OUTPUT_DIRECTORY();
    const std::string oPath = oDir + std::string{ "june3.actual.xml" };
    const std::vector<std::string> args =
    {
        "/some/path/to/the/executable",
        "-o",
        oPath,
        "--instrument-config",
        iConfig,
    };
}
