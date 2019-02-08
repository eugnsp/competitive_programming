cmake_minimum_required (VERSION 3.5)
project (algorithms)

set(CMAKE_CXX_STANDARD 14) # 11
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -m64 -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-Wextra -O0 -ggdb3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

file(GLOB_RECURSE ALGO_SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/uva")

set(UVA_FILES)
foreach(CPP_FILE ${ALGO_SRC})
	get_filename_component(F_NAME ${CPP_FILE} NAME_WE)
	add_executable(${F_NAME} ${CPP_FILE})

	string(REPLACE ".cpp" ".uva" UVA_FILE ${CPP_FILE})
	string(REPLACE "${PROJECT_SOURCE_DIR}/src" "${PROJECT_BINARY_DIR}/uva" UVA_FILE ${UVA_FILE})
	add_custom_command(
		OUTPUT ${UVA_FILE}
		COMMAND "${PROJECT_SOURCE_DIR}/generate.pl" ${CPP_FILE} ${UVA_FILE}
		DEPENDS ${CPP_FILE})
	list(APPEND UVA_FILES ${UVA_FILE})
endforeach()

add_custom_target(uva DEPENDS ${UVA_FILES})
