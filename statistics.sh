#!/usr/bin/env sh

find -name "*.cpp" -o -name "*.hpp" | xargs cat | grep -v -e '$^' | wc -l
