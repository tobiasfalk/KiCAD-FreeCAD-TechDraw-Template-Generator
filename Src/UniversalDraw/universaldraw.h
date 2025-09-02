#ifndef UNIVERSALDRAW_H
#define UNIVERSALDRAW_H
#include <memory>

#include <QLine>
#include <QLineF>
#include <QObject>
#include <QPageLayout>
#include <QPainterPath>
#include <QPoint>
#include <QPolygon>
#include <QPolygonF>
#include <QRect>
#include <QRectF>
#include <QSharedData>
#include <QString>

///
/// \brief The TextHeightAnchor enum defines the possible position for text in
/// the height
///
enum class TextHeightAnchor {
    Top,
    Middle,
    Bottom,
};

///
/// \brief The TextWidthAnchor enum defines the possible position for text in
/// the width
///
enum class TextWidthAnchor {
    Left,
    Center,
    Right,
};

///
/// \brief The UniversalDraw class is the base class for a universal drawing
/// system to draw SVG, KiCAD Template, FreeCAD Template, pdf and more in a
/// common interface
///
class UniversalDraw
{
public:
    ///
    /// \brief UniversalDraw is the constructor of the universal drawing base
    /// class
    ///
    explicit UniversalDraw();

    ///
    /// \brief drawLine draws a line between the start point and the end point with
    /// a certain line width
    /// \param start is the start point of the line in mm
    /// \param end is the end point of the line
    /// \param lineWidth is the width of the line in mm
    ///
    virtual void drawLine(const QPointF &start, const QPointF &end, double lineWidth);
    ///
    /// \brief drawLine draws a line between the start point and the end point with
    /// a certain line width
    /// \param line is the line to be drawn
    /// \param lineWidth is the width of the line in mm
    ///
    virtual void drawLine(const QLineF &line, double lineWidth);
    ///
    /// \brief drawRect draws a rectangle between start and end point where the top
    /// line parallel to the upper page edge
    /// \param start is the start point of
    /// the rectangle in mm
    /// \param end is the end point of the rectangle in mm
    /// \param lineWidth is the line width that the rectangle is drawn in mm
    /// \param fill defines if the polygon is filled(true) or not(false)
    ///
    virtual void drawRect(const QPointF &start, const QPointF &end, double lineWidth, bool fill = false);
    ///
    /// \brief drawRect draws a rectangle between start and end point where the top
    /// line parallel to the upper page edge
    /// \param rect is the rectangle to be drawn
    /// \param lineWidth is the line width that the rectangle is drawn in mm
    /// \param fill defines if the polygon is filled(true) or not(false)
    ///
    virtual void drawRect(const QRectF &rect, double lineWidth, bool fill = false);
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
    virtual void drawPoly(const QPointF &position, const QList<QPointF> &points, double lineWidth,
                          bool fill = false);
    ///
    /// \brief drawPoly draws a polygon
    /// \param poly is the polygon to be drawn
    /// \param lineWidth is the width of line that the polygon
    /// is drawn width in mm
    /// \param fill defines if the polygon is filled(true) or not(false)
    ///
    virtual void drawPoly(const QPolygonF &poly, double lineWidth, bool fill = false);
    ///
    /// \brief drawCircle draws a circle
    /// \param center is the position of the Center point in mm
    /// \param radius is the radius of of the circle in mm
    /// \param lineWidth is the width of the line that the circle drawn with in mm
    /// \param fill defines if the polygon is filled(true) or not(false)
    ///
    virtual void drawCircle(const QPointF &center, double radius, double lineWidth, bool fill = false);
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
    /// \param name is the name that the text field is given, often
    /// used for variable/editable text
    ///
    virtual void drawText(const QPointF &position, const QString &text, double textSize,
                          TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor,
                          double lineWidth, const QString &font = QString::fromLatin1("osifont"),
                          const QString &name = QString::fromLatin1(""), bool isEditable = false);
    ///
    /// \brief drawText draws multiple lines of text on the given position
    /// \param position is the Position of the Text(Text Anchor) in mm
    /// \param text is the list of text lines that needs to be drawn
    /// \param textSize is the height/size of the text in mm
    /// \param textHeightAnchor is the position of the text anchor in the height
    /// \param textWidthAnchor is the position of the text anchor in the width
    /// \param lineWidth is the width of the text line in mm
    /// \param font is the name of the font
    /// \param isEditable defines if the text field is editable(true) or not(false)
    /// \param name is the name that the text field is given, often used for variable/editable text
    ///
    void drawText(const QPointF &position, const QStringList &text, double textSize,
                  TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor,
                  double lineWidth, const QString &font = QString::fromLatin1("osifont"),
                  const QString &name = QString::fromLatin1(""), bool isEditable = false);
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
    virtual void drawPicture(const QString &picturePath, const QPointF &position, double width, double height,
                             int dpiVector = 33020);

    ///
    /// \brief fileName returns the name of the file to draw in to
    /// \return
    ///
    const QString &fileName() const;
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
    /// \brief setHeight sets the height of the page/template
    /// \param newHeight
    ///
    void setHeight(qreal newHeight);

    ///
    /// \brief width is the width of the page/template
    /// \return
    ///
    qreal width() const;
    ///
    /// \brief setWidth sets the width of the page/template
    /// \param newWidth
    ///
    void setWidth(qreal newWidth);

    ///
    /// \brief start initialises the file and make everything ready
    /// to be drawn in to
    /// \return true if successful
    ///
    virtual bool start();

    ///
    /// \brief end finishes and closes the file
    /// \return true if successful
    ///
    virtual bool end();

    ///
    /// \brief printTest is a test function to test the universal draw classes
    /// \param drawer is the drawer clast that is to be tested
    ///
    /// This function draws a A4 Picture that has one .5mm line from the top left
    /// corner to the bottom right, one 3mm line from the top right to the bottom
    /// left,
    ///
    /// one circle with the Center at the middle of the page(where the two lines
    /// cross) with a 1mm line width a 50mm radius and no fill,
    ///
    /// a rectangle with start(20,20) end(30,30) a .3mm line width and no fill,
    ///
    /// a polygon with position(40,40)
    /// points[(0,0),(0,10),(10,10),(10,5),(5,5),(5,0)] a .8 line width and no
    /// fill,
    ///
    /// one circle with the Center at (100,20) with a 1mm line width a 5mm radius
    /// and fill,
    ///
    /// a rectangle with start(120,20) end(130,30) a .3mm line width and fill,
    ///
    /// a polygon with position(140,40)
    /// points[(0,0),(0,10),(10,10),(10,5),(5,5),(5,0)] a .8 line width and fill,
    ///
    /// a text "TextABCabc" at (60,10) size 3mm TextHeightAnchor Bottom
    /// TextWidthAnchor Left lineWidth .3 editable
    ///
    /// a text "TextABCabc" at (60,20) size 5mm TextHeightAnchor Middle
    /// TextWidthAnchor Center lineWidth .5 not editable
    ///
    /// a text "TextABCabc" at (60,30) size 1mm TextHeightAnchor Right
    /// TextWidthAnchor Top lineWidth .1 not editable
    ///
    /// \image html Test/test.SVG
    ///
    ///
    static void printTest(const std::shared_ptr<UniversalDraw> &drawer);
    ///
    /// \brief printTest makes the same as printTest but scales everything to the given page layout
    /// \param drawer
    /// \param layout
    ///
    static void printTest(const std::shared_ptr<UniversalDraw> &drawer, const QPageLayout &layout);

    ///
    /// \brief showEditable returns true if editable fields/texts should be rendered
    /// \return
    ///
    bool showEditable() const;
    ///
    /// \brief setShowEditable sets whether editable fields/texts should be rendered
    /// \param newShowEditable
    ///
    void setShowEditable(bool newShowEditable);

signals:

protected:
private:
    ///
    /// \brief m_fileName is the name and path of the file that is written to
    ///
    QString m_fileName;
    ///
    /// \brief m_height is the height of the sheet/page
    ///
    qreal m_height;
    ///
    /// \brief m_width is the width of the sheet/page
    ///
    qreal m_width;
    ///
    /// \brief m_showEditable if set to true, editable text is shown; backends may skip editable
    /// text when false to produce "empty" templates
    ///
    bool m_showEditable = false;
};

///
/// \brief operator << is used to print the state of the class to a debugging
/// console, with qDebug()
/// \param debug
/// \param universalDraw
/// \return
///
auto operator<<(QDebug debug, const UniversalDraw &universalDraw) -> QDebug;

#endif // UNIVERSALDRAW_H
