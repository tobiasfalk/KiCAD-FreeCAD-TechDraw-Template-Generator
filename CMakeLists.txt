message("Starting CMake Config")
message("#################################################################################")
message("#   _____                    _       _        ____                              #")
message("#  |_   _|__ _ __ ___  _ __ | | __ _| |_ ___ / ___| ___ _ __                    #")
message("#    | |/ _ \\ '_ ` _ \\| '_ \\| |/ _` | __/ _ \\ |  _ / _ \\ '_ \\                   #")
message("#    | |  __/ | | | | | |_) | | (_| | ||  __/ |_| |  __/ | | |                  #")
message("#    |_|\\___|_| |_| |_| .__/|_|\\__,_|\\__\\___|\\____|\\___|_| |_|                  #")
message("#                     |_|                                                       #")
message("#         KiCAD-FreeCAD-TechDraw-Template-Generator (TempGen)                   #")
message("#################################################################################")
message("")

cmake_minimum_required(VERSION 3.18)
message("CMake: "${CMAKE_VERSION})

project(KiCAD-FreeCAD-TechDraw-Template-Generator VERSION 2.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    message(STATUS ">>> Linux DEBUG: -Wall -Wextra -g")
    message(STATUS ">>> Linux RELEASE: -Wall -Wextra -O3")
elseif(MSVC)
    #set(CMAKE_CXX_FLAGS_RELEASE "/O2")
    #message(STATUS ">>> MSVC RELEASE: /O2")
endif()

find_package(QT NAMES Qt6 COMPONENTS Core Widgets LinguistTools Xml Svg SvgWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets LinguistTools Xml Svg SvgWidgets REQUIRED)

message("Qt: ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")

if(Qt6_FOUND AND WIN32 AND TARGET Qt6::qmake AND NOT TARGET Qt6::windeployqt)
    get_target_property(_qt6_qmake_location Qt6::qmake IMPORTED_LOCATION)

    execute_process(
        COMMAND "${_qt6_qmake_location}" -query QT_INSTALL_PREFIX
        RESULT_VARIABLE return_code
        OUTPUT_VARIABLE qt6_install_prefix
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    set(imported_location "${qt6_install_prefix}/bin/windeployqt.exe")
 
    if(EXISTS ${imported_location})
        add_executable(Qt6::windeployqt IMPORTED)

        set_target_properties(Qt6::windeployqt PROPERTIES
            IMPORTED_LOCATION ${imported_location}
        )
    endif()
endif()

add_subdirectory(Src/)
add_subdirectory(Doc/)

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

# Include AppImage build support
include(AppDir/AppImage.cmake)

# CPack-Konfiguration für RPM
include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR "RPM")
set(CPACK_PACKAGE_NAME "KiCAD-FreeCAD-TechDraw-Template-Generator")
set(CPACK_PACKAGE_VERSION "2.1")
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_CONTACT "Tobias Falk tobiasfalk200242@gmail.com")
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "Productivity/Graphics")
set(CPACK_RPM_PACKAGE_URL "https://github.com/tobiasfalk/KiCAD-FreeCAD-TechDraw-Template-Generator")
set(CPACK_RPM_PACKAGE_DESCRIPTION "Generator für KiCAD/FreeCAD TechDraw-Vorlagen.")

# Install-Regeln (Beispiel, passe ggf. an):
install(DIRECTORY Doc/ DESTINATION share/doc/KiCAD-FreeCAD-TechDraw-Template-Generator)
install(DIRECTORY Examples/ DESTINATION share/KiCAD-FreeCAD-TechDraw-Template-Generator/examples)
install(DIRECTORY TemplateLibrary/ DESTINATION share/KiCAD-FreeCAD-TechDraw-Template-Generator/templates)
install(FILES README.md CODESTYLE.md DESTINATION share/doc/KiCAD-FreeCAD-TechDraw-Template-Generator)

include(CPack)

# Custom Target: Banner beim Build ausgeben
add_custom_target(banner
    COMMAND ${CMAKE_COMMAND} -E echo "  _____                    _       _        ____            "
    COMMAND ${CMAKE_COMMAND} -E echo " |_   _|__ _ __ ___  _ __ | | __ _| |_ ___ / ___| ___ _ __  "
    COMMAND ${CMAKE_COMMAND} -E echo "   | |/ _ \\ '_ ` _ \\| '_ \\| |/ _` | __/ _ \\ |  _ / _ \\ '_ \\ "
    COMMAND ${CMAKE_COMMAND} -E echo "   | |  __/ | | | | | |_) | | (_| | ||  __/ |_| |  __/ | | |"
    COMMAND ${CMAKE_COMMAND} -E echo "   |_|\\___|_| |_| |_| .__/|_|\\__,_|\\__\\___|\\____|\\___|_| |_|"
    COMMAND ${CMAKE_COMMAND} -E echo "                    |_|                                      "
    VERBATIM
)
add_dependencies(KiCAD-FreeCAD-TechDraw-Template-Generator banner)
