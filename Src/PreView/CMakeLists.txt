set(PreView_SOURCES
)

add_library(PreView STATIC
    # ${PreView_SOURCES}
    preview.cpp
    preview.h
)

target_link_libraries(PreView PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
    UniversalDraw
    PageLayout
    PageFrame
)

message(STATUS "Conft PreView")

# target_include_directories(PreView PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# get_target_property(LIB_INCLUDES PreView INCLUDE_DIRECTORIES)

# message(${LIB_INCLUDES})
