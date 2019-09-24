# scriabin by (c) Matthew James Briggs
cmake_minimum_required(VERSION 3.0)
project(scriabin LANGUAGES CXX VERSION 0.0.1)

set(DEBUG_INFO "scriabin/CMakeLists.txt")
set(CORE_LIBRARY_NAME scriabin_core)
set(MAIN_PROGRAM_NAME scriabin)
set(TEST_PROGRAM_NAME scriabin_test)
message(STATUS "${DEBUG_INFO} Line:${CMAKE_CURRENT_LIST_LINE} cmdgen cmake file starting")

# Options
option(ENABLE_TESTS "Enable tests" ON)

# Directories
set(DIR_EXTERN    "${CMAKE_CURRENT_SOURCE_DIR}/sourcecode/submodules")
set(DIR_EZXML     "${DIR_EXTERN}/ezxml")
set(DIR_INCLUDE   "${CMAKE_CURRENT_SOURCE_DIR}/sourcecode")
set(DIR_MX        "${DIR_EXTERN}/mx")
set(DIR_SOURCES   "${CMAKE_CURRENT_SOURCE_DIR}/sourcecode/scriabin")
set(DIR_TEST      "${CMAKE_CURRENT_SOURCE_DIR}/sourcecode/test")
set(EZXML_INCLUDE "${DIR_EZXML}/include")
set(MX_INCLUDE    "${DIR_MX}/Sourcecode/include")

message(STATUS "${DEBUG_INFO} Line:${CMAKE_CURRENT_LIST_LINE} DIR_EXTERN    = ${DIR_EXTERN}")
message(STATUS "${DEBUG_INFO} Line:${CMAKE_CURRENT_LIST_LINE} DIR_EZXML     = ${DIR_EZXML}")
message(STATUS "${DEBUG_INFO} Line:${CMAKE_CURRENT_LIST_LINE} DIR_INCLUDE   = ${DIR_INCLUDE}")
message(STATUS "${DEBUG_INFO} Line:${CMAKE_CURRENT_LIST_LINE} DIR_MX        = ${DIR_MX}")
message(STATUS "${DEBUG_INFO} Line:${CMAKE_CURRENT_LIST_LINE} DIR_SOURCES   = ${DIR_SOURCES}")
message(STATUS "${DEBUG_INFO} Line:${CMAKE_CURRENT_LIST_LINE} DIR_TEST      = ${DIR_TEST}")
message(STATUS "${DEBUG_INFO} Line:${CMAKE_CURRENT_LIST_LINE} EZXML_INCLUDE = ${EZXML_INCLUDE}")
message(STATUS "${DEBUG_INFO} Line:${CMAKE_CURRENT_LIST_LINE} MX_INCLUDE    = ${MX_INCLUDE}")

file(GLOB_RECURSE FILES_SOURCES ${DIR_SOURCES}/*.cpp)
file(GLOB_RECURSE FILES_HEADERS ${DIR_INCLUDE}/*.h*)
file(GLOB_RECURSE FILES_TEST_SOURCES ${DIR_TEST}/*.cpp)
file(GLOB_RECURSE FILES_TEST_HEADERS ${DIR_TEST}/*.h*)

add_subdirectory(${DIR_MX})
add_subdirectory(${DIR_EZXML})

# Create core library
add_library(${CORE_LIBRARY_NAME} STATIC "${FILES_SOURCES}")
target_include_directories(${CORE_LIBRARY_NAME} PUBLIC "${DIR_INCLUDE}")
target_include_directories(${CORE_LIBRARY_NAME} PRIVATE "${DIR_SOURCES}")
set_property(TARGET ${CORE_LIBRARY_NAME} PROPERTY CXX_STANDARD 17)
target_link_libraries(${CORE_LIBRARY_NAME} Mx)
target_link_libraries(${CORE_LIBRARY_NAME} ezxml)
target_include_directories(${CORE_LIBRARY_NAME} PRIVATE "${MX_INCLUDE}")
target_include_directories(${CORE_LIBRARY_NAME} PRIVATE "${EZXML_INCLUDE}")

# Create test runner
add_executable(${TEST_PROGRAM_NAME} "${FILES_TEST_SOURCES}")
target_include_directories(${TEST_PROGRAM_NAME} PUBLIC "${DIR_TEST}")
target_include_directories(${TEST_PROGRAM_NAME} PRIVATE "${DIR_INCLUDE}")
target_include_directories(${TEST_PROGRAM_NAME} PRIVATE "${DIR_SOURCES}")
set_property(TARGET ${TEST_PROGRAM_NAME} PROPERTY CXX_STANDARD 17)
#add_subdirectory(${DIR_MX})
#add_subdirectory(${DIR_EZXML})
target_link_libraries(${TEST_PROGRAM_NAME} ${CORE_LIBRARY_NAME})
target_include_directories(${TEST_PROGRAM_NAME} PRIVATE "${MX_INCLUDE}")
target_include_directories(${TEST_PROGRAM_NAME} PRIVATE "${EZXML_INCLUDE}")
