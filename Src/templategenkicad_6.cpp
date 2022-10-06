#include "templategenkicad_6.h"

#include <QSvgRenderer>
#include <QPainter>
#include <QImage>
#include <QBuffer>

QString TemplateGenKiCAD_6::getFILEENDING()
{
    return "_ki6.kicad_wks";
}

bool TemplateGenKiCAD_6::writeBase()
{
    FILE = new QFile(createFileName());
    if(FILE->open(QIODeviceBase::WriteOnly))
    {
        FILE->write("(kicad_wks (version 20210606) (generator pl_editor)\n  (setup (textsize 0 0)(linewidth 0)(textlinewidth 0)\n  (left_margin 0)(right_margin 0)(top_margin 0)(bottom_margin 0))\n");
        return true;
    }
    else
    {
        qCritical() << "Could not open File(KiCAD 5)";
        return false;
    }
}

TemplateGenKiCAD_6::TemplateGenKiCAD_6(QObject *parent) : TemplateGenKiCAD_5(parent)
{
}

TemplateGenKiCAD_6::~TemplateGenKiCAD_6()
{
}
