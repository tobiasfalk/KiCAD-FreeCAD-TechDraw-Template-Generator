#include "preview.h"
#include <QPainterPath>
#include <math.h>
#include <QSvgRenderer>


Preview::Preview()
{

}

Preview::~Preview()
{
    free(PAINTER);
}

void Preview::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);

    PAINTER = &paint;
    draw();

    paint.end();
    QFrame::paintEvent(e);
}

QString Preview::getFILEENDING()
{
    return "";
}

bool Preview::writeBase()
{
    double scale = this->minimumWidth() / PAGESIZE.width;
    if(PAGESIZE.height * scale > this->height())
    {
        scale = this->height() / PAGESIZE.height;
    }
    SCALE = scale;
    PAINTER->setTransform(QTransform().scale(scale, scale));// 18,897.6378 p/mm = 480,000 dpi

    NOINIT = false;
    PARTINDEX = 0;
    SHEETINDEX = 0;

    return true;
}

bool Preview::newPage()
{
    static int i = 0;
    qDebug() << i++;
    NOINIT = false;
    PARTINDEX = 0;
    SHEETINDEX = 0;
    BOMStd = readBOMStd(FULLSHEETPARTSLISTCSVFILE);
    return false;
}

void Preview::drawLine(Coordinate start, Coordinate end, double lineWidth)
{
    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(lineWidth);
    PAINTER->setPen(pen);
    PAINTER->setBrush(Qt::NoBrush);

    QLineF line(QPointF(start.X, start.Y), QPointF(end.X, end.Y));
    PAINTER->drawLine(line);
}

void Preview::drawRect(Coordinate start, Coordinate end, double lineWidth)
{
    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(lineWidth);
    PAINTER->setPen(pen);
    PAINTER->setBrush(Qt::NoBrush);

    QRectF rectangle(QPointF(start.X, start.Y), QPointF(end.X, end.Y));
    PAINTER->drawRect(rectangle);
}

void Preview::drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth, bool fill)
{
    // Becaus ther is a ofset with the size of the line width
    if(!fill)
    {
        position.X += lineWidth;
        position.Y += lineWidth;
    }
    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(lineWidth);
    PAINTER->setPen(pen);

    QList<QPointF> qPoints;
    for(int i = 0; i < points.length(); i++)
    {
        qPoints.append(QPoint(points[i].X + position.X, points[i].Y + position.Y));
    }

    QPolygonF polygon(qPoints);
    PAINTER->drawPolygon(polygon, Qt::WindingFill);

    // Brush
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);

    if(fill)
    {
        // Fill polygon
        QPainterPath path;
        path.addPolygon(polygon);
        PAINTER->fillPath(path, brush);
    }
}

void Preview::drawCircle(Coordinate center, double radius, double lineWidth)
{
    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(lineWidth);
    PAINTER->setPen(pen);
    PAINTER->setBrush(Qt::NoBrush);

    QRectF rectangle(center.X - radius, center.Y - radius, radius * 2, radius * 2);

    PAINTER->drawEllipse(rectangle);
}

qint64 Preview::drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable, QString font)
{
    QFont qFont(font);
    QFont qFontA(font);
    qFont.setPointSizeF(textSize);//18897.6378
    qFontA.setPointSizeF(100);
    double posX = position.X;
    double posY = position.Y;
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
    PAINTER->setPen(pen);
    PAINTER->setBrush(Qt::NoBrush);

    PAINTER->setFont(qFont);
    PAINTER->drawText(QPointF(posX, posY), text);
    return text.length();
}

void Preview::drawLogoTitelblockISO7200()
{
    // Load SVG
//    QSvgRenderer RENDERER(LOGODIR);
//    QSize size = RENDERER.defaultSize();

//    double widthMM = 24;
//    double heightMM =  24 * (double(RENDERER.defaultSize().height())/RENDERER.defaultSize().width());
//    if(heightMM > 24)
//    {
//        heightMM = 30;
//        widthMM = 30 * (double(RENDERER.defaultSize().width())/RENDERER.defaultSize().height());
//    }
//    QPen pen(Qt::black);
//    pen.setStyle(Qt::SolidLine);
//    pen.setWidthF(0.1);
//    PAINTER->setPen(pen);
//    PAINTER->setBrush(Qt::NoBrush);

//    QRectF rectangle(QPointF(PAGESIZE.width - 111 - widthMM, PAGESIZE.height - 11), QPointF(PAGESIZE.width - 111, PAGESIZE.height - 11 - heightMM));
//    PAINTER->drawRect(rectangle);
//    RENDERER.render(PAINTER, rectangle);



//    QImage image(widthMM, heightMM, QImage::Format_ARGB32);
//    image.fill(0x00FFFFFF);  // partly transparent background

//    // Get QPainter that paints to the image
//    QPainter painter(&image);
//    RENDERER.render(&painter);

//    PAINTER->drawImage(30,30, image);
}
