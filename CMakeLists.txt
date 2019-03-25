cmake_minimum_required (VERSION 3.7)
project (algorithms)

set(CMAKE_CXX_STANDARD 17) # 11
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wno-comment -Wno-switch -m64 -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-Wextra -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

include_directories("${PROJECT_SOURCE_DIR}/include")
add_definitions(-DOFFLINE_JUDGE)

file(GLOB UVA_SRC   "${PROJECT_SOURCE_DIR}/src/uva/*.cpp")
file(GLOB OTHER_SRC "${PROJECT_SOURCE_DIR}/src/other/*.cpp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin/uva")
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/uva_src")
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/other_src")

set(UVA_FILES)
foreach(CPP_FILE ${UVA_SRC})
	get_filename_component(F_NAME ${CPP_FILE} NAME_WE)
#	add_executable(${F_NAME} ${CPP_FILE})

	string(REPLACE ".cpp" ".uva" UVA_FILE ${CPP_FILE})
	string(REPLACE "${PROJECT_SOURCE_DIR}/src/uva" "${PROJECT_BINARY_DIR}/uva_src" UVA_FILE ${UVA_FILE})
	add_custom_command(
		OUTPUT ${UVA_FILE}
		COMMAND "${PROJECT_SOURCE_DIR}/generate.pl" "${CPP_FILE}" "${UVA_FILE}" "${PROJECT_SOURCE_DIR}/include"
		DEPENDS ${CPP_FILE})
	list(APPEND UVA_FILES ${UVA_FILE})
endforeach()

foreach(CPP_FILE ${OTHER_SRC})
	get_filename_component(F_NAME ${CPP_FILE} NAME_WE)
#	add_executable(${F_NAME} ${CPP_FILE})

	string(REPLACE ".cpp" ".uva" OTHER_FILE ${CPP_FILE})
	string(REPLACE "${PROJECT_SOURCE_DIR}/src/other" "${PROJECT_BINARY_DIR}/other_src" OTHER_FILE ${OTHER_FILE})
	add_custom_command(
		OUTPUT ${OTHER_FILE}
		COMMAND "${PROJECT_SOURCE_DIR}/generate.pl" "${CPP_FILE}" "${OTHER_FILE}" "${PROJECT_SOURCE_DIR}/include"
		DEPENDS ${CPP_FILE})
	list(APPEND UVA_FILES ${OTHER_FILE})
endforeach()

add_custom_target(pre DEPENDS ${UVA_FILES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
foreach(CPP_FILE ${UVA_SRC} ${OTHER_SRC})
	get_filename_component(F_NAME ${CPP_FILE} NAME_WE)
	add_executable(${F_NAME} ${CPP_FILE})
endforeach()
