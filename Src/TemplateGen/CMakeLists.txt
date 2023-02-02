set(TemplateGen_SOURCES
    templategen.cpp
    templategen.h
    templategenkicad_5.cpp
    templategenkicad_5.h
    templategenkicad_6.cpp
    templategenkicad_6.h
    templategenkicad_7.cpp
    templategenkicad_7.h
    templategenfreecad.cpp
    templategenfreecad.h
    templategenpdf.cpp
    templategenpdf.h
    templategeneagle.cpp
    templategeneagle.h
)

add_library(TemplateGen STATIC
   ${TemplateGen_SOURCES}
)

target_link_libraries(TemplateGen PRIVATE
   Qt${QT_VERSION_MAJOR}::Widgets
   Qt${QT_VERSION_MAJOR}::Xml
   Qt${QT_VERSION_MAJOR}::Svg
   Qt${QT_VERSION_MAJOR}::SvgWidgets
   Templateoptions
   Window
)

target_include_directories(TemplateGen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
