cmake_minimum_required(VERSION 2.8)
project(helper)

set(SUBDIRS
        tests
        tools)

foreach(DIR ${SUBDIRS})
    add_subdirectory(${DIR})
endforeach()