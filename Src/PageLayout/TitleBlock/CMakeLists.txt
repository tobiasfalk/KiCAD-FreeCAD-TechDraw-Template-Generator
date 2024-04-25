set(TitleBlock_SOURCES
     titleblock.h
     titleblock.cpp
)

add_library(TitleBlock STATIC
    ${TitleBlock_SOURCES}
    Plain/plaintitleblock.h
    Plain/plaintitleblock.cpp
    Plain/plaintitleblockdialog.h
    Plain/plaintitleblockdialog.cpp
    Plain/plaintitleblockdialog.ui
    ISO7200A/iso7200a.h ISO7200A/iso7200a.cpp
)

target_link_libraries(TitleBlock PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
    UniversalDraw
    PageLayout
)

# target_include_directories(TitleBlock PUBLIC BEFORE ${CMAKE_CURRENT_SOURCE_DIR})
# set(INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

