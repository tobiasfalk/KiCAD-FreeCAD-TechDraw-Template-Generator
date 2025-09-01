# Provide project-wide includes via a target to avoid global include_directories
add_library(ProjectIncludes INTERFACE)
target_include_directories(ProjectIncludes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
# Subdirs
add_subdirectory(UniversalDraw/)
add_subdirectory(PageLayout/)
add_subdirectory(Threads/)
add_subdirectory(PreView/)
add_subdirectory(Window/)
add_subdirectory(Utils/)

add_subdirectory(KiCAD_Symbol_Scaler/)
add_subdirectory(Icon/)

# Executable
set(PROJECT_SOURCES
    main.cpp
)

set(APP_TARGET KiCAD-FreeCAD-TechDraw-Template-Generator)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${APP_TARGET}
        MANUAL_FINALIZATION
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
        add_executable(${APP_TARGET})
    endif()
endif()

target_sources(${APP_TARGET} PRIVATE ${PROJECT_SOURCES})
target_link_libraries(${APP_TARGET} PRIVATE ProjectIncludes)

target_link_libraries(${APP_TARGET} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
    Qt${QT_VERSION_MAJOR}::SvgWidgets
    KiCAD_Symbol_scaler
    Window
    UniversalDraw
    PageLayout
    PageFrame
    Threads
    Utils
)

set_target_properties(${APP_TARGET} PROPERTIES
    #MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${APP_TARGET})
endif()

if(TARGET Qt6::windeployqt)
    # execute windeployqt in a tmp directory after build
    add_custom_command(TARGET ${APP_TARGET}
        POST_BUILD
        #COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_BINARY_DIR}/windeployqt"
        COMMAND set PATH=%PATH%$<SEMICOLON>${qt6_install_prefix}/bin
        COMMAND Qt6::windeployqt --dir "$<TARGET_FILE_DIR:${APP_TARGET}>" "$<TARGET_FILE_DIR:${APP_TARGET}>/$<TARGET_FILE_NAME:${APP_TARGET}>"
    )

    # copy deployment directory during installation
#    install(
#        DIRECTORY
#        "${CMAKE_CURRENT_BINARY_DIR}/windeployqt/"
#        DESTINATION ${FOO_INSTALL_RUNTIME_DESTINATION}
#    )
endif()

# Copy Test Folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Test/
    DESTINATION ${CMAKE_BINARY_DIR}/bin/Test/)

