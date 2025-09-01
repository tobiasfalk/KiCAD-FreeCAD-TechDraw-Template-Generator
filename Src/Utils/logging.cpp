#include "logging.h"

#include <QMessageLogContext>
#include <QString>

#include <iostream>
#include <cstring>

static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
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

void installQtLoggingHandler()
{
    qInstallMessageHandler(myMessageOutput);
}
