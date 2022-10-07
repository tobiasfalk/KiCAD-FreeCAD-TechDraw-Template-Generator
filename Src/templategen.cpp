#include "templategen.h"

bool TemplateGen::getDESCRIPTION() const
{
    return DESCRIPTION;
}

void TemplateGen::setDESCRIPTION(bool newDESCRIPTION)
{
    DESCRIPTION = newDESCRIPTION;
    finisheD.descriptioN = true;
}

quint64 TemplateGen::getDESCRIPTIONNUMLINES() const
{
    return DESCRIPTIONNUMLINES;
}

void TemplateGen::setDESCRIPTIONNUMLINES(quint64 newDESCRIPTIONNUMLINES)
{
    DESCRIPTIONNUMLINES = newDESCRIPTIONNUMLINES;
    finisheD.descriptionnumlineS = true;
}

bool TemplateGen::init()
{
    if(DESCRIPTION && PAGESIZE.height / 2 < 10 + (11 * (5 + NUMOPTLINES) + (2.5 * 1.5) * (DESCRIPTIONNUMLINES + 1) + 3.7))
    {
        CENTERINGMARKS.Right = false;
        if(PAGESIZE.width / 2 < 190)
        {
            CENTERINGMARKS.Left = false;
        }
    }
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

    if(allFinisheD(finisheD))
    {
        return writeBase();
    }
    else
    {
        printFinisheD(finisheD);
        qCritical() << "Not all options where filled(KiCAD 5)";
        return false;
    }
    return false;
}

QString TemplateGen::createFileName()
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

    // description field
    if(DESCRIPTION)
    {
        ret += "+d" + QString::number(DESCRIPTIONNUMLINES);
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

    ret +=  getFILEENDING();
    return ret;
}

qint64 TemplateGen::drawText(Coordinate position, QStringList text, QString name, double textSize, TextHeightAnchor textHeightAnchor, TextWidthAnchor textWidthAnchor, double lineWidth, bool isEditable, qint64 index)
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

void TemplateGen::drawVerFoldLine(double x, double depth)
{
    drawLine(Coordinate{x, 0}, Coordinate{x, depth}, 0.35);
    drawLine(Coordinate{x, PAGESIZE.height}, Coordinate{x, PAGESIZE.height - depth}, 0.35);
}

void TemplateGen::drawHorFoldLine(double y, double depth)
{
    drawLine(Coordinate{0, y}, Coordinate{depth, y}, 0.35);
    drawLine(Coordinate{PAGESIZE.width, y}, Coordinate{PAGESIZE.width - depth, y}, 0.35);
}

void TemplateGen::drawTrimmingMarksISO5457()
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

void TemplateGen::drawDrawingBorderISO5457()
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

            if(lineX >= PAGESIZE.width - 80)
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

void TemplateGen::drawTitelblockISO7200()
{
    // Frame
    Coordinate topLeft = Coordinate{PAGESIZE.width - 190, PAGESIZE.height - 10 - 11 * (5 + NUMOPTLINES)};
    double descHeight = 0;
    if(DESCRIPTION)
    {
        descHeight = (2.5 * 1.5) * (DESCRIPTIONNUMLINES + 1) + 3.7;
        drawRect(Coordinate{topLeft.X, topLeft.Y - descHeight}, Coordinate{PAGESIZE.width - 10, topLeft.Y}, 0.7);
        drawText(Coordinate{topLeft.X + 1.5, topLeft.Y - descHeight + 1.5}, TITELBLOCKFIELDS["opt23"].Label, TITELBLOCKFIELDS["opt23"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
        drawText(Coordinate{topLeft.X + 1.5, topLeft.Y - descHeight + 1.5 + 4.75}, TITELBLOCKFIELDS["opt23"].Value, TITELBLOCKFIELDS["opt23"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    }
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
            drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt1"].Label, TITELBLOCKFIELDS["opt1"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt2"].Label, TITELBLOCKFIELDS["opt2"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt3"].Label, TITELBLOCKFIELDS["opt3"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
            drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt1"].Value, TITELBLOCKFIELDS["opt1"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt2"].Value, TITELBLOCKFIELDS["opt2"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt3"].Value, TITELBLOCKFIELDS["opt3"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
            drawProjectionMethod(Coordinate{lastLineLeft.X + 80, lastLineLeft.Y + .5}, TITELBLOCKFIELDS["opt1"].ProjectionMethod);
            drawProjectionMethod(Coordinate{lastLineLeft.X + 140, lastLineLeft.Y + .5}, TITELBLOCKFIELDS["opt2"].ProjectionMethod);
            drawProjectionMethod(Coordinate{lastLineLeft.X + 180, lastLineLeft.Y + .5}, TITELBLOCKFIELDS["opt3"].ProjectionMethod);
        }
        else if((NUMOPTLINES == 3 && i == 1) || (NUMOPTLINES == 2 && i == 0))
        {
            drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt4"].Label, TITELBLOCKFIELDS["opt4"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt5"].Label, TITELBLOCKFIELDS["opt5"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt6"].Label, TITELBLOCKFIELDS["opt6"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
            drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt4"].Value, TITELBLOCKFIELDS["opt4"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt5"].Value, TITELBLOCKFIELDS["opt5"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt6"].Value, TITELBLOCKFIELDS["opt6"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
            drawProjectionMethod(Coordinate{lastLineLeft.X + 80, lastLineLeft.Y + .5}, TITELBLOCKFIELDS["opt4"].ProjectionMethod);
            drawProjectionMethod(Coordinate{lastLineLeft.X + 140, lastLineLeft.Y + .5}, TITELBLOCKFIELDS["opt5"].ProjectionMethod);
            drawProjectionMethod(Coordinate{lastLineLeft.X + 180, lastLineLeft.Y + .5}, TITELBLOCKFIELDS["opt6"].ProjectionMethod);
        }
        else if((NUMOPTLINES == 3 && i == 2) || (NUMOPTLINES == 2 && i == 1) || (NUMOPTLINES == 1 && i == 0))
        {
            drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt7"].Label, TITELBLOCKFIELDS["opt4"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt8"].Label, TITELBLOCKFIELDS["opt4"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt9"].Label, TITELBLOCKFIELDS["opt4"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
            drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt7"].Value, TITELBLOCKFIELDS["opt7"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt8"].Value, TITELBLOCKFIELDS["opt8"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
            drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt9"].Value, TITELBLOCKFIELDS["opt9"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
            drawProjectionMethod(Coordinate{lastLineLeft.X + 80, lastLineLeft.Y + .5}, TITELBLOCKFIELDS["opt7"].ProjectionMethod);
            drawProjectionMethod(Coordinate{lastLineLeft.X + 140, lastLineLeft.Y + .5}, TITELBLOCKFIELDS["opt8"].ProjectionMethod);
            drawProjectionMethod(Coordinate{lastLineLeft.X + 180, lastLineLeft.Y + .5}, TITELBLOCKFIELDS["opt9"].ProjectionMethod);
        }

        lastLineLeft = Coordinate{lastLineLeft.X, lastLineLeft.Y + 11};
        drawLine(lastLineLeft, Coordinate{PAGESIZE.width - 10, lastLineLeft.Y}, 0.35);
    }
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt10"].Label, TITELBLOCKFIELDS["opt10"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt11"].Label, TITELBLOCKFIELDS["opt11"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt12"].Label, TITELBLOCKFIELDS["opt12"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt10"].Value, TITELBLOCKFIELDS["opt10"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt11"].Value, TITELBLOCKFIELDS["opt11"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt12"].Value, TITELBLOCKFIELDS["opt12"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    drawProjectionMethod(Coordinate{lastLineLeft.X + 80, lastLineLeft.Y + .5}, TITELBLOCKFIELDS["opt10"].ProjectionMethod);
    drawProjectionMethod(Coordinate{lastLineLeft.X + 140, lastLineLeft.Y + .5}, TITELBLOCKFIELDS["opt11"].ProjectionMethod);
    drawProjectionMethod(Coordinate{lastLineLeft.X + 180, lastLineLeft.Y + .5}, TITELBLOCKFIELDS["opt12"].ProjectionMethod);
    lastLineLeft = Coordinate{lastLineLeft.X, lastLineLeft.Y + 11};
    drawLine(lastLineLeft, Coordinate{PAGESIZE.width - 10, lastLineLeft.Y}, 0.35);

    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt13"].Label, TITELBLOCKFIELDS["opt13"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt14"].Label, TITELBLOCKFIELDS["opt14"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt15"].Label, TITELBLOCKFIELDS["opt15"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt13"].Value, TITELBLOCKFIELDS["opt13"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt14"].Value, TITELBLOCKFIELDS["opt14"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt15"].Value, TITELBLOCKFIELDS["opt15"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    drawProjectionMethod(Coordinate{lastLineLeft.X + 80, lastLineLeft.Y + .5}, TITELBLOCKFIELDS["opt13"].ProjectionMethod);
    drawProjectionMethod(Coordinate{lastLineLeft.X + 140, lastLineLeft.Y + .5}, TITELBLOCKFIELDS["opt14"].ProjectionMethod);
    drawProjectionMethod(Coordinate{lastLineLeft.X + 180, lastLineLeft.Y + .5}, TITELBLOCKFIELDS["opt15"].ProjectionMethod);
    lastLineLeft = Coordinate{lastLineLeft.X, lastLineLeft.Y + 11};
    drawLine(lastLineLeft, Coordinate{PAGESIZE.width - 10, lastLineLeft.Y}, 0.35);

    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt16"].Label, TITELBLOCKFIELDS["opt16"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt17"].Label, TITELBLOCKFIELDS["opt17"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt18"].Label, TITELBLOCKFIELDS["opt18"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 7.5}, TITELBLOCKFIELDS["opt16"].Value, TITELBLOCKFIELDS["opt16"].Name, 5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.5, true);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 80, lastLineLeft.Y + 1.5 + 7.5}, TITELBLOCKFIELDS["opt17"].Value, TITELBLOCKFIELDS["opt17"].Name, 5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.5, true);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 140, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt18"].Value, TITELBLOCKFIELDS["opt18"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    drawProjectionMethod(Coordinate{lastLineLeft.X + 80, lastLineLeft.Y + .5}, TITELBLOCKFIELDS["opt16"].ProjectionMethod);
    drawProjectionMethod(Coordinate{lastLineLeft.X + 140, lastLineLeft.Y + .5}, TITELBLOCKFIELDS["opt17"].ProjectionMethod);
    drawProjectionMethod(Coordinate{lastLineLeft.X + 180, lastLineLeft.Y + .5}, TITELBLOCKFIELDS["opt18"].ProjectionMethod);
    lastLineLeft = Coordinate{lastLineLeft.X + 140, lastLineLeft.Y + 11};
    drawLine(lastLineLeft, Coordinate{PAGESIZE.width - 10, lastLineLeft.Y}, 0.35);

    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt19"].Label, TITELBLOCKFIELDS["opt19"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 12, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt20"].Label, TITELBLOCKFIELDS["opt20"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt19"].Value, TITELBLOCKFIELDS["opt19"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 12, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt20"].Value, TITELBLOCKFIELDS["opt20"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    lastLineLeft = Coordinate{lastLineLeft.X, lastLineLeft.Y + 11};
    drawLine(lastLineLeft, Coordinate{PAGESIZE.width - 10, lastLineLeft.Y}, 0.35);

    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt21"].Label, TITELBLOCKFIELDS["opt21"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 12, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt22"].Label, TITELBLOCKFIELDS["opt22"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt21"].Value, TITELBLOCKFIELDS["opt21"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 12, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt22"].Value, TITELBLOCKFIELDS["opt22"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    topLeft = Coordinate{PAGESIZE.width - 190, PAGESIZE.height - 10 - 11 * (5 + NUMOPTLINES) - descHeight};
    TOPLEFTITELBLOCKCORNER = topLeft;
}

void TemplateGen::drawRevHistoryASME_Y14_35_Width180()
{
    drawRect(Coordinate{TOPRIGHTDRAWINGCORNER.X - 180, TOPRIGHTDRAWINGCORNER.Y}, Coordinate{TOPRIGHTDRAWINGCORNER.X, TOPRIGHTDRAWINGCORNER.Y + 8 + NUMREVHISTORY * 13.5}, 0.7);
    // Head
    drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 90, TOPRIGHTDRAWINGCORNER.Y + 2}, REVHISTORYFIELDS["head"].Label, REVHISTORYFIELDS["head"].Name + "_l", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
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
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 172.5, TOPRIGHTDRAWINGCORNER.Y + 9.5 + 13.5 * i}, REVHISTORYFIELDS["opt1"].Value, TITELBLOCKFIELDS["opt1"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 155, TOPRIGHTDRAWINGCORNER.Y + 9.5 + 13.5 * i}, REVHISTORYFIELDS["opt2"].Value, TITELBLOCKFIELDS["opt2"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 97.5, TOPRIGHTDRAWINGCORNER.Y + 9.5 + 13.5 * i}, REVHISTORYFIELDS["opt3"].Value, TITELBLOCKFIELDS["opt3"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 40, TOPRIGHTDRAWINGCORNER.Y + 9.5 + 13.5 * i}, REVHISTORYFIELDS["opt4"].Value, TITELBLOCKFIELDS["opt4"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 15, TOPRIGHTDRAWINGCORNER.Y + 9.5 + 13.5 * i}, REVHISTORYFIELDS["opt5"].Value, TITELBLOCKFIELDS["opt5"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, true, i);
    }
}

void TemplateGen::drawFoldLines(double depth)
{
    switch (PAGESTYLE)
    {
    case PageStyle::ISO5457_ISO7200:
        if(FOLDLINETARGET.sizeString == "A4P with border" && PAGESIZE.height >= 297 && PAGESIZE.width >= 210)
        {
            double len = 0; // length of the blocck
            int num = 0; // number of blocks
            do
            {
                num++;
                len = (PAGESIZE.width - 210) / num;
            }while(len > 190 || num % 2 != 0);

            for(int i = 1; i <= num; i++)
            {
                drawVerFoldLine(20 + len * i, depth);
            }

            // Horizontal
            double indexHeight = PAGESIZE.height - 297;
            while(indexHeight > 0)
            {
                drawHorFoldLine(indexHeight, depth);
                indexHeight -= 297;
            }

        }else if(FOLDLINETARGET.sizeString == "200mmX290mm with border" && PAGESIZE.height >= 290 && PAGESIZE.width >= 200)
        {
            double len = 0; // length of the blocck
            int num = 0; // number of blocks
            do
            {
                num++;
                len = (PAGESIZE.width - 210) / num;
            }while(len > 180 || num % 2 != 0);

            drawVerFoldLine(PAGESIZE.width - 10, depth);

            for(int i = 1; i <= num; i++)
            {
                drawVerFoldLine(20 + len * i, depth);
            }

            // Horizontal
            double indexHeight = PAGESIZE.height - 290;
            while(indexHeight > 0)
            {
                drawHorFoldLine(indexHeight, depth);
                indexHeight -= 290;
            }

        }
        break;
    }
}

void TemplateGen::drawSmallPartsList()
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
            opt1Val.append(SMALLPARTSLISTFIELDS["opt1"].Value.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt2Val.append(SMALLPARTSLISTFIELDS["opt2"].Value.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt3Val.append(SMALLPARTSLISTFIELDS["opt3"].Value.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt4Val.append(SMALLPARTSLISTFIELDS["opt4"].Value.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt5Val.append(SMALLPARTSLISTFIELDS["opt5"].Value.at(0) + QString::number(i) + NumToABC(j).at(0));
        }
        drawText(Coordinate{topLeft.X + (width * (double(1)/18)) / 2, topLeft.Y + (fildHeight * (i - 1)) + fildHeight / 2 + 0.5}, opt1Val, SMALLPARTSLISTFIELDS["opt1"].Name, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true);
        drawText(Coordinate{topLeft.X + width * (double(1)/18) + (width * (double(3)/36)) / 2, topLeft.Y + (fildHeight * (i - 1)) + fildHeight / 2 + 0.5}, opt2Val, SMALLPARTSLISTFIELDS["opt2"].Name, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{topLeft.X + width * (double(5)/36) + (width * (double(2)/36)) / 2, topLeft.Y + (fildHeight * (i - 1)) + fildHeight / 2 + 0.5}, opt3Val, SMALLPARTSLISTFIELDS["opt3"].Name, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{topLeft.X + width * (double(7)/36) + (width * (double(14)/36)) / 2, topLeft.Y + (fildHeight * (i - 1)) + fildHeight / 2 + 0.5}, opt4Val, SMALLPARTSLISTFIELDS["opt4"].Name, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{topLeft.X + width * (double(21)/36) + (width * (double(15)/36)) / 2, topLeft.Y + (fildHeight * (i - 1)) + fildHeight / 2 + 0.5}, opt5Val, SMALLPARTSLISTFIELDS["opt5"].Name, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
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

void TemplateGen::drawFullSheetPartsList()
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
            opt1Val.append(FULLSHEETPARTSLISTFIELDS["opt1"].Value.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt2Val.append(FULLSHEETPARTSLISTFIELDS["opt2"].Value.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt3Val.append(FULLSHEETPARTSLISTFIELDS["opt3"].Value.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt4Val.append(FULLSHEETPARTSLISTFIELDS["opt4"].Value.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt5Val.append(FULLSHEETPARTSLISTFIELDS["opt5"].Value.at(0) + QString::number(i) + NumToABC(j).at(0));
            opt6Val.append(FULLSHEETPARTSLISTFIELDS["opt6"].Value.at(0) + QString::number(i) + NumToABC(j).at(0));
        }
        drawText(Coordinate{left + (width * (2/double(36))) / 2, indexTop - fieldHeight/2}, opt1Val, FULLSHEETPARTSLISTFIELDS["opt1"].Name, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true);
        drawText(Coordinate{left + width * (2/double(36)) + (width * (3/double(36))) / 2, indexTop - fieldHeight/2}, opt2Val, FULLSHEETPARTSLISTFIELDS["opt2"].Name, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{left + width * (5/double(36)) + (width * (2/double(36))) / 2, indexTop - fieldHeight/2}, opt3Val, FULLSHEETPARTSLISTFIELDS["opt3"].Name, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{left + width * (7/double(36)) + (width * (14/double(36))) / 2, indexTop - fieldHeight/2}, opt4Val, FULLSHEETPARTSLISTFIELDS["opt4"].Name, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{left + width * (21/double(36)) + (width * (8/double(36))) / 2, indexTop - fieldHeight/2}, opt5Val, FULLSHEETPARTSLISTFIELDS["opt5"].Name, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{left + width * (29/double(36)) + (width * (7/double(36))) / 2, indexTop - fieldHeight/2}, opt6Val, FULLSHEETPARTSLISTFIELDS["opt6"].Name, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawLine(Coordinate{left, indexTop}, Coordinate{right, indexTop}, 0.35);
        indexTop +=fieldHeight;
        i++;
    }
}

void TemplateGen::drawFullSheetPartsListCSV()
{
}

void TemplateGen::drawISO5457_ISO7200()
{
    if(TRIMMINGMARKS)
    {
        drawTrimmingMarksISO5457();
    }
    drawDrawingBorderISO5457();

    drawTitelblockISO7200();
}

void TemplateGen::drawProjectionMethod(Coordinate at, ProjectionMethodType what)
{
    const double unit = double(10)/24;
    switch (what) {
    case ProjectionMethodType::None:
        break;
    case ProjectionMethodType::FirstAngle:
        drawCircle(Coordinate{17 * -unit + at.X, 12 * unit + at.Y}, 5 * unit, .35);
        drawCircle(Coordinate{17 * -unit + at.X, 12 * unit + at.Y}, 10 * unit, .35);

        drawLine(Coordinate{30 * -unit + at.X, 2 * unit + at.Y}, Coordinate{-30 * unit + at.X, 22 * unit + at.Y}, .35);
        drawLine(Coordinate{30 * -unit + at.X, 22 * unit + at.Y}, Coordinate{-50 * unit + at.X, 16 * unit + at.Y}, .35);
        drawLine(Coordinate{50 * -unit + at.X, 16 * unit + at.Y}, Coordinate{-50 * unit + at.X, 8 * unit + at.Y}, .35);
        drawLine(Coordinate{50 * -unit + at.X, 8 * unit + at.Y}, Coordinate{-30 * unit + at.X, 2 * unit + at.Y}, .35);

        drawSlimDotLine(Coordinate{-52 * unit + at.X, 12 * unit + at.Y}, Coordinate{5 * -unit + at.X, 12 * unit + at.Y}, .18);
        drawSlimDotLine(Coordinate{-17 * unit + at.X, 0 * unit + at.Y}, Coordinate{17 * -unit + at.X, 24 * unit + at.Y}, .18);
        break;
    case ProjectionMethodType::ThirdAngle:
        drawLine(Coordinate{7 * -unit + at.X, 2 * unit + at.Y}, Coordinate{-7 * unit + at.X, 22 * unit + at.Y}, .35);
        drawLine(Coordinate{7 * -unit + at.X, 22 * unit + at.Y}, Coordinate{-27 * unit + at.X, 16 * unit + at.Y}, .35);
        drawLine(Coordinate{27 * -unit + at.X, 16 * unit + at.Y}, Coordinate{-27 * unit + at.X, 8 * unit + at.Y}, .35);
        drawLine(Coordinate{27 * -unit + at.X, 8 * unit + at.Y}, Coordinate{-7 * unit + at.X, 2 * unit + at.Y}, .35);

        drawCircle(Coordinate{40 * -unit + at.X, 12 * unit + at.Y}, 5 * unit, .35);
        drawCircle(Coordinate{40 * -unit + at.X, 12 * unit + at.Y}, 10 * unit, .35);

        drawSlimDotLine(Coordinate{-52 * unit + at.X, 12 * unit + at.Y}, Coordinate{5 * -unit + at.X, 12 * unit + at.Y}, .18);
        drawSlimDotLine(Coordinate{-40 * unit + at.X, 0 * unit + at.Y}, Coordinate{40 * -unit + at.X, 24 * unit + at.Y}, .18);

        break;
    }
}

void TemplateGen::drawDot(Coordinate at, double lineWidth)
{
    drawLine(Coordinate{at.X - lineWidth/2, at.Y}, Coordinate{at.X + lineWidth/2, at.Y}, lineWidth);
}

void TemplateGen::drawDotLine(Coordinate start, Coordinate end, double lineWidth)
{
    Coordinate current = start;
    while(lineLenght(current, end) >= 13 * lineWidth)
    {
        current = drawLineAdv(current, end, 8 * lineWidth, lineWidth);
        current = drawLineAdv(current, end, 2 * lineWidth, 0);// 2 * lineWidth empty
        current = drawLineAdv(current, end, 1 * lineWidth, lineWidth);
        current = drawLineAdv(current, end, 2 * lineWidth, 0);// 2 * lineWidth empty
    }
    if(lineLenght(current, end) >= 11 * lineWidth && lineLenght(current, end) < 13 * lineWidth)
    {
        current = drawLineAdv(current, end, 8 * lineWidth, lineWidth);
        current = drawLineAdv(current, end, 2 * lineWidth, 0);// 2 * lineWidth empty
        current = drawLineAdv(current, end, 1 * lineWidth, lineWidth);
    }else if(lineLenght(current, end) >= 10 * lineWidth && lineLenght(current, end) < 11 * lineWidth)
    {
        current = drawLineAdv(current, end, 8 * lineWidth, lineWidth);
        current = drawLineAdv(current, end, 2 * lineWidth, 0);// 2 * lineWidth empty
        drawLine(current, end, lineWidth);
    }else if(lineLenght(current, end) >= 8 * lineWidth && lineLenght(current, end) < 10 * lineWidth)
    {
        current = drawLineAdv(current, end, 8 * lineWidth, lineWidth);
    }else if(lineLenght(current, end) > 0 * lineWidth && lineLenght(current, end) < 8 * lineWidth)
    {
        drawLine(current, end, lineWidth);
    }
}

void TemplateGen::drawSlimDotLine(Coordinate start, Coordinate end, double lineWidth)
{
    Coordinate current = start;
    while(lineLenght(current, end) >= 14 * lineWidth)
    {
        current = drawLineAdv(current, end, 8 * lineWidth, lineWidth);
        current = drawLineAdv(current, end, 2 * lineWidth, 0);// 2 * lineWidth empty
        current = drawLineAdv(current, end, 2 * lineWidth, lineWidth);
        current = drawLineAdv(current, end, 2 * lineWidth, 0);// 2 * lineWidth empty
    }
    if(lineLenght(current, end) >= 12 * lineWidth && lineLenght(current, end) < 14 * lineWidth)
    {
        current = drawLineAdv(current, end, 8 * lineWidth, lineWidth);
        current = drawLineAdv(current, end, 2 * lineWidth, 0);// 2 * lineWidth empty
        current = drawLineAdv(current, end, 2 * lineWidth, lineWidth);
    }else if(lineLenght(current, end) >= 10 * lineWidth && lineLenght(current, end) < 12 * lineWidth)
    {
        current = drawLineAdv(current, end, 8 * lineWidth, lineWidth);
        current = drawLineAdv(current, end, 2 * lineWidth, 0);// 2 * lineWidth empty
        drawLine(current, end, lineWidth);
    }else if(lineLenght(current, end) >= 8 * lineWidth && lineLenght(current, end) < 10 * lineWidth)
    {
        current = drawLineAdv(current, end, 8 * lineWidth, lineWidth);
    }else if(lineLenght(current, end) > 0 && lineLenght(current, end) < 8 * lineWidth)
    {
        drawLine(current, end, lineWidth);
    }
}

Coordinate TemplateGen::drawLineAdv(Coordinate start, Coordinate end, double length, double lineWidth)
{
    double lenghtBase = lineLenght(start, end);
    Coordinate target{start.X-( (length * (start.X - end.X) ) / lenghtBase), start.Y-( (length * (start.Y - end.Y) ) / lenghtBase)};
    if(lineWidth != 0)
    {
        drawLine(start, target, lineWidth);
    }
    return target;
}

void TemplateGen::draw()
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

TemplateGen::TemplateGen(QObject *parent)
    : QObject{parent}
{

}

const QString &TemplateGen::getLOGODIR() const
{
    return LOGODIR;
}

void TemplateGen::setLOGODIR(const QString &newLOGODIR)
{
    LOGODIR = newLOGODIR;
    finisheD.logodiR = true;
}

bool TemplateGen::getLOGO() const
{
    return LOGO;
}

void TemplateGen::setLOGO(bool newLOGO)
{
    LOGO = newLOGO;
    finisheD.logO = true;
}

const QString &TemplateGen::getSHEETNAME() const
{
    return SHEETNAME;
}

void TemplateGen::setSHEETNAME(const QString &newSHEETNAME)
{
    SHEETNAME = newSHEETNAME;
    finisheD.sheetnamE = true;
}

const QString &TemplateGen::getDIR() const
{
    return DIR;
}

void TemplateGen::setDIR(const QString &newDIR)
{
    finisheD.diR = true;
    DIR = newDIR;
}

const PageSize &TemplateGen::getPAGESIZE() const
{
    return PAGESIZE;
}

void TemplateGen::setPAGESIZE(const PageSize &newPAGESIZE)
{
    finisheD.pagesizeE = true;
    PAGESIZE = newPAGESIZE;
}

PageStyle TemplateGen::getPAGESTYLE() const
{
    return PAGESTYLE;
}

void TemplateGen::setPAGESTYLE(PageStyle newPAGESTYLE)
{
    finisheD.pagestylE = true;
    PAGESTYLE = newPAGESTYLE;
}

qint64 TemplateGen::getNUMOPTLINES() const
{
    return NUMOPTLINES;
}

void TemplateGen::setNUMOPTLINES(qint64 newNUMOPTLINES)
{
    NUMOPTLINES = newNUMOPTLINES;
    finisheD.numoptlineS = true;
}

const QMap<QString, TitelblockField> &TemplateGen::getTITELBLOCKFIELDS() const
{
    return TITELBLOCKFIELDS;
}

void TemplateGen::setTITELBLOCKFIELDS(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS)
{
    TITELBLOCKFIELDS = newTITELBLOCKFIELDS;
    finisheD.titelblockfieldS = true;
}

bool TemplateGen::getTRIMMINGMARKS() const
{
    return TRIMMINGMARKS;
}

void TemplateGen::setTRIMMINGMARKS(bool newTRIMMINGMARKS)
{
    TRIMMINGMARKS = newTRIMMINGMARKS;
    finisheD.trimmingmarkS = true;
}

RevHistoryStyle TemplateGen::getREVHISTORYSTYLE() const
{
    return REVHISTORYSTYLE;
}

void TemplateGen::setREVHISTORYSTYLE(RevHistoryStyle newREVHISTORYSTYLE)
{
    REVHISTORYSTYLE = newREVHISTORYSTYLE;
    finisheD.revhistorystylE = true;
}

const QMap<QString, TitelblockField> &TemplateGen::getREVHISTORYFIELDS() const
{
    return REVHISTORYFIELDS;
}

void TemplateGen::setREVHISTORYFIELDS(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS)
{
    REVHISTORYFIELDS = newREVHISTORYFIELDS;
    finisheD.revhistoryfieldS = true;
}

qint64 TemplateGen::getNUMREVHISTORY() const
{
    return NUMREVHISTORY;
}

void TemplateGen::setNUMREVHISTORY(qint64 newNUMREVHISTORY)
{
    NUMREVHISTORY = newNUMREVHISTORY;
    finisheD.numrevhistorY = true;
}

bool TemplateGen::getREVHISTORY() const
{
    return REVHISTORY;
}

void TemplateGen::setREVHISTORY(bool newREVHISTORY)
{
    REVHISTORY = newREVHISTORY;
    finisheD.revhistorY = true;
}

bool TemplateGen::getFOLDLINES() const
{
    return FOLDLINES;
}

void TemplateGen::setFOLDLINES(bool newFOLDLINES)
{
    FOLDLINES = newFOLDLINES;
    finisheD.foldlineS = true;
}

const PageSize &TemplateGen::getFOLDLINETARGET() const
{
    return FOLDLINETARGET;
}

void TemplateGen::setFOLDLINETARGET(const PageSize &newFOLDLINETARGET)
{
    FOLDLINETARGET = newFOLDLINETARGET;
    finisheD.foldlinestargeT = true;
}

quint64 TemplateGen::getNUMPARTSSMALLPARTSLIST() const
{
    return NUMPARTSSMALLPARTSLIST;
}

void TemplateGen::setNUMPARTSSMALLPARTSLIST(quint64 newNUMPARTSSMALLPARTSLIST)
{
    NUMPARTSSMALLPARTSLIST = newNUMPARTSSMALLPARTSLIST;
    finisheD.numpartssmallpartslisT = true;
}

bool TemplateGen::getSMALLPARTSLIST() const
{
    return SMALLPARTSLIST;
}

void TemplateGen::setSMALLPARTSLIST(bool newSMALLPARTSLIST)
{
    SMALLPARTSLIST = newSMALLPARTSLIST;
    finisheD.smallpartslisT = true;
}

quint64 TemplateGen::getNUMLINESMALLPARTSLIST() const
{
    return NUMLINESMALLPARTSLIST;
}

void TemplateGen::setNUMLINESMALLPARTSLIST(quint64 newNUMLINESMALLPARTSLIST)
{
    NUMLINESMALLPARTSLIST = newNUMLINESMALLPARTSLIST;
    finisheD.numlinessmallpartslisT = true;
}

const QMap<QString, TitelblockField> &TemplateGen::getSMALLPARTSLISTFIELDS() const
{
    return SMALLPARTSLISTFIELDS;
}

void TemplateGen::setSMALLPARTSLISTFIELDS(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS)
{
    SMALLPARTSLISTFIELDS = newSMALLPARTSLISTFIELDS;
    finisheD.smallpartslistfieldS = true;
}

bool TemplateGen::getFULLSHEETPARTSLIST() const
{
    return FULLSHEETPARTSLIST;
}

void TemplateGen::setFULLSHEETPARTSLIST(bool newFULLSHEETPARTSLIST)
{
    FULLSHEETPARTSLIST = newFULLSHEETPARTSLIST;
    finisheD.fullsheetpartslisT = true;
}

quint64 TemplateGen::getNUMLINESFULLSHEETPARTSLIST() const
{
    return NUMLINESFULLSHEETPARTSLIST;
}

void TemplateGen::setNUMLINESFULLSHEETPARTSLIST(quint64 newNUMLINESFULLSHEETPARTSLIST)
{
    NUMLINESFULLSHEETPARTSLIST = newNUMLINESFULLSHEETPARTSLIST;
    finisheD.numlinesfullsheetpartslisT = true;
}

const QMap<QString, TitelblockField> &TemplateGen::getFULLSHEETPARTSLISTFIELDS() const
{
    return FULLSHEETPARTSLISTFIELDS;
}

void TemplateGen::setFULLSHEETPARTSLISTFIELDS(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS)
{
    FULLSHEETPARTSLISTFIELDS = newFULLSHEETPARTSLISTFIELDS;
    finisheD.fullsheetpartlistfieldS = true;
}

