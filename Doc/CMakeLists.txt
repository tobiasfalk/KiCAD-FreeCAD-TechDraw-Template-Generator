# Documentation
option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen)
if(NOT DOXYGEN_FOUND)
    message(WARNING "Doxygen not found, unable to generate documentation")
else()
    set(DOC_DEST_DIR ${CMAKE_BINARY_DIR} CACHE PATH "Path to the doxygen output")                      ## used in the doxyfile.in
    set(DOC_INPUT_ROOT_DIRS ${CMAKE_HOME_DIRECTORY} CACHE PATH "Path from where to start to parse")    ## used in the doxyfile.in
    set(DOC_EXCLUDE_PATTERNS_DIRS ${CMAKE_BINARY_DIR} CACHE STRING "Regex patterns exclusion")          ## used in the doxyfile.in
    set(DOC_COMMON_IMG_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Path from which doxygen will be able to found referenced images")## used in the doxyfile.in
    configure_file(Doxyfile.in ${CMAKE_BINARY_DIR}/doxyfile @ONLY)
    add_custom_target(Build_Doc COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/doxyfile"
        WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}
        COMMENT "Building user's documentation into doxyDoc build dir..."

        SOURCES
            Doxyfile.in
            ../README.md
    )
endif()

