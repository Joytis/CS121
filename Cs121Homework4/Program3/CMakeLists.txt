#
# Source Includes
#=======================================================================
file(GLOB_RECURSE PGRM3_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

#
# Includes
#=====================================================================
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(program3 ${PGRM3_SOURCES})