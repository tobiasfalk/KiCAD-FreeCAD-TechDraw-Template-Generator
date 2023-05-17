 set(Templateoptions_SOURCES
     templateoptions.cpp
     templateoptions.h
     iso7200options.cpp
     iso7200options.h
)

add_library(Templateoptions STATIC
    ${Templateoptions_SOURCES}
)

target_link_libraries(Templateoptions PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
)

target_include_directories(Templateoptions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
