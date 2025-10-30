cmake_minimum_required(VERSION 3.15)
project(speller2 C)

# Require C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Warnings and reasonable defaults
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wvla)
    # Optimize a bit by default unless user sets CMAKE_BUILD_TYPE
    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    endif()
endif()

add_executable(speller
    speller.c
    dictionary.c
)

target_include_directories(speller PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# On Unix, link rt if needed for getrusage on some systems (usually not required on modern Linux)
# Uncomment if you hit unresolved symbols related to time/resource usage
# if(UNIX)
#     target_link_libraries(speller PRIVATE rt)
# endif()
