cmake_minimum_required(VERSION 3.12)
project(ihpcc)

set(CMAKE_CXX_COMPILER "mpicxx")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wno-comment -Wno-switch -m64 -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "-Wextra -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

include_directories("${CMAKE_SOURCE_DIR}/include" "${MKLROOT}/../compilers_and_libraries/linux/mpi/intel64/include")
add_definitions(-DOFFLINE_JUDGE)

file(GLOB CPP_FILES "[^-]*.cpp")

foreach(CPP_FILE ${CPP_FILES})
	get_filename_component(F_NAME ${CPP_FILE} NAME_WE)
	add_executable(${F_NAME} ${CPP_FILE})
	target_link_libraries(${F_NAME} ${MPI_LIBRARIES})
endforeach()

