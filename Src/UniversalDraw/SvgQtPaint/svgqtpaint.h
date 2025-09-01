#ifndef SVGQTPAINT_H
#define SVGQTPAINT_H

#include <QPainter>
#include <QSvgGenerator>
#include <QSvgRenderer>

#include "UniversalDraw/QtPaint/qtpainterdrawer.h"
#include "UniversalDraw/universaldraw.h"

///
/// \brief The SvgQtPaint class is used to draw in to SVG using the QT Painter class
///
class SvgQtPaint : public QtPainterDrawer
{
public:
    ///
    /// \brief SvgQtPaint the base constructor
    ///
    SvgQtPaint();

    ///
    /// \brief drawText draws Text on the given position
    /// \param position is the Position of the Text(Text Anchor) in mm
    /// \param text is the text that needs to be drawn
    /// \param textSize is the height/size of the text in mm
    /// \param textHeightAnchor is the position of the text anchor in the height
    /// \param textWidthAnchor is the position of the text anchor in the width
    /// \param lineWidth is the width of the text line in mm
    /// \param font is the name of the font
    /// \param isEditable defines if the text field is editable(true) or
    /// not(false)
    /// \param name is the name that the text field is given, often
    /// used for variable/editable text
    ///
    virtual void drawText(const QPointF &position, const QString &text, double textSize,
                          TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor,
                          double lineWidth, const QString &font = QString::fromLatin1("osifont"),
                          const QString &name = QString::fromLatin1(""), bool isEditable = false) override;

    ///
    /// \brief start initialises the file and make everything ready
    /// to be drawn in to
    /// \return true if successful
    ///
    virtual bool start() override;

    ///
    /// \brief end finishes and closes the file
    /// \return true if successful
    ///
    virtual bool end() override;

private:
    ///
    /// \brief m_svgWriter the Qt SVG generator that is used
    ///
    std::shared_ptr<QSvgGenerator> m_svgWriter;
};

#endif // SVGQTPAINT_H
