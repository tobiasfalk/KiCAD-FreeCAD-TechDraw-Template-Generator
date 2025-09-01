set(UniversalDraw_SOURCES
    universaldraw.cpp
    QtPaint/qtpainterdrawer.cpp
    PdfQtPaint/pdfqtpaint.cpp
    SvgQtPaint/svgqtpaint.cpp
    Svg/svgdraw.cpp
    FreeCADSvg/freecadsvg.cpp
    KiCAD8/kicad8.cpp
    Html/htmldraw.cpp
    PngQtPaint/pngqtpaint.cpp
)

add_library(UniversalDraw STATIC ${UniversalDraw_SOURCES})

target_sources(UniversalDraw PRIVATE ${UniversalDraw_SOURCES})
target_include_directories(UniversalDraw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(UniversalDraw PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
    ProjectIncludes
)

# target_include_directories(UniversalDraw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
