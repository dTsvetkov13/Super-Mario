cmake_minimum_required(VERSION 3.12)

project(SuperMario)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/") 

set(SOURCES
	src/Game.cpp
	src/main.cpp
	src/Component.cpp
	src/DrawingComponent.cpp
	src/GameObject.cpp
	headers/Game.h
	headers/Component.h
	headers/DrawingComponent.h	
	headers/GameObject.h
	src/Enums.h
	headers/Player.h
	src/Player.cpp
	src/Map.cpp
	headers/Map.h
	src/Enemy.cpp
	headers/Enemy.h
	src/BadTurtle.cpp
	headers/BadTurtle.h
	src/World.cpp
	headers/World.h
	src/Camera.cpp
	headers/Camera.h
	src/SeverusSnape.cpp
	headers/SeverusSnape.h
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2TTF REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2TFF_LIBRARY})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY})

target_include_directories("${PROJECT_NAME}"
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/headers
)