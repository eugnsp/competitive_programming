cmake_minimum_required(VERSION 3.7)
project(uva)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wno-comment -Wno-switch -m64 -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-Wextra -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

file(GLOB CPP_FILES "[^-]*.cpp")
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/txt")

set(TXT_FILES)
foreach(CPP_FILE ${CPP_FILES})
	get_filename_component(F_NAME ${CPP_FILE} NAME_WE)
	add_executable(${F_NAME} ${CPP_FILE})
	target_compile_definitions(${F_NAME} PUBLIC OFFLINE_JUDGE)
	target_include_directories(${F_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include")
	target_compile_features(${F_NAME} PUBLIC cxx_std_17)
	target_compile_options(${F_NAME} PUBLIC -Wall -Wpedantic -Wextra -Werror=return-type -m64 -march=native 
		$<$<CONFIG:DEBUG>:-O0 -g> $<$<CONFIG:RELEASE>:-Wno-unused-parameter -Wno-deprecated-declarations -O3 -DNDEBUG>)

	string(REPLACE ".cpp" ".txt" TXT_FILE ${CPP_FILE})
	string(REPLACE "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}/txt" TXT_FILE ${TXT_FILE})
	add_custom_command(
		OUTPUT ${TXT_FILE}
		COMMAND "${CMAKE_SOURCE_DIR}/generate.pl" "${CPP_FILE}" "${TXT_FILE}" "${CMAKE_SOURCE_DIR}/include"
		DEPENDS ${CPP_FILE})
	list(APPEND TXT_FILES ${TXT_FILE})
endforeach()

add_custom_target(uva_txt ALL DEPENDS ${TXT_FILES})
