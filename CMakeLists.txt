cmake_minimum_required(VERSION 3.1)

project(TheHungryCell)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(SOURCES Cells/BackgroundCell.cpp
Cells/BackgroundCell.h
Cells/Cell.cpp
Cells/Cell.h
Cells/Entity.cpp
Cells/Entity.h
Cells/FontHolder.cpp
Cells/FontHolder.h
Cells/Fonts.h
Cells/FoodCell.cpp
Cells/FoodCell.h
Cells/Game.cpp
Cells/Game.h
Cells/GameEndState.cpp
Cells/GameEndState.h
Cells/GameProgress.cpp
Cells/GameProgress.h
Cells/GameSettings.cpp
Cells/GameSettings.h
Cells/GameState.cpp
Cells/GameState.h
Cells/InitState.cpp
Cells/InitState.h
Cells/main.cpp
Cells/MenuState.cpp
Cells/MenuState.h
Cells/NeutralCell.cpp
Cells/NeutralCell.h
Cells/PauseState.cpp
Cells/PauseState.h
Cells/PlayerCell.cpp
Cells/PlayerCell.h
Cells/ResourceHolder.cpp
Cells/ResourceHolder.h
Cells/SceneNode.cpp
Cells/SceneNode.h
Cells/State.cpp
Cells/State.h
Cells/States.h
Cells/StateStack.cpp
Cells/StateStack.h
Cells/Textures.h
Cells/Utility.h
Cells/World.cpp
Cells/World.h)


IF (WIN32)
    # sfml-main needed on Windows for not showing the console
    add_executable(TheHungryCell WIN32 ${SOURCES})
    target_link_libraries(TheHungryCell sfml-graphics sfml-main)
ELSE()
    add_executable(TheHungryCell ${SOURCES})
    target_link_libraries(TheHungryCell sfml-graphics)
ENDIF()

# Add math library explicitly for GCC
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(TheHungryCell  m)
ENDIF()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Fonts/arial.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Fonts)
