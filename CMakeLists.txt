cmake_minimum_required(VERSION 3.5)

project(KiCAD-FreeCAD-TechDraw-Template-Generator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_DOC "Build documentation" ON)
if(BUILD_DOC)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(WARNING "Doxygen not found, unable to generate documentation")
    else()
        set(DOC_DEST_DIR ${CMAKE_BINARY_DIR} CACHE PATH "Path to the doxygen output")                      ## used in the doxyfile.in
        set(DOC_INPUT_ROOT_DIRS ${CMAKE_HOME_DIRECTORY} CACHE PATH "Path from where to start to parse")    ## used in the doxyfile.in
        set(DOC_EXCLUDE_PATTERNS_DIRS ${CMAKE_BINARY_DIR} CACHE STRING "Regex patterns exclusion")          ## used in the doxyfile.in
        set(DOC_COMMON_IMG_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Path from which doxygen will be able to found referenced images")## used in the doxyfile.in
        configure_file(Doxyfile.in ${CMAKE_BINARY_DIR}/doxyfile @ONLY)
        add_custom_target(Build_Doc COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/doxyfile"
            WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}
            COMMENT "Building user's documentation into doxyDoc build dir..."
        )
    endif()

    add_custom_target(Documentation
        SOURCES
            Doxyfile.in
            README.md
        )

endif()


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools Xml Svg REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools Xml Svg REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        templateoptions.cpp
        templateoptions.h
        changetitelblockfield.cpp
        changetitelblockfield.h
        changetitelblockfield.ui
        iso7200options.cpp
        iso7200options.h
        iso7200options.ui
        asme_y14_35_width180.cpp
        asme_y14_35_width180.h
        asme_y14_35_width180.ui
        fullsheetspartlistoptions.cpp
        fullsheetspartlistoptions.h
        fullsheetspartlistoptions.ui
        smallpartslistoptions.cpp
        smallpartslistoptions.h
        smallpartslistoptions.ui
        templategen.cpp
        templategen.h
        templategenkicad_5.cpp
        templategenkicad_5.h
        templategenkicad_6.cpp
        templategenkicad_6.h
        templategenkicad_7.cpp
        templategenkicad_7.h
        templategenfreecad.cpp
        templategenfreecad.h
        templategenpdf.cpp
        templategenpdf.h
        loadesavesettings.cpp
        loadesavesettings.h
        KiCAD_Symbol_Scaler/kicad_symbol_scaler.cpp
        KiCAD_Symbol_Scaler/kicad_symbol_scaler.h
        KiCAD_Symbol_Scaler/kicad_symbol_scaler_ui.cpp
        KiCAD_Symbol_Scaler/kicad_symbol_scaler_ui.h
        KiCAD_Symbol_Scaler/kicad_symbol_scaler_ui.ui
        )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(KiCAD-FreeCAD-TechDraw-Template-Generator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET KiCAD-FreeCAD-TechDraw-Template-Generator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(KiCAD-FreeCAD-TechDraw-Template-Generator SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(KiCAD-FreeCAD-TechDraw-Template-Generator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(KiCAD-FreeCAD-TechDraw-Template-Generator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Xml  Qt${QT_VERSION_MAJOR}::Svg)

set_target_properties(KiCAD-FreeCAD-TechDraw-Template-Generator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(KiCAD-FreeCAD-TechDraw-Template-Generator)
endif()
