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

add_executable(assignment3 ${PGRM3_SOURCES})

macro(port_file arg arg2)
	add_custom_command(TARGET assignment3
	          POST_BUILD
	          COMMAND ${CMAKE_COMMAND} -E copy 
	          	${CMAKE_CURRENT_SOURCE_DIR}/${arg} 
	          	${PROJECT_BINARY_DIR}/bin/${arg2}
	)
endmacro(port_file)

macro (do_test_runs arg result)
  add_test (TutorialComp${arg} ${PROJECT_BINARY_DIR}/bin/baby_block_bot ${PROJECT_BINARY_DIR}/bin/${arg})
  set_tests_properties (TutorialComp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test_runs)

port_file(daily_data.txt Debug/daily_data.txt)

# do_test_runs(test_case_1.txt abefiijnpqrsttuvwxyy)



