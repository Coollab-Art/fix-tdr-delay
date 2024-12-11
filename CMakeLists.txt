cmake_minimum_required(VERSION 3.20)

set(WARNINGS_AS_ERRORS_FOR_FIX_TDR_DELAY OFF CACHE BOOL "ON iff you want to treat warnings as errors")

add_library(fix_tdr_delay)
add_library(fix_tdr_delay::fix_tdr_delay ALIAS fix_tdr_delay)
target_compile_features(fix_tdr_delay PUBLIC cxx_std_14)

# ---Add source files---
if(WARNINGS_AS_ERRORS_FOR_FIX_TDR_DELAY)
    target_include_directories(fix_tdr_delay PUBLIC include)
else()
    target_include_directories(fix_tdr_delay SYSTEM PUBLIC include)
endif()

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
target_sources(fix_tdr_delay PRIVATE ${SRC_FILES})

# ---Set warning level---
if(MSVC)
    target_compile_options(fix_tdr_delay PRIVATE /W4)
else()
    target_compile_options(fix_tdr_delay PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion -Wimplicit-fallthrough)
endif()

# ---Maybe enable warnings as errors---
if(WARNINGS_AS_ERRORS_FOR_FIX_TDR_DELAY)
    if(MSVC)
        target_compile_options(fix_tdr_delay PRIVATE /WX)
    else()
        target_compile_options(fix_tdr_delay PRIVATE -Werror)
    endif()
endif()
