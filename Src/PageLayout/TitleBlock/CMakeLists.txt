set(TitleBlock_SOURCES
     titleblock.h
     titleblock.cpp
)

add_library(TitleBlock STATIC
    ${TitleBlock_SOURCES}
)

target_link_libraries(TitleBlock PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
    UniversalDraw
    PageLayout
)

target_include_directories(TitleBlock PUBLIC BEFORE ${CMAKE_CURRENT_SOURCE_DIR})
# set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

