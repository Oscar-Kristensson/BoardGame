cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(game VERSION 1.0)



set(OUTPUT_ROOT ${CMAKE_BINARY_DIR})

# For single-config generators (MinGW, Ninja, Makefiles)
if(NOT CMAKE_CONFIGURATION_TYPES)
    # Ensure CMAKE_BUILD_TYPE is defined
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug)
    endif()

    message(STATUS "Configuring for single-config generator, build type: ${CMAKE_BUILD_TYPE}")

    message(STATUS "Output dir: ${OUTPUT_ROOT}/bin/${CMAKE_BUILD_TYPE}")

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_ROOT}/bin/${CMAKE_BUILD_TYPE}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_ROOT}/lib/${CMAKE_BUILD_TYPE}")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_ROOT}/lib/${CMAKE_BUILD_TYPE}")

# For multi-config generators (Visual Studio, Xcode)
else()


    foreach(OUTPUTCONFIG Debug Release RelWithDebInfo MinSizeRel)
        string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${OUTPUT_ROOT}/bin/${OUTPUTCONFIG})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${OUTPUT_ROOT}/lib/${OUTPUTCONFIG})
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG_UPPER} ${OUTPUT_ROOT}/lib/${OUTPUTCONFIG})
    endforeach()

endif()

add_subdirectory(src)

