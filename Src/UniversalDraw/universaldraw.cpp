#include "universaldraw.h"

UniversalDraw::UniversalDraw() { }

QString UniversalDraw::fileName() const
{
    return m_fileName;
}

void UniversalDraw::setFileName(const QString &newFileName)
{
    m_fileName = newFileName;
}

void printTest(QSharedPointer<UniversalDraw> drawer) { }
