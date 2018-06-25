#include "catch.hpp"
#include "pen/etude1.h"
#include "PEN_PATH.h"
#include "mx/api/DocumentManager.h"
#include "mx/api/ScoreData.h"
#include "pen/Coalescence.h"

using namespace zeus;

TEST_CASE( "coalescence", "Comp" )
{
    const std::string outFilename = "coalescence.large.xml";
    const std::string inFilename = "coalescence.input.xml";
    const auto inFilepath = pen::MUSIC_INPUT_FILES_DIRECTORY() + "/" + inFilename;
    const auto outFilepath = pen::MUSIC_OUTPUT_FILES_DIRECTORY() + "/" + outFilename;
    //inFilepath, outFilepath
    pen::Coalescence coalescence{  };
    coalescence.doEverthing();
}
