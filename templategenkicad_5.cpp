#include "templategenkicad_5.h"

#include <QSvgRenderer>
#include <QPainter>
#include <QImage>
#include <QBuffer>

const QString &TemplateGenKiCAD_5::getLOGODIR() const
{
    return LOGODIR;
}

void TemplateGenKiCAD_5::setLOGODIR(const QString &newLOGODIR)
{
    LOGODIR = newLOGODIR;
    finisheD.logodiR = true;
}

bool TemplateGenKiCAD_5::getLOGO() const
{
    return LOGO;
}

void TemplateGenKiCAD_5::setLOGO(bool newLOGO)
{
    LOGO = newLOGO;
    finisheD.logO = true;
}

const QString &TemplateGenKiCAD_5::getSHEETNAME() const
{
    return SHEETNAME;
}

void TemplateGenKiCAD_5::setSHEETNAME(const QString &newSHEETNAME)
{
    SHEETNAME = newSHEETNAME;
    finisheD.sheetnamE = true;
}

bool TemplateGenKiCAD_5::init()
{
    if((PAGESIZE.height / 2 < 10 + (11 * (5 + NUMOPTLINES) + 8 + ((2.5 * 1.5) * NUMLINESMALLPARTSLIST + 3) * NUMPARTSSMALLPARTSLIST)) && SMALLPARTSLIST)
    {
        CENTERINGMARKS.Reight = false;
        if(PAGESIZE.width / 2 < 190)
        {
            CENTERINGMARKS.Left = false;
        }
    }
    if(FULLSHEETPARTSLIST)
    {
        CENTERINGMARKS.Reight = false;
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
        CENTERINGMARKS.Reight = false;
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
            FILE->write("(page_layout\n  (setup (textsize 0 0)(linewidth 0)(textlinewidth 0)\n  (left_margin 0)(right_margin 0)(top_margin 0)(bottom_margin 0))\n");
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

QString TemplateGenKiCAD_5::createFileName()
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

    ret +=  "_ki5.kicad_wks";
    return ret;
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

void TemplateGenKiCAD_5::drawPoly(Coordinate position, double rotaition, QList<Coordinate> points, double lineWidth)
{
    QString lineString = "  (polygon (name " + QString::number(NAMEINDEX) + ") (pos " + QString::number(position.X) + " " + QString::number(position.Y) + " ltcorner) (rotate " + QString::number(rotaition) + ") (linewidth " + QString::number(lineWidth) + ")\n";
    lineString += "    (pts ";
    foreach(Coordinate pt, points)
    {
        lineString += "(xy " + QString::number(pt.X) + " " + QString::number(pt.Y) + ") ";
    }
    lineString += "))\n";
    FILE->write(lineString.toLatin1());
    NAMEINDEX++;
}

qint64 TemplateGenKiCAD_5::drawText(Coordinate position, QString text, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth)
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

qint64 TemplateGenKiCAD_5::drawText(Coordinate position, QStringList text, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, qint64 index)
{
    qint64 ret = 0;
    if(text.length() == 1)
    {
        ret =  drawText(position, text[0].replace("&{N}", QString::number(index + 1)), textSize, textHeightAnchor, textWidthAnchor, lineWidth);
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
                ret += drawText(Coordinate{position.X, height}, txt.replace("&{N}", QString::number(index + 1)), textSize, TextHeightAnchor::Top, textWidthAnchor, lineWidth);
            }
            break;
        case TextHeightAnchor::Middle:
            for(int i = 0; i < text.length(); i++)
            {
                double height = position.Y - (heightTotal / 2) + lineHeight * i;
                QString txt = text.at(i);
                ret +=  drawText(Coordinate{position.X, height}, txt.replace("&{N}", QString::number(index + 1)), textSize, TextHeightAnchor::Top, textWidthAnchor, lineWidth);
            }
            break;
        case TextHeightAnchor::Bottom:
            for(int i = 0; i < text.length(); i++)
            {
                double height = position.Y - heightTotal + lineHeight * i;
                QString txt = text.at(i);
                ret +=  drawText(Coordinate{position.X, height}, txt.replace("&{N}", QString::number(index + 1)), textSize, TextHeightAnchor::Top, textWidthAnchor, lineWidth);
            }
            break;
        }
    }
    return -1;
}

void TemplateGenKiCAD_5::drawVerFoldLine(double x, double depth)
{
    drawLine(Coordinate{x, 0}, Coordinate{x, depth}, 0.35);
    drawLine(Coordinate{x, PAGESIZE.height}, Coordinate{x, PAGESIZE.height - depth}, 0.35);
}

void TemplateGenKiCAD_5::drawHorFoldLine(double y, double depth)
{
    drawLine(Coordinate{0, y}, Coordinate{depth, y}, 0.35);
    drawLine(Coordinate{PAGESIZE.width, y}, Coordinate{PAGESIZE.width - depth, y}, 0.35);
}

void TemplateGenKiCAD_5::drawTrimmingMarksISO5457()
{
    QList<Coordinate> trimmingMark
    {
        Coordinate{0, 0},
        Coordinate{10, 0},
        Coordinate{10, 5},
        Coordinate{5, 5},
        Coordinate{5, 10},
        Coordinate{0, 10}
    };
    drawPoly(Coordinate{0, 0}, 0, trimmingMark, 0);
    drawPoly(Coordinate{PAGESIZE.width, 0}, -90, trimmingMark, 0);
    drawPoly(Coordinate{PAGESIZE.width, PAGESIZE.height}, -180, trimmingMark, 0);
    drawPoly(Coordinate{0, PAGESIZE.height}, -270, trimmingMark, 0);
}

void TemplateGenKiCAD_5::drawDrawingBorderISO5457()
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
        if(CENTERINGMARKS.Reight)
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
            drawText(Coordinate{pos, 7.5}, QString::number(index), 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            if(PAGESIZE.height >= 297 && PAGESIZE.width >= 297)
            {
                drawText(Coordinate{pos, PAGESIZE.height - 7.5}, QString::number(index), 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            index++;
        }

        //Middle Text
        // Left
        drawText(Coordinate{halfPageWidth - 25, 7.5}, QString::number(index), 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        if(PAGESIZE.height >= 297 && PAGESIZE.width >= 297)
        {
            drawText(Coordinate{halfPageWidth - 25, PAGESIZE.height - 7.5}, QString::number(index), 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        }
        index++;
        // Right
        drawText(Coordinate{halfPageWidth + 25, 7.5}, QString::number(index), 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        if(PAGESIZE.height >= 297 && PAGESIZE.width >= 297)
        {
            drawText(Coordinate{halfPageWidth + 25, PAGESIZE.height - 7.5}, QString::number(index), 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
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
            drawText(Coordinate{lineX + 25, 7.5}, QString::number(index), 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            //Bottom
            if(lineX < PAGESIZE.width - spaceRightBottom)
            {
                drawLine(Coordinate{lineX, PAGESIZE.height - 5}, Coordinate{lineX, PAGESIZE.height - 10}, 0.35);
                lastBottomLine = lineX;
            }

            if(lineX >= PAGESIZE.width - 60 && lastBottomLine >= PAGESIZE.width - 60)
            {
                drawText(Coordinate{lineX + 25, PAGESIZE.height - 7.5}, PAGESIZE.sizeString, 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            else if(lineX >= PAGESIZE.width - 60)
            {
                drawText(Coordinate{lastBottomLine + (PAGESIZE.width - lastBottomLine) / 2, PAGESIZE.height - 7.5}, PAGESIZE.sizeString, 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            else if(PAGESIZE.height >= 297  && lineX < PAGESIZE.width - spaceRightBottom - 50)
            {
                drawText(Coordinate{lineX + 25, PAGESIZE.height - 7.5}, QString::number(index), 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
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
            drawText(Coordinate{17.5, pos}, NumToABC(index), 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            if(PAGESIZE.width >= 297 && PAGESIZE.height >= 297)
            {
                drawText(Coordinate{PAGESIZE.width - 7.5, pos}, NumToABC(index), 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            index++;
        }
        // Middle
        drawText(Coordinate{17.5, halfPageHeight - 25}, NumToABC(index), 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        if(PAGESIZE.width >= 297 && PAGESIZE.height >= 297)
        {
            drawText(Coordinate{PAGESIZE.width - 7.5, halfPageHeight - 25}, NumToABC(index), 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        }
        index++;
        drawText(Coordinate{17.5, halfPageHeight + 25}, NumToABC(index), 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        if(PAGESIZE.width >= 297 && PAGESIZE.height >= 297)
        {
            drawText(Coordinate{PAGESIZE.width - 7.5, halfPageHeight + 25}, NumToABC(index), 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
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
                drawText(Coordinate{17.5, textY}, NumToABC(index), 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            else
            {
                drawText(Coordinate{17.5, lineY + 25}, NumToABC(index), 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            // Right
            if(lineY < PAGESIZE.height - spaceBottom)
            {
                drawLine(Coordinate{PAGESIZE.width - 5, lineY}, Coordinate{PAGESIZE.width - 10, lineY}, 0.35);
                lastBottomLine = lineY;
            }
            if(PAGESIZE.width >= 297  && lineY <= PAGESIZE.height - 60 && PAGESIZE.height >= 297)
            {
                drawText(Coordinate{PAGESIZE.width - 7.5, lineY + 25}, NumToABC(index), 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            else if(PAGESIZE.width >= 297  && lineY > PAGESIZE.height - 60 && PAGESIZE.height >= 297)
            {
                drawText(Coordinate{PAGESIZE.width - 7.5, textY}, NumToABC(index), 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
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

void TemplateGenKiCAD_5::drawTitelblockISO7200()
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
            drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt1"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt2"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt3"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
            drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt1"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt2"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt3"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25);
        }
        else if((NUMOPTLINES == 3 && i == 1) || (NUMOPTLINES == 2 && i == 0))
        {
            drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt4"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt5"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt6"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
            drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt4"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt5"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt6"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25);
        }
        else if((NUMOPTLINES == 3 && i == 2) || (NUMOPTLINES == 2 && i == 1) || (NUMOPTLINES == 1 && i == 0))
        {
            drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt7"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt8"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt9"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
            drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt7"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt8"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt9"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25);
        }

        lastLineLeft = Coordinate{lastLineLeft.X, lastLineLeft.Y + 11};
        drawLine(lastLineLeft, Coordinate{PAGESIZE.width - 10, lastLineLeft.Y}, 0.35);
    }
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt10"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt11"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt12"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt10"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt11"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt12"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25);
    lastLineLeft = Coordinate{lastLineLeft.X, lastLineLeft.Y + 11};
    drawLine(lastLineLeft, Coordinate{PAGESIZE.width - 10, lastLineLeft.Y}, 0.35);

    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt13"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt14"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt15"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt13"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt14"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt15"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25);
    lastLineLeft = Coordinate{lastLineLeft.X, lastLineLeft.Y + 11};
    drawLine(lastLineLeft, Coordinate{PAGESIZE.width - 10, lastLineLeft.Y}, 0.35);

    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt16"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt17"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt18"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 7.5}, TITELBLOCKFIELDS["opt16"].ValueKiCAD5, 5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.5);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5 + 7.5}, TITELBLOCKFIELDS["opt17"].ValueKiCAD5, 5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.5);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt18"].ValueKiCAD5, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
    lastLineLeft = Coordinate{lastLineLeft.X + 140, lastLineLeft.Y + 11};
    drawLine(lastLineLeft, Coordinate{PAGESIZE.width - 10, lastLineLeft.Y}, 0.35);

    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt19"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 12, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt20"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt19"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 12, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt20"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
    lastLineLeft = Coordinate{lastLineLeft.X, lastLineLeft.Y + 11};
    drawLine(lastLineLeft, Coordinate{PAGESIZE.width - 10, lastLineLeft.Y}, 0.35);

    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt21"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 12, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt22"].Label, 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18);
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt21"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 12, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt22"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25);

    topLeft = Coordinate{PAGESIZE.width - 190, PAGESIZE.height - 10 - 11 * (5 + NUMOPTLINES)};
}

void TemplateGenKiCAD_5::drawRevHistoryASME_Y14_35_Width180()
{
    drawRect(TOPRIGHTDRAWINGCORNER, Coordinate{TOPRIGHTDRAWINGCORNER.X - 180, TOPRIGHTDRAWINGCORNER.Y + 8 + NUMREVHISTORY * 13.5}, 0.7);
    // Head
    drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 90, TOPRIGHTDRAWINGCORNER.Y + 2}, REVHISTORYFIELDS["head"].Label, 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawLine(Coordinate{TOPRIGHTDRAWINGCORNER.X, TOPRIGHTDRAWINGCORNER.Y + 4}, Coordinate{TOPRIGHTDRAWINGCORNER.X - 180, TOPRIGHTDRAWINGCORNER.Y + 4}, 0.35);
    drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 172.5, TOPRIGHTDRAWINGCORNER.Y + 6}, REVHISTORYFIELDS["opt1"].Label, 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 155, TOPRIGHTDRAWINGCORNER.Y + 6}, REVHISTORYFIELDS["opt2"].Label, 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 97.5, TOPRIGHTDRAWINGCORNER.Y + 6}, REVHISTORYFIELDS["opt3"].Label, 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 40, TOPRIGHTDRAWINGCORNER.Y + 6}, REVHISTORYFIELDS["opt4"].Label, 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 15, TOPRIGHTDRAWINGCORNER.Y + 6}, REVHISTORYFIELDS["opt5"].Label, 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
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
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 172.5, TOPRIGHTDRAWINGCORNER.Y + 9.5 + 13.5 * i}, REVHISTORYFIELDS["opt1"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, i);
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 155, TOPRIGHTDRAWINGCORNER.Y + 9.5 + 13.5 * i}, REVHISTORYFIELDS["opt2"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, i);
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 97.5, TOPRIGHTDRAWINGCORNER.Y + 9.5 + 13.5 * i}, REVHISTORYFIELDS["opt3"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, i);
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 40, TOPRIGHTDRAWINGCORNER.Y + 9.5 + 13.5 * i}, REVHISTORYFIELDS["opt4"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, i);
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 15, TOPRIGHTDRAWINGCORNER.Y + 9.5 + 13.5 * i}, REVHISTORYFIELDS["opt5"].ValueKiCAD5, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, i);
    }
}

void TemplateGenKiCAD_5::drawFoldLines(double depth)
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

void TemplateGenKiCAD_5::drawSmallPartsList()
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
            opt1Val.append(SMALLPARTSLISTFIELDS["opt1"].ValueKiCAD5.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt2Val.append(SMALLPARTSLISTFIELDS["opt2"].ValueKiCAD5.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt3Val.append(SMALLPARTSLISTFIELDS["opt3"].ValueKiCAD5.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt4Val.append(SMALLPARTSLISTFIELDS["opt4"].ValueKiCAD5.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt5Val.append(SMALLPARTSLISTFIELDS["opt5"].ValueKiCAD5.at(0) + QString::number(i) + NumToABC(j).at(0));
        }
        drawText(Coordinate{topLeft.X + (width * (double(1)/18)) / 2, topLeft.Y + (fildHeight * (i - 1)) + fildHeight / 2 + 0.5}, opt1Val, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25);
        drawText(Coordinate{topLeft.X + width * (double(1)/18) + (width * (double(3)/36)) / 2, topLeft.Y + (fildHeight * (i - 1)) + fildHeight / 2 + 0.5}, opt2Val, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25);
        drawText(Coordinate{topLeft.X + width * (double(5)/36) + (width * (double(2)/36)) / 2, topLeft.Y + (fildHeight * (i - 1)) + fildHeight / 2 + 0.5}, opt3Val, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25);
        drawText(Coordinate{topLeft.X + width * (double(7)/36) + (width * (double(14)/36)) / 2, topLeft.Y + (fildHeight * (i - 1)) + fildHeight / 2 + 0.5}, opt4Val, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25);
        drawText(Coordinate{topLeft.X + width * (double(21)/36) + (width * (double(15)/36)) / 2, topLeft.Y + (fildHeight * (i - 1)) + fildHeight / 2 + 0.5}, opt5Val, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25);
        drawLine(Coordinate{topLeft.X, topLeft.Y + (fildHeight * i)}, Coordinate{TOPRIGHTDRAWINGCORNER.X, topLeft.Y + (fildHeight * i)}, 0.35);
    }
    drawText(Coordinate{topLeft.X + (width * (double(1)/18)) / 2, TOPLEFTITELBLOCKCORNER.Y - 6}, SMALLPARTSLISTFIELDS["opt1"].Label, 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{topLeft.X + width * (double(1)/18) + (width * (double(3)/36)) / 2, TOPLEFTITELBLOCKCORNER.Y - 6}, SMALLPARTSLISTFIELDS["opt2"].Label, 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{topLeft.X + width * (double(5)/36) + (width * (double(2)/36)) / 2, TOPLEFTITELBLOCKCORNER.Y - 6}, SMALLPARTSLISTFIELDS["opt3"].Label, 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{topLeft.X + width * (double(7)/36) + (width * (double(14)/36)) / 2, TOPLEFTITELBLOCKCORNER.Y - 6}, SMALLPARTSLISTFIELDS["opt4"].Label, 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{topLeft.X + width * (double(21)/36) + (width * (double(15)/36)) / 2, TOPLEFTITELBLOCKCORNER.Y - 6}, SMALLPARTSLISTFIELDS["opt5"].Label, 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawLine(Coordinate{topLeft.X, topLeft.Y + (fildHeight * NUMPARTSSMALLPARTSLIST) + 4}, Coordinate{TOPRIGHTDRAWINGCORNER.X, topLeft.Y + (fildHeight * NUMPARTSSMALLPARTSLIST) + 4}, 0.35);
    drawText(Coordinate{topLeft.X + (width * (double(1)/18)) / 2, TOPLEFTITELBLOCKCORNER.Y - 2}, "1", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{topLeft.X + width * (double(1)/18) + (width * (double(3)/36)) / 2, TOPLEFTITELBLOCKCORNER.Y - 2}, "2", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{topLeft.X + width * (double(5)/36) + (width * (double(2)/36)) / 2, TOPLEFTITELBLOCKCORNER.Y - 2}, "3", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{topLeft.X + width * (double(7)/36) + (width * (double(14)/36)) / 2, TOPLEFTITELBLOCKCORNER.Y - 2}, "4", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{topLeft.X + width * (double(21)/36) + (width * (double(15)/36)) / 2, TOPLEFTITELBLOCKCORNER.Y - 2}, "5", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
}

void TemplateGenKiCAD_5::drawFullSheetPartsList()
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
    drawText(Coordinate{left + (width * (2/double(36))) / 2, top + 2}, "1", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{left + width * (2/double(36)) + (width * (3/double(36))) / 2, top + 2}, "2", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{left + width * (5/double(36)) + (width * (2/double(36))) / 2, top + 2}, "3", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{left + width * (7/double(36)) + (width * (14/double(36))) / 2, top + 2}, "4", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{left + width * (21/double(36)) + (width * (8/double(36))) / 2, top + 2}, "5", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{left + width * (29/double(36)) + (width * (7/double(36))) / 2, top + 2}, "6", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawLine(Coordinate{left, top + 4}, Coordinate{right, top + 4}, 0.35);
    drawText(Coordinate{left + (width * (2/double(36))) / 2, top + 6}, FULLSHEETPARTSLISTFIELDS["opt1"].Label, 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{left + width * (2/double(36)) + (width * (3/double(36))) / 2, top + 6}, FULLSHEETPARTSLISTFIELDS["opt2"].Label, 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{left + width * (5/double(36)) + (width * (2/double(36))) / 2, top + 6}, FULLSHEETPARTSLISTFIELDS["opt3"].Label, 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{left + width * (7/double(36)) + (width * (14/double(36))) / 2, top + 6}, FULLSHEETPARTSLISTFIELDS["opt4"].Label, 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{left + width * (21/double(36)) + (width * (8/double(36))) / 2, top + 6}, FULLSHEETPARTSLISTFIELDS["opt5"].Label, 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
    drawText(Coordinate{left + width * (29/double(36)) + (width * (7/double(36))) / 2, top + 6}, FULLSHEETPARTSLISTFIELDS["opt6"].Label, 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18);
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
            opt1Val.append(FULLSHEETPARTSLISTFIELDS["opt1"].ValueKiCAD5.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt2Val.append(FULLSHEETPARTSLISTFIELDS["opt2"].ValueKiCAD5.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt3Val.append(FULLSHEETPARTSLISTFIELDS["opt3"].ValueKiCAD5.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt4Val.append(FULLSHEETPARTSLISTFIELDS["opt4"].ValueKiCAD5.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt5Val.append(FULLSHEETPARTSLISTFIELDS["opt5"].ValueKiCAD5.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt6Val.append(FULLSHEETPARTSLISTFIELDS["opt6"].ValueKiCAD5.at(0) + QString::number(i) + NumToABC(j).at(0));
        }
        drawText(Coordinate{left + (width * (2/double(36))) / 2, indexTop - fieldHeight/2}, opt1Val, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25);
        drawText(Coordinate{left + width * (2/double(36)) + (width * (3/double(36))) / 2, indexTop - fieldHeight/2}, opt2Val, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25);
        drawText(Coordinate{left + width * (5/double(36)) + (width * (2/double(36))) / 2, indexTop - fieldHeight/2}, opt3Val, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25);
        drawText(Coordinate{left + width * (7/double(36)) + (width * (14/double(36))) / 2, indexTop - fieldHeight/2}, opt4Val, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25);
        drawText(Coordinate{left + width * (21/double(36)) + (width * (8/double(36))) / 2, indexTop - fieldHeight/2}, opt5Val, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25);
        drawText(Coordinate{left + width * (29/double(36)) + (width * (7/double(36))) / 2, indexTop - fieldHeight/2}, opt6Val, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25);
        drawLine(Coordinate{left, indexTop}, Coordinate{right, indexTop}, 0.35);
        indexTop +=fieldHeight;
        i++;
    }
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

void TemplateGenKiCAD_5::drawISO5457_ISO7200()
{
    if(TRIMMINGMARKS)
    {
        drawTrimmingMarksISO5457();
    }
    drawDrawingBorderISO5457();

    drawTitelblockISO7200();
}

TemplateGenKiCAD_5::TemplateGenKiCAD_5(QObject *parent) : QObject(parent)
{
}

TemplateGenKiCAD_5::~TemplateGenKiCAD_5()
{
    FILE->write(")\n");
    FILE->flush();
    free(FILE);
}

void TemplateGenKiCAD_5::draw()
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

const QString &TemplateGenKiCAD_5::getDIR() const
{
    return DIR;
}

void TemplateGenKiCAD_5::setDIR(const QString &newDIR)
{
    finisheD.diR = true;
    DIR = newDIR;
}

const PageSize &TemplateGenKiCAD_5::getPAGESIZE() const
{
    return PAGESIZE;
}

void TemplateGenKiCAD_5::setPAGESIZE(const PageSize &newPAGESIZE)
{
    finisheD.pagesizeE = true;
    PAGESIZE = newPAGESIZE;
}

PageStyle TemplateGenKiCAD_5::getPAGESTYLE() const
{
    return PAGESTYLE;
}

void TemplateGenKiCAD_5::setPAGESTYLE(PageStyle newPAGESTYLE)
{
    finisheD.pagestylE = true;
    PAGESTYLE = newPAGESTYLE;
}

qint64 TemplateGenKiCAD_5::getNUMOPTLINES() const
{
    return NUMOPTLINES;
}

void TemplateGenKiCAD_5::setNUMOPTLINES(qint64 newNUMOPTLINES)
{
    NUMOPTLINES = newNUMOPTLINES;
    finisheD.numoptlineS = true;
}

const QMap<QString, TitelblockField> &TemplateGenKiCAD_5::getTITELBLOCKFIELDS() const
{
    return TITELBLOCKFIELDS;
}

void TemplateGenKiCAD_5::setTITELBLOCKFIELDS(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS)
{
    TITELBLOCKFIELDS = newTITELBLOCKFIELDS;
    finisheD.titelblockfieldS = true;
}

bool TemplateGenKiCAD_5::getTRIMMINGMARKS() const
{
    return TRIMMINGMARKS;
}

void TemplateGenKiCAD_5::setTRIMMINGMARKS(bool newTRIMMINGMARKS)
{
    TRIMMINGMARKS = newTRIMMINGMARKS;
    finisheD.trimmingmarkS = true;
}

RevHistoryStyle TemplateGenKiCAD_5::getREVHISTORYSTYLE() const
{
    return REVHISTORYSTYLE;
}

void TemplateGenKiCAD_5::setREVHISTORYSTYLE(RevHistoryStyle newREVHISTORYSTYLE)
{
    REVHISTORYSTYLE = newREVHISTORYSTYLE;
    finisheD.revhistorystylE = true;
}

const QMap<QString, TitelblockField> &TemplateGenKiCAD_5::getREVHISTORYFIELDS() const
{
    return REVHISTORYFIELDS;
}

void TemplateGenKiCAD_5::setREVHISTORYFIELDS(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS)
{
    REVHISTORYFIELDS = newREVHISTORYFIELDS;
    finisheD.revhistoryfieldS = true;
}

qint64 TemplateGenKiCAD_5::getNUMREVHISTORY() const
{
    return NUMREVHISTORY;
}

void TemplateGenKiCAD_5::setNUMREVHISTORY(qint64 newNUMREVHISTORY)
{
    NUMREVHISTORY = newNUMREVHISTORY;
    finisheD.numrevhistorY = true;
}

bool TemplateGenKiCAD_5::getREVHISTORY() const
{
    return REVHISTORY;
}

void TemplateGenKiCAD_5::setREVHISTORY(bool newREVHISTORY)
{
    REVHISTORY = newREVHISTORY;
    finisheD.revhistorY = true;
}

bool TemplateGenKiCAD_5::getFOLDLINES() const
{
    return FOLDLINES;
}

void TemplateGenKiCAD_5::setFOLDLINES(bool newFOLDLINES)
{
    FOLDLINES = newFOLDLINES;
    finisheD.foldlineS = true;
}

const PageSize &TemplateGenKiCAD_5::getFOLDLINETARGET() const
{
    return FOLDLINETARGET;
}

void TemplateGenKiCAD_5::setFOLDLINETARGET(const PageSize &newFOLDLINETARGET)
{
    FOLDLINETARGET = newFOLDLINETARGET;
    finisheD.foldlinestargeT = true;
}

quint64 TemplateGenKiCAD_5::getNUMPARTSSMALLPARTSLIST() const
{
    return NUMPARTSSMALLPARTSLIST;
}

void TemplateGenKiCAD_5::setNUMPARTSSMALLPARTSLIST(quint64 newNUMPARTSSMALLPARTSLIST)
{
    NUMPARTSSMALLPARTSLIST = newNUMPARTSSMALLPARTSLIST;
    finisheD.numpartssmallpartslisT = true;
}

bool TemplateGenKiCAD_5::getSMALLPARTSLIST() const
{
    return SMALLPARTSLIST;
}

void TemplateGenKiCAD_5::setSMALLPARTSLIST(bool newSMALLPARTSLIST)
{
    SMALLPARTSLIST = newSMALLPARTSLIST;
    finisheD.smallpartslisT = true;
}

quint64 TemplateGenKiCAD_5::getNUMLINESMALLPARTSLIST() const
{
    return NUMLINESMALLPARTSLIST;
}

void TemplateGenKiCAD_5::setNUMLINESMALLPARTSLIST(quint64 newNUMLINESMALLPARTSLIST)
{
    NUMLINESMALLPARTSLIST = newNUMLINESMALLPARTSLIST;
    finisheD.numlinessmallpartslisT = true;
}

const QMap<QString, TitelblockField> &TemplateGenKiCAD_5::getSMALLPARTSLISTFIELDS() const
{
    return SMALLPARTSLISTFIELDS;
}

void TemplateGenKiCAD_5::setSMALLPARTSLISTFIELDS(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS)
{
    SMALLPARTSLISTFIELDS = newSMALLPARTSLISTFIELDS;
    finisheD.smallpartslistfieldS = true;
}

bool TemplateGenKiCAD_5::getFULLSHEETPARTSLIST() const
{
    return FULLSHEETPARTSLIST;
}

void TemplateGenKiCAD_5::setFULLSHEETPARTSLIST(bool newFULLSHEETPARTSLIST)
{
    FULLSHEETPARTSLIST = newFULLSHEETPARTSLIST;
    finisheD.fullsheetpartslisT = true;
}

quint64 TemplateGenKiCAD_5::getNUMLINESFULLSHEETPARTSLIST() const
{
    return NUMLINESFULLSHEETPARTSLIST;
}

void TemplateGenKiCAD_5::setNUMLINESFULLSHEETPARTSLIST(quint64 newNUMLINESFULLSHEETPARTSLIST)
{
    NUMLINESFULLSHEETPARTSLIST = newNUMLINESFULLSHEETPARTSLIST;
    finisheD.numlinesfullsheetpartslisT = true;
}

const QMap<QString, TitelblockField> &TemplateGenKiCAD_5::getFULLSHEETPARTSLISTFIELDS() const
{
    return FULLSHEETPARTSLISTFIELDS;
}

void TemplateGenKiCAD_5::setFULLSHEETPARTSLISTFIELDS(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS)
{
    FULLSHEETPARTSLISTFIELDS = newFULLSHEETPARTSLISTFIELDS;
    finisheD.fullsheetpartlistfieldS = true;
}
