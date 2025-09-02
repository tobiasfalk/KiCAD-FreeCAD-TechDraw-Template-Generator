cmake_minimum_required(VERSION 3.18)
message("CMake: "${CMAKE_VERSION})

project(KiCAD-FreeCAD-TechDraw-Template-Generator VERSION 2.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    message(STATUS ">>> Linux DEBUG: -Wall -Wextra -g")
    message(STATUS ">>> Linux RELEASE: -Wall -Wextra -O3")
elseif(MSVC)
    #set(CMAKE_CXX_FLAGS_RELEASE "/O2")
    #message(STATUS ">>> MSVC RELEASE: /O2")
endif()

find_package(QT NAMES Qt6 COMPONENTS Core Widgets LinguistTools Xml Svg SvgWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets LinguistTools Xml Svg SvgWidgets REQUIRED)

message("Qt: "${QT_VERSION_MAJOR})

if(Qt6_FOUND AND WIN32 AND TARGET Qt6::qmake AND NOT TARGET Qt6::windeployqt)
    get_target_property(_qt6_qmake_location Qt6::qmake IMPORTED_LOCATION)

    execute_process(
        COMMAND "${_qt6_qmake_location}" -query QT_INSTALL_PREFIX
        RESULT_VARIABLE return_code
        OUTPUT_VARIABLE qt6_install_prefix
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    set(imported_location "${qt6_install_prefix}/bin/windeployqt.exe")
 
    if(EXISTS ${imported_location})
        add_executable(Qt6::windeployqt IMPORTED)

        set_target_properties(Qt6::windeployqt PROPERTIES
            IMPORTED_LOCATION ${imported_location}
        )
    endif()
endif()

add_subdirectory(Src/)
add_subdirectory(Doc/)

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
