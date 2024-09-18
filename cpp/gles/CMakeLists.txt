# Mnimum version that supports CMake Presets feature.
cmake_minimum_required(VERSION 3.22)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Link a runtime library statically on Windows.
if (POLICY CMP0141)
  cmake_policy(SET CMP0091 NEW)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Enable a hot-reloading feature of MSVC if it's supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# `cmake_policy` must be applied before this line.
# `CMAKE_<LANG>_COMPILER_ID` must be applied before this line.
project ("xgles" LANGUAGES CXX C VERSION 0.1.0)

if(CMAKE_CXX_COMPILE_ID MATCHES "GNU|Clang")
    add_compile_options(-Werror -Wall -Wextra -Wpedantic)
    # Drop unused libraries.
    add_link_options(--as-needed)
endif()

# Apparently, sanitizers only work well on Linux with clang.
# I couldn't find out how to get MSVC to work with it.
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

add_executable (${PROJECT_NAME} "src/main.c" "src/font.c")

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Fontconfig REQUIRED)

if(MINGW)
    # Dependant goes first followed by dependencies as in some_dependant.c -lsome_dependency.
    target_link_libraries(${PROJECT_NAME} PRIVATE -lglfw3 -lgdi32 -lEGL -lGLESv2 -lfontconfig -lfreetype)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw ${OPENGL_egl_LIBRARY} ${OPENGL_gles2_LIBRARY} ${Fontconfig_LIBRARIES})
endif()

# The below is an example of how to build a C library.
# add_library(${PROJECT_NAME} SHARED "src/lib.c")
# set_target_properties(core PROPERTIES
#                      VERSION ${PROJECT_VERSION}
#                      SOVERSION ${PROJECT_VERSION_MAJOR})
