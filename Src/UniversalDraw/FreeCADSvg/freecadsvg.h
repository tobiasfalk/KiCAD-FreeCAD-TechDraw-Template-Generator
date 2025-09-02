#ifndef FREECADSVG_H
#define FREECADSVG_H

#include "UniversalDraw/Svg/svgdraw.h"

///
/// \brief The FreeCADSvg class is used to draw a FreeCAD Compatible SVG
///
class FreeCADSvg : public SvgDraw
{
public:
    ///
    /// \brief FreeCADSvg the base constructor
    ///
    FreeCADSvg();
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
    /// not(false), this does nothing with base SVG
    /// \param name is the name that the text field is given, often
    /// used for variable/editable text
    ///
    virtual void drawText(const QPointF &position, const QString &text, double textSize,
                          TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor,
                          double lineWidth, const QString &font = QString::fromLatin1("osifont"),
                          const QString &name = QString::fromLatin1(""), bool isEditable = false) override;
};

#endif // FREECADSVG_H
