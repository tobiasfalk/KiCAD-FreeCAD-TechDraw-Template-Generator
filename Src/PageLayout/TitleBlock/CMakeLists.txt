set(TitleBlock_SOURCES
     titleblock.h
     titleblock.cpp
)

set(PlainTitleBlock_SOURCES
    Plain/plaintitleblock.h
    Plain/plaintitleblock.cpp
    Plain/plaintitleblockdialog.h
    Plain/plaintitleblockdialog.cpp
    Plain/plaintitleblockdialog.ui
)

set(ISO7200ATitleBlock_SOURCES
    ISO7200A/iso7200a.h
    ISO7200A/iso7200a.cpp
    ISO7200A/iso7200adialog.h
    ISO7200A/iso7200adialog.cpp
    ISO7200A/iso7200adialog.ui
)

set(ISO7200BTitleBlock_SOURCES
    ISO7200B/iso7200b.h
    ISO7200B/iso7200b.cpp
    ISO7200B/iso7200bdialog.h
    ISO7200B/iso7200bdialog.cpp
    ISO7200B/iso7200bdialog.ui
)

set(FreeCADATitleBlock_SOURCES
    FreeCADA/freecada.h
    FreeCADA/freecada.cpp
)

add_library(TitleBlock STATIC
    ${TitleBlock_SOURCES}
    ${PlainTitleBlock_SOURCES}
    ${ISO7200ATitleBlock_SOURCES}
    ${ISO7200BTitleBlock_SOURCES}
    ${FreeCADATitleBlock_SOURCES}

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

