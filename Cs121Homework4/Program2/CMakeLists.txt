#
# Source Includes
#=======================================================================
file(GLOB_RECURSE PGRM2_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

#
# Includes
#=====================================================================
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(program2 ${PGRM2_SOURCES})

add_custom_command(TARGET program2
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy 
          	${CMAKE_SOURCE_DIR}/program2/pgrm2_input.txt 
          	${PROJECT_BINARY_DIR}/bin/pgrm2_input.txt
)