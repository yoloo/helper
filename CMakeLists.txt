##############################################################################################
# 0.编译参数
##############################################################################################
# @工程配置
cmake_minimum_required(VERSION 2.8)
project(helper)

# @编译器选择
if (HELPER_CXX STREQUAL gcc)
    set(CMAKE_CXX_COMPILER g++)
    set(CMAKE_C_COMPILER gcc)
else()
    set(CMAKE_CXX_COMPILER clang++)
    set(CMAKE_C_COMPILER clang)
endif()
message(${CMAKE_CXX_COMPILER})
message(${CMAKE_C_COMPILER})

# @debug/release
if (HELPER_RELEASE)
    set(VERSIONSTRING ${HELPER_RELEASE})
else()
    set(VERSIONSTRING "0.0.0")
endif()
#message(${VERSIONSTRING})

##############################################################################################
# 1.编译器特定选项
##############################################################################################
# @gcc/clang
message(${CMAKE_C_COMPILER})
if (CMAKE_C_COMPILER STREQUAL gcc)
    set(HELPER_CXXFLAGS "-std=c++11 -Wno-error=delete-non-virtual-dtor -D_CXX_GCC")

    #set(ZT2_CXXLIB_DIR /zt2/gcc/lib)
else()
    message("hello")
    set(HELPER_CXXFLAGS "-std=c++11 -Wno-error=delete-non-virtual-dtor -D_CXX_CLANG")

    #set(ZT2_CXXLIB_DIR /zt2/clang/lib)
endif()
message(${HELPER_CXXFLAGS})

# @内存检测
if(HELPER_ASAN)
    set(ASAN_CXXFLAGS "-fsanitize=address -fno-omit-frame-pointer")
    set(ASAN_LDFLAGS "-fsanitize=address")
endif()

# @内存泄漏检测
if(HELPER_LSAN)
    set(LSAN_CXXFLAGS "-fsanitize=leak")
    set(LSAN_LDFLAGS "-fsanitize=leak")
endif()

# @性能检测
if(HELPER_PROFILE)
    set(PROFILE_CXXFLAGS "-fprofile-instr-generate")
    set(PROFILE_LDFLAGS "-fprofile-instr-generate")
endif()

##############################################################################################
# 2.编译选项
##############################################################################################
# @通用编译选项
set(HELPER_CXXFLAGS_COMMON "-g -Werror -Wno-deprecated ${HELPER_CXXFLAGS} ${ASAN_CXXFLAGS} ${LSAN_CXXFLAGS} ${PROFILE_CXXFLAGS}")

# @debug编译选项
set(HELPER_CXXFLAGS_DEBUG ${HELPER_CXXFLAGS_COMMON})

# @release编译选项
set(HELPER_CXXFLAGS_RELEASE "-O2 ${HELPER_CXXFLAGS_COMMON}")

##############################################################################################
# 3.链接选项
##############################################################################################
# @通用链接选项
set(HELPER_LDFLAGS_COMMON "-static-libstdc++ -static-libgcc ${ASAN_LDFLAGS} ${LSAN_LDFLAGS} ${PROFILE_LDFLAGS}")

# @debug链接选项
set(HELPER_LDFLAGS_DEBUG ${HELPER_LDFLAGS_COMMON})

# @release链接选项
set(HELPER_LDFLAGS_RELEASE ${HELPER_LDFLAGS_COMMON})

##############################################################################################
# 4.debug/release的编译、连接选项
##############################################################################################
if(HELPER_RELEASE)
    set(CMAKE_CXX_FLAGS ${HELPER_CXXFLAGS_RELEASE})
    set(CMAKE_EXE_LINKER_FLAGS ${HELPER_LDFLAGS_RELEASE})
else()
    set(CMAKE_CXX_FLAGS ${HELPER_CXXFLAGS_DEBUG})
    set(CMAKE_EXE_LINKER_FLAGS ${HELPER_LDFLAGS_DEBUG})
endif()

message("编译器: ${CMAKE_CXX_COMPILER}")
message("内存检测: ${ASAN_CXXFLAGS}")
message("性能检测: ${PROFILE_CXXFLAGS}")
message("编译选项: ${CMAKE_CXX_FLAGS}")
message("链接选项: ${CMAKE_EXE_LINKER_FLAGS}")

##############################################################################################
# 5.源码目录
##############################################################################################
set(SUBDIRS
        tests
        tools)

foreach(DIR ${SUBDIRS})
    add_subdirectory(${DIR})
endforeach()