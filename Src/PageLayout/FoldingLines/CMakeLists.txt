set(FoldingLines_SOURCES
    foldinglines.cpp
)

add_library(FoldingLines STATIC
    ${FoldingLines_SOURCES}
    DIN824ALike/din824alike.cpp
    DIN824CLike/din824clike.cpp
)

target_sources(FoldingLines PRIVATE ${FoldingLines_SOURCES} DIN824ALike/din824alike.cpp DIN824CLike/din824clike.cpp)
target_include_directories(FoldingLines PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(FoldingLines PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
    UniversalDraw
    PageLayout
    ProjectIncludes
)
