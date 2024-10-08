# Copyright (C) 2018-2022 Intel Corporation
# SPDX-License-Identifier: Apache-2.0
#

project(zlib)

if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4996 /W3")
    set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /wd4995 /wd4996")
else()
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-all")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
        #266: function "XXX" declared implicitly
        set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -diag-disable=266")
    endif()
endif()

set(TARGET_NAME "zlib")

set(lib_srcs 
    zlib/adler32.c
    zlib/compress.c
    zlib/crc32.c
    zlib/deflate.c
    zlib/gzclose.c
    zlib/gzlib.c
    zlib/gzread.c
    zlib/gzwrite.c
    zlib/inflate.c
    zlib/infback.c
    zlib/inftrees.c
    zlib/inffast.c
    zlib/trees.c
    zlib/uncompr.c
    zlib/zutil.c
)

set(lib_hdrs 
    zlib/crc32.h
    zlib/deflate.h
    zlib/gzguts.h
    zlib/inffast.h
    zlib/inffixed.h
    zlib/inflate.h
    zlib/inftrees.h
    zlib/trees.h
    zlib/zutil.h
)

set(lib_ext_hdrs "zlib/zlib.h" "zlib/zconf.h")
add_library(${TARGET_NAME} STATIC ${lib_srcs} ${lib_hdrs} ${lib_ext_hdrs})

target_include_directories(${TARGET_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/zlib")

set_target_properties(zlib PROPERTIES FOLDER thirdparty)
