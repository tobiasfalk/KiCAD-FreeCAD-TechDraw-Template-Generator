#ifndef UNIVERSALDRAW_H
#define UNIVERSALDRAW_H
#include <memory>


#include <QObject>
#include <QPageLayout>
#include <QPoint>
#include <QSharedData>
#include <QString>
#include <QLine>
#include <QLineF>
#include <QRect>
#include <QRectF>
#include <QPolygon>
#include <QPolygonF>
#include <QPainterPath>

///
/// \brief The TextHeightAnchor enum defines the posible positenings for text in the height
///
enum class TextHeightAnchor {
    Top,
    Middle,
    Bottom,
};

///
/// \brief The TextWidthAnchor enum defines the posible positenings for text in the width
///
enum class TextWidthAnchor {
    Left,
    Center,
    Right,
};

///
/// \brief The UniversalDraw class is the base class for a universal drawing system
/// to draw svg, KiCAD Template, FreeCAD Template, pdf and more in a common interface
///
class UniversalDraw
{
public:
    ///
    /// \brief UniversalDraw is the constructor of the universal drawing base class
    ///
    explicit UniversalDraw();

    ///
    /// \brief drawLine draws a line betwen the start point and the end point with a
    /// certin line width
    /// \param start is the start point of the line in mm
    /// \param end is the end point of the line
    /// \param lineWidth is the width of the line in mm
    ///
    virtual void drawLine(QPointF start, QPointF end, double lineWidth);
    ///
    /// \brief drawLine draws a line betwen the start point and the end point with a
    /// certin line width
    /// \param line is the line to be drawn
    /// \param lineWidth is the width of the line in mm
    ///
    virtual void drawLine(QLineF line, double lineWidth);
    ///
    /// \brief drawRect draws a rectangel betwen start and end point where the top line parralel
    /// to the upper page edge
    /// \param start is the start point of the rectagle in mm
    /// \param end is the end point of the rectagle in mm
    /// \param lineWidth is the line width that the rectagen is drawn in mm
    /// \param fill defines if the polygone is filled(true) or not(false)
    ///
    virtual void drawRect(QPointF start, QPointF end, double lineWidth, bool fill = false);
    ///
    /// \brief drawRect draws a rectangel betwen start and end point where the top line parralel
    /// to the upper page edge
    /// \param rect is the rectanlge to be drawn
    /// \param lineWidth is the line width that the rectagen is drawn in mm
    /// \param fill defines if the polygone is filled(true) or not(false)
    ///
    virtual void drawRect(QRectF rect, double lineWidth, bool fill = false);
    ///
    /// \brief drawPoly draws a polygon
    /// \param position is the position of the first point in mm
    /// \param points is a list of points that define the polygon, all points are moved py position
    /// and therfore position is alwys the (0,0) for this list of points in mm
    /// \param lineWidth is the width of line that the polygone is drawn width in mm
    /// \param fill defines if the polygone is filled(true) or not(false)
    ///
    virtual void drawPoly(QPointF position, QList<QPointF> points, double lineWidth,
                          bool fill = false);
    ///
    /// \brief drawPoly draws a polygon
    /// \param poly is the polygone to be drawn
    /// \param lineWidth is the width of line that the polygone is drawn width in mm
    /// \param fill defines if the polygone is filled(true) or not(false)
    ///
    virtual void drawPoly(QPolygonF poly, double lineWidth, bool fill = false);
    ///
    /// \brief drawCircle draws a circle
    /// \param center is the position of the cener point in mm
    /// \param radius is the radius of of the circle in mm
    /// \param lineWidth is the width of the line that the cirleis drwn with in mm
    /// \param fill defines if the polygone is filled(true) or not(false)
    ///
    virtual void drawCircle(QPointF center, double radius, double lineWidth, bool fill = false);
    ///
    /// \brief drawText draws Text on the given position
    /// \param position is the Position of the Text(Text Anchor) in mm
    /// \param text is the text that needs to be drawn
    /// \param textSize is the height/size of the text in mm
    /// \param textHeightAnchor is the position of the text anchor in the height
    /// \param textWidthAnchor is the position of the text anchor in the width
    /// \param lineWidth is the width of the text line in mm
    /// \param font is the name of the font
    /// \param isEditable defines if the text field is editable(true) or not(false)
    /// \param name is the name that the text field is given, ofthen used for
    /// variable/editable text
    ///
    virtual void drawText(QPointF position, QString text, double textSize,
                          TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor,
                          double lineWidth, QString font = QString::fromLatin1("osifont"),
                          bool isEditable = false, QString name = QString::fromLatin1(""));
    ///
    /// \brief drawPicture draws a Picture on the given position, the anchor is on the bottom right
    /// \param picturePath is the file path to the picture
    /// \param position is the position of the anchor in mm, witch is on the bottom right
    /// \param width is the the width of the picture in mm
    /// \param height is the the height of the picture in mm
    /// \param dpiVector is the resolution a Vectorgrapic like SVG should be renderd, this may needs to be loward if the picture should be big
    ///
    virtual void drawPicture(QString picturePath, QPointF position, double width, double height, int dpiVector = 33020);

    ///
    /// \brief fileName returns the name of the file to draw in to
    /// \return
    ///
    QString fileName() const;
    ///
    /// \brief setFileName sets the name of the file to draw in to
    /// \param newFileName
    ///
    void setFileName(const QString &newFileName);

    ///
    /// \brief height is the height of the page/template
    /// \return
    ///
    qreal height() const;
    ///
    /// \brief setHight sets the height of the page/template
    /// \param newHight
    ///
    void setHight(qreal newHight);

    ///
    /// \brief width ist the width of the page/template
    /// \return
    ///
    qreal width() const;
    ///
    /// \brief setWidth sets the width of the page/template
    /// \param newWidth
    ///
    void setWidth(qreal newWidth);

signals:

protected:
private:
    QString m_fileName;
    qreal m_height;
    qreal m_width;
};

///
/// \brief operator << is used to print the state of the class to a debuging consol, with qDebug()
/// \param debug
/// \param universalDraw
/// \return
///
auto operator<<(QDebug debug, const UniversalDraw &universalDraw) -> QDebug;

namespace test {

///
/// \brief printTest is a test function to test the universal draw classes
/// \param drawer is the drawer clast that is to be tested
///
/// This function draws a A4 Picture that has one .5mm line from the top left corner to the bottem
/// right, one 3mm line from the top right to the bottom left,
///
/// one circle with the center at the middle of the page(where the two lines cross) with a 1mm
/// linewidth a 50mm radius and no fill,
///
/// a rectangle with start(20,20) end(30,30) a .3mm line width and no fill,
///
/// a polygone with position(40,40) points[(0,0),(0,10),(10,10),(10,5),(5,5),(5,0)] a .8 linewidth
/// and no fill,
///
/// one circle with the center at (100,20) with a 1mm linewidth a 5mm radius and fill,
///
/// a rectangle with start(120,20) end(130,30) a .3mm line width and fill,
///
/// a polygone with position(140,40) points[(0,0),(0,10),(10,10),(10,5),(5,5),(5,0)] a .8 linewidth
/// and fill,
///
/// a text "TextABCabc" at (60,10) size 3mm TextHeightAnchor Bottom TextWidthAnchor Left
/// lineWidth .3 editable
///
/// a text "TextABCabc" at (60,20) size 5mm TextHeightAnchor Middle TextWidthAnchor Center
/// lineWidth .5 not editable
///
/// a text "TextABCabc" at (60,30) size 1mm TextHeightAnchor Right TextWidthAnchor Top
/// lineWidth .1 not editable
///
/// \dot
/// digraph G {
///   node [fontname = "Handlee"];
///   edge [fontname = "Handlee"];
///
///   draw [
///     label = "Draw a picture";
///     shape = rect;
///   ];
///   win [
///     label = "You win!";
///     shape = oval;
///   ];
///   guess [
///     label = "Did they\nguess it?";
///     shape = diamond;
///   ];
///   point [
///     label = "Point repeatedly\nto the same picture.";
///     shape = rect;
///   ];
///
///   draw -> guess;
///   win -> guess [ label = "Yes"; dir=back ];
///   point -> guess;
///   guess -> point [ label = "No" ];
///   {
///     rank=same;
///     guess; point; win;
///   }
/// }
/// \enddot
///
void printTest(std::shared_ptr<UniversalDraw> drawer);

}

#endif // UNIVERSALDRAW_H
