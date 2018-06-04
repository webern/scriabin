#include "catch.hpp"
#include "pen/etude1.h"
#include "PEN_PATH.h"
#include "mx/api/DocumentManager.h"
#include "mx/api/ScoreData.h"
#include "pen/june3.h"

using namespace zeus;

TEST_CASE( "june3", "Comp" )
{
//    const auto& iConfig = pen::INSTRUMENT_CONFIG_FILEPATH();
//    const auto& oDir = pen::OUTPUT_DIRECTORY();
//    const std::string oPath = oDir + std::string{ "june3.actual.xml" };
//    const std::vector<std::string> args =
//    {
//        "/some/path/to/the/executable",
//        "-o",
//        oPath,
//        "--instrument-config",
//        iConfig,
//    };
    
    pen::June3 june3;
    june3.doEverthing();
}
