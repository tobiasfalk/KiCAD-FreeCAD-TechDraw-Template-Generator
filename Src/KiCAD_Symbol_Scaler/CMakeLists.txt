set(KiCAD_Symbol_scaler_SOURCES
)

add_library(KiCAD_Symbol_scaler STATIC ${KiCAD_Symbol_scaler_SOURCES})

target_sources(KiCAD_Symbol_scaler PRIVATE ${KiCAD_Symbol_scaler_SOURCES})
target_include_directories(KiCAD_Symbol_scaler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(KiCAD_Symbol_scaler PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Svg
    ProjectIncludes
)

