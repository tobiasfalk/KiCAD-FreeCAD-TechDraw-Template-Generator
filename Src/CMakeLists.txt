# Subdirs
add_subdirectory(KiCAD_Symbol_Scaler/)
add_subdirectory(Templateoptions/)
add_subdirectory(TemplateGen/)
add_subdirectory(Window/)
add_subdirectory(Icon/)

# Executable
set(PROJECT_SOURCES
    main.cpp
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

target_link_libraries(KiCAD-FreeCAD-TechDraw-Template-Generator PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
    TemplateGen
    Templateoptions
    KiCAD_Symbol_scaler
    Window
)

set_target_properties(KiCAD-FreeCAD-TechDraw-Template-Generator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(KiCAD-FreeCAD-TechDraw-Template-Generator)
endif()
