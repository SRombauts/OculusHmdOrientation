# Copyright (c) 2014 Sebastien Rombauts (sebastien.rombauts@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT) 

cmake_minimum_required(VERSION 2.6)
project(OculusHmdOrientation)

# Define useful variables to handle OS/Compiler differences
if (MSVC)
    # disable Visual Studio usual warnings
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    # For OculusVR / LibOVR debug build
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -DOVR_BUILD_DEBUG")
elseif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Using std::shared_ptr
    message(STATUS "C++11 activated for std::shared_ptr")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")  # -std=c++11
endif ()


## Core source code ##

# All includes are relative to the "src" directory 
include_directories("${PROJECT_SOURCE_DIR}/src")

# adding a new file require explicittly modifing the CMakeLists.txt
# so that CMake knows that it should rebuild the project (it is best practice)


# add sources for the executable :
add_executable(OculusHmdOrientation
 src/OculusHMD.h src/OculusHMD.cpp
)


## Libraries ##

## Oculus SDK library in last position ##
# add the subdirectory of the Oculus SDK LibOVR library
if (MSVC)
    # Oculus LibOVR uses unicode (WCHAR/wchar_t) windows API
    # WARNING: this can affect any further library! Keep in last position.
    add_definitions(-DUNICODE -D_UNICODE)
endif ()
add_subdirectory(OculusSDK/LibOVR)
include_directories("${PROJECT_SOURCE_DIR}/OculusSDK/LibOVR/Include")


## Linking ##

# link the executable with all required libraries
target_link_libraries(OculusHmdOrientation OculusVR)


