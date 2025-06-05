cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Only for single-config generators (MinGW, Make)
if(NOT CMAKE_CONFIGURATION_TYPES)
    set(allowed_build_types Debug Release RelWithDebInfo MinSizeRel Dist)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${allowed_build_types})
endif()

if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo;MinSizeRel;Dist" CACHE STRING "" FORCE)
endif()

# Linker flags to enable whole program optimization and other optimizations
if (MSVC)
set(CMAKE_EXE_LINKER_FLAGS_DIST "/LTCG")
set(CMAKE_SHARED_LINKER_FLAGS_DIST "/LTCG")
endif()

# Use static runtime (optional, but common for distribution builds)
foreach(flag_var
    CMAKE_C_FLAGS_DIST
    CMAKE_CXX_FLAGS_DIST
)
    string(REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    string(REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}")
endforeach()





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

