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

add_executable(baby_block_bot ${PGRM1_SOURCES})

macro(port_file arg)
	add_custom_command(TARGET baby_block_bot
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


port_file(test_case_1.txt)
port_file(test_case_2.txt)
port_file(test_case_3.txt)
port_file(test_case_4.txt)
port_file(test_case_5.txt)

do_test_runs(test_case_1.txt abefiijnpqrsttuvwxyy abefiijnpqrsttuvwxyy)
do_test_runs(test_case_2.txt abfghijkmoprstuvwxyz abfghijkmoprstwuvxyz)
do_test_runs(test_case_3.txt abfghiijkoprstuvwxyz)
do_test_runs(test_case_4.txt aaaaaqqqqqxxxxxyyyyy)
do_test_runs(test_case_5.txt aaaaaqqqvvvvxxxyyzzz)


