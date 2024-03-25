#ifndef PREVIEW_H
#define PREVIEW_H
#include <memory>

#include <QFrame>
#include <QPainter>
#include <QSvgRenderer>

#include "universaldraw.h"


class PreView_Painter : public UniversalDraw
{
public:
    PreView_Painter(std::shared_ptr<QPainter> painter);
    ~PreView_Painter();

private:
    std::shared_ptr<QPainter> m_painter;

    ///
    /// \brief drawLine draws a line betwen the start point and the end point with a
    /// certin line width
    /// \param start is the start point of the line in mm
    /// \param end is the end point of the line
    /// \param lineWidth is the width of the line in mm
    ///
    virtual void drawLine(QPointF start, QPointF end, double lineWidth) override;
    ///
    /// \brief drawLine draws a line betwen the start point and the end point with a
    /// certin line width
    /// \param line is the line to be drawn
    /// \param lineWidth is the width of the line in mm
    ///
    virtual void drawLine(QLineF line, double lineWidth) override;
    ///
    /// \brief drawRect draws a rectangel betwen start and end point where the top line parralel
    /// to the upper page edge
    /// \param start is the start point of the rectagle in mm
    /// \param end is the end point of the rectagle in mm
    /// \param lineWidth is the line width that the rectagen is drawn in mm
    /// \param fill defines if the polygone is filled(true) or not(false)
    ///
    virtual void drawRect(QPointF start, QPointF end, double lineWidth, bool fill = false) override;
    ///
    /// \brief drawRect draws a rectangel betwen start and end point where the top line parralel
    /// to the upper page edge
    /// \param rect is the rectanlge to be drawn
    /// \param lineWidth is the line width that the rectagen is drawn in mm
    /// \param fill defines if the polygone is filled(true) or not(false)
    ///
    virtual void drawRect(QRectF rect, double lineWidth, bool fill = false) override;
    ///
    /// \brief drawPoly draws a polygon
    /// \param position is the position of the first point in mm
    /// \param points is a list of points that define the polygon, all points are moved py position
    /// and therfore position is alwys the (0,0) for this list of points in mm
    /// \param lineWidth is the width of line that the polygone is drawn width in mm
    /// \param fill defines if the polygone is filled(true) or not(false)
    ///
    virtual void drawPoly(QPointF position, QList<QPointF> points, double lineWidth,
                  bool fill = false) override;
    ///
    /// \brief drawPoly draws a polygon
    /// \param poly is the polygone to be drawn
    /// \param lineWidth is the width of line that the polygone is drawn width in mm
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
    virtual void drawCircle(QPointF center, double radius, double lineWidth, bool fill = false) override;
    ///
    /// \brief drawText draws Text on the given position
    /// \param position is the Position of the Text(Text Anchor) in mm
    /// \param text is the text that needs to be drawn
    /// \param textSize is the hight/size of the text in mm
    /// \param textHeightAnchor is the position of the text anchor in the hight
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
                  bool isEditable = false, QString name = QString::fromLatin1("")) override;
    ///
    /// \brief drawPicture draws a Picture on the given position, the anchor is on the bottom right
    /// \param picturePath is the file path to the picture
    /// \param position is the position of the anchor in mm, witch is on the bottom right
    /// \param width is the the width of the picture in mm
    /// \param hight is the the hight of the picture in mm
    ///
    virtual void drawPicture(QString picturePath, QPointF position, double width, double hight);

};


class PreView : public QFrame, public UniversalDraw
{
public:
    PreView();
    ~PreView();

private:

    std::shared_ptr<QPainter> m_painter;

    void paintEvent(QPaintEvent *e) override;
};

#endif // PREVIEW_H
