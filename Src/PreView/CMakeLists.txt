set(PreView_SOURCES
    preview.cpp
)

add_library(PreView STATIC ${PreView_SOURCES})

target_sources(PreView PRIVATE ${PreView_SOURCES})
target_include_directories(PreView PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(PreView PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
    UniversalDraw
    PageLayout
    PageFrame
    ProjectIncludes
)

