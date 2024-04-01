#include "universaldrawthread.h"
#include "qtmetamacros.h"

#include "PdfQtPaint/pdfqtpaint.h"
#include "SvgQtPaint/svgqtpaint.h"
#include "Svg/svgdraw.h"
#include "FreeCADSvg/freecadsvg.h"
#include "KiCAD8/kicad8.h"

UniversalDrawThread::UniversalDrawThread() { }

UniversalDrawThread::UniversalDrawThread(QString fileName, PageStyle pageStyle,
                                         DrawingFormate drawingFormate)
    : m_pageStyle(pageStyle), m_fileName(fileName), m_drawingFormate(drawingFormate)
{
}

void UniversalDrawThread::run()
{
    qDebug() << "Test";

    if (m_drawingFormate == DrawingFormate::FreeCADSvg) {
        runFreeCADSvg();
    }

    emit resultReady(this);
}

QString UniversalDrawThread::fileName() const
{
    return m_fileName;
}

void UniversalDrawThread::setFileName(const QString &newFileName)
{
    m_fileName = newFileName;
}

PageStyle UniversalDrawThread::pageStyle() const
{
    return m_pageStyle;
}

void UniversalDrawThread::setPageStyle(const PageStyle &newPageStyle)
{
    m_pageStyle = newPageStyle;
}

DrawingFormate UniversalDrawThread::drawingFormate() const
{
    return m_drawingFormate;
}

void UniversalDrawThread::setDrawingFormate(DrawingFormate newDrawingFormate)
{
    m_drawingFormate = newDrawingFormate;
}

void UniversalDrawThread::runFreeCADSvg()
{
    std::shared_ptr<FreeCADSvg> draw = std::make_shared<FreeCADSvg>();

    draw->setFileName(m_fileName + ".freecad.svg");

    m_pageStyle.draw(draw);
}
