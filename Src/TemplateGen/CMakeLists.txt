set(TemplateGen_SOURCES
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
