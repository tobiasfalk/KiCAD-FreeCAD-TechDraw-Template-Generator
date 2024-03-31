#ifndef QTPAINTERDRAWER_H
#define QTPAINTERDRAWER_H
#include <memory>

#include <QFrame>
#include <QPainter>
#include <QSvgRenderer>

#include "universaldraw.h"

///
/// \brief The QtPainterDrawer class draws on to a provided QPainter
///
class QtPainterDrawer : public UniversalDraw
{
public:
    ///
    /// \brief QtPainterDrawer is the basic constuctor with an initilasytion of
    /// the painter
    /// \param painter is the painter to use
    ///
    QtPainterDrawer(std::shared_ptr<QPainter> painter);
    ///
    /// \brief QtPainterDrawer is the basic constructor
    ///
    QtPainterDrawer();
    ~QtPainterDrawer();

    ///
    /// \brief drawLine draws a line betwen the start point and the end point with
    /// a certin line width
    /// \param start is the start point of the line in mm
    /// \param end is the end point of the line
    /// \param lineWidth is the width of the line in mm
    ///
    virtual void drawLine(QPointF start, QPointF end, double lineWidth) override;
    ///
    /// \brief drawLine draws a line betwen the start point and the end point with
    /// a certin line width
    /// \param line is the line to be drawn
    /// \param lineWidth
    /// is the width of the line in mm
    ///
    virtual void drawLine(QLineF line, double lineWidth) override;
    ///
    /// \brief drawRect draws a rectangel betwen start and end point where the top
    /// line parralel to the upper page edge
    /// \param start is the start point of the rectagle in mm
    /// \param end is the end point of the rectagle in mm
    /// \param lineWidth is the line width that the rectagen is drawn in mm
    /// \param fill defines if the polygone is filled(true) or not(false)
    ///
    virtual void drawRect(QPointF start, QPointF end, double lineWidth, bool fill = false) override;
    ///
    /// \brief drawRect draws a rectangel betwen start and end point where the top
    /// line parralel to the upper page edge
    /// \param rect is the rectanlge to be drawn
    /// \param lineWidth is the line width that the rectagen is drawn in mm
    /// \param fill defines if the polygone is filled(true) or not(false)
    ///
    virtual void drawRect(QRectF rect, double lineWidth, bool fill = false) override;
    ///
    /// \brief drawPoly draws a polygon
    /// \param position is the position of the first point in mm
    /// \param points is a list of points that define the polygon, all points are
    /// moved py position and therfore position is alwys the (0,0) for this list
    /// of points in mm
    /// \param lineWidth is the width of line that the polygone
    /// is drawn width in mm
    /// \param fill defines if the polygone is filled(true) or not(false)
    ///
    virtual void drawPoly(QPointF position, QList<QPointF> points, double lineWidth,
                          bool fill = false) override;
    ///
    /// \brief drawPoly draws a polygon
    /// \param poly is the polygone to be drawn
    /// \param lineWidth is the width of line that the polygone is drawn width in
    /// mm
    /// \param fill defines if the polygone is filled(true) or not(false)
    ///
    virtual void drawPoly(QPolygonF poly, double lineWidth, bool fill = false) override;
    ///
    /// \brief drawCircle draws a circle
    /// \param center is the position of the cener point in mm
    /// \param radius is the radius of of the circle in mm
    /// \param lineWidth is the width of the line that the cirleis drwn with in mm
    /// \param fill defines if the polygone is filled(true) or not(false)
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
    /// \param name is the name that the text field is given, ofthen
    /// used for variable/editable text
    ///
    virtual void drawText(QPointF position, QString text, double textSize,
                          TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor,
                          double lineWidth, QString font = QString::fromLatin1("osifont"),
                          QString name = QString::fromLatin1(""), bool isEditable = false) override;
    ///
    /// \brief drawPicture draws a Picture on the given position, the anchor is on
    /// the bottom right
    /// \param picturePath is the file path to the picture
    /// \param position is the position of the anchor in mm, witch is on the top
    /// left
    /// \param width is the the width of the picture in mm, it is also the primary
    /// size. the height is adjustet to keep the aspect ratio
    /// \param height is the
    /// the height of the picture in mm, it is the secondary size, if the
    /// calculated(with the width) picture heigth is higher than this than it
    /// reducec the with to fit
    /// \param dpiVector is the resolution per inch that a
    /// Vector graphics should be drawen with, this may needlowering if a picture
    /// is big
    ///
    virtual void drawPicture(QString picturePath, QPointF position, double width, double height,
                             int dpiVector = 33020) override;

    ///
    /// \brief painter returns the painter that is painted on
    /// \return
    ///
    std::shared_ptr<QPainter> painter() const;
    ///
    /// \brief setPainter sets the painter that is painted on
    /// \param newPainter
    ///
    void setPainter(const std::shared_ptr<QPainter> &newPainter);

private:
    ///
    /// \brief m_painter is the painter that is painted on
    ///
    std::shared_ptr<QPainter> m_painter;
};

///
/// \brief operator << is to print out the status of the QtPainterDrawer class
/// to the Debuging interface
/// \param debug
/// \param qtpainterdrawer
/// \return
///
auto operator<<(QDebug debug, const QtPainterDrawer &qtpainterdrawer) -> QDebug;

#endif // QTPAINTERDRAWER_H
