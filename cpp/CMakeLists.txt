# Specify version that supports CMake Presets.
cmake_minimum_required(VERSION 3.22)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Link runtime library statically.
cmake_policy(SET CMP0091 NEW)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Enable hot-reloading for MSVC if it's supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# `cmake_policy` must be applied before this line.
# `CMAKE_<LANG>_COMPILER_ID` must be applied before this line.
project ("dbmgr" LANGUAGES CXX C VERSION 0.1.0)

if(CMAKE_CXX_COMPILE_ID MATCHES "GNU|Clang")
    add_compile_options(-Werror -Wall -Wextra -Wpedantic)
endif()

# Apparently, sanitizers only works on Linux with clang. I couldn't use it with
# MSVC.
if(LINUX AND CMAKE_CXX_COMPILE_ID STREQUAL "Clang")
    add_compile_options(
                        $<$<CONFIG:DEBUG>:-O1>
                        $<$<CONFIG:DEBUG>:-fsanitize=undefined>
                        $<$<CONFIG:DEBUG>:-fsanitize=address>
                        # $<$<CONFIG:DEBUG>:-fsanitize=memory>
                        # $<$<CONFIG:DEBUG>:-fsanitize=thread>
                        )
    add_link_options(
                     $<$<CONFIG:DEBUG>:-fsanitize=undefined>
                     $<$<CONFIG:DEBUG>:-fsanitize=address>
                     # $<$<CONFIG:DEBUG>:-fsanitize=memory>
                     # $<$<CONFIG:DEBUG>:-fsanitize=thread>
                     )
endif()

include_directories(src)

add_executable (${PROJECT_NAME} WIN32 "src/main.cpp" "src/app.cpp" "src/frame.cpp")

# Setting file for high DPI devices on Windows.
target_sources(${PROJECT_NAME} PRIVATE app.manifest)

find_package(wxWidgets CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE wx::core wx::base)

# Example for building a library.

# add_library(core SHARED src/lib.cpp)
# set_target_properties(core PROPERTIES
#                      VERSION ${PROJECT_VERSION}
#                      SOVERSION ${PROJECT_VERSION_MAJOR})
