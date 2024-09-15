#include "universaldrawthread.h"
#include "qtmetamacros.h"

#include "UniversalDraw/PdfQtPaint/pdfqtpaint.h"
#include "UniversalDraw/SvgQtPaint/svgqtpaint.h"
#include "UniversalDraw/Svg/svgdraw.h"
#include "UniversalDraw/FreeCADSvg/freecadsvg.h"
#include "UniversalDraw/KiCAD8/kicad8.h"
#include "UniversalDraw/Html/htmldraw.h"
#include "UniversalDraw/PngQtPaint/pngqtpaint.h"

UniversalDrawThread::UniversalDrawThread() { }

UniversalDrawThread::UniversalDrawThread(QString fileName, PageStyle pageStyle,
                                         QList<DrawingFormate> drawingFormates)
    : m_pageStyle(pageStyle), m_fileName(fileName), m_drawingFormates(drawingFormates)
{
}

void UniversalDrawThread::run()
{
    // if (m_drawingFormates == DrawingFormate::FreeCADSvg) {
    //     runFreeCADSvg();
    // }

    foreach (DrawingFormate formate, m_drawingFormates) {
        switch (formate) {
        case DrawingFormate::FreeCADSvg:
            qInfo() << "FreeCAD";
            runFreeCADSvg();
            break;
        case DrawingFormate::KiCAD8:
            qInfo() << "KiCAD8";
            runKiCAD8();
            break;
        case DrawingFormate::PdfQtPaint:
            qInfo() << "PdfQtPaint";
            runPdfQtPaint();
            break;
        case DrawingFormate::Svg:
            qInfo() << "Svg";
            runSvg();
            break;
        case DrawingFormate::SvgQtPaint:
            qInfo() << "SvgQtPaint";
            runSvgQtPaint();
            break;
        case DrawingFormate::Html:
            qInfo() << "Html";
            runHtml();
            break;
        case DrawingFormate::PngQtPaint:
            qInfo() << "Png";
            runPng();
            break;
        default:
            break;
        }
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

QList<DrawingFormate> UniversalDrawThread::drawingFormates() const
{
    return m_drawingFormates;
}

void UniversalDrawThread::setDrawingFormate(QList<DrawingFormate> newDrawingFormates)
{
    m_drawingFormates = newDrawingFormates;
}

void UniversalDrawThread::runFreeCADSvg()
{
    std::shared_ptr<FreeCADSvg> draw = std::make_shared<FreeCADSvg>();

    draw->setFileName(m_fileName + ".freecad.svg");

    m_pageStyle.draw(draw);
}

void UniversalDrawThread::runKiCAD8()
{
    std::shared_ptr<KiCAD8> draw = std::make_shared<KiCAD8>();

    draw->setFileName(m_fileName + ".ki8.kicad_wks");

    m_pageStyle.draw(draw);
}

void UniversalDrawThread::runPdfQtPaint()
{
    std::shared_ptr<PdfQtPaint> draw = std::make_shared<PdfQtPaint>();

    draw->setFileName(m_fileName + ".qt.pdf");

    m_pageStyle.draw(draw);
}

void UniversalDrawThread::runSvg()
{
    std::shared_ptr<SvgDraw> draw = std::make_shared<SvgDraw>();

    draw->setFileName(m_fileName + ".svg");

    m_pageStyle.draw(draw);
}

void UniversalDrawThread::runSvgQtPaint()
{
    std::shared_ptr<SvgQtPaint> draw = std::make_shared<SvgQtPaint>();

    draw->setFileName(m_fileName + ".qt.svg");

    m_pageStyle.draw(draw);
}

void UniversalDrawThread::runHtml()
{
    std::shared_ptr<HtmlDraw> draw = std::make_shared<HtmlDraw>();

    draw->setFileName(m_fileName + ".html");

    m_pageStyle.draw(draw);
}

void UniversalDrawThread::runPng()
{
    std::shared_ptr<PngQtPaint> draw = std::make_shared<PngQtPaint>();

    draw->setFileName(m_fileName + ".qt.png");

    m_pageStyle.draw(draw);
}
