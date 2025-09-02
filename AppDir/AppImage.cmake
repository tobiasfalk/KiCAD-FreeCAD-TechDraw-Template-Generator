# AppImage-Tool installieren:
# Stelle sicher, dass das AppImage-Tool (appimagetool) auf deinem System verfügbar ist. Du kannst es von appimage.org herunterladen.

# CMakeLists.txt anpassen:
# Füge ein neues Custom Target in deiner Haupt-CMakeLists.txt hinzu, das nach dem Build die AppImage-Erstellung übernimmt. Typischerweise wird dafür ein Skript oder ein Kommando ausgeführt, das die nötigen Dateien in ein AppDir kopiert und dann appimagetool aufruft.

# AppDir-Struktur bereitstellen:
# Erstelle ein Verzeichnis (z.B. AppDir), das die Struktur und alle nötigen Dateien für die AppImage enthält (z.B. die gebaute Binary, Desktop-Datei, Icon, ggf. Abhängigkeiten).

# Desktop-Datei und Icon bereitstellen:
# Lege eine .desktop-Datei und ein Icon im AppDir ab. Die Desktop-Datei beschreibt die Anwendung für Linux-Desktops.

# cmake --build . --target appimage

# CMake Custom Target Beispiel:
# Hier ein Beispiel, wie du ein Target appimage in deiner CMakeLists.txt definierst:

# AppImage Target für KiCAD-FreeCAD-TechDraw-Template-Generator
if(UNIX AND NOT APPLE)
    find_program(APPIMAGETOOL appimagetool)
    if(NOT APPIMAGETOOL)
        message(FATAL_ERROR "appimagetool nicht gefunden. Bitte installiere appimagetool und stelle sicher, dass es im PATH ist.")
    endif()

    add_custom_target(appimage
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/AppDir/usr/bin
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${APP_TARGET}> ${CMAKE_BINARY_DIR}/AppDir/usr/bin/
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/AppDir/KiCAD-FreeCAD-TechDraw-Template-Generator.desktop ${CMAKE_BINARY_DIR}/AppDir/
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/AppDir/icon.png ${CMAKE_BINARY_DIR}/AppDir/
        COMMAND ${APPIMAGETOOL} ${CMAKE_BINARY_DIR}/AppDir ${CMAKE_BINARY_DIR}/KiCAD-FreeCAD-TechDraw-Template-Generator.AppImage
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS ${APP_TARGET}
    )
endif()
