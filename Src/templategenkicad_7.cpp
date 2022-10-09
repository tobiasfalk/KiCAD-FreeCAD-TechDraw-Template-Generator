#include "templategenkicad_7.h"

#include <QSvgRenderer>
#include <QPainter>
#include <QImage>
#include <QBuffer>

QString TemplateGenKiCAD_7::getFILEENDING()
{
    return "_ki7.kicad_wks";
}

bool TemplateGenKiCAD_7::writeBase()
{
    if(!FULLSHEETPARTSLISTCSVKiCAD)
    {
        FILE = new QFile(createFileName());
        if(FILE->open(QIODeviceBase::WriteOnly))
        {
            FILE->write("(kicad_wks (version 20220228) (generator pl_editor)\n  (setup (textsize 0 0)(linewidth 0)(textlinewidth 0)\n  (left_margin 0)(right_margin 0)(top_margin 0)(bottom_margin 0))\n");
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
    }
}

qint64 TemplateGenKiCAD_7::drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable, QString font)
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

    QString lineString = "  (tbtext \"" + text + "\" (name " + QString::number(NAMEINDEX) + ") (pos " + QString::number(position.X) + " " + QString::number(position.Y) + " ltcorner) (font (face \"" + font + "\")  (linewidth " + QString::number(lineWidth) + ") (size " + QString::number(textSize) + " " + QString::number(textSize) + ")) " + anchorString + ")\n";
    NAMEINDEX++;
    return  FILE->write(lineString.toLatin1());
}

TemplateGenKiCAD_7::TemplateGenKiCAD_7(QObject *parent) : TemplateGenKiCAD_6(parent)
{
}

TemplateGenKiCAD_7::~TemplateGenKiCAD_7()
{
}
