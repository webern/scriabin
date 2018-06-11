#include "catch.hpp"
#include "pen/etude1.h"
#include "PEN_PATH.h"
#include "mx/api/DocumentManager.h"
#include "mx/api/ScoreData.h"
#include "pen/Coalescence.h"

using namespace zeus;

TEST_CASE( "coalescence", "Comp" )
{
    pen::Coalescence coalescence;
    coalescence.doEverthing();
}
