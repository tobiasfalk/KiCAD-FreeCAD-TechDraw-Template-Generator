cmake_minimum_required(VERSION 3.5)

project(KiCAD-FreeCAD-TechDraw-Template-Generator VERSION 1.2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
if(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    message(STATUS ">>> Linux RELEASE: -O3")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
    message(STATUS ">>> MSVC RELEASE: /O2")
endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools Xml Svg REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools Xml Svg REQUIRED)

add_subdirectory(Src/)
add_subdirectory(Doc/)
