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
)

# Automatically find all header files in the include/ directory
file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/include/*.h")



add_executable(game ${SOURCES} ${HEADERS}) 



target_include_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/lib)


# Link directories where your 'raylib.lib' is located
target_link_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/lib/)

# Link the prebuilt raylib library
target_link_libraries(game PRIVATE raylib)

# Link to winmm.lib (required for runtime stuff)
if (WIN32)
    target_link_libraries(game PRIVATE winmm.lib)

elseif(APPEL)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    target_link_libraries(game PRIVATE ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
else()
    target_link_libraries(game PRIVATE X11 pthread GL)

endif()

set_target_properties(game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)


