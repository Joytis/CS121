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

add_executable(assignment1 ${PGRM1_SOURCES})

macro(port_file arg arg2)
	add_custom_command(TARGET assignment1
	          POST_BUILD
	          COMMAND ${CMAKE_COMMAND} -E copy 
	          	${CMAKE_CURRENT_SOURCE_DIR}/${arg} 
	          	${PROJECT_BINARY_DIR}/bin/${arg2}
	)
endmacro(port_file)

macro (do_test_runs arg result)
  add_test (TutorialComp${arg} ${PROJECT_BINARY_DIR}/bin/assignment1 ${PROJECT_BINARY_DIR}/bin/${arg})
  set_tests_properties (TutorialComp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test_runs)

port_file(input.txt Debug/input.txt)
port_file(dictionary_of_four_letter_words.txt Debug/dictionary_of_four_letter_words.txt)

# do_test_runs(test_case_1.txt abefiijnpqrsttuvwxyy)



