set(Window_SOURCES
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    changetitelblockfield.cpp
    changetitelblockfield.h
    changetitelblockfield.ui
    iso7200dialog.h
    iso7200dialog.cpp
    iso7200dialog.ui
    asme_y14_35_width180dialog.cpp
    asme_y14_35_width180dialog.h
    asme_y14_35_width180dialog.ui
    fullsheetspartlistoptions.cpp
    fullsheetspartlistoptions.h
    fullsheetspartlistoptions.ui
    smallpartslistoptions.cpp
    smallpartslistoptions.h
    smallpartslistoptions.ui
    loadesavesettings.cpp
    loadesavesettings.h
    preview.h
    preview.cpp
    iso5457dialog.h
    iso5457dialog.cpp
    iso5457dialog.ui
)

add_library(Window STATIC
    ${Window_SOURCES}
)

target_link_libraries(Window PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
    TemplateGen
    Templateoptions
    KiCAD_Symbol_scaler
)

target_include_directories(Window PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

