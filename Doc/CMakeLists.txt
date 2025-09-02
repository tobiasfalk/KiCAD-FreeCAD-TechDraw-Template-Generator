# cmake --build build --target Build_Doc

# Documentation
# option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen #REQUIRED
    OPTIONAL_COMPONENTS mscgen dia dot)
string(TIMESTAMP timestamp "%Y-%m-%d %H:%M:%S")
message(STATUS "local time: ${timestamp}")
find_program (qhelpgen NAMES qhelpgenerator)
message(STATUS "qhelpgen: ${qhelpgen}")
if(NOT DOXYGEN_FOUND)
    message(WARNING "Doxygen not found, unable to generate documentation")
else()
    message(STATUS "Doxygen found: ${DOXYGEN_EXECUTABLE} (version ${DOXYGEN_VERSION})")

    set(DOC_DEST_DIR ${CMAKE_BINARY_DIR} CACHE PATH "Path to the doxygen output")                      ## used in the doxyfile.in
    set(DOC_INPUT_ROOT_DIRS ${CMAKE_HOME_DIRECTORY} CACHE PATH "Path from where to start to parse")    ## used in the doxyfile.in
    set(DOC_EXCLUDE_PATTERNS_DIRS ${CMAKE_BINARY_DIR} CACHE STRING "Regex patterns exclusion")          ## used in the doxyfile.in
    set(DOC_COMMON_IMG_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Path from which doxygen will be able to found referenced images")## used in the doxyfile.in

    # Include Qt doc tagfiles, if provided.(https://forum.qt.io/topic/143679/list-of-tags-files-for-doxygen-for-qt5-and-qt6/7)

    if(EXISTS "${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qdoc")
        set(QT_DOC_PATH "${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}")
    elseif(EXISTS "C:/Qt/Docs/Qt-${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}/qdoc")
        set(QT_DOC_PATH "C:/Qt/Docs/Qt-${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")
    endif()

    if (QT_DOC_PATH)
      set(QT_DOCS_BASEURL "https://doc.qt.io/qt-${QT_VERSION_MAJOR}/")
      message(STATUS "Using Qt doc tagfiles ${QT_DOC_PATH} (${QT_DOCS_BASEURL})")
      set(DOX_TAGFILES "\\
          \"${QT_DOC_PATH}/qdoc/qdoc.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qmake/qmake.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qt3d/qt3d.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtbluetooth/qtbluetooth.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtconcurrent/qtconcurrent.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtcore/qtcore.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtdbus/qtdbus.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtgrpc/qtgrpc.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtgui/qtgui.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtlabsplatform/qtlabsplatform.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtlocation/qtlocation.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtlottieanimation/qtlottieanimation.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtnetwork/qtnetwork.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtnetworkauth/qtnetworkauth.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtnfc/qtnfc.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtopcua/qtopcua.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtopengl/qtopengl.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtpositioning/qtpositioning.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtprintsupport/qtprintsupport.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtprotobuf/qtprotobuf.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtqml/qtqml.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtqmlcore/qtqmlcore.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtqmlmodels/qtqmlmodels.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtqmltest/qtqmltest.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtqmlworkerscript/qtqmlworkerscript.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtqmlxmllistmodel/qtqmlxmllistmodel.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtquick/qtquick.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtquick3d/qtquick3d.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtquick3dphysics/qtquick3dphysics.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtquickcontrols/qtquickcontrols.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtquickdialogs/qtquickdialogs.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtquickeffectmaker/qtquickeffectmaker.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtquicktimeline/qtquicktimeline.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtremoteobjects/qtremoteobjects.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtscxml/qtscxml.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtsensors/qtsensors.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtserialbus/qtserialbus.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtshadertools/qtshadertools.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtsql/qtsql.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtstatemachine/qtstatemachine.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtsvg/qtsvg.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qttestlib/qttestlib.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtwebchannel/qtwebchannel.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtwebengine/qtwebengine.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtwebsockets/qtwebsockets.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtwidgets/qtwidgets.tags=${QT_DOCS_BASEURL}\" \\
          \"${QT_DOC_PATH}/qtxml/qtxml.tags=${QT_DOCS_BASEURL}\" \\")
      # Add more Qt modules here, if relevant.
    endif()

    # if the Variable is set add Cpp Red tag files
    if(CPPREF_TAG_FILE)
        set(DOX_TAGFILES "${DOX_TAGFILES}
          \"${CPPREF_TAG_FILE}\"\\")
    endif()

    configure_file(Doxyfile.in ${CMAKE_BINARY_DIR}/doxyfile @ONLY)
    add_custom_target(Build_Doc COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/doxyfile"
        WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}
        COMMENT "Building user's documentation into doxyDoc build dir..."

        SOURCES
            Doxyfile.in
            ../README.md
            Test/test.svg
    )
    add_dependencies(KiCAD-FreeCAD-TechDraw-Template-Generator Build_Doc)
#    set_target_properties(Build_Doc PROPERTIES ADDITIONAL_CLEAN_FILES
#            "${CMAKE_BINARY_DIR}/doxyfile")
endif()

