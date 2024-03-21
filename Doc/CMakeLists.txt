# Documentation
#option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen REQUIRED dot
    OPTIONAL_COMPONENTS mscgen dia)
string(TIMESTAMP timestamp "%Y-%m-%d %H:%M:%S")
message(STATUS "local time: ${timestamp}")
find_program (qhelpgen NAMES qhelpgenerator)
message(STATUS "qhelpgen: ${qhelpgen}")
if(NOT DOXYGEN_FOUND)
    message(WARNING "Doxygen not found, unable to generate documentation")
else()
    set(DOC_DEST_DIR ${CMAKE_BINARY_DIR} CACHE PATH "Path to the doxygen output")                      ## used in the doxyfile.in
    set(DOC_INPUT_ROOT_DIRS ${CMAKE_HOME_DIRECTORY} CACHE PATH "Path from where to start to parse")    ## used in the doxyfile.in
    set(DOC_EXCLUDE_PATTERNS_DIRS ${CMAKE_BINARY_DIR} CACHE STRING "Regex patterns exclusion")          ## used in the doxyfile.in
    set(DOC_COMMON_IMG_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Path from which doxygen will be able to found referenced images")## used in the doxyfile.in

    # Include Qt doc tagfiles, if provided.(https://forum.qt.io/topic/143679/list-of-tags-files-for-doxygen-for-qt5-and-qt6/7)
    if (QT6_INSTALL_DOCS)
      set(QT_DOCS_BASEURL "https://doc.qt.io/qt-${QT_VERSION_MAJOR}/")
      message(STATUS "Using Qt doc tagfiles ${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS} (${QT_DOCS_BASEURL})")
      set(DOX_TAGFILES "\\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qdoc/qdoc.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qmake/qmake.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qt3d/qt3d.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtbluetooth/qtbluetooth.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtconcurrent/qtconcurrent.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtcore/qtcore.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtdbus/qtdbus.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtgrpc/qtgrpc.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtgui/qtgui.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtlabsplatform/qtlabsplatform.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtlocation/qtlocation.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtlottieanimation/qtlottieanimation.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtnetwork/qtnetwork.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtnetworkauth/qtnetworkauth.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtnfc/qtnfc.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtopcua/qtopcua.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtopengl/qtopengl.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtpositioning/qtpositioning.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtprintsupport/qtprintsupport.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtprotobuf/qtprotobuf.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtqml/qtqml.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtqmlcore/qtqmlcore.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtqmlmodels/qtqmlmodels.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtqmltest/qtqmltest.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtqmlworkerscript/qtqmlworkerscript.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtqmlxmllistmodel/qtqmlxmllistmodel.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtquick/qtquick.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtquick3d/qtquick3d.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtquick3dphysics/qtquick3dphysics.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtquickcontrols/qtquickcontrols.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtquickdialogs/qtquickdialogs.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtquickeffectmaker/qtquickeffectmaker.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtquicktimeline/qtquicktimeline.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtremoteobjects/qtremoteobjects.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtscxml/qtscxml.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtsensors/qtsensors.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtserialbus/qtserialbus.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtshadertools/qtshadertools.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtsql/qtsql.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtstatemachine/qtstatemachine.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtsvg/qtsvg.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qttestlib/qttestlib.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtwebchannel/qtwebchannel.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtwebengine/qtwebengine.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtwebsockets/qtwebsockets.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtwidgets/qtwidgets.tags=${QT_DOCS_BASEURL}\" \\
          \"${CMAKE_PREFIX_PATH}/${QT6_INSTALL_DOCS}/qtxml/qtxml.tags=${QT_DOCS_BASEURL}\" \\")
      # Add more Qt modules here, if relevant.
    endif()

    configure_file(Doxyfile.in ${CMAKE_BINARY_DIR}/doxyfile @ONLY)
    add_custom_target(Build_Doc COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/doxyfile"
        WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}
        COMMENT "Building user's documentation into doxyDoc build dir..."

        SOURCES
            Doxyfile.in
            ../README.md
    )
#    set_target_properties(Build_Doc PROPERTIES ADDITIONAL_CLEAN_FILES
#            "${CMAKE_BINARY_DIR}/doxyfile")
endif()

