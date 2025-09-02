#pragma once

#include <QtGlobal>

///
/// \brief installQtLoggingHandler installs the Qt message handler used across the application
///
/// This sets a global Qt message handler (qInstallMessageHandler) so that qDebug, qWarning,
/// qCritical, and qFatal messages are routed consistently (e.g. to console or log files).
/// Call this once during application startup.
///
void installQtLoggingHandler();
