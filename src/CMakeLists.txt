# Adds .cpp files
set(SOURCES
    main.cpp
    parser.cpp
    game.cpp
    startMenu.cpp
    utils.cpp
    entity.cpp
    player.cpp
    inputElement.cpp
    uiElement.cpp
    debugScreen.cpp
    dice.cpp
    label.cpp
    mouseDragController.cpp
)

# Automatically find all header files in the include/ directory
file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/include/*.h")



add_executable(game ${SOURCES} ${HEADERS} ../assets/icons/icon.rc) 


if(MSVC)
    target_compile_options(game PRIVATE
        $<$<CONFIG:Debug>:/MDd>
        $<$<CONFIG:Dist>:/MD>
        $<$<CONFIG:Release>:/MD>
        $<$<CONFIG:RelWithDebInfo>:/MD>
        $<$<CONFIG:MinSizeRel>:/MD>
    )
endif()







target_include_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/lib)


# Link directories where your 'raylib.lib' is located
target_link_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/lib/)

# Link the prebuilt raylib library
target_link_libraries(game PRIVATE raylib)

# Link to winmm.lib (required for runtime stuff)
if (WIN32)
    target_link_libraries(game PRIVATE winmm.lib)

elseif(APPLE)
    target_link_libraries(game PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework CoreAudio"
        "-framework AudioToolbox"
    )
else()
    target_link_libraries(game PRIVATE pthread)

endif()

set_target_properties(game PROPERTIES
 #   RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
  VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)


