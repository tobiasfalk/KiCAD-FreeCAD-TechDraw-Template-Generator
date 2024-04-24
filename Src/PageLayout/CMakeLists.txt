subdirs(Frame/)
subdirs(TitleBlock/)

add_library(PageLayout STATIC
    pagestyle.h pagestyle.cpp
)

target_link_libraries(PageLayout PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
    TitleBlock
    PageFrame
    UniversalDraw
)

# target_include_directories(PageLayout PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
