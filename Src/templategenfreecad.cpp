#include "templategenfreecad.h"

#include <cmath>

#include <QSvgRenderer>
#include <QPainter>
#include <QImage>
#include <QBuffer>

#include "templategen.h"

QString TemplateGenFreeCAD::getFILEENDING()
{
    return ".freecad.svg";
}

bool TemplateGenFreeCAD::writeBase()
{
    FILE = new QFile(createFileName());
    if(FILE->open(QIODeviceBase::WriteOnly))
    {
        FILE->write("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
        XMLTEXTSTREM = new QTextStream(FILE);
        ROOT = DOCUMENT.createElement("svg");
        ROOT.setAttribute("xmlns:freecad", "http://www.freecadweb.org/wiki/index.php?title=Svg_Namespace");
        ROOT.setAttribute("xmlns:dc", "http://purl.org/dc/elements/1.1/");
        ROOT.setAttribute("xmlns:cc", "http://creativecommons.org/ns#");
        ROOT.setAttribute("xmlns:rdf", "http://www.w3.org/1999/02/22-rdf-syntax-ns#");
        ROOT.setAttribute("xmlns:svg", "http://www.w3.org/2000/svg");
        ROOT.setAttribute("xmlns", "http://www.w3.org/2000/svg");
        ROOT.setAttribute("version", "1.1");
        ROOT.setAttribute("id", "svg2");
        ROOT.setAttribute("width", QString::number(PAGESIZE.width) + "mm");
        ROOT.setAttribute("height", QString::number(PAGESIZE.height) + "mm");
        ROOT.setAttribute("viewBox", "0 0 " + QString::number(PAGESIZE.width) + " " + QString::number(PAGESIZE.height));

        DOCUMENT.appendChild(ROOT);
        return true;
    }
    else
    {
        qCritical() << "Could not open File(KiCAD 5)";
        return false;
    }
}

void TemplateGenFreeCAD::drawLine(Coordinate start, Coordinate end, double lineWidth)
{
    QDomElement obj = DOCUMENT.createElement("line");
    obj.setAttribute("x1", QString::number(start.X));
    obj.setAttribute("y1", QString::number(start.Y));
    obj.setAttribute("x2", QString::number(end.X));
    obj.setAttribute("y2", QString::number(end.Y));
    obj.setAttribute("style", "stroke:black;stroke-width:" + QString::number(lineWidth));
    ROOT.appendChild(obj);
}

void TemplateGenFreeCAD::drawRect(Coordinate start, Coordinate end, double lineWidth)
{
    QDomElement obj = DOCUMENT.createElement("rect");
    obj.setAttribute("x", QString::number(start.X));
    obj.setAttribute("y", QString::number(start.Y));
    obj.setAttribute("width", QString::number(end.X - start.X));
    obj.setAttribute("height", QString::number(end.Y - start.Y));
    obj.setAttribute("style", "fill:none;stroke:black;stroke-width:" + QString::number(lineWidth));
    ROOT.appendChild(obj);
}

void TemplateGenFreeCAD::drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth, bool fill)
{
    QString pointsString = "";
    foreach (Coordinate cord, points)
    {
        pointsString += QString::number(position.X + cord.X) + "," + QString::number(position.Y + cord.Y) + " ";
    }
    QDomElement obj = DOCUMENT.createElement("polygon");
    obj.setAttribute("points", pointsString);
    QString style = "fill:black;stroke:black;stroke-width:";
    if(!fill)
    {
        style = "fill:none;stroke:black;stroke-width:";
    }
    obj.setAttribute("style", style + QString::number(lineWidth));
    ROOT.appendChild(obj);
}

void TemplateGenFreeCAD::drawCircle(Coordinate center, double radius, double lineWidth)
{
    QDomElement obj = DOCUMENT.createElement("circle");
    obj.setAttribute("cx", QString::number(center.X));
    obj.setAttribute("cy", QString::number(center.Y));
    obj.setAttribute("r", QString::number(radius));
    obj.setAttribute("fill", "none");
    obj.setAttribute("style", "stroke:black;stroke-width:" + QString::number(lineWidth));
    ROOT.appendChild(obj);
}

qint64 TemplateGenFreeCAD::drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable, QString font)
{
    QString anchorString = "";
    double posX = position.X;
    double posY = position.Y;

    if(textWidthAnchor == TextWidthAnchor::Left)
    {
        anchorString = "start";
    }
    else if(textWidthAnchor == TextWidthAnchor::Center)
    {
        anchorString = "middle";
    }
    else if(textWidthAnchor == TextWidthAnchor::Right)
    {
        anchorString = "end";
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

    if(isEditable)
    {
        QDomElement obj = DOCUMENT.createElement("text");
        obj.setAttribute("x", QString::number(posX));
        obj.setAttribute("y", QString::number(posY));
        obj.setAttribute("freecad:editable", name);
        obj.setAttribute("style", "fill: #000000; stroke: none; font-family: " + font +"; font-size: " + QString::number(textSize * (1+double(7)/18)) +"; text-anchor: " + anchorString + ";");
        QDomElement obj2 = DOCUMENT.createElement("tspan");
        obj2.setAttribute("x", QString::number(posX));
        obj2.setAttribute("y", QString::number(posY));
        obj2.setAttribute("style", "fill: #000000; stroke: none; font-family: " + font +"; font-size: " + QString::number(textSize * (1+double(7)/18)) +"; text-anchor: " + anchorString + ";");
        obj2.appendChild(DOCUMENT.createTextNode(text));
        obj.appendChild(obj2);
        ROOT.appendChild(obj);
    }
    else
    {
        QDomElement obj = DOCUMENT.createElement("text");
        obj.setAttribute("x", QString::number(posX));
        obj.setAttribute("y", QString::number(posY));
        obj.setAttribute("style", "fill: #000000; stroke: none; font-family: " + font +"; font-size: " + QString::number(textSize * (1+double(7)/18)) +"; text-anchor: " + anchorString + ";");
        obj.appendChild(DOCUMENT.createTextNode(text));
        ROOT.appendChild(obj);
    }

    return  0;
}

void TemplateGenFreeCAD::drawLogoTitelblockISO7200()
{
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

    QFile file(LOGODIR);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qWarning() << "Cannot read file" << file.errorString();
        exit(0);
    }

    QDomDocument xmlBOM;
    xmlBOM.setContent(&file);
    QDomElement root=xmlBOM.documentElement();

    root.setTagName("g");
    root.setAttribute("transform", "translate(" + QString::number(PAGESIZE.width - 111 - widthMM) + " " + QString::number(PAGESIZE.height - 11 - heightMM) + ") scale(" + QString::number(widthMM/root.attribute("width").remove("mm").toDouble()) + ")");
    ROOT. appendChild(root);
}

void TemplateGenFreeCAD::newPage()
{
    *XMLTEXTSTREM << DOCUMENT.toString();
    //FILE->write(")\n");
    XMLTEXTSTREM->flush();
    FILE->flush();
    free(XMLTEXTSTREM);
    free(FILE);
    DOCUMENT = QDomDocument();
    ROOT = QDomElement();
}

TemplateGenFreeCAD::TemplateGenFreeCAD(QObject *parent) : TemplateGen(parent)
{
}

TemplateGenFreeCAD::~TemplateGenFreeCAD()
{
    *XMLTEXTSTREM << DOCUMENT.toString();
    //FILE->write(")\n");
    XMLTEXTSTREM->flush();
    FILE->flush();
    free(XMLTEXTSTREM);
    free(FILE);
}
