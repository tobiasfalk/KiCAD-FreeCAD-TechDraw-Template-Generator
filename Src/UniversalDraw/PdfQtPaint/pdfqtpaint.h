#ifndef PDFQTPAINT_H
#define PDFQTPAINT_H

#include <QPainter>
#include <QSvgRenderer>
#include <QPdfWriter>

#include "UniversalDraw/universaldraw.h"
#include "UniversalDraw/QtPaint/qtpainterdrawer.h"

///
/// \brief The PdfQtPaint class is used to draw a PDF with the Qt Painter
///
class PdfQtPaint : public QtPainterDrawer
{
public:
    ///
    /// \brief PdfQtPaint is a class that uses the QPainter class to draw
    ///
    explicit PdfQtPaint();

    ///
    /// \brief drawText draws Text on the given position
    /// \param position is the Position of the Text(Text Anchor) in mm
    /// \param text is the text that needs to be drawn
    /// \param textSize is the height/size of the text in mm
    /// \param textHeightAnchor is the position of the text anchor in the height
    /// \param textWidthAnchor is the position of the text anchor in the width
    /// \param lineWidth is the width of the text line in mm
    /// \param font is the name of the font
    /// \param isEditable defines if the text field is editable(true) or not(false), this does
    /// nothing with base
    /// \param name is the name that the text field is given, often used for
    /// variable/editable text
    ///
    virtual void drawText(QPointF position, QString text, double textSize,
                          TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor,
                          double lineWidth, QString font = QString::fromLatin1("osifont"),
                          QString name = QString::fromLatin1(""), bool isEditable = false) override;

    ///
    /// \brief start initialises the file and make everything ready to be drawn in to
    /// \return true if successful
    ///
    virtual bool start() override;

    ///
    /// \brief end finishes and closes the file
    /// \return true if successful
    ///
    virtual bool end() override;

    ///
    /// \brief resolutionDPI is the general resolution the PDF is generated with in DPI
    /// \return
    ///
    int resolutionDPI() const;
    ///
    /// \brief setResolutionDPI sets the general resolution the PDF is generated with in DPI
    /// \param newResolutionDPI
    ///
    void setResolutionDPI(int newResolutionDPI);

    ///
    /// \brief resolutionPMM is the general resolution the PDF is generated with in Px Per mm
    /// \return
    ///
    double resolutionPMM() const;
    ///
    /// \brief setResolutionPMM sets the general resolution the PDF is generated with in Px Per mm
    /// \param newResolutionPMM
    ///
    void setResolutionPMM(double newResolutionPMM);

private:
    ///
    /// \brief m_pdfWriter the Qt PDF writer that is used to crearte the PDF
    ///
    std::shared_ptr<QPdfWriter> m_pdfWriter;

    ///
    /// \brief m_resolutionDPI the used resolution of the drawing coordinates
    ///
    int m_resolutionDPI = 33020;
    ///
    /// \brief m_resolutionPMM the used resolution of the drawing coordinates in Px per mm
    ///
    double m_resolutionPMM = m_resolutionDPI * (1 / 25.4);
};

#endif // PDFQTPAINT_H
