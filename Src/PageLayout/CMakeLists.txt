add_subdirectory(Frame)
add_subdirectory(TitleBlock)
add_subdirectory(FoldingLines)

set(PageLayout_SOURCES
    pagestyle.cpp
)

add_library(PageLayout STATIC ${PageLayout_SOURCES})
target_sources(PageLayout PRIVATE ${PageLayout_SOURCES})
target_include_directories(PageLayout PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(PageLayout PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
    TitleBlock
    PageFrame
    UniversalDraw
    ProjectIncludes
)

