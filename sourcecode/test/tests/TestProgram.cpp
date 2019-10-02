#include "catch.hpp"
#include "scriabin/Program.h"
#include "SCRIABIN_PATH.h"

using namespace zeus;

TEST_CASE( "Program test001", "Program" )
{
    const std::string opath = "/my/path.xml";
    const std::string ipath = scriabin::INSTRUMENT_CONFIG_FILEPATH();

    constexpr const int argc = 5;
    const char* argv[argc] = {
            "/some/path/to/the/executable",
            "-o",
            opath.c_str(),
            "--instrument-config",
            ipath.c_str(),
    };

    scriabin::Program program{ argc, argv };
    CHECK( program.isOutfileSpecified );
    CHECK( opath == program.outfilePath.c_str() );
    CHECK( program.isInstrumentConfigSpecified );
    CHECK( ipath == program.instrumentConfigPath.c_str() );
}

