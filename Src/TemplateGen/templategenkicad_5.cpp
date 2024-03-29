#include "templategenkicad_5.h"

#include <QSvgRenderer>
#include <QPainter>
#include <QImage>
#include <QBuffer>
#include <math.h>

QString TemplateGenKiCAD_5::getFILEENDING()
{
    return "_ki5.kicad_wks";
}

bool TemplateGenKiCAD_5::writeBase()
{
    if(!FULLSHEETPARTLISTOPIONS->getImporCSV())
    {
        FILE = std::shared_ptr<QFile>(new QFile(createFileName()));
        if(FILE->open(QIODeviceBase::WriteOnly))
        {
            FILE->write("(sheet_layout\n  (setup (textsize 0 0)(linewidth 0)(textlinewidth 0)\n  (left_margin 0)(right_margin 0)(top_margin 0)(bottom_margin 0))\n");
            return true;
        }
        else
        {
            qCritical() << "Could not open File(KiCAD 5)";
            return false;
        }
    }else
    {
        NODRAW = true;
        return true;
    }
}

void TemplateGenKiCAD_5::drawLine(Coordinate start, Coordinate end, double lineWidth)
{
    QString lineString = "  (line (name " + QString::number(NAMEINDEX) + ") (start " + QString::number(start.X) + " " + QString::number(start.Y) + " ltcorner) (end " + QString::number(end.X) + " " + QString::number(end.Y) + " ltcorner) (linewidth " + QString::number(lineWidth) + "))\n";
    FILE->write(lineString.toLatin1());
    NAMEINDEX++;
}

void TemplateGenKiCAD_5::drawRect(Coordinate start, Coordinate end, double lineWidth)
{
    QString lineString = "  (rect (name " + QString::number(NAMEINDEX) + ") (start " + QString::number(start.X) + " " + QString::number(start.Y) + " ltcorner) (end " + QString::number(end.X) + " " + QString::number(end.Y) + " ltcorner) (linewidth " + QString::number(lineWidth) + "))\n";
    FILE->write(lineString.toLatin1());
    NAMEINDEX++;
}

void TemplateGenKiCAD_5::drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth, bool fill)
{
    if(fill)
    {
        QString lineString = "  (polygon (name " + QString::number(NAMEINDEX) + ") (pos " + QString::number(position.X) + " " + QString::number(position.Y) + " ltcorner) (rotate 0) (linewidth " + QString::number(lineWidth) + ")\n";
        lineString += "    (pts ";
        foreach(Coordinate pt, points)
        {
            lineString += "(xy " + QString::number(pt.X) + " " + QString::number(pt.Y) + ") ";
        }
        lineString += "))\n";
        FILE->write(lineString.toLatin1());
        NAMEINDEX++;
    }else
    {
        int i = 1;
        for(i = 1; i < points.size(); i++)
        {
            drawLine(points[i - 1] + position, points[i] + position, lineWidth);
        }
        drawLine(points[i - 1] + position, points[0] + position, lineWidth);
    }
}

void TemplateGenKiCAD_5::drawCircle(Coordinate center, double radius, double lineWidth, double circleArc)
{
    double arc = 0;
    double arcPre = 0;
    while(arc <= 360)
    {
        if(arc)
        {
            double x1 = center.X + radius * std::cos(arcPre * M_PI / 180);
            double y1 = center.Y + radius * std::sin(arcPre * M_PI / 180);
            double x2 = center.X + radius * std::cos(arc * M_PI / 180);
            double y2 = center.Y + radius * std::sin(arc * M_PI / 180);
            drawLine(Coordinate{x1, y1}, Coordinate{x2, y2}, lineWidth);
        }
        arcPre = arc;
        arc += circleArc;
    }
}

qint64 TemplateGenKiCAD_5::drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable, QString font)
{
    QString anchorString = "";

    // Left
    if(textHeightAnchor == TextHeightAnchor::Top && textWidthAnchor == TextWidthAnchor::Left)
    {
        anchorString = "(justify top)";
    }
    else if(textHeightAnchor == TextHeightAnchor::Middle && textWidthAnchor == TextWidthAnchor::Left)
    {
        anchorString = "";
    }
    else if(textHeightAnchor == TextHeightAnchor::Bottom && textWidthAnchor == TextWidthAnchor::Left)
    {
        anchorString = "(justify bottom)";
    }

    // Center
    else if(textHeightAnchor == TextHeightAnchor::Top && textWidthAnchor == TextWidthAnchor::Center)
    {
        anchorString = "(justify center top)";
    }
    else if(textHeightAnchor == TextHeightAnchor::Middle && textWidthAnchor == TextWidthAnchor::Center)
    {
        anchorString = "(justify center)";
    }
    else if(textHeightAnchor == TextHeightAnchor::Bottom && textWidthAnchor == TextWidthAnchor::Center)
    {
        anchorString = "(justify center bottom)";
    }

    // Right
    else if(textHeightAnchor == TextHeightAnchor::Top && textWidthAnchor == TextWidthAnchor::Right)
    {
        anchorString = "(justify right top)";
    }
    else if(textHeightAnchor == TextHeightAnchor::Middle && textWidthAnchor == TextWidthAnchor::Right)
    {
        anchorString = "(justify right)";
    }
    else if(textHeightAnchor == TextHeightAnchor::Bottom && textWidthAnchor == TextWidthAnchor::Right)
    {
        anchorString = "(justify right bottom)";
    }

    QString lineString = "  (tbtext \"" + text + "\" (name " + QString::number(NAMEINDEX) + ") (pos " + QString::number(position.X) + " " + QString::number(position.Y + .3) + " ltcorner) (font (linewidth " + QString::number(lineWidth) + ") (size " + QString::number(textSize) + " " + QString::number(textSize) + ")) " + anchorString + ")\n";
    NAMEINDEX++;
    return  FILE->write(lineString.toLatin1());
}

void TemplateGenKiCAD_5::drawLogoTitelblockISO7200()
{
    // Load SVG
    QSvgRenderer renderer(LOGODIR);
    QSize size = renderer.defaultSize();

#define resulutionDPI 9600
#define resulutionPMM (resulutionDPI * 0.0393700787)// 1300.0 p/mm = 33020 dpi

    // Prepare a QImage with desired characteritisc
    double widthMM = 24;// 2400dpi to p/mm
    int widthPx = resulutionPMM * widthMM; // 24mm bei 2400dpi(KiCAD scale 0.125)

    int heightPx = int(widthPx * (double(size.height())/size.width()));
    double heightMM = heightPx / resulutionPMM;// 2400dpi to p/mm

    if(heightMM > 24)
    {
        heightMM = 30;// 2400dpi to p/mm
        heightPx = resulutionPMM * heightMM;// 30mm bei 2400dpi(KiCAD scale 0.125)

        widthPx = int(heightPx * (double(size.width())/size.height()));
        widthMM = widthPx / resulutionPMM;// 2400dpi to p/mm
    }
    QImage image(widthPx, heightPx, QImage::Format_ARGB32);
    image.fill(0x00FFFFFF);  // partly transparent background

    // Get QPainter that paints to the image
    QPainter painter(&image);
    renderer.render(&painter);

    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");

    int rows=ba.length()/32;  // number of lines
    if(ba.length()%32) rows++;

    // create hex dump(https://forum.qt.io/topic/106891/displaying-data-in-hex-format)
    QString data = "  (bitmap (name \"\") (pos " + QString::number(SHEETSIZE.width - 111 - widthMM/2) + " " + QString::number(SHEETSIZE.height - 11 - heightMM/2) + "  ltcorner) (scale " + QString::number((double)300 / (double)resulutionDPI) + ")\n";
    data += "  (pngdata\n";
    for(int i=0; i<rows; i++)
    {
        QString dump;

        dump = "";   //
        QByteArray line=ba.mid(32*i,32);
        QString hex;

        // 16 ba by line
        for(int b=0;b<line.length();b++)
        {
            uint8_t c=uint8_t(line.at(b));
            hex+=QString::asprintf("%02X ", c); // hex
        }

        while(hex.size()<48) hex.append(' ');
        dump.append(hex);
        data.append("    (data \"" + dump.toLatin1() + " \")\n");
    }
    data.append("    )\n  )\n");
    FILE->write(data.toLatin1());
}

bool TemplateGenKiCAD_5::newSheet()
{
    return false;
}

TemplateGenKiCAD_5::TemplateGenKiCAD_5(QObject *parent) : TemplateGen(parent)
{
}

TemplateGenKiCAD_5::~TemplateGenKiCAD_5()
{
    if(!NODRAW)
    {
        FILE->write(")\n");
        FILE->flush();
    }
}
