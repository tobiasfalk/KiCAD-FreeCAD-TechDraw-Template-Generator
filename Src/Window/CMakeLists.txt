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
    UniversalDraw
    PageLayout
    PageFrame
    TitleBlock
    FoldingLines
    PreView
    Threads

    KiCAD_Symbol_scaler
)

# target_include_directories(Window PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

get_target_property(LIB_INCLUDES PreView INCLUDE_DIRECTORIES)

message(${LIB_INCLUDES})

