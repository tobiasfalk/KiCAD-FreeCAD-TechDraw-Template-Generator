set(Window_SOURCES
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

add_library(Window STATIC
    ${Window_SOURCES}
)

target_link_libraries(Window PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
    TemplateGen
    Templateoptions
    KiCAD_Symbol_scaler
)

target_include_directories(Window PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

