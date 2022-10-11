#include "templategenkicad_5.h"

#include <QSvgRenderer>
#include <QPainter>
#include <QImage>
#include <QBuffer>

QString TemplateGenKiCAD_5::getFILEENDING()
{
    return "_ki5.kicad_wks";
}

bool TemplateGenKiCAD_5::writeBase()
{
    if(!FULLSHEETPARTSLISTCSV)
    {
        FILE = new QFile(createFileName());
        if(FILE->open(QIODeviceBase::WriteOnly))
        {
            FILE->write("(page_layout\n  (setup (textsize 0 0)(linewidth 0)(textlinewidth 0)\n  (left_margin 0)(right_margin 0)(top_margin 0)(bottom_margin 0))\n");
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

void TemplateGenKiCAD_5::drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth)
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
}

void TemplateGenKiCAD_5::drawCircle(Coordinate center, double radius, double lineWidth)
{
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

    QString lineString = "  (tbtext \"" + text + "\" (name " + QString::number(NAMEINDEX) + ") (pos " + QString::number(position.X) + " " + QString::number(position.Y) + " ltcorner) (font (linewidth " + QString::number(lineWidth) + ") (size " + QString::number(textSize) + " " + QString::number(textSize) + ")) " + anchorString + ")\n";
    NAMEINDEX++;
    return  FILE->write(lineString.toLatin1());
}

void TemplateGenKiCAD_5::drawLogoTitelblockISO7200()
{
    // Load SVG
    QSvgRenderer renderer(LOGODIR);
    QSize size = renderer.defaultSize();

    // Prepare a QImage with desired characteritisc
    int widthPx = 2268; // 24mm bei 2400dpi(KiCAD scale 0.125)
    double widthMM = widthPx / 94.4882;// 2400dpi to p/mm
    int heightPx = int(widthPx * (double(size.height())/size.width()));
    double heightMM = heightPx / 94.4882;// 2400dpi to p/mm
    if(heightPx > 2268)
    {
        heightPx = 2835;// 30mm bei 2400dpi(KiCAD scale 0.25)
        heightMM = heightPx / 94.4882;// 2400dpi to p/mm
        widthPx = int(heightPx * (double(size.width())/size.height()));
        widthMM = widthPx / 94.4882;// 2400dpi to p/mm
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
    QString data = "  (bitmap (name \"\") (pos " + QString::number(PAGESIZE.width - 111 - widthMM/2) + " " + QString::number(PAGESIZE.height - 11 - heightMM/2) + "  ltcorner) (scale 0.125)\n";
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

void TemplateGenKiCAD_5::newPage()
{
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
        free(FILE);
    }
}
