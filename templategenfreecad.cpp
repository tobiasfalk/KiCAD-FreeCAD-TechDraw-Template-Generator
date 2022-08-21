#include "templategenfreecad.h"

#include <QSvgRenderer>
#include <QPainter>
#include <QImage>
#include <QBuffer>

const QString &TemplateGenFreeCAD::getLOGODIR() const
{
    return LOGODIR;
}

void TemplateGenFreeCAD::setLOGODIR(const QString &newLOGODIR)
{
    LOGODIR = newLOGODIR;
    finisheD.logodiR = true;
}

bool TemplateGenFreeCAD::getLOGO() const
{
    return LOGO;
}

void TemplateGenFreeCAD::setLOGO(bool newLOGO)
{
    LOGO = newLOGO;
    finisheD.logO = true;
}

const QString &TemplateGenFreeCAD::getSHEETNAME() const
{
    return SHEETNAME;
}

void TemplateGenFreeCAD::setSHEETNAME(const QString &newSHEETNAME)
{
    SHEETNAME = newSHEETNAME;
    finisheD.sheetnamE = true;
}

bool TemplateGenFreeCAD::init()
{
    if((PAGESIZE.height / 2 < 10 + (11 * (5 + NUMOPTLINES) + 8 + ((2.5 * 1.5) * NUMLINESMALLPARTSLIST + 3) * NUMPARTSSMALLPARTSLIST)) && SMALLPARTSLIST)
    {
        CENTERINGMARKS.Right = false;
        if(PAGESIZE.width / 2 < 190)
        {
            CENTERINGMARKS.Left = false;
        }
    }
    if(FULLSHEETPARTSLIST)
    {
        CENTERINGMARKS.Right = false;
        CENTERINGMARKS.Left = false;
        CENTERINGMARKS.Top = false;
    }
    if(PAGESIZE.width / 2 < 190)
    {
        CENTERINGMARKS.Bottom = false;
    }
    if(PAGESIZE.width / 2 < 190 && REVHISTORY)
    {
        CENTERINGMARKS.Top = false;
    }
    if(PAGESIZE.height / 2 > (PAGESIZE.height - 11 * (5 + NUMOPTLINES) + 0) || (PAGESIZE.height / 2 < (10 + 8 + NUMREVHISTORY * 13.5) && REVHISTORY))
    {
        CENTERINGMARKS.Right = false;
    }
    if((PAGESIZE.height / 2 > (PAGESIZE.height - 11 * (5 + NUMOPTLINES) + 0)) && (PAGESIZE.width / 2 < 190))
    {
        CENTERINGMARKS.Left = false;
    }

    finisheD.numsheetsfullsheetpartslisT = true;
    if(allFinisheD(finisheD))
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
    else
    {
        printFinisheD(finisheD);
        qCritical() << "Not all options where filled(KiCAD 5)";
        return false;
    }
    return false;
}

QString TemplateGenFreeCAD::createFileName()
{
    QString ret =  DIR + "/" + PAGESIZE.sizeString.replace(" ", "_");

    switch (PAGESTYLE)
    {
    case PageStyle::ISO5457_ISO7200:
        ret += "_ISO5457_ISO7200";
        break;
    }

    // optional lines
    if(NUMOPTLINES > 0)
    {
        ret += "+" + QString::number(NUMOPTLINES);
    }

    if(FOLDLINES)
    {
        if(FOLDLINETARGET.sizeString == "A4P with border")
        {
            ret += "_flA4wb";
        }
        else
        {
            ret += "_fl";
        }
    }

    if(REVHISTORY)
    {
        ret += "_rev+" + QString::number(NUMREVHISTORY);
    }

    if(FULLSHEETPARTSLIST)
    {
        ret += "_fspl+" + QString::number(NUMLINESFULLSHEETPARTSLIST);
    }

    if(SMALLPARTSLIST)
    {
        ret += "_spl+" + QString::number(NUMPARTSSMALLPARTSLIST) + "+" + QString::number(NUMLINESMALLPARTSLIST);
    }

    ret +=  "_.freecad.svg";
    return ret;
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

void TemplateGenFreeCAD::drawPoly(Coordinate position, QList<Coordinate> points, double lineWidth)
{
    QString pointsString = "";
    foreach (Coordinate cord, points)
    {
        pointsString += QString::number(position.X + cord.X) + "," + QString::number(position.Y + cord.Y) + " ";
    }
    QDomElement obj = DOCUMENT.createElement("polygon");
    obj.setAttribute("points", pointsString);
    obj.setAttribute("style", "fill:black;stroke:black;stroke-width:" + QString::number(lineWidth));
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

qint64 TemplateGenFreeCAD::drawText(Coordinate position, QStringList text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable, qint64 index)
{
    if(text.length() == 1)
    {
        drawText(position, text[0].replace("&{N}", QString::number(index + 1)), name.replace("&{N}", QString::number(index + 1)) + QString::number(index + 4), textSize, textHeightAnchor, textWidthAnchor, lineWidth, isEditable);
    }
    else if(text.length() > 1)
    {
        double lineHeight = (textSize * 1.5);
        double heightTotal = lineHeight * text.length();
        switch (textHeightAnchor)
        {
        case TextHeightAnchor::Top:
            for(int i = 0; i < text.length(); i++)
            {
                double height = position.Y + lineHeight * i;
                QString txt = text.at(i);
                drawText(Coordinate{position.X, height}, txt.replace("&{N}", QString::number(index + 1)), name + QString::number(index + 1) + QString::number(i), textSize, TextHeightAnchor::Top, textWidthAnchor, lineWidth, isEditable);
            }
            break;
        case TextHeightAnchor::Middle:
            for(int i = 0; i < text.length(); i++)
            {
                double height = position.Y - (heightTotal / 2) + lineHeight * i;
                QString txt = text.at(i);
                drawText(Coordinate{position.X, height}, txt.replace("&{N}", QString::number(index + 1)), name + QString::number(index + 1) + QString::number(i), textSize, TextHeightAnchor::Top, textWidthAnchor, lineWidth, isEditable);
            }
            break;
        case TextHeightAnchor::Bottom:
            for(int i = 0; i < text.length(); i++)
            {
                double height = position.Y - heightTotal + lineHeight * i;
                QString txt = text.at(i);
                drawText(Coordinate{position.X, height}, txt.replace("&{N}", QString::number(index + 1)), name + QString::number(index + 1) + QString::number(i), textSize, TextHeightAnchor::Top, textWidthAnchor, lineWidth, isEditable);
            }
            break;
        }
    }
    return -1;
}

void TemplateGenFreeCAD::drawVerFoldLine(double x, double depth)
{
    drawLine(Coordinate{x, 0}, Coordinate{x, depth}, 0.35);
    drawLine(Coordinate{x, PAGESIZE.height}, Coordinate{x, PAGESIZE.height - depth}, 0.35);
}

void TemplateGenFreeCAD::drawHorFoldLine(double y, double depth)
{
    drawLine(Coordinate{0, y}, Coordinate{depth, y}, 0.35);
    drawLine(Coordinate{PAGESIZE.width, y}, Coordinate{PAGESIZE.width - depth, y}, 0.35);
}

void TemplateGenFreeCAD::drawTrimmingMarksISO5457()
{
    QList<Coordinate> trimmingMarkLT
    {
        Coordinate{0, 0},
        Coordinate{10, 0},
        Coordinate{10, 5},
        Coordinate{5, 5},
        Coordinate{5, 10},
        Coordinate{0, 10}
    };
    QList<Coordinate> trimmingMarkRT
    {
        Coordinate{0, 0},
        Coordinate{-10, 0},
        Coordinate{-10, 5},
        Coordinate{-5, 5},
        Coordinate{-5, 10},
        Coordinate{0, 10}
    };
    QList<Coordinate> trimmingMarkRB
    {
        Coordinate{0, 0},
        Coordinate{-10, 0},
        Coordinate{-10, -5},
        Coordinate{-5, -5},
        Coordinate{-5, -10},
        Coordinate{0, -10}
    };
    QList<Coordinate> trimmingMarkLB
    {
        Coordinate{0, 0},
        Coordinate{10, 0},
        Coordinate{10, -5},
        Coordinate{5, -5},
        Coordinate{5, -10},
        Coordinate{0, -10}
    };
    drawPoly(Coordinate{0, 0}, trimmingMarkLT, 0);
    drawPoly(Coordinate{PAGESIZE.width, 0}, trimmingMarkRT, 0);
    drawPoly(Coordinate{PAGESIZE.width, PAGESIZE.height}, trimmingMarkRB, 0);
    drawPoly(Coordinate{0, PAGESIZE.height}, trimmingMarkLB, 0);
}

void TemplateGenFreeCAD::drawDrawingBorderISO5457()
{
    // Inseid and Outseid Rectangal
    {
        drawRect(Coordinate{15, 5}, Coordinate{PAGESIZE.width - 5, PAGESIZE.height - 5}, 0.35);
        drawRect(Coordinate{20, 10}, Coordinate{PAGESIZE.width - 10, PAGESIZE.height - 10}, 0.7);
    }

    // Centermarks
    {
        if(CENTERINGMARKS.Top)
        {
            drawLine(Coordinate{PAGESIZE.width/2, 5}, Coordinate{PAGESIZE.width/2, 20}, 0.7);
        }
        else
        {
            drawLine(Coordinate{PAGESIZE.width/2, 5}, Coordinate{PAGESIZE.width/2, 10}, 0.7);
        }
        if(CENTERINGMARKS.Bottom)
        {
            drawLine(Coordinate{PAGESIZE.width/2, PAGESIZE.height - 5}, Coordinate{PAGESIZE.width/2, PAGESIZE.height - 20}, 0.7);
        }
        else
        {
            drawLine(Coordinate{PAGESIZE.width/2, PAGESIZE.height - 5}, Coordinate{PAGESIZE.width/2, PAGESIZE.height - 10}, 0.7);
        }

        if(CENTERINGMARKS.Left)
        {
            drawLine(Coordinate{15, PAGESIZE.height/2}, Coordinate{30, PAGESIZE.height/2}, 0.7);
        }
        else
        {
            drawLine(Coordinate{15, PAGESIZE.height/2}, Coordinate{20, PAGESIZE.height/2}, 0.7);
        }
        if(CENTERINGMARKS.Right)
        {
            drawLine(Coordinate{PAGESIZE.width - 5, PAGESIZE.height/2}, Coordinate{PAGESIZE.width - 20, PAGESIZE.height/2}, 0.7);
        }
        else
        {
            drawLine(Coordinate{PAGESIZE.width - 5, PAGESIZE.height/2}, Coordinate{PAGESIZE.width - 10, PAGESIZE.height/2}, 0.7);
        }
    }

    // Top and Bottom Framegrid
    {
        double halfPageWidth = PAGESIZE.width/2;
        // Lines
        qint64 index = 1;
        qint64 indexNumDigets = QString::number((PAGESIZE.width - 30) / 50).length();
        // Left
        double spaceLeft = 20 + 3.5;
        double lineX = halfPageWidth - 50;
        QList<double> indexListLeft;
        double lastLine;
        while(lineX > spaceLeft)
        {
            // Top
            drawLine(Coordinate{lineX, 5}, Coordinate{lineX, 10}, 0.35);
            // Bottom
            drawLine(Coordinate{lineX, PAGESIZE.height - 5}, Coordinate{lineX, PAGESIZE.height - 10}, 0.35);
            lastLine = lineX;
            lineX -= 50;
            indexListLeft.prepend(lineX +25);
        }

        foreach(double pos, indexListLeft)
        {
            if(pos <= spaceLeft)
            {
                pos = 10 + (lastLine - 10) / 2;
            }
            drawText(Coordinate{pos, 7.5}, QString::number(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            if(PAGESIZE.height >= 297 && PAGESIZE.width >= 297)
            {
                drawText(Coordinate{pos, PAGESIZE.height - 7.5}, QString::number(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            index++;
        }

        //Middle Text
        // Left
        drawText(Coordinate{halfPageWidth - 25, 7.5}, QString::number(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        if(PAGESIZE.height >= 297 && PAGESIZE.width >= 297)
        {
            drawText(Coordinate{halfPageWidth - 25, PAGESIZE.height - 7.5}, QString::number(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        }
        index++;
        // Right
        drawText(Coordinate{halfPageWidth + 25, 7.5}, QString::number(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        if(PAGESIZE.height >= 297 && PAGESIZE.width >= 297)
        {
            drawText(Coordinate{halfPageWidth + 25, PAGESIZE.height - 7.5}, QString::number(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        }
        index++;

        // Right
        double spaceRight = 10 + (3.5 * indexNumDigets);
        double spaceRightBottom = 10 + (3.5 * PAGESIZE.sizeString.length());
        double lastBottomLine = halfPageWidth;
        lineX = halfPageWidth + 50;
        while(lineX < PAGESIZE.width - spaceRight)
        {
            // Top
            drawLine(Coordinate{lineX, 5}, Coordinate{lineX, 10}, 0.35);
            drawText(Coordinate{lineX + 25, 7.5}, QString::number(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            //Bottom
            if(lineX < PAGESIZE.width - spaceRightBottom)
            {
                drawLine(Coordinate{lineX, PAGESIZE.height - 5}, Coordinate{lineX, PAGESIZE.height - 10}, 0.35);
                lastBottomLine = lineX;
            }

            if(lineX >= PAGESIZE.width - 60 && lastBottomLine >= PAGESIZE.width - 60)
            {
                drawText(Coordinate{lineX + 25, PAGESIZE.height - 7.5}, PAGESIZE.sizeString, "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            else if(lineX >= PAGESIZE.width - 60)
            {
                drawText(Coordinate{lastBottomLine + (PAGESIZE.width - lastBottomLine) / 2, PAGESIZE.height - 7.5}, PAGESIZE.sizeString, "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            else if(PAGESIZE.height >= 297  && lineX < PAGESIZE.width - spaceRightBottom - 50)
            {
                drawText(Coordinate{lineX + 25, PAGESIZE.height - 7.5}, QString::number(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            lineX += 50;
            index++;
        }
    }

    // Left and Right Framgrid
    {
        double halfPageHeight = PAGESIZE.height/2;
        // Lines
        qint64 index = 1;
        qint64 indexNumDigets = NumToABC((PAGESIZE.height - 30) / 50).length();
        // Top
        double spaceTop = 10 + 3.5;
        double lineY = halfPageHeight - 50;
        QList<double> indexListTop;
        double lastLine;
        while(lineY > spaceTop)
        {
            drawLine(Coordinate{15, lineY}, Coordinate{20, lineY}, 0.35);
            drawLine(Coordinate{PAGESIZE.width - 5, lineY}, Coordinate{PAGESIZE.width -  10, lineY}, 0.35);
            lastLine = lineY;
            lineY -= 50;
            indexListTop.prepend(lineY + 25);
        }

        foreach(double pos, indexListTop)
        {
            if(pos <= spaceTop)
            {
                pos = (10 + (lastLine - 10) / 2);
            }
            drawText(Coordinate{17.5, pos}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            if(PAGESIZE.width >= 297 && PAGESIZE.height >= 297)
            {
                drawText(Coordinate{PAGESIZE.width - 7.5, pos}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            index++;
        }
        // Middle
        drawText(Coordinate{17.5, halfPageHeight - 25}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        if(PAGESIZE.width >= 297 && PAGESIZE.height >= 297)
        {
            drawText(Coordinate{PAGESIZE.width - 7.5, halfPageHeight - 25}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        }
        index++;
        drawText(Coordinate{17.5, halfPageHeight + 25}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        if(PAGESIZE.width >= 297 && PAGESIZE.height >= 297)
        {
            drawText(Coordinate{PAGESIZE.width - 7.5, halfPageHeight + 25}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        }
        index++;

        // Bottom
        double spaceBottom = 10 + (3.5 * indexNumDigets);
        double lastBottomLine = halfPageHeight;
        lineY = halfPageHeight + 50;
        while(lineY < PAGESIZE.height - spaceBottom)
        {
            // Left
            double textY = 0;
            drawLine(Coordinate{15, lineY}, Coordinate{20, lineY}, 0.35);
            if(lineY > PAGESIZE.height - 60)
            {
                textY = lineY + ((PAGESIZE.height - 10) - lineY) / 2;
                drawText(Coordinate{17.5, textY}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            else
            {
                drawText(Coordinate{17.5, lineY + 25}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            // Right
            if(lineY < PAGESIZE.height - spaceBottom)
            {
                drawLine(Coordinate{PAGESIZE.width - 5, lineY}, Coordinate{PAGESIZE.width - 10, lineY}, 0.35);
                lastBottomLine = lineY;
            }
            if(PAGESIZE.width >= 297  && lineY <= PAGESIZE.height - 60 && PAGESIZE.height >= 297)
            {
                drawText(Coordinate{PAGESIZE.width - 7.5, lineY + 25}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            else if(PAGESIZE.width >= 297  && lineY > PAGESIZE.height - 60 && PAGESIZE.height >= 297)
            {
                drawText(Coordinate{PAGESIZE.width - 7.5, textY}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            lineY += 50;
            index++;
        }
    }
    TOPRIGHTDRAWINGCORNER.X = PAGESIZE.width - 10;
    TOPRIGHTDRAWINGCORNER.Y = 10;
    TOPLEFTDRAWINGCORNER.X = 20;
    TOPLEFTDRAWINGCORNER.Y = 10;
}

void TemplateGenFreeCAD::drawTitelblockISO7200()
{
    // Frame
    Coordinate topLeft = Coordinate{PAGESIZE.width - 190, PAGESIZE.height - 10 - 11 * (5 + NUMOPTLINES)};
    TOPLEFTITELBLOCKCORNER = topLeft;
    drawRect(topLeft, Coordinate{PAGESIZE.width - 10, PAGESIZE.height - 10}, 0.7);
    // Vertical
    drawLine(Coordinate{topLeft.X + 80, topLeft.Y}, Coordinate{topLeft.X + 80, PAGESIZE.height-10}, 0.35);
    drawLine(Coordinate{topLeft.X + 140, topLeft.Y}, Coordinate{topLeft.X + 140, PAGESIZE.height-10}, 0.35);
    drawLine(Coordinate{topLeft.X + 152, PAGESIZE.height - 10 - 22}, Coordinate{topLeft.X + 152, PAGESIZE.height-10}, 0.35);
    // Horizontal
    Coordinate lastLineLeft = topLeft;
    for(qint64 i = 0; i < NUMOPTLINES; i++)
    {
        if(NUMOPTLINES == 3 && i == 0)
        {
            drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt1"].Label, TITELBLOCKFIELDS["opt1"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt2"].Label, TITELBLOCKFIELDS["opt2"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt3"].Label, TITELBLOCKFIELDS["opt3"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
            drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt1"].ValueFreeCAD, TITELBLOCKFIELDS["opt1"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt2"].ValueFreeCAD, TITELBLOCKFIELDS["opt2"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt3"].ValueFreeCAD, TITELBLOCKFIELDS["opt3"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
        }
        else if((NUMOPTLINES == 3 && i == 1) || (NUMOPTLINES == 2 && i == 0))
        {
            drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt4"].Label, TITELBLOCKFIELDS["opt4"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt5"].Label, TITELBLOCKFIELDS["opt5"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt6"].Label, TITELBLOCKFIELDS["opt6"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
            drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt4"].ValueFreeCAD, TITELBLOCKFIELDS["opt4"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt5"].ValueFreeCAD, TITELBLOCKFIELDS["opt5"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt6"].ValueFreeCAD, TITELBLOCKFIELDS["opt6"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
        }
        else if((NUMOPTLINES == 3 && i == 2) || (NUMOPTLINES == 2 && i == 1) || (NUMOPTLINES == 1 && i == 0))
        {
            drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt7"].Label, TITELBLOCKFIELDS["opt4"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt8"].Label, TITELBLOCKFIELDS["opt4"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt9"].Label, TITELBLOCKFIELDS["opt4"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
            drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt7"].ValueFreeCAD, TITELBLOCKFIELDS["opt7"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt8"].ValueFreeCAD, TITELBLOCKFIELDS["opt8"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt9"].ValueFreeCAD, TITELBLOCKFIELDS["opt9"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
        }

        lastLineLeft = Coordinate{lastLineLeft.X, lastLineLeft.Y + 11};
        drawLine(lastLineLeft, Coordinate{PAGESIZE.width - 10, lastLineLeft.Y}, 0.35);
    }
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt10"].Label, TITELBLOCKFIELDS["opt10"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt11"].Label, TITELBLOCKFIELDS["opt11"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt12"].Label, TITELBLOCKFIELDS["opt12"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt10"].ValueFreeCAD, TITELBLOCKFIELDS["opt10"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt11"].ValueFreeCAD, TITELBLOCKFIELDS["opt11"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt12"].ValueFreeCAD, TITELBLOCKFIELDS["opt12"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    lastLineLeft = Coordinate{lastLineLeft.X, lastLineLeft.Y + 11};
    drawLine(lastLineLeft, Coordinate{PAGESIZE.width - 10, lastLineLeft.Y}, 0.35);

    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt13"].Label, TITELBLOCKFIELDS["opt13"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt14"].Label, TITELBLOCKFIELDS["opt14"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt15"].Label, TITELBLOCKFIELDS["opt15"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt13"].ValueFreeCAD, TITELBLOCKFIELDS["opt13"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt14"].ValueFreeCAD, TITELBLOCKFIELDS["opt14"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt15"].ValueFreeCAD, TITELBLOCKFIELDS["opt15"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    lastLineLeft = Coordinate{lastLineLeft.X, lastLineLeft.Y + 11};
    drawLine(lastLineLeft, Coordinate{PAGESIZE.width - 10, lastLineLeft.Y}, 0.35);

    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt16"].Label, TITELBLOCKFIELDS["opt16"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt17"].Label, TITELBLOCKFIELDS["opt17"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt18"].Label, TITELBLOCKFIELDS["opt18"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 7.5}, TITELBLOCKFIELDS["opt16"].ValueFreeCAD, TITELBLOCKFIELDS["opt16"].NameFreeCAD, 5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.5, true);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5 + 7.5}, TITELBLOCKFIELDS["opt17"].ValueFreeCAD, TITELBLOCKFIELDS["opt17"].NameFreeCAD, 5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.5, true);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt18"].ValueFreeCAD, TITELBLOCKFIELDS["opt18"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    lastLineLeft = Coordinate{lastLineLeft.X + 140, lastLineLeft.Y + 11};
    drawLine(lastLineLeft, Coordinate{PAGESIZE.width - 10, lastLineLeft.Y}, 0.35);

    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt19"].Label, TITELBLOCKFIELDS["opt19"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 12, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt20"].Label, TITELBLOCKFIELDS["opt20"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt19"].ValueFreeCAD, TITELBLOCKFIELDS["opt19"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 12, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt20"].ValueFreeCAD, TITELBLOCKFIELDS["opt20"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    lastLineLeft = Coordinate{lastLineLeft.X, lastLineLeft.Y + 11};
    drawLine(lastLineLeft, Coordinate{PAGESIZE.width - 10, lastLineLeft.Y}, 0.35);

    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt21"].Label, TITELBLOCKFIELDS["opt21"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 12, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt22"].Label, TITELBLOCKFIELDS["opt22"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt21"].ValueFreeCAD, TITELBLOCKFIELDS["opt21"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 12, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt22"].ValueFreeCAD, TITELBLOCKFIELDS["opt22"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);

    topLeft = Coordinate{PAGESIZE.width - 190, PAGESIZE.height - 10 - 11 * (5 + NUMOPTLINES)};
}

void TemplateGenFreeCAD::drawRevHistoryASME_Y14_35_Width180()
{
    drawRect(Coordinate{TOPRIGHTDRAWINGCORNER.X - 180, TOPRIGHTDRAWINGCORNER.Y}, Coordinate{TOPRIGHTDRAWINGCORNER.X, TOPRIGHTDRAWINGCORNER.Y + 8 + NUMREVHISTORY * 13.5}, 0.7);
    // Head
    drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 90, TOPRIGHTDRAWINGCORNER.Y + 2}, REVHISTORYFIELDS["head"].Label, REVHISTORYFIELDS["head"].NameFreeCAD + "_l", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawLine(Coordinate{TOPRIGHTDRAWINGCORNER.X, TOPRIGHTDRAWINGCORNER.Y + 4}, Coordinate{TOPRIGHTDRAWINGCORNER.X - 180, TOPRIGHTDRAWINGCORNER.Y + 4}, 0.35);
    drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 172.5, TOPRIGHTDRAWINGCORNER.Y + 6}, REVHISTORYFIELDS["opt1"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 155, TOPRIGHTDRAWINGCORNER.Y + 6}, REVHISTORYFIELDS["opt2"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 97.5, TOPRIGHTDRAWINGCORNER.Y + 6}, REVHISTORYFIELDS["opt3"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 40, TOPRIGHTDRAWINGCORNER.Y + 6}, REVHISTORYFIELDS["opt4"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 15, TOPRIGHTDRAWINGCORNER.Y + 6}, REVHISTORYFIELDS["opt5"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawLine(Coordinate{TOPRIGHTDRAWINGCORNER.X, TOPRIGHTDRAWINGCORNER.Y + 8}, Coordinate{TOPRIGHTDRAWINGCORNER.X - 180, TOPRIGHTDRAWINGCORNER.Y + 8}, 0.7);

    // Vertical Lines
    drawLine(Coordinate{TOPRIGHTDRAWINGCORNER.X - 165, TOPRIGHTDRAWINGCORNER.Y}, Coordinate{TOPRIGHTDRAWINGCORNER.X - 165, TOPRIGHTDRAWINGCORNER.Y + 8 + NUMREVHISTORY * 13.5}, 0.35);
    drawLine(Coordinate{TOPRIGHTDRAWINGCORNER.X - 145, TOPRIGHTDRAWINGCORNER.Y}, Coordinate{TOPRIGHTDRAWINGCORNER.X - 145, TOPRIGHTDRAWINGCORNER.Y + 8 + NUMREVHISTORY * 13.5}, 0.35);
    drawLine(Coordinate{TOPRIGHTDRAWINGCORNER.X - 50, TOPRIGHTDRAWINGCORNER.Y}, Coordinate{TOPRIGHTDRAWINGCORNER.X - 50, TOPRIGHTDRAWINGCORNER.Y + 8 + NUMREVHISTORY * 13.5}, 0.35);
    drawLine(Coordinate{TOPRIGHTDRAWINGCORNER.X - 30, TOPRIGHTDRAWINGCORNER.Y}, Coordinate{TOPRIGHTDRAWINGCORNER.X - 30, TOPRIGHTDRAWINGCORNER.Y + 8 + NUMREVHISTORY * 13.5}, 0.35);

    // Lines
    for(int i = 0; i < NUMREVHISTORY; i++)
    {
        drawLine(Coordinate{TOPRIGHTDRAWINGCORNER.X, TOPRIGHTDRAWINGCORNER.Y + 8 + 13.5 * i}, Coordinate{TOPRIGHTDRAWINGCORNER.X - 180, TOPRIGHTDRAWINGCORNER.Y + 8 + 13.5 * i}, 0.35);
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 172.5, TOPRIGHTDRAWINGCORNER.Y + 9.5 + 13.5 * i}, REVHISTORYFIELDS["opt1"].ValueFreeCAD, TITELBLOCKFIELDS["opt1"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 155, TOPRIGHTDRAWINGCORNER.Y + 9.5 + 13.5 * i}, REVHISTORYFIELDS["opt2"].ValueFreeCAD, TITELBLOCKFIELDS["opt2"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 97.5, TOPRIGHTDRAWINGCORNER.Y + 9.5 + 13.5 * i}, REVHISTORYFIELDS["opt3"].ValueFreeCAD, TITELBLOCKFIELDS["opt3"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 40, TOPRIGHTDRAWINGCORNER.Y + 9.5 + 13.5 * i}, REVHISTORYFIELDS["opt4"].ValueFreeCAD, TITELBLOCKFIELDS["opt4"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 15, TOPRIGHTDRAWINGCORNER.Y + 9.5 + 13.5 * i}, REVHISTORYFIELDS["opt5"].ValueFreeCAD, TITELBLOCKFIELDS["opt5"].NameFreeCAD, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, true, i);
    }
}

void TemplateGenFreeCAD::drawFoldLines(double depth)
{
    switch (PAGESTYLE)
    {
    case PageStyle::ISO5457_ISO7200:
        if(FOLDLINETARGET.sizeString == "A4P with border" && PAGESIZE.height >= 297 && PAGESIZE.width >= 210)
        {
            double indexWidth = 0;
            double indexWidthMax = PAGESIZE.width;
            // Left upper corner
            if(PAGESIZE.height > 297)
            {
                drawLine(Coordinate{105, 0}, Coordinate{105, depth}, 0.35);
            }

            // Vertical
            // First line (left)
            indexWidth += 210;
            drawVerFoldLine(indexWidth, depth);
            // Last line (right)
            indexWidthMax -= 190;
            drawVerFoldLine(indexWidthMax, depth);

            while (indexWidth < indexWidthMax - (190 * 2))
            {
                indexWidth += 190;
                drawVerFoldLine(indexWidth, depth);
            }

            double smalFoldX = indexWidth + (indexWidthMax - indexWidth) / 2;
            if(smalFoldX != indexWidthMax && smalFoldX < indexWidthMax)
            {
                drawVerFoldLine(smalFoldX, depth);
            }

            // Horizontal
            double indexHeight = PAGESIZE.height - 297;
            while(indexHeight > 0)
            {
                drawHorFoldLine(indexHeight, depth);
                indexHeight -= 297;
            }

        }
        break;
    }
}

void TemplateGenFreeCAD::drawSmallPartsList()
{
    double listHeight = 8 + ((2.5 * 1.5) * NUMLINESMALLPARTSLIST + 3) * NUMPARTSSMALLPARTSLIST;
    double fildHeight = (2.5 * 1.5) * NUMLINESMALLPARTSLIST + 3;
    Coordinate topLeft = Coordinate{TOPLEFTITELBLOCKCORNER.X, TOPLEFTITELBLOCKCORNER.Y - listHeight};
    drawRect(topLeft, Coordinate{TOPRIGHTDRAWINGCORNER.X, TOPLEFTITELBLOCKCORNER.Y}, 0.7);
    double width = TOPRIGHTDRAWINGCORNER.X - TOPLEFTITELBLOCKCORNER.X;
    drawLine(Coordinate{topLeft.X + width * (double(1)/18), topLeft.Y}, Coordinate{topLeft.X + width * (double(1)/18), TOPLEFTITELBLOCKCORNER.Y}, 0.35);
    drawLine(Coordinate{topLeft.X + width * (double(5)/36), topLeft.Y}, Coordinate{topLeft.X + width * (double(5)/36), TOPLEFTITELBLOCKCORNER.Y}, 0.35);
    drawLine(Coordinate{topLeft.X + width * (double(7)/36), topLeft.Y}, Coordinate{topLeft.X + width * (double(7)/36), TOPLEFTITELBLOCKCORNER.Y}, 0.35);
    drawLine(Coordinate{topLeft.X + width * (double(21)/36), topLeft.Y}, Coordinate{topLeft.X + width * (double(21)/36), TOPLEFTITELBLOCKCORNER.Y}, 0.35);
    for(int i = 1; i <= NUMPARTSSMALLPARTSLIST; i++)
    {
        QStringList opt1Val;
        QStringList opt2Val;
        QStringList opt3Val;
        QStringList opt4Val;
        QStringList opt5Val;
        for(int j = 0; j < NUMLINESMALLPARTSLIST; j++)
        {
            opt1Val.append(SMALLPARTSLISTFIELDS["opt1"].ValueFreeCAD.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt2Val.append(SMALLPARTSLISTFIELDS["opt2"].ValueFreeCAD.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt3Val.append(SMALLPARTSLISTFIELDS["opt3"].ValueFreeCAD.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt4Val.append(SMALLPARTSLISTFIELDS["opt4"].ValueFreeCAD.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt5Val.append(SMALLPARTSLISTFIELDS["opt5"].ValueFreeCAD.at(0) + QString::number(i) + NumToABC(j).at(0));
        }
        drawText(Coordinate{topLeft.X + (width * (double(1)/18)) / 2, topLeft.Y + (fildHeight * (i - 1)) + fildHeight / 2 + 0.5}, opt1Val, SMALLPARTSLISTFIELDS["opt1"].NameFreeCAD, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true);
        drawText(Coordinate{topLeft.X + width * (double(1)/18) + (width * (double(3)/36)) / 2, topLeft.Y + (fildHeight * (i - 1)) + fildHeight / 2 + 0.5}, opt2Val, SMALLPARTSLISTFIELDS["opt2"].NameFreeCAD, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{topLeft.X + width * (double(5)/36) + (width * (double(2)/36)) / 2, topLeft.Y + (fildHeight * (i - 1)) + fildHeight / 2 + 0.5}, opt3Val, SMALLPARTSLISTFIELDS["opt3"].NameFreeCAD, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{topLeft.X + width * (double(7)/36) + (width * (double(14)/36)) / 2, topLeft.Y + (fildHeight * (i - 1)) + fildHeight / 2 + 0.5}, opt4Val, SMALLPARTSLISTFIELDS["opt4"].NameFreeCAD, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{topLeft.X + width * (double(21)/36) + (width * (double(15)/36)) / 2, topLeft.Y + (fildHeight * (i - 1)) + fildHeight / 2 + 0.5}, opt5Val, SMALLPARTSLISTFIELDS["opt5"].NameFreeCAD, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawLine(Coordinate{topLeft.X, topLeft.Y + (fildHeight * i)}, Coordinate{TOPRIGHTDRAWINGCORNER.X, topLeft.Y + (fildHeight * i)}, 0.35);
    }
    drawText(Coordinate{topLeft.X + (width * (double(1)/18)) / 2, TOPLEFTITELBLOCKCORNER.Y - 6}, SMALLPARTSLISTFIELDS["opt1"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{topLeft.X + width * (double(1)/18) + (width * (double(3)/36)) / 2, TOPLEFTITELBLOCKCORNER.Y - 6}, SMALLPARTSLISTFIELDS["opt2"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{topLeft.X + width * (double(5)/36) + (width * (double(2)/36)) / 2, TOPLEFTITELBLOCKCORNER.Y - 6}, SMALLPARTSLISTFIELDS["opt3"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{topLeft.X + width * (double(7)/36) + (width * (double(14)/36)) / 2, TOPLEFTITELBLOCKCORNER.Y - 6}, SMALLPARTSLISTFIELDS["opt4"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{topLeft.X + width * (double(21)/36) + (width * (double(15)/36)) / 2, TOPLEFTITELBLOCKCORNER.Y - 6}, SMALLPARTSLISTFIELDS["opt5"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawLine(Coordinate{topLeft.X, topLeft.Y + (fildHeight * NUMPARTSSMALLPARTSLIST) + 4}, Coordinate{TOPRIGHTDRAWINGCORNER.X, topLeft.Y + (fildHeight * NUMPARTSSMALLPARTSLIST) + 4}, 0.35);
    drawText(Coordinate{topLeft.X + (width * (double(1)/18)) / 2, TOPLEFTITELBLOCKCORNER.Y - 2}, "1", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{topLeft.X + width * (double(1)/18) + (width * (double(3)/36)) / 2, TOPLEFTITELBLOCKCORNER.Y - 2}, "2", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{topLeft.X + width * (double(5)/36) + (width * (double(2)/36)) / 2, TOPLEFTITELBLOCKCORNER.Y - 2}, "3", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{topLeft.X + width * (double(7)/36) + (width * (double(14)/36)) / 2, TOPLEFTITELBLOCKCORNER.Y - 2}, "4", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{topLeft.X + width * (double(21)/36) + (width * (double(15)/36)) / 2, TOPLEFTITELBLOCKCORNER.Y - 2}, "5", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
}

void TemplateGenFreeCAD::drawFullSheetPartsList()
{
    double width = TOPRIGHTDRAWINGCORNER.X - TOPLEFTDRAWINGCORNER.X;
    double left = TOPLEFTDRAWINGCORNER.X;
    double right = TOPRIGHTDRAWINGCORNER.X;
    double top = TOPRIGHTDRAWINGCORNER.Y;
    double bottom = TOPLEFTITELBLOCKCORNER.Y;
    double fieldHeight = (2.5 * 1.5) * NUMLINESFULLSHEETPARTSLIST + 3;
    // Vertival
    drawLine(Coordinate{left + width * (2/double(36)), top}, Coordinate{left + width * (2/double(36)), bottom}, 0.35);
    drawLine(Coordinate{left + width * (5/double(36)), top}, Coordinate{left + width * (5/double(36)), bottom}, 0.35);
    drawLine(Coordinate{left + width * (7/double(36)), top}, Coordinate{left + width * (7/double(36)), bottom}, 0.35);
    drawLine(Coordinate{left + width * (21/double(36)), top}, Coordinate{left + width * (21/double(36)), bottom}, 0.35);
    drawLine(Coordinate{left + width * (29/double(36)), top}, Coordinate{left + width * (29/double(36)), bottom}, 0.35);

    // Head
    drawText(Coordinate{left + (width * (2/double(36))) / 2, top + 2}, "1", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{left + width * (2/double(36)) + (width * (3/double(36))) / 2, top + 2}, "2", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{left + width * (5/double(36)) + (width * (2/double(36))) / 2, top + 2}, "3", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{left + width * (7/double(36)) + (width * (14/double(36))) / 2, top + 2}, "4", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{left + width * (21/double(36)) + (width * (8/double(36))) / 2, top + 2}, "5", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{left + width * (29/double(36)) + (width * (7/double(36))) / 2, top + 2}, "6", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawLine(Coordinate{left, top + 4}, Coordinate{right, top + 4}, 0.35);
    drawText(Coordinate{left + (width * (2/double(36))) / 2, top + 6}, FULLSHEETPARTSLISTFIELDS["opt1"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{left + width * (2/double(36)) + (width * (3/double(36))) / 2, top + 6}, FULLSHEETPARTSLISTFIELDS["opt2"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{left + width * (5/double(36)) + (width * (2/double(36))) / 2, top + 6}, FULLSHEETPARTSLISTFIELDS["opt3"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{left + width * (7/double(36)) + (width * (14/double(36))) / 2, top + 6}, FULLSHEETPARTSLISTFIELDS["opt4"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{left + width * (21/double(36)) + (width * (8/double(36))) / 2, top + 6}, FULLSHEETPARTSLISTFIELDS["opt5"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{left + width * (29/double(36)) + (width * (7/double(36))) / 2, top + 6}, FULLSHEETPARTSLISTFIELDS["opt6"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawLine(Coordinate{left, top + 8}, Coordinate{right, top + 8}, 0.7);
    drawLine(Coordinate{left, bottom}, Coordinate{right, bottom}, 0.7);
    top += 8;
    double indexTop = top + fieldHeight;
    int i = 0;
    while(indexTop <= bottom)
    {
        QStringList opt1Val;
        QStringList opt2Val;
        QStringList opt3Val;
        QStringList opt4Val;
        QStringList opt5Val;
        QStringList opt6Val;
        for(int j = 0; j < NUMLINESFULLSHEETPARTSLIST; j++)
        {
            opt1Val.append(FULLSHEETPARTSLISTFIELDS["opt1"].ValueFreeCAD.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt2Val.append(FULLSHEETPARTSLISTFIELDS["opt2"].ValueFreeCAD.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt3Val.append(FULLSHEETPARTSLISTFIELDS["opt3"].ValueFreeCAD.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt4Val.append(FULLSHEETPARTSLISTFIELDS["opt4"].ValueFreeCAD.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt5Val.append(FULLSHEETPARTSLISTFIELDS["opt5"].ValueFreeCAD.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt6Val.append(FULLSHEETPARTSLISTFIELDS["opt6"].ValueFreeCAD.at(0) + QString::number(i) + NumToABC(j).at(0));
        }
        drawText(Coordinate{left + (width * (2/double(36))) / 2, indexTop - fieldHeight/2}, opt1Val, FULLSHEETPARTSLISTFIELDS["opt1"].NameFreeCAD, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true);
        drawText(Coordinate{left + width * (2/double(36)) + (width * (3/double(36))) / 2, indexTop - fieldHeight/2}, opt2Val, FULLSHEETPARTSLISTFIELDS["opt2"].NameFreeCAD, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{left + width * (5/double(36)) + (width * (2/double(36))) / 2, indexTop - fieldHeight/2}, opt3Val, FULLSHEETPARTSLISTFIELDS["opt3"].NameFreeCAD, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{left + width * (7/double(36)) + (width * (14/double(36))) / 2, indexTop - fieldHeight/2}, opt4Val, FULLSHEETPARTSLISTFIELDS["opt4"].NameFreeCAD, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{left + width * (21/double(36)) + (width * (8/double(36))) / 2, indexTop - fieldHeight/2}, opt5Val, FULLSHEETPARTSLISTFIELDS["opt5"].NameFreeCAD, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{left + width * (29/double(36)) + (width * (7/double(36))) / 2, indexTop - fieldHeight/2}, opt6Val, FULLSHEETPARTSLISTFIELDS["opt6"].NameFreeCAD, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawLine(Coordinate{left, indexTop}, Coordinate{right, indexTop}, 0.35);
        indexTop +=fieldHeight;
        i++;
    }
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
        qDebug() << "Cannot read file" << file.errorString();
        exit(0);
    }

    QDomDocument xmlBOM;
    xmlBOM.setContent(&file);
    QDomElement root=xmlBOM.documentElement();

    root.setTagName("g");
    root.setAttribute("transform", "translate(" + QString::number(PAGESIZE.width - 111 - widthMM) + " " + QString::number(PAGESIZE.height - 11 - heightMM) + ") scale(" + QString::number(widthMM/root.attribute("width").remove("mm").toDouble()) + ")");
    ROOT. appendChild(root);
}

void TemplateGenFreeCAD::drawISO5457_ISO7200()
{
    if(TRIMMINGMARKS)
    {
        drawTrimmingMarksISO5457();
    }
    drawDrawingBorderISO5457();

    drawTitelblockISO7200();
}

TemplateGenFreeCAD::TemplateGenFreeCAD(QObject *parent) : QObject(parent)
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

void TemplateGenFreeCAD::draw()
{
    if(init())
    {
        qint64 foldlinesDepth = 0;
        switch (PAGESTYLE)
        {
        case PageStyle::ISO5457_ISO7200:
            drawISO5457_ISO7200();
            foldlinesDepth = 5;
            break;
        }
        if(REVHISTORY)
        {
            switch (REVHISTORYSTYLE)
            {
            case RevHistoryStyle::ASME_Y14_35_Width180:
                drawRevHistoryASME_Y14_35_Width180();
                break;
            }
        }

        if(FOLDLINES)
        {
            drawFoldLines(foldlinesDepth);
        }

        if(FULLSHEETPARTSLIST)
        {
            drawFullSheetPartsList();
        }

        if(SMALLPARTSLIST)
        {
            drawSmallPartsList();
        }

        if(LOGO)
        {
            drawLogoTitelblockISO7200();
        }
    }
}

const QString &TemplateGenFreeCAD::getDIR() const
{
    return DIR;
}

void TemplateGenFreeCAD::setDIR(const QString &newDIR)
{
    finisheD.diR = true;
    DIR = newDIR;
}

const PageSize &TemplateGenFreeCAD::getPAGESIZE() const
{
    return PAGESIZE;
}

void TemplateGenFreeCAD::setPAGESIZE(const PageSize &newPAGESIZE)
{
    finisheD.pagesizeE = true;
    PAGESIZE = newPAGESIZE;
}

PageStyle TemplateGenFreeCAD::getPAGESTYLE() const
{
    return PAGESTYLE;
}

void TemplateGenFreeCAD::setPAGESTYLE(PageStyle newPAGESTYLE)
{
    finisheD.pagestylE = true;
    PAGESTYLE = newPAGESTYLE;
}

qint64 TemplateGenFreeCAD::getNUMOPTLINES() const
{
    return NUMOPTLINES;
}

void TemplateGenFreeCAD::setNUMOPTLINES(qint64 newNUMOPTLINES)
{
    NUMOPTLINES = newNUMOPTLINES;
    finisheD.numoptlineS = true;
}

const QMap<QString, TitelblockField> &TemplateGenFreeCAD::getTITELBLOCKFIELDS() const
{
    return TITELBLOCKFIELDS;
}

void TemplateGenFreeCAD::setTITELBLOCKFIELDS(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS)
{
    TITELBLOCKFIELDS = newTITELBLOCKFIELDS;
    finisheD.titelblockfieldS = true;
}

bool TemplateGenFreeCAD::getTRIMMINGMARKS() const
{
    return TRIMMINGMARKS;
}

void TemplateGenFreeCAD::setTRIMMINGMARKS(bool newTRIMMINGMARKS)
{
    TRIMMINGMARKS = newTRIMMINGMARKS;
    finisheD.trimmingmarkS = true;
}

RevHistoryStyle TemplateGenFreeCAD::getREVHISTORYSTYLE() const
{
    return REVHISTORYSTYLE;
}

void TemplateGenFreeCAD::setREVHISTORYSTYLE(RevHistoryStyle newREVHISTORYSTYLE)
{
    REVHISTORYSTYLE = newREVHISTORYSTYLE;
    finisheD.revhistorystylE = true;
}

const QMap<QString, TitelblockField> &TemplateGenFreeCAD::getREVHISTORYFIELDS() const
{
    return REVHISTORYFIELDS;
}

void TemplateGenFreeCAD::setREVHISTORYFIELDS(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS)
{
    REVHISTORYFIELDS = newREVHISTORYFIELDS;
    finisheD.revhistoryfieldS = true;
}

qint64 TemplateGenFreeCAD::getNUMREVHISTORY() const
{
    return NUMREVHISTORY;
}

void TemplateGenFreeCAD::setNUMREVHISTORY(qint64 newNUMREVHISTORY)
{
    NUMREVHISTORY = newNUMREVHISTORY;
    finisheD.numrevhistorY = true;
}

bool TemplateGenFreeCAD::getREVHISTORY() const
{
    return REVHISTORY;
}

void TemplateGenFreeCAD::setREVHISTORY(bool newREVHISTORY)
{
    REVHISTORY = newREVHISTORY;
    finisheD.revhistorY = true;
}

bool TemplateGenFreeCAD::getFOLDLINES() const
{
    return FOLDLINES;
}

void TemplateGenFreeCAD::setFOLDLINES(bool newFOLDLINES)
{
    FOLDLINES = newFOLDLINES;
    finisheD.foldlineS = true;
}

const PageSize &TemplateGenFreeCAD::getFOLDLINETARGET() const
{
    return FOLDLINETARGET;
}

void TemplateGenFreeCAD::setFOLDLINETARGET(const PageSize &newFOLDLINETARGET)
{
    FOLDLINETARGET = newFOLDLINETARGET;
    finisheD.foldlinestargeT = true;
}

quint64 TemplateGenFreeCAD::getNUMPARTSSMALLPARTSLIST() const
{
    return NUMPARTSSMALLPARTSLIST;
}

void TemplateGenFreeCAD::setNUMPARTSSMALLPARTSLIST(quint64 newNUMPARTSSMALLPARTSLIST)
{
    NUMPARTSSMALLPARTSLIST = newNUMPARTSSMALLPARTSLIST;
    finisheD.numpartssmallpartslisT = true;
}

bool TemplateGenFreeCAD::getSMALLPARTSLIST() const
{
    return SMALLPARTSLIST;
}

void TemplateGenFreeCAD::setSMALLPARTSLIST(bool newSMALLPARTSLIST)
{
    SMALLPARTSLIST = newSMALLPARTSLIST;
    finisheD.smallpartslisT = true;
}

quint64 TemplateGenFreeCAD::getNUMLINESMALLPARTSLIST() const
{
    return NUMLINESMALLPARTSLIST;
}

void TemplateGenFreeCAD::setNUMLINESMALLPARTSLIST(quint64 newNUMLINESMALLPARTSLIST)
{
    NUMLINESMALLPARTSLIST = newNUMLINESMALLPARTSLIST;
    finisheD.numlinessmallpartslisT = true;
}

const QMap<QString, TitelblockField> &TemplateGenFreeCAD::getSMALLPARTSLISTFIELDS() const
{
    return SMALLPARTSLISTFIELDS;
}

void TemplateGenFreeCAD::setSMALLPARTSLISTFIELDS(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS)
{
    SMALLPARTSLISTFIELDS = newSMALLPARTSLISTFIELDS;
    finisheD.smallpartslistfieldS = true;
}

bool TemplateGenFreeCAD::getFULLSHEETPARTSLIST() const
{
    return FULLSHEETPARTSLIST;
}

void TemplateGenFreeCAD::setFULLSHEETPARTSLIST(bool newFULLSHEETPARTSLIST)
{
    FULLSHEETPARTSLIST = newFULLSHEETPARTSLIST;
    finisheD.fullsheetpartslisT = true;
}

quint64 TemplateGenFreeCAD::getNUMLINESFULLSHEETPARTSLIST() const
{
    return NUMLINESFULLSHEETPARTSLIST;
}

void TemplateGenFreeCAD::setNUMLINESFULLSHEETPARTSLIST(quint64 newNUMLINESFULLSHEETPARTSLIST)
{
    NUMLINESFULLSHEETPARTSLIST = newNUMLINESFULLSHEETPARTSLIST;
    finisheD.numlinesfullsheetpartslisT = true;
}

const QMap<QString, TitelblockField> &TemplateGenFreeCAD::getFULLSHEETPARTSLISTFIELDS() const
{
    return FULLSHEETPARTSLISTFIELDS;
}

void TemplateGenFreeCAD::setFULLSHEETPARTSLISTFIELDS(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS)
{
    FULLSHEETPARTSLISTFIELDS = newFULLSHEETPARTSLISTFIELDS;
    finisheD.fullsheetpartlistfieldS = true;
}
