#ifndef KICAD8_H
#define KICAD8_H

#include "UniversalDraw/universaldraw.h"

#include <QFile>
#include <QDebug>

class KiCAD8 : public UniversalDraw
{
public:
    KiCAD8();

    ///
    /// \brief drawLine draws a line between the start point and the end point with
    /// a certain line width
    /// \param start is the start point of the line in mm
    /// \param end is the end point of the line
    /// \param lineWidth is the width of the line in mm
    ///
    virtual void drawLine(QPointF start, QPointF end, double lineWidth) override;
    ///
    /// \brief drawLine draws a line between the start point and the end point with
    /// a certain line width
    /// \param line is the line to be drawn
    /// \param lineWidth is the width of the line in mm
    ///
    virtual void drawLine(QLineF line, double lineWidth) override;
    ///
    /// \brief drawRect draws a rectangle between start and end point where the top
    /// line parallel to the upper page edge
    /// \param start is the start point of
    /// the rectangle in mm
    /// \param end is the end point of the rectangle in mm
    /// \param lineWidth is the line width that the rectangle is drawn in mm
    /// \param fill defines if the polygon is filled(true) or not(false)
    ///
    virtual void drawRect(QPointF start, QPointF end, double lineWidth, bool fill = false) override;
    ///
    /// \brief drawRect draws a rectangle between start and end point where the top
    /// line parallel to the upper page edge
    /// \param rect is the rectangle to be drawn
    /// \param lineWidth is the line width that the rectangle is drawn in mm
    /// \param fill defines if the polygon is filled(true) or not(false)
    ///
    virtual void drawRect(QRectF rect, double lineWidth, bool fill = false) override;
    ///
    /// \brief drawPoly draws a polygon
    /// \param position is the position of the first point in mm
    /// \param points is a list of points that define the polygon, all points are
    /// moved by position and there for position is always the (0,0) for this list
    /// of points in mm
    /// \param lineWidth is the width of line that the polygon is
    /// drawn width in mm
    /// \param fill defines if the polygon is filled(true) or
    /// not(false)
    ///
    virtual void drawPoly(QPointF position, QList<QPointF> points, double lineWidth,
                          bool fill = false) override;
    ///
    /// \brief drawPoly draws a polygon
    /// \param poly is the polygon to be drawn
    /// \param lineWidth is the width of line that the polygon
    /// is drawn width in mm
    /// \param fill defines if the polygon is filled(true) or not(false)
    ///
    virtual void drawPoly(QPolygonF poly, double lineWidth, bool fill = false) override;
    ///
    /// \brief drawCircle draws a circle
    /// \param center is the position of the center point in mm
    /// \param radius is the radius of of the circle in mm
    /// \param lineWidth is the width of the line that the circle drawn with in mm
    /// \param fill defines if the polygon is filled(true) or not(false)
    ///
    virtual void drawCircle(QPointF center, double radius, double lineWidth,
                            bool fill = false) override;
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
    virtual void drawText(QPointF position, QString text, double textSize,
                          TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor,
                          double lineWidth, QString font = QString::fromLatin1("osifont"),
                          QString name = QString::fromLatin1(""), bool isEditable = false) override;
    ///
    /// \brief drawPicture draws a Picture on the given position, the anchor is on
    /// the Top Left
    /// \param picturePath is the file path to the picture
    /// \param position is the position of the anchor in mm, witch is on the bottom right
    /// \param width is the the width of the picture in mm
    /// \param height is the the height of the picture in mm
    /// \param dpiVector is the resolution a vector graphic like SVG should be
    /// renders, this may needs to be lowered if the picture should be big, it may
    /// not be used in every output format
    ///
    virtual void drawPicture(QString picturePath, QPointF position, double width, double height,
                             int dpiVector = 33020) override;

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

protected:
    ///
    /// \brief m_file is the file to write to
    ///
    std::shared_ptr<QFile> m_file;

    ///
    /// \brief m_circleArc in degree(°) and it needs to be a fraction of 360, 5° is not noticeable
    ///
    double m_circleArc = 5;
};

#endif // KICAD8_H
