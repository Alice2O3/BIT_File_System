cmake_minimum_required( VERSION 3.8 )

project( "BIT_File_System" )

set( CMAKE_CXX_STANDARD 17 )

set( MAIN_DIRECTORY "main" )
set( MAIN_EXE_NAME "BIT_VFS" )
set( UNIT_TEST_DIRECTORY "unit_test" )
set( RUN_DIRECTORY "run" )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${RUN_DIRECTORY}" )

include_directories( "include" "template" )
aux_source_directory( "src" SRCLIST )
add_library( VFS_Lib ${SRCLIST})

add_executable( ${MAIN_EXE_NAME} ${MAIN_DIRECTORY}/${MAIN_EXE_NAME}.cpp )
target_link_libraries( ${MAIN_EXE_NAME} VFS_Lib )

file( GLOB UNIT_TESTS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/${UNIT_TEST_DIRECTORY}" "${UNIT_TEST_DIRECTORY}/*.cpp" )
foreach( relative_path ${UNIT_TESTS} )
    string( REPLACE ".cpp" "" file_name ${relative_path} )
	add_executable( ${file_name} "${UNIT_TEST_DIRECTORY}/${relative_path}" )
	target_link_libraries( ${file_name} VFS_Lib )
endforeach()
