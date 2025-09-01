set(TitleBlock_SOURCES
     titleblock.cpp
)

set(PlainTitleBlock_SOURCES
    Plain/plaintitleblock.cpp
    Plain/plaintitleblockdialog.cpp
    Plain/plaintitleblockdialog.ui
)

set(ISO7200ATitleBlock_SOURCES
    ISO7200A/iso7200a.cpp
    ISO7200A/iso7200adialog.cpp
    ISO7200A/iso7200adialog.ui
)

set(ISO7200BTitleBlock_SOURCES
    ISO7200B/iso7200b.cpp
    ISO7200B/iso7200bdialog.cpp
    ISO7200B/iso7200bdialog.ui
)

set(FreeCADATitleBlock_SOURCES
    FreeCADA/freecada.cpp
)

add_library(TitleBlock STATIC
    ${TitleBlock_SOURCES}
    ${PlainTitleBlock_SOURCES}
    ${ISO7200ATitleBlock_SOURCES}
    ${ISO7200BTitleBlock_SOURCES}
    ${FreeCADATitleBlock_SOURCES}

)

target_sources(TitleBlock PRIVATE ${TitleBlock_SOURCES} ${PlainTitleBlock_SOURCES} ${ISO7200ATitleBlock_SOURCES} ${ISO7200BTitleBlock_SOURCES} ${FreeCADATitleBlock_SOURCES})
target_include_directories(TitleBlock PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TitleBlock PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
    UniversalDraw
    PageLayout
    ProjectIncludes
)

