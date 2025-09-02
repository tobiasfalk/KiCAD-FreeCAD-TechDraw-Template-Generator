#ifndef UNIVERSALDRAWTHREAD_H
#define UNIVERSALDRAWTHREAD_H

#include <QObject>
#include <QThread>

#include "PageLayout/pagestyle.h"

///
/// \brief The DrawingFormate enum defines in what formate the output should have
///
enum class DrawingFormate {
    /// saves the output as SVG hat is compatible with FreeCAD,
    /// it ends with <b>".freecad.svg"</b> and uses the FreeCADSvg class
    /// (adds freecad:editable/autofill attributes for TechDraw)
    FreeCADSvg,
    /// saves the output as a KiCAD Worksheet Template,
    /// it ends with <b>".ki8.kicad_wks"</b> and uses the KiCAD8 class
    /// (uses KiCAD v8 worksheet S-expression format; text maps to ${...})
    KiCAD8,
    /// saves the output as a PDF with all the editable fields empty,
    /// it ends with <b>".qt.pdf"</b> and uses the PdfQtPaint class
    /// (Qt painter backend)
    PdfQtPaint,
    /// saves the output as a SVG with all the editable fields empty,
    /// it ends with <b>".svg"</b> and uses the SvgDraw class
    /// (plain SVG without FreeCAD-specific attributes)
    Svg,
    /// saves the output as a SVG with all the editable fields empty,
    /// it ends with <b>".qt.svg"</b> and uses the SvgQtPaint class
    /// (SVG generated via Qt painter)
    SvgQtPaint,
    /// writes an HTML page that embeds the SVG output
    Html,
    /// writes a PNG image using a Qt painter backend
    PngQtPaint,
};

///
/// \brief The UniversalDrawThread class prepares UniversalDraw backends and renders in a QThread
///
class UniversalDrawThread : public QThread
{
    Q_OBJECT

public:
    ///
    /// \brief UniversalDrawThread is the basic constructor
    ///
    UniversalDrawThread();
    ///
    /// \brief UniversalDrawThread is a constructor that sets the name and the page style
    /// \param fileName
    /// \param pageStyle
    /// \param drawingFormates
    ///
    UniversalDrawThread(const QString &fileName, const PageStyle &pageStyle,
                        const QList<DrawingFormate> &drawingFormates);

    ///
    /// \brief run starts the thread
    ///
    /// Iterates all selected formats, instantiates the matching backend, appends
    /// the proper file extension to m_fileName, and calls PageStyle::draw().
    /// Emits resultReady(this) when finished.
    ///
    void run() override;

    ///
    /// \brief fileName is the name of the file the Thread should write in to(without a file ending)
    /// \return
    ///
    const QString &fileName() const;
    ///
    /// \brief setFileName sets the name of the file the Thread should write in to(without a file
    /// ending)
    /// \param newFileName
    ///
    void setFileName(const QString &newFileName);

    ///
    /// \brief pageStyle is the page style
    /// \return
    ///
    const PageStyle &pageStyle() const;
    ///
    /// \brief setPageStyle sets the page style
    /// \param newPageStyle
    ///
    void setPageStyle(const PageStyle &newPageStyle);

    ///
    /// \brief drawingFormates returns the selected output formats
    /// \return list of formats
    ///
    const QList<DrawingFormate> &drawingFormates() const;
    ///
    /// \brief setDrawingFormate sets the selected output formats
    /// \param newDrawingFormates list of formats
    ///
    void setDrawingFormate(const QList<DrawingFormate> &newDrawingFormates);

signals:
    ///
    /// \brief resultReady is emitted when the Thread is finished
    ///
    void resultReady(UniversalDrawThread *thread);

private:
    ///
    /// \brief m_fileName is the base name/path without extension; each backend appends its own extension
    ///
    QString m_fileName;

    ///
    /// \brief pageStyle is the page style to be drawn
    ///
    PageStyle m_pageStyle;

    ///
    /// \brief m_drawingFormates is the list of file formats to generate
    ///
    QList<DrawingFormate> m_drawingFormates;

    ///
    /// \brief runFreeCADSvg creates a FreeCADSVG file and is triggered by
    /// DrawingFormate::FreeCADSvg
    ///
    void runFreeCADSvg();
    ///
    /// \brief runKiCAD8 creates a KiCAD WKS file and is triggered by
    /// DrawingFormate::KiCAD8
    ///
    void runKiCAD8();
    ///
    /// \brief runPdfQtPaint creates a PDF file and is triggered by
    /// DrawingFormate::PdfQtPaint
    ///
    void runPdfQtPaint();
    ///
    /// \brief runSvg creates a SVG file and is triggered by
    /// DrawingFormate::SVG
    ///
    void runSvg();
    ///
    /// \brief runSvgQtPaint creates a SVG file and is triggered by
    /// DrawingFormate::SvgQtPaint
    ///
    void runSvgQtPaint();

    ///
    /// \brief runHtml creates a HTML file and is triggered by DrawingFormate::Html
    ///
    void runHtml();

    ///
    /// \brief runPng creates a PNG file and is triggered by DrawingFormate::PngQtPaint
    ///
    void runPng();
};

#endif // UNIVERSALDRAWTHREAD_H
