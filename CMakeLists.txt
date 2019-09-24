# scriabin by (c) Matthew James Briggs
cmake_minimum_required(VERSION 3.0)
project(scriabin LANGUAGES CXX VERSION 0.0.1)

set(DEBUG_INFO "scriabin/CMakeLists.txt")
set(CORE_LIBRARY_NAME scriabin_core)
set(MAIN_PROGRAM_NAME scriabin)
set(TEST_PROGRAM_NAME scriabin_test)
message(STATUS "${DEBUG_INFO} Line:${CMAKE_CURRENT_LIST_LINE} cmdgen cmake file starting")

# Options
option(CMDGEN_ENABLE_TESTS "Enable tests" ON)

# Directories
set(DIR_CMDGEN_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sourcecode/scriabin")
set(DIR_CMDGEN_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/sourcecode")
#set(DIR_MAIN_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sourcecode/scriabin")
#set(DIR_MAIN_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/sourcecode/scriabin")
set(DIR_TEST "${CMAKE_CURRENT_SOURCE_DIR}/sourcecode/test")
set(DIR_EXTERN "${CMAKE_CURRENT_SOURCE_DIR}/sourcecode/submodules")
set(DIR_MX "${DIR_EXTERN}/mx")
set(DIR_EZXML "${DIR_EXTERN}/ezxml")
set(MX_INCLUDE "${DIR_MX}/Sourcecode/include")
set(EZXML_INCLUDE "${DIR_EZXML}/include")

file(GLOB_RECURSE FILES_CMDGEN_SOURCES ${DIR_CMDGEN_SOURCES}/*.cpp)
file(GLOB_RECURSE FILES_CMDGEN_HEADERS ${DIR_CMDGEN_INCLUDE}/*.h*)
#file(GLOB FILES_MAIN_SOURCES ${DIR_MAIN_SOURCES}/*.cpp)
#file(GLOB FILES_MAIN_HEADERS ${DIR_MAIN_INCLUDE}/*.h*)
file(GLOB_RECURSE FILES_CMDGEN_TEST_SOURCES ${DIR_TEST}/*.cpp)
file(GLOB_RECURSE FILES_CMDGEN_TEST_HEADERS ${DIR_TEST}/*.h*)

# Create core library
add_library(${CORE_LIBRARY_NAME} "${FILES_CMDGEN_SOURCES}")
target_include_directories(${CORE_LIBRARY_NAME} PUBLIC "${DIR_CMDGEN_INCLUDE}")
target_include_directories(${CORE_LIBRARY_NAME} PRIVATE "${DIR_CMDGEN_SOURCES}")
set_property(TARGET ${CORE_LIBRARY_NAME} PROPERTY CXX_STANDARD 17)
add_subdirectory(${DIR_MX})
add_subdirectory(${DIR_EZXML})
target_link_libraries(${CORE_LIBRARY_NAME} mx)
target_link_libraries(${CORE_LIBRARY_NAME} ezxml)
target_include_directories(${CORE_LIBRARY_NAME} PRIVATE "${MX_INCLUDE}")
target_include_directories(${CORE_LIBRARY_NAME} PRIVATE "${EZXML_INCLUDE}")