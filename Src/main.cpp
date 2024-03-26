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
#include "PreView/preview.h"

///
/// \brief myMessageOutput is the handelar for all the Qt debuging messages and formats it
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
/// \brief main is the entrypoint for this programm and starts the actuall main window
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

    //style.draw(draw);

    MainWindow window;
    window.show();
    return QApplication::exec();
}
