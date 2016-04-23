cmake_minimum_required(VERSION 3.3)
project(UnderKek)

# Set executable name
set(EXECUTABLE_NAME UnderKek)

set(CMAKE_INSTALL_RPATH "$ORIGIN")

#Libraries path
#set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML)

set(CMAKE_INSTALL_RPATH "${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML")
SET(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,$ORIGIN")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#My include dirs
include_directories(BEFORE ${MY_SOURCE_DIR}includes/)

# Include cmake KekEngine
include(${CMAKE_CURRENT_SOURCE_DIR}/../GameEngine/KekEngine.cmake)

# Output directory
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")

link_directories(libs/SFML)

set(SOURCE_FILES src/main.cpp src/underkek.cpp src/init.cpp src/combat.cpp src/combatMenus.cpp)
add_executable(UnderKek ${KEKENGINE_SRC} ${COLLISIONS_SRC} ${ANIMATIONS_SRC}  ${SOURCE_FILES})

# Detect and add SFML
#set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../common/cmake_modules" ${CMAKE_MODULE_PATH})
#find_package(SFML 2 REQUIRED system window graphics network audio)
#target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

# SFML and BOX2D libraries
find_library(SFMLLIBS
        NAMES Box2D sfml-window sfml-network sfml-audio sfml-graphics sfml-system
        PATHS ${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML)
MESSAGE("CACA")
MESSAGE(${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML)
MESSAGE(STATUS ${SFMLLIBS})
MESSAGE("END")
#target_link_libraries(${EXECUTABLE_NAME} ${SFMLLIBS})
target_link_libraries(${EXECUTABLE_NAME} sfml-window)
target_link_libraries(${EXECUTABLE_NAME} sfml-audio)
target_link_libraries(${EXECUTABLE_NAME} sfml-graphics)
target_link_libraries(${EXECUTABLE_NAME} sfml-system)
target_link_libraries(${EXECUTABLE_NAME} sfml-network)
target_link_libraries(${EXECUTABLE_NAME} Box2D)


#BOX2D
#find_library(BOX2DLIB PATHS ${CMAKE_CURRENT_SOURCE_DIR}/libs/BOX2D)
#target_link_libraries(${EXECUTABLE_NAME} ${BOX2DLIB})
#find_package(Box2D)
#target_link_libraries(${EXECUTABLE_NAME} ${BOX2D_LIBRARIES})
#target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/libs/BOX2D/libBox2D.so)
