#
# Source Includes
#=======================================================================
file(GLOB_RECURSE PGRM1_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

#
# Includes
#=====================================================================
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(program1 ${PGRM1_SOURCES})

# add_custom_command(TARGET program1
#           POST_BUILD
#           COMMAND ${CMAKE_COMMAND} -E copy 
#           	${CMAKE_SOURCE_DIR}/al_weather_station.txt 
#           	${PROJECT_BINARY_DIR}/bin/al_weather_station.txt
# )