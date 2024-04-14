#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <iostream>

#include <cstdio>
#include <cstdlib>

#include "pagestyle.h"

#include "pageframe.h"

#include "universaldraw.h"
// #include "PreView/preview.h"

#include "PdfQtPaint/pdfqtpaint.h"
#include "SvgQtPaint/svgqtpaint.h"
#include "Svg/svgdraw.h"
#include "FreeCADSvg/freecadsvg.h"
#include "KiCAD8/kicad8.h"
#include "universaldrawthread.h"

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
        case QtDebugMsg:
            std::cerr << "Debug: " << localMsg.constData() << " (" << file << ":" << context.line
                      << ", " << function << ")" << std::endl;
            break;
        case QtInfoMsg:
            std::cerr << "Info: " << localMsg.constData() << " (" << file << ":" << context.line
                      << ", " << function << ")" << std::endl;
            break;
        case QtWarningMsg:
            std::cerr << "Warning: " << localMsg.constData() << " (" << file << ":" << context.line
                      << ", " << function << ")" << std::endl;
            break;
        case QtCriticalMsg:
            std::cerr << "Critical: " << localMsg.constData() << " (" << file << ":" << context.line
                      << ", " << function << ")" << std::endl;
            break;
        case QtFatalMsg:
            std::cerr << "Fatal: " << localMsg.constData() << " (" << file << ":" << context.line
                      << ", " << function << ")" << std::endl;
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
            std::cerr << "Warning: " << localMsg.constData() << std::endl;
            break;
        case QtCriticalMsg:
            std::cerr << "Critical: " << localMsg.constData() << std::endl;
            break;
        case QtFatalMsg:
            std::cerr << "Fatal: " << localMsg.constData() << std::endl;
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

    // PageStyle style;

    // style.setPageSize(297, 215, QPageLayout::Landscape);
    // qDebug() << style.getPageHight();
    // qDebug() << style.getPageSize();
    // qDebug() << style.getLayout();
    // qDebug() << style << "ABC";

    // std::shared_ptr<UniversalDraw> draw = std::make_shared<UniversalDraw>();

    // // PreView view;

    // // printTest(view);

    // test::printTest(draw);

    // style.draw(draw);

    // std::shared_ptr<SvgQtPaint> draw = std::make_shared<SvgQtPaint>();
    // draw->setFileName("test.svg");

    // std::shared_ptr<SvgDraw> draw = std::make_shared<SvgDraw>();
    // draw->setFileName("test_3.svg");

    // std::shared_ptr<FreeCADSvg> draw = std::make_shared<FreeCADSvg>();
    // draw->setFileName("test_4.svg");

    // std::shared_ptr<KiCAD8> draw = std::make_shared<KiCAD8>();
    // draw->setFileName("test.kicad_wks");

    // std::shared_ptr<PdfQtPaint> draw = std::make_shared<PdfQtPaint>();
    // draw->setFileName("test.pdf");

    // UniversalDraw::printTest(draw);

    MainWindow window;
    window.show();
    return QApplication::exec();
}
