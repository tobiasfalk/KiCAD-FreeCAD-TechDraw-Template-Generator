#include "templategenpdf.h"
#include <QPainterPath>
#include <math.h>
#include <QGraphicsSvgItem>

#define pdfResulutionDPI 33020
#define pdfResulutionPMM 1300.0// 1300.0 p/mm = 33020 dpi


QString TemplateGenPDF::getFILEENDING()
{
    return ".pdf";
}

bool TemplateGenPDF::writeBase()
{
    PDFWRITER = std::shared_ptr<QPdfWriter>(new QPdfWriter(createFileName()));
    PDFWRITER->setPdfVersion(QPagedPaintDevice::PdfVersion_A1b);
    PDFWRITER->setPageMargins(QMarginsF(0, 0, 0, 0));
    PDFWRITER->setPageSize(QPageSize(QSizeF(SHEETSIZE.width, SHEETSIZE.height), QPageSize::Millimeter));
    PDFWRITER->setResolution(pdfResulutionDPI);
    PAINTER = std::shared_ptr<QPainter>(new QPainter(PDFWRITER.get()));
    PAINTER->setTransform(QTransform().scale(pdfResulutionPMM, pdfResulutionPMM));
    return true;
}

bool TemplateGenPDF::newSheet()
{
    PDFWRITER->newPage();
    NOINIT = true;
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

void TemplateGenPDF::drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth, bool fill)
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
        qPoints.append(QPointF(points[i].X + position.X, points[i].Y + position.Y));
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

void TemplateGenPDF::drawCircle(Coordinate center, double radius, double lineWidth, double circleArc)
{
    QPen pen(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(lineWidth);
    PAINTER->setPen(pen);
    PAINTER->setBrush(Qt::NoBrush);

    QRectF rectangle(center.X - radius, center.Y - radius, radius * 2, radius * 2);

    PAINTER->drawEllipse(rectangle);
}

qint64 TemplateGenPDF::drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable, QString font)
{
    QFont qFont(font);
    QFont qFontA(font);
    qFont.setPointSizeF(((textSize * std::sqrt(2))/pdfResulutionPMM) * 2.8346456692913 );//pdfResulutionPMM
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
    LOGORENDERER = std::shared_ptr<QSvgRenderer>(new QSvgRenderer(LOGODIR));
    QSize size = LOGORENDERER->defaultSize();

    // Prepare a QImage with desired characteritisc
    double widthMM = 24;// 2400dpi to p/mm
    int widthPx = pdfResulutionPMM * widthMM; // 24mm bei 2400dpi(KiCAD scale 0.125)

    int heightPx = int(widthPx * (double(size.height())/size.width()));
    double heightMM = heightPx / pdfResulutionPMM;// 2400dpi to p/mm

    if(heightMM > 24)
    {
        heightMM = 30;// 2400dpi to p/mm
        heightPx = pdfResulutionPMM * heightMM;// 30mm bei 2400dpi(KiCAD scale 0.25)

        widthPx = int(heightPx * (double(size.width())/size.height()));
        widthMM = widthPx / pdfResulutionPMM;// 2400dpi to p/mm
    }

    QImage image(widthPx, heightPx, QImage::Format_ARGB32);
    image.fill(0x00FFFFFF);  // partly transparent background

    // Get QPainter that paints to the image
    QPainter painter(&image);
    LOGORENDERER->render(&painter);

    QRectF target(QPointF(SHEETSIZE.width - 111 - widthMM, SHEETSIZE.height - 11 - heightMM), QSizeF(widthMM, heightMM));
    QRectF  source(QPoint(0, 0), QPoint(widthPx, heightPx));
    // Draw the Logo
    PAINTER->drawImage(target, image);
}

TemplateGenPDF::TemplateGenPDF(QObject *parent)
    : TemplateGen{parent}
{

}

TemplateGenPDF::~TemplateGenPDF()
{
    PAINTER->end();
}
