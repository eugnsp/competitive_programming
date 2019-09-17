#!/bin/sh

find ./src/ihpcc -type f -iname "*.cpp" | xargs clang-format -style=file -i
find ./src/misc -type f -iname "*.cpp" | xargs clang-format -style=file -i
find ./src/uva -type f -iname "*.cpp" | xargs clang-format -style=file -i
