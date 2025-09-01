#include "Window/mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <iostream>

#include <cstdio>
#include <cstdlib>

#include "PageLayout/pagestyle.h"

#include "PageLayout/Frame/pageframe.h"

#include "UniversalDraw/universaldraw.h"
// #include "PreView/preview.h"

#include "UniversalDraw/PdfQtPaint/pdfqtpaint.h"
#include "UniversalDraw/SvgQtPaint/svgqtpaint.h"
#include "UniversalDraw/Svg/svgdraw.h"
#include "UniversalDraw/FreeCADSvg/freecadsvg.h"
#include "UniversalDraw/KiCAD8/kicad8.h"
#include "Threads/universaldrawthread.h"

// #include "preview.h"

///
/// \brief myMessageOutput is the handler for all the Qt debugging messages and formats it
/// \param type
/// \param context
/// \param msg
///
// logging moved to Src/Utils
#include "Utils/logging.h"

///
/// \brief main is the entry point for this program and starts the actual main window
/// \param argc
/// \param argv
/// \return
///
auto main(int argc, char *argv[]) -> int
{
    installQtLoggingHandler();
    QApplication application(argc, argv);

    UTGMainWindow window;
    window.show();
    return QApplication::exec();
}
