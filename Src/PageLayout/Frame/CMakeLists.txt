set(PageFrame_SOURCES
     pageframe.cpp
)

set(PlainFrame_SOURCES
    Plain/plainframe.cpp
    Plain/plainframedialog.cpp
    Plain/plainframedialog.ui
)

set(ISO5457_SOURCES
    ISO5457/iso5457frame.cpp
    ISO5457/iso5457framedialog.cpp
    ISO5457/iso5457framedialog.ui
)

qt_add_library(PageFrame STATIC
    ${PageFrame_SOURCES}
    ${PlainFrame_SOURCES}
    ${ISO5457_SOURCES}
)

target_sources(PageFrame PRIVATE ${PageFrame_SOURCES} ${PlainFrame_SOURCES} ${ISO5457_SOURCES})
target_include_directories(PageFrame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(PageFrame PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
    UniversalDraw
    PageLayout
    ProjectIncludes
)

target_include_directories(PageFrame PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
