add_library(Utils
    logging.cpp
)

target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(Utils PRIVATE logging.cpp)

target_link_libraries(Utils PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
)
target_link_libraries(Utils PUBLIC ProjectIncludes)
