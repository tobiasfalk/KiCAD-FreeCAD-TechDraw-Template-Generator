#include "templategenpdf.h"
#include <QPainterPath>
#include <math.h>

QString TemplateGenPDF::getFILEENDING()
{
    return ".pdf";
}

bool TemplateGenPDF::writeBase()
{
    PDFWRITER = new QPdfWriter(createFileName());
    PDFWRITER->setPageMargins(QMarginsF(0, 0, 0, 0));
    PDFWRITER->setPageSize(QPageSize(QSizeF(PAGESIZE.width, PAGESIZE.height), QPageSize::Millimeter));
    PDFWRITER->setResolution(480000);
    PAINTER = new QPainter(PDFWRITER);
    PAINTER->setTransform(QTransform().scale(18897.6378, 18897.6378));// 18,897.6378 p/mm = 480,000 dpi
    return true;
}

void TemplateGenPDF::drawLine(Coordinate start, Coordinate end, double lineWidth)
{
    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(lineWidth);
    PAINTER->setPen(pen);
    PAINTER->setBrush(Qt::NoBrush);

    QLineF line(QPointF(start.X, start.Y), QPointF(end.X, end.Y));
    PAINTER->drawLine(line);
}

void TemplateGenPDF::drawRect(Coordinate start, Coordinate end, double lineWidth)
{
    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(lineWidth);
    PAINTER->setPen(pen);
    PAINTER->setBrush(Qt::NoBrush);

    QRectF rectangle(QPointF(start.X, start.Y), QPointF(end.X, end.Y));
    PAINTER->drawRect(rectangle);
}

void TemplateGenPDF::drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth)
{
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

    // Fill polygon
    QPainterPath path;
    path.addPolygon(polygon);
    PAINTER->fillPath(path, brush);
}

qint64 TemplateGenPDF::drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable, QString font)
{
    QFont qFont(font);
    QFont qFontA(font);
    qFont.setPointSizeF(((textSize * std::sqrt(2))/18897.6378) * 2.8346456692913 );//18897.6378
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

void TemplateGenPDF::drawLogoTitelblockISO7200()
{
    // Load SVG
    RENDERER = new QSvgRenderer(LOGODIR);
    QSize size = RENDERER->defaultSize();
    qDebug() << size;

    double widthMM = 24;
    double heightMM =  24 * (double(RENDERER->defaultSize().height())/RENDERER->defaultSize().width());
    if(heightMM > 24)
    {
        heightMM = 30;
        widthMM = 30 * (double(RENDERER->defaultSize().width())/RENDERER->defaultSize().height());
    }
    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(0.1);
    PAINTER->setPen(pen);
    PAINTER->setBrush(Qt::NoBrush);

    QRectF rectangle(QPointF(PAGESIZE.width - 111 - widthMM, PAGESIZE.height - 11), QPointF(PAGESIZE.width - 111, PAGESIZE.height - 11 - heightMM));
    PAINTER->drawRect(rectangle);
    RENDERER->render(PAINTER, rectangle);



    //QImage image(widthPx, heightPx, QImage::Format_ARGB32);
    //image.fill(0x00FFFFFF);  // partly transparent background

    // Get QPainter that paints to the image
    //QPainter painter(&image);
    //renderer.render(&painter);

    //PAINTER->drawImage(30,30, image);
}

TemplateGenPDF::TemplateGenPDF(QObject *parent)
    : TemplateGen{parent}
{

}

TemplateGenPDF::~TemplateGenPDF()
{
    PAINTER->end();
    free(PAINTER);
    free(PDFWRITER);
}
