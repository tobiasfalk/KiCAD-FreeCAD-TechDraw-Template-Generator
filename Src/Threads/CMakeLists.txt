set(Threads_SOURCES
    universaldrawthread.cpp
)

add_library(Threads STATIC ${Threads_SOURCES})

target_sources(Threads PRIVATE ${Threads_SOURCES})
target_include_directories(Threads PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Threads PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
    UniversalDraw
    PageLayout
    PageFrame
    ProjectIncludes
)


