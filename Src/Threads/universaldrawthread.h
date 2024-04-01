#ifndef UNIVERSALDRAWTHREAD_H
#define UNIVERSALDRAWTHREAD_H

#include <QObject>
#include <QThread>

#include "pagestyle.h"

///
/// \brief The DrawingFormate enum defines in what formate the output should have
///
enum class DrawingFormate {
    /// saves the output as SVG hat is compatible with FreeCAD,
    /// it ends with <b>".freecad.svg"</b> and uses the FreeCADSvg class
    FreeCADSvg,
    /// saves the output as a KiCAD Worksheet Template,
    /// it ends with <b>".ki8.kicad_wks"</b> and uses the KiCAD8 class
    KiCAD8,
    /// saves the output as a PDF with all the editable fields empty,
    /// it ends with <b>".qt.pdf"</b> and uses the PdfQtPaint class
    PdfQtPaint,
    /// saves the output as a SVG with all the editable fields empty,
    /// it ends with <b>".svg"</b> and uses the SvgDraw class
    Svg,
    /// saves the output as a SVG with all the editable fields empty,
    /// it ends with <b>".qt.svg"</b> and uses the SvgQtPaint class
    SvgQtPaint,
};

///
/// \brief The UniversalDrawThread class prepares a UniversalDraw Class and starts it in a QThread
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
    /// \param drawingFormate
    ///
    UniversalDrawThread(QString fileName, PageStyle pageStyle, DrawingFormate drawingFormate);

    ///
    /// \brief run starts the thread
    ///
    void run() override;

    ///
    /// \brief fileName is the name of the file the Thread should write in to(without a file ending)
    /// \return
    ///
    QString fileName() const;
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
    PageStyle pageStyle() const;
    ///
    /// \brief setPageStyle sets the page style
    /// \param newPageStyle
    ///
    void setPageStyle(const PageStyle &newPageStyle);

    DrawingFormate drawingFormate() const;
    void setDrawingFormate(DrawingFormate newDrawingFormate);

signals:
    ///
    /// \brief resultReady is emitted when the Thread is finished
    ///
    void resultReady(UniversalDrawThread *thread);

private:
    ///
    /// \brief m_fileName is the name and path of the file that is written to
    ///
    QString m_fileName;

    ///
    /// \brief pageStyle is the page style to be drawn
    ///
    PageStyle m_pageStyle;

    ///
    /// \brief m_drawingFormate is the style/file formate of the output;
    ///
    DrawingFormate m_drawingFormate;

    ///
    /// \brief runFreeCADSvg creates a FreeCADSVG file
    ///
    void runFreeCADSvg();
};

#endif // UNIVERSALDRAWTHREAD_H
