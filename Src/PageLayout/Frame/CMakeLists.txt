set(PageFrame_SOURCES
     pageframe.h
     pageframe.cpp
)

add_library(PageFrame STATIC
    ${PageFrame_SOURCES}
)

target_link_libraries(PageFrame PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
    UniversalDraw
    PageLayout
)

target_include_directories(PageFrame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
