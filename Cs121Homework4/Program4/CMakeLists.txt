#
# Source Includes
#=======================================================================
file(GLOB_RECURSE PGRM4_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

#
# Includes
#=====================================================================
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(program4 ${PGRM4_SOURCES})
