#!/bin/sh

CLANG_FORMAT=clang-format-9

find ./ihpcc/src -type f -iname "*.cpp" | xargs $CLANG_FORMAT -style=file -i
find ./misc/src -type f -iname "*.cpp" | xargs $CLANG_FORMAT -style=file -i
find ./uva/src -type f -iname "*.cpp" | xargs $CLANG_FORMAT -style=file -i
