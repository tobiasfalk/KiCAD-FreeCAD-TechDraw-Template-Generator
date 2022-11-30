#include "templategeneagle.h"
#include <QRegularExpression>

QString TemplateGenEagle::getFILEENDING()
{
    return "";
}

bool TemplateGenEagle::writeBase()
{
    if(!FULLSHEETPARTSLISTCSV)
    {
        if(QFile::exists(DIR + "/sheet_template_eagle_6-5.lbr"))
        {
            QFile file(DIR + "/sheet_template_eagle_6-5.lbr");
            if(!file.open(QFile::ReadOnly | QFile::Text))
            {
                qWarning() << "Cannot read file" << file.errorString();
                exit(0);
            }

            QDomDocument xmlBOM;
            xmlBOM.setContent(&file);
            QDomElement root=xmlBOM.documentElement();

            // Get the first child of the root (Markup COMPONENT is expected)
            QDomElement componentA = root.firstChild().toElement().firstChild().toElement();

            // Loop while there is a child
            while(!componentA.isNull())
            {
                if(componentA.tagName() == "library")
                {
                    QDomElement componentB = componentA.firstChild().toElement();
                    while(!componentB.isNull())
                    {
                        QDomElement componentC = componentB.firstChild().toElement();
                        while(!componentC.isNull())
                        {
                            if(componentC.tagName() == "package")
                            {
                                OPACKAGES.append(componentC);
                            } else if(componentC.tagName() == "symbol")
                            {
                                OSYMBOLS.append(componentC);
                                ONAMELIST.append(componentC.attribute("name"));
                            } else if(componentC.tagName() == "deviceset")
                            {
                                ODEVICESETS.append(componentC);
                            }
                            componentC = componentC.nextSibling().toElement();
                        }
                        componentB = componentB.nextSibling().toElement();
                    }
                }
                componentA = componentA.nextSibling().toElement();
            }
        }
        FILE = std::shared_ptr<QFile>(new QFile(DIR + "/sheet_template_eagle_6-5.lbr"));
        if(FILE->open(QIODeviceBase::WriteOnly))
        {
            FILE->write("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
            FILE->write("<!DOCTYPE eagle SYSTEM \"eagle.dtd\">\n");
            XMLTEXTSTREM = std::shared_ptr<QTextStream>(new QTextStream(FILE.get()));
            ROOT = DOCUMENT.createElement("eagle");
            ROOT.setAttribute("version", "6.5.0");

            QString name = createFileName().remove(DIR + "/");

            if(ONAMELIST.indexOf(createFileName().remove(DIR + "/")) >= 0)
            {
                int i = 0;
                do
                {
                    name = createFileName().remove(DIR + "/") + "_" + QString::number(i++);
                }while(ONAMELIST.indexOf(name) >= 0);
            }


            DRAWING = DOCUMENT.createElement("drawing");
            LIBRARY = DOCUMENT.createElement("library");
            PACKAGES = DOCUMENT.createElement("packages");
            SYMBOLS = DOCUMENT.createElement("symbols");
            DEVICESETS = DOCUMENT.createElement("devicesets");

            CSYMBOL = DOCUMENT.createElement("symbol");
            CSYMBOL.setAttribute("name", name);
            CPACKAGE = DOCUMENT.createElement("package");
            CPACKAGE.setAttribute("name", name);

            CDEVICS = DOCUMENT.createElement("deviceset");
            CDEVICS.setAttribute("name", name);

            QDomElement settings = DOCUMENT.createElement("settings");
            QDomElement settingA = DOCUMENT.createElement("setting");
            settingA.setAttribute("alwaysvectorfont", "no");
            QDomElement settingB = DOCUMENT.createElement("setting");
            settingB.setAttribute("verticaltext", "up");
            settings.appendChild(settingA);
            settings.appendChild(settingB);
            DRAWING.appendChild(settings);
            QDomElement grid = DOCUMENT.createElement("grid");
            grid.setAttribute("distance", "0.1");
            grid.setAttribute("unitdist", "inch");
            grid.setAttribute("unit", "inch");
            grid.setAttribute("style", "lines");
            grid.setAttribute("multiple", "1");
            grid.setAttribute("display", "no");
            grid.setAttribute("altdistance", "0.01");
            grid.setAttribute("altunitdist", "inch");
            grid.setAttribute("altunit", "inch");
            DRAWING.appendChild(grid);
            QDomElement layers = DOCUMENT.createElement("layers");
            QDomElement layer94 = DOCUMENT.createElement("layer");
            layer94.setAttribute("number", "94");
            layer94.setAttribute("name", "Symbols");
            layer94.setAttribute("color", "4");
            layer94.setAttribute("fill", "1");
            layer94.setAttribute("visible", "yes");
            layer94.setAttribute("active", "yes");
            layers.appendChild(layer94);
            QDomElement layer48 = DOCUMENT.createElement("layer");
            layer48.setAttribute("number", "48");
            layer48.setAttribute("name", "Document");
            layer48.setAttribute("color", "7");
            layer48.setAttribute("fill", "1");
            layer48.setAttribute("visible", "yes");
            layer48.setAttribute("active", "yes");
            layers.appendChild(layer48);
            DRAWING.appendChild(layers);

            // Symol Deice
            QDomElement gates_s = DOCUMENT.createElement("gates");
            QDomElement gate_s = DOCUMENT.createElement("gate");
            gate_s.setAttribute("name", "G$1");
            gate_s.setAttribute("symbol", name);
            gate_s.setAttribute("x", 0);
            gate_s.setAttribute("y", 0);
            gates_s.appendChild(gate_s);
            CDEVICS.appendChild(gates_s);

            QDomElement devices_s = DOCUMENT.createElement("devices");
            QDomElement device_s = DOCUMENT.createElement("device");
            device_s.setAttribute("name", "");
            QDomElement technologies_s = DOCUMENT.createElement("technologies");
            QDomElement technology_s = DOCUMENT.createElement("technology");
            technology_s.setAttribute("name", "");
            technologies_s.appendChild(technology_s);
            device_s.appendChild(technologies_s);
            devices_s.appendChild(device_s);
            CDEVICS.appendChild(devices_s);

            return true;
        }
        else
        {
            qCritical() << "Could not open File(EAGLE 6.5)";
            return false;
        }
    }else
    {
        NODRAW = true;
        return true;
    }
}

bool TemplateGenEagle::newPage()
{
    return false;
}

void TemplateGenEagle::drawLine(Coordinate start, Coordinate end, double lineWidth)
{
    start = Coordinate{start.X - 5, start.Y + 5};
    end = Coordinate{end.X - 5, end.Y + 5};
    QDomElement wireSym = DOCUMENT.createElement("wire");
    wireSym.setAttribute("x1", start.X);
    wireSym.setAttribute("y1", PAGESIZE.height - start.Y);
    wireSym.setAttribute("x2", end.X);
    wireSym.setAttribute("y2", PAGESIZE.height - end.Y);
    wireSym.setAttribute("width", lineWidth);
    wireSym.setAttribute("layer", "94");
    CSYMBOL.appendChild(wireSym);

    QDomElement wirePack = DOCUMENT.createElement("wire");
    wirePack.setAttribute("x1", start.X);
    wirePack.setAttribute("y1", PAGESIZE.height - start.Y);
    wirePack.setAttribute("x2", end.X);
    wirePack.setAttribute("y2", PAGESIZE.height - end.Y);
    wirePack.setAttribute("width", lineWidth);
    wirePack.setAttribute("layer", "48");
    CPACKAGE.appendChild(wirePack);
}

void TemplateGenEagle::drawRect(Coordinate start, Coordinate end, double lineWidth)
{
    start = Coordinate{start.X - 5, start.Y + 5};
    end = Coordinate{end.X - 5, end.Y + 5};
    QDomElement wireSymA = DOCUMENT.createElement("wire");
    wireSymA.setAttribute("x1", start.X);
    wireSymA.setAttribute("y1", PAGESIZE.height - start.Y);
    wireSymA.setAttribute("x2", start.X);
    wireSymA.setAttribute("y2", PAGESIZE.height - end.Y);
    wireSymA.setAttribute("width", lineWidth);
    wireSymA.setAttribute("layer", "94");
    CSYMBOL.appendChild(wireSymA);

    QDomElement wireSymB = DOCUMENT.createElement("wire");
    wireSymB.setAttribute("x1", start.X);
    wireSymB.setAttribute("y1", PAGESIZE.height - end.Y);
    wireSymB.setAttribute("x2", end.X);
    wireSymB.setAttribute("y2", PAGESIZE.height - end.Y);
    wireSymB.setAttribute("width", lineWidth);
    wireSymB.setAttribute("layer", "94");
    CSYMBOL.appendChild(wireSymB);

    QDomElement wireSymC = DOCUMENT.createElement("wire");
    wireSymC.setAttribute("x1", end.X);
    wireSymC.setAttribute("y1", PAGESIZE.height - end.Y);
    wireSymC.setAttribute("x2", end.X);
    wireSymC.setAttribute("y2", PAGESIZE.height - start.Y);
    wireSymC.setAttribute("width", lineWidth);
    wireSymC.setAttribute("layer", "94");
    CSYMBOL.appendChild(wireSymC);

    QDomElement wireSymD = DOCUMENT.createElement("wire");
    wireSymD.setAttribute("x1", end.X);
    wireSymD.setAttribute("y1", PAGESIZE.height - start.Y);
    wireSymD.setAttribute("x2", start.X);
    wireSymD.setAttribute("y2", PAGESIZE.height - start.Y);
    wireSymD.setAttribute("width", lineWidth);
    wireSymD.setAttribute("layer", "94");
    CSYMBOL.appendChild(wireSymD);

    QDomElement wirePackA = DOCUMENT.createElement("wire");
    wirePackA.setAttribute("x1", start.X);
    wirePackA.setAttribute("y1", PAGESIZE.height - start.Y);
    wirePackA.setAttribute("x2", start.X);
    wirePackA.setAttribute("y2", PAGESIZE.height - end.Y);
    wirePackA.setAttribute("width", lineWidth);
    wirePackA.setAttribute("layer", "48");
    CPACKAGE.appendChild(wirePackA);

    QDomElement wirePackB = DOCUMENT.createElement("wire");
    wirePackB.setAttribute("x1", start.X);
    wirePackB.setAttribute("y1", PAGESIZE.height - end.Y);
    wirePackB.setAttribute("x2", end.X);
    wirePackB.setAttribute("y2", PAGESIZE.height - end.Y);
    wirePackB.setAttribute("width", lineWidth);
    wirePackB.setAttribute("layer", "48");
    CPACKAGE.appendChild(wirePackB);

    QDomElement wirePackC = DOCUMENT.createElement("wire");
    wirePackC.setAttribute("x1", end.X);
    wirePackC.setAttribute("y1", PAGESIZE.height - end.Y);
    wirePackC.setAttribute("x2", end.X);
    wirePackC.setAttribute("y2", PAGESIZE.height - start.Y);
    wirePackC.setAttribute("width", lineWidth);
    wirePackC.setAttribute("layer", "48");
    CPACKAGE.appendChild(wirePackC);

    QDomElement wirePackD = DOCUMENT.createElement("wire");
    wirePackD.setAttribute("x1", end.X);
    wirePackD.setAttribute("y1", PAGESIZE.height - start.Y);
    wirePackD.setAttribute("x2", start.X);
    wirePackD.setAttribute("y2", PAGESIZE.height - start.Y);
    wirePackD.setAttribute("width", lineWidth);
    wirePackD.setAttribute("layer", "48");
    CPACKAGE.appendChild(wirePackD);
}

void TemplateGenEagle::drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth, bool fill)
{
    position = Coordinate{position.X - 5, position.Y - 5};
    QDomElement polygonSym = DOCUMENT.createElement("polygon");
    polygonSym.setAttribute("width", lineWidth);
    polygonSym.setAttribute("layer", "94");

    QDomElement polygonPack = DOCUMENT.createElement("polygon");
    polygonPack.setAttribute("width", lineWidth);
    polygonPack.setAttribute("layer", "48");

    foreach (Coordinate p, points)
    {
        QDomElement vertexA = DOCUMENT.createElement("vertex");
        vertexA.setAttribute("x", position.X + p.X);
        vertexA.setAttribute("y", position.Y + p.Y);
        polygonSym.appendChild(vertexA);

        QDomElement vertexB = DOCUMENT.createElement("vertex");
        vertexB.setAttribute("x", position.X + p.X);
        vertexB.setAttribute("y", position.Y + p.Y);
        polygonPack.appendChild(vertexB);
    }
    CSYMBOL.appendChild(polygonSym);
    CPACKAGE.appendChild(polygonPack);
}

void TemplateGenEagle::drawCircle(Coordinate center, double radius, double lineWidth)
{
}

qint64 TemplateGenEagle::drawText(Coordinate position, QString text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable, QString font)
{
    position = Coordinate{position.X - 5, position.Y + 5};
    QDomElement textSym = DOCUMENT.createElement("text");
    textSym.setAttribute("x", position.X);
    textSym.setAttribute("y", PAGESIZE.height - position.Y);
    textSym.setAttribute("size", textSize);
    textSym.setAttribute("layer", "94");
    textSym.appendChild(DOCUMENT.createTextNode(text));
    if(textHeightAnchor == TextHeightAnchor::Middle && textWidthAnchor == TextWidthAnchor::Left)
    {
        textSym.setAttribute("align", "center-left");
    } else if(textHeightAnchor == TextHeightAnchor::Top && textWidthAnchor == TextWidthAnchor::Left)
    {
        textSym.setAttribute("align", "top-left");
    } else if(textHeightAnchor == TextHeightAnchor::Bottom && textWidthAnchor == TextWidthAnchor::Center)
    {
        textSym.setAttribute("align", "bottom-center");
    } else if(textHeightAnchor == TextHeightAnchor::Middle && textWidthAnchor == TextWidthAnchor::Center)
    {
        textSym.setAttribute("align", "center");
    } else if(textHeightAnchor == TextHeightAnchor::Top && textWidthAnchor == TextWidthAnchor::Center)
    {
        textSym.setAttribute("align", "top-center");
    } else if(textHeightAnchor == TextHeightAnchor::Bottom && textWidthAnchor == TextWidthAnchor::Right)
    {
        textSym.setAttribute("align", "bottom-right");
    } else if(textHeightAnchor == TextHeightAnchor::Middle && textWidthAnchor == TextWidthAnchor::Right)
    {
        textSym.setAttribute("align", "center-right");
    } else if(textHeightAnchor == TextHeightAnchor::Top && textWidthAnchor == TextWidthAnchor::Right)
    {
        textSym.setAttribute("align", "top-right");
    }
    CSYMBOL.appendChild(textSym);

    QDomElement textPack = DOCUMENT.createElement("text");
    textPack.setAttribute("x", position.X);
    textPack.setAttribute("y", PAGESIZE.height - position.Y);
    textPack.setAttribute("size", textSize);
    textPack.setAttribute("layer", "48");
    textPack.appendChild(DOCUMENT.createTextNode(text));
    if(textHeightAnchor == TextHeightAnchor::Middle && textWidthAnchor == TextWidthAnchor::Left)
    {
        textPack.setAttribute("align", "center-left");
    } else if(textHeightAnchor == TextHeightAnchor::Top && textWidthAnchor == TextWidthAnchor::Left)
    {
        textPack.setAttribute("align", "top-left");
    } else if(textHeightAnchor == TextHeightAnchor::Bottom && textWidthAnchor == TextWidthAnchor::Center)
    {
        textPack.setAttribute("align", "bottom-center");
    } else if(textHeightAnchor == TextHeightAnchor::Middle && textWidthAnchor == TextWidthAnchor::Center)
    {
        textPack.setAttribute("align", "center");
    } else if(textHeightAnchor == TextHeightAnchor::Top && textWidthAnchor == TextWidthAnchor::Center)
    {
        textPack.setAttribute("align", "top-center");
    } else if(textHeightAnchor == TextHeightAnchor::Bottom && textWidthAnchor == TextWidthAnchor::Right)
    {
        textPack.setAttribute("align", "bottom-right");
    } else if(textHeightAnchor == TextHeightAnchor::Middle && textWidthAnchor == TextWidthAnchor::Right)
    {
        textPack.setAttribute("align", "center-right");
    } else if(textHeightAnchor == TextHeightAnchor::Top && textWidthAnchor == TextWidthAnchor::Right)
    {
        textPack.setAttribute("align", "top-right");
    }
    CPACKAGE.appendChild(textPack);
    return 0;
}

void TemplateGenEagle::drawLogoTitelblockISO7200()
{
}

TemplateGenEagle::TemplateGenEagle(QObject *parent)
    : TemplateGen{parent}
{

}

TemplateGenEagle::~TemplateGenEagle()
{
    if(!NODRAW)
    {
        foreach (QDomElement pack, OPACKAGES)
        {
            PACKAGES.appendChild(pack);
        }
        foreach (QDomElement sym, OSYMBOLS)
        {
            SYMBOLS.appendChild(sym);
        }
        foreach (QDomElement devic, ODEVICESETS)
        {
            DEVICESETS.appendChild(devic);
        }

        SYMBOLS.appendChild(CSYMBOL);
        PACKAGES.appendChild(CPACKAGE);
        DEVICESETS.appendChild(CDEVICS);
        //DEVICESETS.appendChild(CDEVICP);
        LIBRARY.appendChild(PACKAGES);
        LIBRARY.appendChild(SYMBOLS);
        LIBRARY.appendChild(DEVICESETS);
        DRAWING.appendChild(LIBRARY);
        ROOT.appendChild(DRAWING);
        DOCUMENT.appendChild(ROOT);
        *XMLTEXTSTREM << DOCUMENT.toString();
        //FILE->write(")\n");
        XMLTEXTSTREM->flush();
        FILE->flush();
        FILE->close();
    }
}
