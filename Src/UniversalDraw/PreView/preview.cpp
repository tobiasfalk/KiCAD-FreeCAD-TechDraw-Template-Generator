#include "preview.h"

#include "universaldraw.h"


PreView_Painter::PreView_Painter(std::shared_ptr<QPainter> painter)
{
    m_painter = painter;

}

PreView_Painter::~PreView_Painter()
{
}

void PreView_Painter::drawLine(QPointF start, QPointF end, double lineWidth)
{
    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(lineWidth);
    m_painter->setPen(pen);
    m_painter->setBrush(Qt::NoBrush);

    QLineF line(start, end);
    m_painter->drawLine(line);
}

void PreView_Painter::drawLine(QLineF line, double lineWidth)
{
    drawLine(line.p1(), line.p2(), lineWidth);
}

void PreView_Painter::drawRect(QPointF start, QPointF end, double lineWidth, bool fill)
{
    drawRect(QRectF{start, end}, lineWidth, fill);
}

void PreView_Painter::drawRect(QRectF rect, double lineWidth, bool fill)
{
    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(lineWidth);
    m_painter->setPen(pen);
    m_painter->setBrush(Qt::NoBrush);

    // QRectF rectangle(QPointF(start.X, start.Y), QPointF(end.X, end.Y));
    m_painter->drawRect(rect);

    // Brush
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);

    if(fill)
    {
        // Fill polygon
        QPainterPath path;
        path.addPolygon(rect);
        m_painter->fillPath(path, brush);
    }
}

void PreView_Painter::drawPoly(QPointF position, QList<QPointF> points, double lineWidth, bool fill)
{
    QList<QPointF> qPoints;
    for(int i = 0; i < points.length(); i++)
    {
        qPoints.append(QPointF(points[i].x() + position.x(), points[i].y() + position.y()));
    }
    drawPoly(qPoints, lineWidth, fill);
}

void PreView_Painter::drawPoly(QPolygonF poly, double lineWidth, bool fill)
{
    // Becaus ther is a ofset with the size of the line width
    // if(!fill)
    // {
    //     position.X += lineWidth;
    //     position.Y += lineWidth;
    // }
    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(lineWidth);
    m_painter->setPen(pen);

    m_painter->drawPolygon(poly, Qt::WindingFill);

    // Brush
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);

    if(fill)
    {
        // Fill polygon
        QPainterPath path;
        path.addPolygon(poly);
        m_painter->fillPath(path, brush);
    }
}

void PreView_Painter::drawCircle(QPointF center, double radius, double lineWidth, bool fill)
{

    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(lineWidth);
    m_painter->setPen(pen);
    m_painter->setBrush(Qt::NoBrush);

    QRectF rectangle(center.x() - radius, center.y() - radius, radius * 2, radius * 2);

    m_painter->drawEllipse(rectangle);

    // Brush
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);

    if(fill)
    {
        // Fill polygon
        QPainterPath path;
        path.addEllipse(rectangle);
        m_painter->fillPath(path, brush);
    }
}

void PreView_Painter::drawText(QPointF position, QString text, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, QString font, bool isEditable, QString name)
{

    QFont qFont(font);
    QFont qFontA(font);
    qFont.setPointSizeF(textSize);//18897.6378
    qFontA.setPointSizeF(100);
    double posX = position.x();
    double posY = position.y();
    QFontMetrics fm(qFontA);

    if(textWidthAnchor == TextWidthAnchor::Left)
    {
    }
    else if(textWidthAnchor == TextWidthAnchor::Center)
    {
        posX -= (textSize * (fm.size(Qt::TextDontPrint, text).width()/double(100))) / 2;
    }
    else if(textWidthAnchor == TextWidthAnchor::Right)
    {
        posX -= (textSize * (fm.size(Qt::TextDontPrint, text).width()/double(100)));
    }

    if(textHeightAnchor == TextHeightAnchor::Top)
    {
        posY += textSize;
    }
    else if(textHeightAnchor == TextHeightAnchor::Middle)
    {
        posY += (textSize / 2);
    }
    else if(textHeightAnchor == TextHeightAnchor::Bottom)
    {
    }

    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(lineWidth);
    m_painter->setPen(pen);
    m_painter->setBrush(Qt::NoBrush);

    m_painter->setFont(qFont);
    m_painter->drawText(QPointF(posX, posY), text);
    // qDebug() << "PreView_Painter::drawText";
}

void PreView_Painter::drawPicture(QString picturePath, QPointF position, double width, double hight)
{
    qDebug() << "PreView_Painter::drawPicture";
}

void PreView::paintEvent(QPaintEvent *e)
{

    m_painter = std::shared_ptr<QPainter>(new QPainter(this));

    std::shared_ptr<PreView_Painter> m_pre_painter = std::make_shared<PreView_Painter>(m_painter);


    double scale = this->minimumWidth() / 297;
    if(210 * scale > this->height())
    {
        scale = this->height() / 210;
    }
    m_painter->setTransform(QTransform().scale(scale, scale));// 18,897.6378 p/mm = 480,000 dpi



    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(1);
    m_painter->setPen(pen);
    m_painter->setBrush(Qt::NoBrush);

    QRectF rectangle(QPointF(0, 0), QPointF(297, 210));
    // m_painter->drawRect(rectangle);

    // Brush, sheetBorder
    QBrush brush;
    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    // Fill polygon
    QPainterPath path;
    path.addPolygon(rectangle);
    m_painter->fillPath(path, brush);

    test::printTest(m_pre_painter);

    // if(sheetBorder){
    //     drawRect(Coordinate{0,0}, Coordinate{SHEETSIZE.width, SHEETSIZE.height}, 1);
    // }


    m_painter->end();

    QFrame::paintEvent(e);
}

PreView::PreView() {}

PreView::~PreView() {}
