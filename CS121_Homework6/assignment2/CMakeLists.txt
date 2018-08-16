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

add_executable(assignment2 ${PGRM2_SOURCES})

macro(port_file arg)
	add_custom_command(TARGET assignment2
	          POST_BUILD
	          COMMAND ${CMAKE_COMMAND} -E copy 
	          	${CMAKE_SOURCE_DIR}/${arg} 
	          	${PROJECT_BINARY_DIR}/bin/${arg}
	)
endmacro(port_file)

macro (do_test_runs arg result)
  add_test (TutorialComp${arg} ${PROJECT_BINARY_DIR}/bin/baby_block_bot ${PROJECT_BINARY_DIR}/bin/${arg})
  set_tests_properties (TutorialComp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test_runs)

# port_file(test_case_1.txt)

# do_test_runs(test_case_1.txt abefiijnpqrsttuvwxyy)



