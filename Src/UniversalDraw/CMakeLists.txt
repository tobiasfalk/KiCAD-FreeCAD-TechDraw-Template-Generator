set(UniversalDraw_SOURCES
     universaldraw.cpp
     universaldraw.h
)

add_library(UniversalDraw STATIC
    ${UniversalDraw_SOURCES}
    QtPaint/qtpainterdrawer.h
    QtPaint/qtpainterdrawer.cpp
    PreView/preview.h
    PreView/preview.cpp
    PdfQtPaint/pdfqtpaint.h
    PdfQtPaint/pdfqtpaint.cpp
    SvgQtPaint/svgqtpaint.h
    SvgQtPaint/svgqtpaint.cpp
    Svg/svgdraw.h
    Svg/svgdraw.cpp
    FreeCADSvg/freecadsvg.h
    FreeCADSvg/freecadsvg.cpp
)

target_link_libraries(UniversalDraw PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
)

target_include_directories(UniversalDraw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
