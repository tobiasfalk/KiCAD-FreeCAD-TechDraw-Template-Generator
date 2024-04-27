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
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file != nullptr ? context.file : "";
    const char *function = context.function != nullptr ? context.function : "";
    if ((strcmp(file, "") != 0) && (strcmp(function, "") != 0)) {
        switch (type) {
        case QtDebugMsg: // blue
            std::cerr << "\033[0;34mDebug:\033[0m " << localMsg.constData() << " (" << file << ":"
                      << context.line << ", " << function << ")" << std::endl;
            break;
        case QtInfoMsg: // green
            std::cerr << "\033[0;32mInfo:\033[0m " << localMsg.constData() << " (" << file << ":"
                      << context.line << ", " << function << ")" << std::endl;
            break;
        case QtWarningMsg:
            std::cerr << "\033[0;35mWarning:\033[0m " << localMsg.constData() << " (" << file << ":"
                      << context.line << ", " << function << ")" << std::endl;
            break;
        case QtCriticalMsg:
            std::cerr << "\033[0;91mCritical:\033[0m " << localMsg.constData() << " (" << file
                      << ":" << context.line << ", " << function << ")" << std::endl;
            break;
        case QtFatalMsg:
            std::cerr << "\033[0;31mFatal:\033[0m " << localMsg.constData() << " (" << file << ":"
                      << context.line << ", " << function << ")" << std::endl;
            break;
        }
    } else {
        switch (type) {
        case QtDebugMsg:
            break;
        case QtInfoMsg:
            std::cerr << localMsg.constData() << std::endl;
            break;
        case QtWarningMsg:
            std::cerr << "\033[0;35mWarning:\033[0m " << localMsg.constData() << std::endl;
            break;
        case QtCriticalMsg:
            std::cerr << "\033[0;91mCritical:\033[0m " << localMsg.constData() << std::endl;
            break;
        case QtFatalMsg:
            std::cerr << "\033[0;31mFatal:\033[0m " << localMsg.constData() << std::endl;
            break;
        }
    }
}

///
/// \brief main is the entry point for this program and starts the actual main window
/// \param argc
/// \param argv
/// \return
///
auto main(int argc, char *argv[]) -> int
{
    qInstallMessageHandler(myMessageOutput);
    QApplication application(argc, argv);

    UTGMainWindow window;
    window.show();
    return QApplication::exec();
}
