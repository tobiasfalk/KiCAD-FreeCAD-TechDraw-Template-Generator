#include "templategen.h"
#include <QFont>
#include <QFontMetrics>

#include <iostream>

const QString &TemplateGen::getBOMCSVFILE() const
{
    return BOMCSVFILE;
}

void TemplateGen::setBOMCSVFILE(const QString &newBOMCSVFILE)
{
    BOMCSVFILE = newBOMCSVFILE;
}

bool TemplateGen::init()
{
    if(NOINIT)
    {
        return true;
    }

    if(!allFinisheD(finisheD))
    {
        printFinisheD(finisheD);
        qCritical() << "Not all options where filled(KiCAD 5)";
        return false;
    }

    initBorder();

    initTitleblock();

    initRevHistory();

    initFullSheetPartList();

//    if(FULLSHEETPARTSLIST)
//    {
//        CENTERINGMARKS.Right = false;
//        CENTERINGMARKS.Left = false;
//        CENTERINGMARKS.Top = false;
//    }
//    if(SHEETSIZE.width / 2 < 190 && REVHISTORY)
//    {
//        CENTERINGMARKS.Top = false;
//    }
//    if(SHEETSIZE.height / 2 > (SHEETSIZE.height - 11 * (5 + ISO7200OPTIONS->getNumOptLins()) + 0) || (SHEETSIZE.height / 2 < (10 + 8 + ASME_Y14_35_WIDTH180->getNumRev() * (ASME_Y14_35_WIDTH180->getNumLinesRev() * 3.5 + 2)) && REVHISTORY))
//    {
//        CENTERINGMARKS.Right = false;
//    }
//    if((SHEETSIZE.height / 2 > (SHEETSIZE.height - 11 * (5 + ISO7200OPTIONS->getNumOptLins()) + 0)) && (SHEETSIZE.width / 2 < 190))
//    {
//        CENTERINGMARKS.Left = false;
//    }

    return writeBase();
}

bool TemplateGen::initBorder()
{
    // Switching between the diferen styles
    switch (SHEETSTYLE)
    {
    case SheetStyle::ISO5457_ISO7200:
        // Defining the corners of the drawing space
        TOPLEFTDRAWINGCORNER.X = 20;
        TOPLEFTDRAWINGCORNER.Y = 10;

        TOPRIGHTDRAWINGCORNER.X = SHEETSIZE.width - 10;
        TOPRIGHTDRAWINGCORNER.Y = 10;

        BOTTOMRIGHTDRAWINGCORNER.X = SHEETSIZE.width - 10;
        BOTTOMRIGHTDRAWINGCORNER.Y = SHEETSIZE.height - 10;

        BOTTOMLEFTDRAWINGCORNER.X = 20;
        BOTTOMLEFTDRAWINGCORNER.Y = SHEETSIZE.height - 10;

        // Set the Centering marks all true and define there depth
        CENTERINGMARKS.Right = true;
        CENTERINGMARKS.Bottom = true;
        CENTERINGMARKS.Left = true;
        CENTERINGMARKS.Top = true;

        LEFTCENTERMARKDEPTH = 30;
        RIGHTCENTERMARKDEPTH = 20;
        TOPCENTERMARKDEPTH = 20;
        BOTTOMCENTERMARKDEPTH = 20;

        break;

    case SheetStyle::BLANK:
        // Defining the corners of the drawing space, all 0 because this is a blank space
        TOPLEFTDRAWINGCORNER.X = 0;
        TOPLEFTDRAWINGCORNER.Y = 0;

        TOPRIGHTDRAWINGCORNER.X = SHEETSIZE.width - 0;
        TOPRIGHTDRAWINGCORNER.Y = 0;

        BOTTOMRIGHTDRAWINGCORNER.X = SHEETSIZE.width - 0;
        BOTTOMRIGHTDRAWINGCORNER.Y = SHEETSIZE.height - 0;

        BOTTOMLEFTDRAWINGCORNER.X = 0;
        BOTTOMLEFTDRAWINGCORNER.Y = SHEETSIZE.height - 0;

        CENTERINGMARKS.Right = false;
        CENTERINGMARKS.Bottom = false;
        CENTERINGMARKS.Left = false;
        CENTERINGMARKS.Top = false;

        break;
    }
    return true;
}

bool TemplateGen::initTitleblock()
{
    double descHeight;
    switch (SHEETSTYLE)
    {
    case SheetStyle::ISO5457_ISO7200:

        descHeight = (11 * (5 + ISO7200OPTIONS->getNumOptLins()) + (((2.5 * 1.5) * (ISO7200OPTIONS->getNumDescLines() + 1) + 3.7)) * ISO7200OPTIONS->getDescField());
        TOPLEFTTITELBLOCKCORNER.X = BOTTOMRIGHTDRAWINGCORNER.X - 180;
        TOPLEFTTITELBLOCKCORNER.Y = BOTTOMRIGHTDRAWINGCORNER.Y - descHeight; // Exaxt size need to be calculated;

        TOPRIGHTTITELBLOCKCORNER.X = BOTTOMRIGHTDRAWINGCORNER.X;
        TOPRIGHTTITELBLOCKCORNER.Y = BOTTOMRIGHTDRAWINGCORNER.Y - descHeight; // Exaxt size need to be calculated

        BOTTOMLEFTTITELBLOCKCORNER.X = BOTTOMRIGHTDRAWINGCORNER.X - 180;
        BOTTOMLEFTTITELBLOCKCORNER.Y = BOTTOMRIGHTDRAWINGCORNER.Y;

        BOTTOMRIGHTTITELBLOCKCORNER = BOTTOMRIGHTDRAWINGCORNER;

        CENTERINGMARKS.Right = true;
        CENTERINGMARKS.Bottom = true;
        CENTERINGMARKS.Left = true;
        CENTERINGMARKS.Top = true;

        break;

    case SheetStyle::BLANK:
        TOPLEFTTITELBLOCKCORNER.X = 0;
        TOPLEFTTITELBLOCKCORNER.Y = 0;

        TOPRIGHTTITELBLOCKCORNER.X = 0;
        TOPRIGHTTITELBLOCKCORNER.Y = 0;

        BOTTOMLEFTTITELBLOCKCORNER.X = 0;
        BOTTOMLEFTTITELBLOCKCORNER.Y = 0;

        BOTTOMRIGHTTITELBLOCKCORNER.X = 0;
        BOTTOMRIGHTTITELBLOCKCORNER.Y = 0;

        CENTERINGMARKS.Right = false;
        CENTERINGMARKS.Bottom = false;
        CENTERINGMARKS.Left = false;
        CENTERINGMARKS.Top = false;

        break;
    }

    if(SMALLPARTSLIST){
        double listHeight = 8 + ((2.5 * 1.5) * SMALLPARTSLISTSOPTIONS->getNumLinesPerField() + 3) * SMALLPARTSLISTSOPTIONS->getNumParts();

        TOPLEFTTITELBLOCKCORNER.Y -= listHeight;
        TOPRIGHTTITELBLOCKCORNER.Y -= listHeight;
    }

    if(TOPLEFTTITELBLOCKCORNER.Y < SHEETSIZE.height / 2){
        CENTERINGMARKS.Right = false;
        if(TOPLEFTTITELBLOCKCORNER.X < 30)// 30 is the depth that the line goes in
        {
            CENTERINGMARKS.Left = false;
        }
    }

    if(TOPLEFTTITELBLOCKCORNER.X < SHEETSIZE.width / 2){
        CENTERINGMARKS.Bottom = false;
        if(TOPLEFTTITELBLOCKCORNER.Y < 20)// 30 is the depth that the line goes in
        {
            CENTERINGMARKS.Top = false;
        }
    }

    return true;
}

bool TemplateGen::initRevHistory()
{
    if(REVHISTORY)
    {
        double revHistHight;
        switch (REVHISTORYSTYLE)
        {
        case RevHistoryStyle::ASME_Y14_35_Width180:

            revHistHight = 8 + ASME_Y14_35_WIDTH180->getNumRev() * (ASME_Y14_35_WIDTH180->getNumLinesRev() * 3.5 + 2);

            TOPLEFTREVHISTORY.X = TOPRIGHTDRAWINGCORNER.X - 180;
            TOPLEFTREVHISTORY.Y = TOPRIGHTDRAWINGCORNER.Y;

            TOPRIGHTREVHISTORY = TOPRIGHTDRAWINGCORNER;

            BOTTOMLEFTREVHISTORY.X = TOPLEFTREVHISTORY.X;
            BOTTOMLEFTREVHISTORY.Y = TOPLEFTREVHISTORY.Y + revHistHight;

            BOTTOMRIGHTREVHISTORY.X = TOPRIGHTREVHISTORY.X;
            BOTTOMRIGHTREVHISTORY.Y = TOPRIGHTREVHISTORY.Y + revHistHight;

            break;

        default:
            TOPLEFTREVHISTORY = Coordinate{0,0};
            TOPRIGHTREVHISTORY = Coordinate{0,0};
            BOTTOMLEFTREVHISTORY = Coordinate{0,0};
            BOTTOMRIGHTREVHISTORY = Coordinate{0,0};
            break;
        }

        if(BOTTOMRIGHTREVHISTORY.Y > SHEETSIZE.height/2){
            CENTERINGMARKS.Right = false;
            if(BOTTOMLEFTREVHISTORY.X < LEFTCENTERMARKDEPTH){
                CENTERINGMARKS.Left = false;
            }
        }
        if(TOPLEFTREVHISTORY.X < SHEETSIZE.width/2){
            CENTERINGMARKS.Top = false;
            if(BOTTOMLEFTREVHISTORY.Y > SHEETSIZE.height - BOTTOMCENTERMARKDEPTH){
                CENTERINGMARKS.Bottom = false;
            }
        }
    }else {
        TOPLEFTREVHISTORY = Coordinate{0,0};
        TOPRIGHTREVHISTORY = Coordinate{0,0};
        BOTTOMLEFTREVHISTORY = Coordinate{0,0};
        BOTTOMRIGHTREVHISTORY = Coordinate{0,0};
    }
    return true;
}

bool TemplateGen::initFullSheetPartList()
{
    if(FULLSHEETPARTSLIST)
    {
        CENTERINGMARKS.Right = false;
        CENTERINGMARKS.Left = false;
        CENTERINGMARKS.Top = false;
        CENTERINGMARKS.Bottom = false;

        if(FULLSHEETPARTLISTOPIONS->getSpace() == "A"){
            TOPLEFTFULLPARTLIST.X = TOPLEFTDRAWINGCORNER.X;
            TOPRIGHTFULLPARTLIST.X = TOPRIGHTDRAWINGCORNER.X;

            if(REVHISTORY){
                TOPLEFTFULLPARTLIST.Y = BOTTOMRIGHTREVHISTORY.Y;
                TOPRIGHTFULLPARTLIST.Y = BOTTOMRIGHTREVHISTORY.Y;
            }else{
                TOPLEFTFULLPARTLIST.Y = TOPLEFTDRAWINGCORNER.Y;
                TOPRIGHTFULLPARTLIST.Y = TOPLEFTDRAWINGCORNER.Y;
            }

            BOTTOMLEFTFULLPARTLIST.X = BOTTOMLEFTDRAWINGCORNER.X;
            BOTTOMLEFTFULLPARTLIST.Y = TOPLEFTTITELBLOCKCORNER.Y;

            BOTTOMRIGHTFULLPARTLIST.X = BOTTOMRIGHTDRAWINGCORNER.X;
            BOTTOMRIGHTFULLPARTLIST.Y = TOPRIGHTTITELBLOCKCORNER.Y;
        }else if(FULLSHEETPARTLISTOPIONS->getSpace() == "B"){
            TOPLEFTFULLPARTLIST = TOPLEFTDRAWINGCORNER;

            if(REVHISTORY){
                TOPRIGHTFULLPARTLIST = TOPLEFTREVHISTORY;
            }else{
                TOPRIGHTFULLPARTLIST.X = BOTTOMLEFTTITELBLOCKCORNER.X;
                TOPRIGHTFULLPARTLIST.Y = TOPLEFTDRAWINGCORNER.Y;
            }

            BOTTOMLEFTFULLPARTLIST = BOTTOMLEFTDRAWINGCORNER;

            BOTTOMRIGHTFULLPARTLIST = BOTTOMLEFTTITELBLOCKCORNER;
        }
    }else{
        TOPLEFTFULLPARTLIST = Coordinate{0,0};
        TOPRIGHTFULLPARTLIST = Coordinate{0,0};
        BOTTOMLEFTFULLPARTLIST = Coordinate{0,0};
        BOTTOMRIGHTFULLPARTLIST = Coordinate{0,0};
    }
    return true;
}

QString TemplateGen::createFileName()
{
    if(FULLSHEETPARTLISTOPIONS->getImporCSV())
    {
        return DIR + "/" + SHEETSIZE.sizeString.replace(" ", "_") + "Partlist_" + QString::number(SHEETINDEX + 1) + getFILEENDING();
    }
    QString ret =  DIR + "/" + SHEETSIZE.sizeString.replace(" ", "_");

    switch (SHEETSTYLE)
    {
    case SheetStyle::ISO5457_ISO7200:
        ret += "_ISO5457_ISO7200";
        break;
    case SheetStyle::BLANK:
        ret += "_BLANK";
        break;
    }

    // optional lines
    if(ISO7200OPTIONS->getNumOptLins() > 0)
    {
        ret += "+" + QString::number(ISO7200OPTIONS->getNumOptLins());
    }

    // description field
    if(ISO7200OPTIONS->getDescField())
    {
        ret += "+d" + QString::number(ISO7200OPTIONS->getNumDescLines());
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
        ret += "_rev+" + QString::number(ASME_Y14_35_WIDTH180->getNumRev());
    }

    if(FULLSHEETPARTSLIST)
    {
        ret += "_fspl+" + QString::number(FULLSHEETPARTLISTOPIONS->getNumLinesPerField());
    }

    if(SMALLPARTSLIST)
    {
        ret += "_spl+" + QString::number(SMALLPARTSLISTSOPTIONS->getNumParts()) + "+" + QString::number(SMALLPARTSLISTSOPTIONS->getNumLinesPerField());
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

QList<QString> TemplateGen::readBOMKiCAD(QString fileDIR)
{
    QList<QString> ret;
    QFile inputFile(fileDIR);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       bool parts = false;
       while (!in.atEnd())
       {
           QString line = in.readLine();
           if(parts && line != "")
           {
               ret.push_back(line);
           }else if(line.contains("\"Ref\",\"Qnty\",\"Value\",\"Cmp name\",\"Footprint\",\"Description\",\"Vendor\""))
           {
               parts = true;
           }
       }
       inputFile.close();
    }
    return ret;
}

QList<BOMColumn> TemplateGen::readBOMStd(QString fileDIR)
{
    QList<BOMColumn> ret;
    double width = TOPRIGHTFULLPARTLIST.X - TOPLEFTFULLPARTLIST.X;
    QFile inputFile(fileDIR);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       QString line;
       int i = 0;
       while (!in.atEnd())
       {
           line = in.readLine();
           QList<QString> fields = line.split(';');
           int j = 0;
           foreach (QString f, fields)
           {
               if(f.length() > 0 && i == 0)
               {
                   BOMColumn c;
                   c.Width = f.toDouble() * (width);
                   ret.append(c);
               }else if(f.length() > 0 && i == 1)
               {
                   ret[j].Title = f;
               }else if(f.length() > 0 && i > 1)
               {
                   ret[j].Values.append(f);
               }
               j++;
           }
           i++;
       }
       inputFile.close();
    }
    return ret;
}

int TemplateGen::splitBOMlineKiCAD(QString line, QStringList &opt1Val, QStringList &opt2Val, QStringList &opt3Val, QStringList &opt4Val, QStringList &opt5Val, QStringList &opt6Val)
{
    double width = TOPRIGHTDRAWINGCORNER.X - TOPLEFTDRAWINGCORNER.X;

    QStringList splitedLine = line.split("\",\"");
    splitedLine = splitedLine.replaceInStrings("\",\"", "");
    splitedLine = splitedLine.replaceInStrings("\"", "");

    opt1Val = QStringList{"42"};
    opt2Val = splitBOMValKiCAD(splitedLine.at(0), width * (2/double(36)));
    opt3Val = splitBOMValKiCAD(splitedLine.at(1), width * (3/double(36)));
    opt4Val = splitBOMValKiCAD(splitedLine.at(3), width * (14/double(36)));
    opt5Val = splitBOMValKiCAD(splitedLine.at(2), width * (8/double(36)));
    opt6Val = splitBOMValKiCAD(splitedLine.at(5), width * (5/double(36)));

    int numLines = 0;
    if(opt1Val.size() > numLines)
    {
        numLines = opt1Val.size();
    }
    if(opt2Val.size() > numLines)
    {
        numLines = opt2Val.size();
    }
    if(opt3Val.size() > numLines)
    {
        numLines = opt3Val.size();
    }
    if(opt4Val.size() > numLines)
    {
        numLines = opt4Val.size();
    }
    if(opt5Val.size() > numLines)
    {
        numLines = opt5Val.size();
    }
    if(opt6Val.size() > numLines)
    {
        numLines = opt6Val.size();
    }

    return numLines;
}

QStringList TemplateGen::splitBOMValKiCAD(QString val, double targetLenght)
{
    QStringList ret;
    // get text length
    QFont qFontA("osifont");
    qFontA.setPointSizeF(100);
    QFontMetrics fm(qFontA);
    double length = (2.5 * (fm.size(Qt::TextDontPrint, val).width()/double(100)));
    if(length > targetLenght && val.contains(' '))
    {
        QString wVal = val;
        if(wVal[0] == ' ')
        {
            wVal = wVal.remove(0, 1);
        }
        if(wVal[wVal.length() - 1] == ' ')
        {
            wVal = wVal.chopped(1);
        }
        if(wVal[wVal.length() - 1] == ',')
        {
            wVal = wVal.chopped(1);
        }
        if(wVal[wVal.length() - 1] == ' ' && wVal[wVal.length() - 2] == ',')
        {
            wVal = wVal.chopped(2);
        }

        int lastSpIndex = -1;
        int i = 0;
        while ((2.5 * (fm.size(Qt::TextDontPrint, wVal).width()/double(100))) > targetLenght - 5 && i < wVal.length())
        {
            if(wVal[0] == ' ' || wVal[0] == ',')
            {
                wVal = wVal.remove(0, 1);
            }
            if(wVal[wVal.length() - 1] == ' ')
            {
                wVal = wVal.chopped(1);
            }
            if(wVal[wVal.length() - 1] == ',')
            {
                wVal = wVal.chopped(1);
            }

            if(wVal[i] == ' ')
            {
                lastSpIndex = i;
            }
            if((2.5 * (fm.size(Qt::TextDontPrint, wVal.chopped(wVal.length() - i - 1)).width()/double(100))) >= targetLenght - 5)
            {
                if(lastSpIndex > 0)
                {
                    ret.append(wVal.chopped(wVal.length() - lastSpIndex - 1));
                    wVal = wVal.remove(0, lastSpIndex + 1);
                    lastSpIndex = -1;
                    i = 0;
                }else
                {
                    ret.append(wVal.chopped(wVal.length() - i - 1));
                    wVal = wVal.remove(0, i + 1);
                    lastSpIndex = -1;
                    i = 0;
                }
            }
            i++;
        };
        if(wVal.length() > 0)
        {
            ret.append(wVal);
        }

        return ret;
    } else
    if(length > targetLenght)
    {
        QString wVal = val;
        do
        {
            int i = 0;
            bool continu = true;
            while(continu && i <= wVal.length())
            {
                i++;
                if((2.5 * (fm.size(Qt::TextDontPrint, wVal.chopped(wVal.length() - i - 1)).width()/double(100))) >= targetLenght - 5)
                {
                    ret.append(wVal.chopped(wVal.length() - i - 1));
                    wVal = wVal.remove(0, i + 1);
                    continu = false;
                }
            }
        }while((2.5 * (fm.size(Qt::TextDontPrint, wVal).width()/double(100))) > targetLenght);
        ret.append(wVal);
        return ret;
    } else
    {
        return QStringList{val};
    }
}

QStringList TemplateGen::splitBOMValStd(QString val, double targetLenght)
{
    QStringList ret;
    // get text length
    QFont qFontA("osifont");
    qFontA.setPointSizeF(100);
    QFontMetrics fm(qFontA);
    double length = (2.5 * (fm.size(Qt::TextDontPrint, val).width()/double(100)));
    if(length > targetLenght && val.contains(' '))
    {
        QString wVal = val;
        if(wVal[0] == ' ')
        {
            wVal = wVal.remove(0, 1);
        }
        if(wVal[wVal.length() - 1] == ' ')
        {
            wVal = wVal.chopped(1);
        }
        if(wVal[wVal.length() - 1] == ',')
        {
            wVal = wVal.chopped(1);
        }
        if(wVal[wVal.length() - 1] == ' ' && wVal[wVal.length() - 2] == ',')
        {
            wVal = wVal.chopped(2);
        }

        int lastSpIndex = -1;
        int i = 0;
        while ((2.5 * (fm.size(Qt::TextDontPrint, wVal).width()/double(100))) > targetLenght - 5 && i < wVal.length())
        {
            if(wVal[0] == ' ' || wVal[0] == ',')
            {
                wVal = wVal.remove(0, 1);
            }
            if(wVal[wVal.length() - 1] == ' ')
            {
                wVal = wVal.chopped(1);
            }
            if(wVal[wVal.length() - 1] == ',')
            {
                wVal = wVal.chopped(1);
            }

            if(wVal[i] == ' ')
            {
                lastSpIndex = i;
            }
            if((2.5 * (fm.size(Qt::TextDontPrint, wVal.chopped(wVal.length() - i - 1)).width()/double(100))) >= targetLenght - 5)
            {
                if(lastSpIndex > 0)
                {
                    ret.append(wVal.chopped(wVal.length() - lastSpIndex - 1));
                    wVal = wVal.remove(0, lastSpIndex + 1);
                    lastSpIndex = -1;
                    i = 0;
                }else
                {
                    ret.append(wVal.chopped(wVal.length() - i - 1));
                    wVal = wVal.remove(0, i + 1);
                    lastSpIndex = -1;
                    i = 0;
                }
            }
            i++;
        };
        if(wVal.length() > 0)
        {
            ret.append(wVal);
        }

        return ret;
    } else
    if(length > targetLenght)
    {
        QString wVal = val;
        do
        {
            int i = 0;
            bool continu = true;
            while(continu && i <= wVal.length())
            {
                i++;
                if((2.5 * (fm.size(Qt::TextDontPrint, wVal.chopped(wVal.length() - i - 1)).width()/double(100))) >= targetLenght - 5)
                {
                    ret.append(wVal.chopped(wVal.length() - i - 1));
                    wVal = wVal.remove(0, i + 1);
                    continu = false;
                }
            }
        }while((2.5 * (fm.size(Qt::TextDontPrint, wVal).width()/double(100))) > targetLenght);
        ret.append(wVal);
        return ret;
    } else
    {
        return QStringList{val};
    }
}

std::shared_ptr<SmallPartsListOptions> TemplateGen::getSMALLPARTSLISTSOPTIONS() const
{
    return SMALLPARTSLISTSOPTIONS;
}

void TemplateGen::setSMALLPARTSLISTSOPTIONS(const std::shared_ptr<SmallPartsListOptions> &newSMALLPARTSLISTSOPTIONS)
{
    SMALLPARTSLISTSOPTIONS = newSMALLPARTSLISTSOPTIONS;
}

std::shared_ptr<FullSheetsPartListOptions> TemplateGen::getFULLSHEETPARTLISTOPIONS() const
{
    return FULLSHEETPARTLISTOPIONS;
}

void TemplateGen::setFULLSHEETPARTLISTOPIONS(const std::shared_ptr<FullSheetsPartListOptions> &newFULLSHEETPARTLISTOPIONS)
{
    FULLSHEETPARTLISTOPIONS = newFULLSHEETPARTLISTOPIONS;
}

std::shared_ptr<ASME_Y14_35_Width180> TemplateGen::getASME_Y14_35_WIDTH180() const
{
    return ASME_Y14_35_WIDTH180;
}

void TemplateGen::setASME_Y14_35_WIDTH180(const std::shared_ptr<ASME_Y14_35_Width180> &newASME_Y14_35_WIDTH180)
{
    ASME_Y14_35_WIDTH180 = newASME_Y14_35_WIDTH180;
}

std::shared_ptr<ISO7200Options> TemplateGen::getISO7200OPTIONS() const
{
    return ISO7200OPTIONS;
}

void TemplateGen::setISO7200OPTIONS(const std::shared_ptr<ISO7200Options> &newISO7200OPTIONS)
{
    ISO7200OPTIONS = newISO7200OPTIONS;
}

void TemplateGen::drawVerFoldLine(double x, double depth)
{
    drawLine(Coordinate{x, 0}, Coordinate{x, depth}, 0.35);
    drawLine(Coordinate{x, SHEETSIZE.height}, Coordinate{x, SHEETSIZE.height - depth}, 0.35);
}

void TemplateGen::drawHorFoldLine(double y, double depth)
{
    drawLine(Coordinate{0, y}, Coordinate{depth, y}, 0.35);
    drawLine(Coordinate{SHEETSIZE.width, y}, Coordinate{SHEETSIZE.width - depth, y}, 0.35);
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
    drawPoly(Coordinate{SHEETSIZE.width, 0}, trimmingMarkRT, 0);
    drawPoly(Coordinate{SHEETSIZE.width, SHEETSIZE.height}, trimmingMarkRB, 0);
    drawPoly(Coordinate{0, SHEETSIZE.height}, trimmingMarkLB, 0);
}

void TemplateGen::drawDrawingBorderISO5457()
{
    // Inseid and Outseid Rectangal
    {
        drawRect(Coordinate{15, 5}, Coordinate{SHEETSIZE.width - 5, SHEETSIZE.height - 5}, 0.35);
        drawRect(Coordinate{20, 10}, Coordinate{SHEETSIZE.width - 10, SHEETSIZE.height - 10}, 0.7);
    }

    // Centermarks
    {
        if(CENTERINGMARKS.Top)
        {
            drawLine(Coordinate{SHEETSIZE.width/2, 5}, Coordinate{SHEETSIZE.width/2, 20}, 0.7);
        }
        else
        {
            drawLine(Coordinate{SHEETSIZE.width/2, 5}, Coordinate{SHEETSIZE.width/2, 10}, 0.7);
        }
        if(CENTERINGMARKS.Bottom)
        {
            drawLine(Coordinate{SHEETSIZE.width/2, SHEETSIZE.height - 5}, Coordinate{SHEETSIZE.width/2, SHEETSIZE.height - 20}, 0.7);
        }
        else
        {
            drawLine(Coordinate{SHEETSIZE.width/2, SHEETSIZE.height - 5}, Coordinate{SHEETSIZE.width/2, SHEETSIZE.height - 10}, 0.7);
        }

        if(CENTERINGMARKS.Left)
        {
            drawLine(Coordinate{15, SHEETSIZE.height/2}, Coordinate{30, SHEETSIZE.height/2}, 0.7);
        }
        else
        {
            drawLine(Coordinate{15, SHEETSIZE.height/2}, Coordinate{20, SHEETSIZE.height/2}, 0.7);
        }
        if(CENTERINGMARKS.Right)
        {
            drawLine(Coordinate{SHEETSIZE.width - 5, SHEETSIZE.height/2}, Coordinate{SHEETSIZE.width - 20, SHEETSIZE.height/2}, 0.7);
        }
        else
        {
            drawLine(Coordinate{SHEETSIZE.width - 5, SHEETSIZE.height/2}, Coordinate{SHEETSIZE.width - 10, SHEETSIZE.height/2}, 0.7);
        }
    }

    // Top and Bottom Framegrid
    {
        double halfSheetWidth = SHEETSIZE.width/2;
        // Lines
        qint64 index = 1;
        qint64 indexNumDigets = QString::number((SHEETSIZE.width - 30) / 50).length();
        // Left
        double spaceLeft = 20 + 3.5;
        double lineX = halfSheetWidth - 50;
        QList<double> indexListLeft;
        double lastLine = lineX;
        while(lineX > spaceLeft)
        {
            // Top
            drawLine(Coordinate{lineX, 5}, Coordinate{lineX, 10}, 0.35);
            // Bottom
            drawLine(Coordinate{lineX, SHEETSIZE.height - 5}, Coordinate{lineX, SHEETSIZE.height - 10}, 0.35);
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
            if(SHEETSIZE.height >= 297 && SHEETSIZE.width >= 297)
            {
                drawText(Coordinate{pos, SHEETSIZE.height - 7.5}, QString::number(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            index++;
        }

        //Middle Text
        // Left
        drawText(Coordinate{halfSheetWidth - 25, 7.5}, QString::number(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        if(SHEETSIZE.height >= 297 && SHEETSIZE.width >= 297)
        {
            drawText(Coordinate{halfSheetWidth - 25, SHEETSIZE.height - 7.5}, QString::number(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        }
        index++;
        // Right
        drawText(Coordinate{halfSheetWidth + 25, 7.5}, QString::number(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        if(SHEETSIZE.height >= 297 && SHEETSIZE.width >= 297)
        {
            drawText(Coordinate{halfSheetWidth + 25, SHEETSIZE.height - 7.5}, QString::number(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        }
        index++;

        // Right
        double spaceRight = 10 + (3.5 * indexNumDigets);
        double spaceRightBottom = 10 + (3.5 * SHEETSIZE.sizeString.length());
        double lastBottomLine = halfSheetWidth;
        lineX = halfSheetWidth + 50;
        while(lineX < SHEETSIZE.width - spaceRight)
        {
            // Top
            drawLine(Coordinate{lineX, 5}, Coordinate{lineX, 10}, 0.35);
            drawText(Coordinate{lineX + 25, 7.5}, QString::number(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            //Bottom
            if(lineX < SHEETSIZE.width - spaceRightBottom)
            {
                drawLine(Coordinate{lineX, SHEETSIZE.height - 5}, Coordinate{lineX, SHEETSIZE.height - 10}, 0.35);
                lastBottomLine = lineX;
            }

            if(lineX >= SHEETSIZE.width - 80)
            {
                drawText(Coordinate{lastBottomLine + (SHEETSIZE.width - lastBottomLine) / 2, SHEETSIZE.height - 7.5}, SHEETSIZE.sizeString, "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            else if(SHEETSIZE.height >= 297  && lineX < SHEETSIZE.width - spaceRightBottom - 50)
            {
                drawText(Coordinate{lineX + 25, SHEETSIZE.height - 7.5}, QString::number(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            lineX += 50;
            index++;
        }
    }

    // Left and Right Framgrid
    {
        double halfSheetHeight = SHEETSIZE.height/2;
        // Lines
        qint64 index = 1;
        qint64 indexNumDigets = NumToABC((SHEETSIZE.height - 30) / 50).length();
        // Top
        double spaceTop = 10 + 3.5;
        double lineY = halfSheetHeight - 50;
        QList<double> indexListTop;
        double lastLine = lineY;
        while(lineY > spaceTop)
        {
            drawLine(Coordinate{15, lineY}, Coordinate{20, lineY}, 0.35);
            drawLine(Coordinate{SHEETSIZE.width - 5, lineY}, Coordinate{SHEETSIZE.width -  10, lineY}, 0.35);
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
            if(SHEETSIZE.width >= 297 && SHEETSIZE.height >= 297)
            {
                drawText(Coordinate{SHEETSIZE.width - 7.5, pos}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            index++;
        }
        // Middle
        drawText(Coordinate{17.5, halfSheetHeight - 25}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        if(SHEETSIZE.width >= 297 && SHEETSIZE.height >= 297)
        {
            drawText(Coordinate{SHEETSIZE.width - 7.5, halfSheetHeight - 25}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        }
        index++;
        drawText(Coordinate{17.5, halfSheetHeight + 25}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        if(SHEETSIZE.width >= 297 && SHEETSIZE.height >= 297)
        {
            drawText(Coordinate{SHEETSIZE.width - 7.5, halfSheetHeight + 25}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
        }
        index++;

        // Bottom
        double spaceBottom = 10 + (3.5 * indexNumDigets);
        lineY = halfSheetHeight + 50;
        while(lineY < SHEETSIZE.height - spaceBottom)
        {
            // Left
            double textY = 0;
            drawLine(Coordinate{15, lineY}, Coordinate{20, lineY}, 0.35);
            if(lineY > SHEETSIZE.height - 60)
            {
                textY = lineY + ((SHEETSIZE.height - 10) - lineY) / 2;
                drawText(Coordinate{17.5, textY}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            else
            {
                drawText(Coordinate{17.5, lineY + 25}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            // Right
            if(lineY < SHEETSIZE.height - spaceBottom)
            {
                drawLine(Coordinate{SHEETSIZE.width - 5, lineY}, Coordinate{SHEETSIZE.width - 10, lineY}, 0.35);
            }
            if(SHEETSIZE.width >= 297  && lineY <= SHEETSIZE.height - 60 && SHEETSIZE.height >= 297)
            {
                drawText(Coordinate{SHEETSIZE.width - 7.5, lineY + 25}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            else if(SHEETSIZE.width >= 297  && lineY > SHEETSIZE.height - 60 && SHEETSIZE.height >= 297)
            {
                drawText(Coordinate{SHEETSIZE.width - 7.5, textY}, NumToABC(index), "", 3.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.35);
            }
            lineY += 50;
            index++;
        }
    }
//    TOPRIGHTDRAWINGCORNER.X = SHEETSIZE.width - 10;
//    TOPRIGHTDRAWINGCORNER.Y = 10;
//    TOPLEFTDRAWINGCORNER.X = 20;
//    TOPLEFTDRAWINGCORNER.Y = 10;
}

void TemplateGen::drawTitelblockISO7200()
{
    // Frame
    //Coordinate topLeft = Coordinate{SHEETSIZE.width - 190, SHEETSIZE.height - 10 - 11 * (5 + ISO7200OPTIONS->getNumOptLins())};
    if(FULLSHEETPARTSLIST && FULLSHEETPARTLISTOPIONS->getImporCSV() && FULLSHEETPARTLISTOPIONS->getBOMStyle() == BOMStyles::KiCAD)// needs to be last
    {
        QString key = getSheetFieldKey();
        TITELBLOCKFIELDS[key].Value = QList{QString::number(SHEETINDEX + 1) + "/" + QString::number(fullSheetPartsListNumSheetsKiCAD())};
    }
    Coordinate topLeft = TOPLEFTTITELBLOCKCORNER;

    if(SMALLPARTSLIST){
        double listHeight = 8 + ((2.5 * 1.5) * SMALLPARTSLISTSOPTIONS->getNumLinesPerField() + 3) * SMALLPARTSLISTSOPTIONS->getNumParts();

        topLeft.Y += listHeight;
    }

    double descHeight = 0;
    if(ISO7200OPTIONS->getDescField())
    {
        descHeight = (2.5 * 1.5) * (ISO7200OPTIONS->getNumDescLines() + 1) + 3.7;
        drawText(Coordinate{topLeft.X + 1.5, topLeft.Y + 1.5}, TITELBLOCKFIELDS["opt23"].Label, TITELBLOCKFIELDS["opt23"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
        drawText(Coordinate{topLeft.X + 1.5, topLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt23"].Value, TITELBLOCKFIELDS["opt23"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
        topLeft = Coordinate{topLeft.X, topLeft.Y + descHeight};
        drawRect(Coordinate{topLeft.X, topLeft.Y - descHeight}, Coordinate{SHEETSIZE.width - 10, topLeft.Y}, 0.7);
    }

    drawRect(topLeft, Coordinate{SHEETSIZE.width - 10, SHEETSIZE.height - 10}, 0.7);
    // Vertical
    drawLine(Coordinate{topLeft.X + 80, topLeft.Y}, Coordinate{topLeft.X + 80, SHEETSIZE.height-10}, 0.35);
    drawLine(Coordinate{topLeft.X + 140, topLeft.Y}, Coordinate{topLeft.X + 140, SHEETSIZE.height-10}, 0.35);
    drawLine(Coordinate{topLeft.X + 152, SHEETSIZE.height - 10 - 22}, Coordinate{topLeft.X + 152, SHEETSIZE.height-10}, 0.35);
    // Horizontal
    Coordinate lastLineLeft = topLeft;
    for(qint64 i = 0; i < ISO7200OPTIONS->getNumOptLins(); i++)
    {
        if(ISO7200OPTIONS->getNumOptLins() == 3 && i == 0)
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
        else if((ISO7200OPTIONS->getNumOptLins() == 3 && i == 1) || (ISO7200OPTIONS->getNumOptLins() == 2 && i == 0))
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
        else if((ISO7200OPTIONS->getNumOptLins() == 3 && i == 2) || (ISO7200OPTIONS->getNumOptLins() == 2 && i == 1) || (ISO7200OPTIONS->getNumOptLins() == 1 && i == 0))
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
        drawLine(lastLineLeft, Coordinate{SHEETSIZE.width - 10, lastLineLeft.Y}, 0.35);
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
    drawLine(lastLineLeft, Coordinate{SHEETSIZE.width - 10, lastLineLeft.Y}, 0.35);

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
    drawLine(lastLineLeft, Coordinate{SHEETSIZE.width - 10, lastLineLeft.Y}, 0.35);

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
    drawLine(lastLineLeft, Coordinate{SHEETSIZE.width - 10, lastLineLeft.Y}, 0.35);

    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt19"].Label, TITELBLOCKFIELDS["opt19"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 12, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt20"].Label, TITELBLOCKFIELDS["opt20"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt19"].Value, TITELBLOCKFIELDS["opt19"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 12, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt20"].Value, TITELBLOCKFIELDS["opt20"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    lastLineLeft = Coordinate{lastLineLeft.X, lastLineLeft.Y + 11};
    drawLine(lastLineLeft, Coordinate{SHEETSIZE.width - 10, lastLineLeft.Y}, 0.35);

    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt21"].Label, TITELBLOCKFIELDS["opt21"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 12, lastLineLeft.Y + 1.5}, TITELBLOCKFIELDS["opt22"].Label, TITELBLOCKFIELDS["opt22"].Name + "_l", 1.8, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.18, false);
    drawText(Coordinate{lastLineLeft.X + 1.5, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt21"].Value, TITELBLOCKFIELDS["opt21"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
    drawText(Coordinate{lastLineLeft.X + 1.5 + 12, lastLineLeft.Y + 1.5 + 4.75}, TITELBLOCKFIELDS["opt22"].Value, TITELBLOCKFIELDS["opt22"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Left, 0.25, true);
}

void TemplateGen::drawRevHistoryASME_Y14_35_Width180()
{
    drawRect(Coordinate{TOPRIGHTDRAWINGCORNER.X - 180, TOPRIGHTDRAWINGCORNER.Y}, Coordinate{TOPRIGHTDRAWINGCORNER.X, TOPRIGHTDRAWINGCORNER.Y + 8 + ASME_Y14_35_WIDTH180->getNumRev() * (ASME_Y14_35_WIDTH180->getNumLinesRev() * 3.5 + 2)}, 0.7);
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
    drawLine(Coordinate{TOPRIGHTDRAWINGCORNER.X - 165, TOPRIGHTDRAWINGCORNER.Y + 4}, Coordinate{TOPRIGHTDRAWINGCORNER.X - 165, TOPRIGHTDRAWINGCORNER.Y + 8 + ASME_Y14_35_WIDTH180->getNumRev() * (ASME_Y14_35_WIDTH180->getNumLinesRev() * 3.5 + 2)}, 0.35);
    drawLine(Coordinate{TOPRIGHTDRAWINGCORNER.X - 145, TOPRIGHTDRAWINGCORNER.Y + 4}, Coordinate{TOPRIGHTDRAWINGCORNER.X - 145, TOPRIGHTDRAWINGCORNER.Y + 8 + ASME_Y14_35_WIDTH180->getNumRev() * (ASME_Y14_35_WIDTH180->getNumLinesRev() * 3.5 + 2)}, 0.35);
    drawLine(Coordinate{TOPRIGHTDRAWINGCORNER.X - 50, TOPRIGHTDRAWINGCORNER.Y + 4}, Coordinate{TOPRIGHTDRAWINGCORNER.X - 50, TOPRIGHTDRAWINGCORNER.Y + 8 + ASME_Y14_35_WIDTH180->getNumRev() * (ASME_Y14_35_WIDTH180->getNumLinesRev() * 3.5 + 2)}, 0.35);
    drawLine(Coordinate{TOPRIGHTDRAWINGCORNER.X - 30, TOPRIGHTDRAWINGCORNER.Y + 4}, Coordinate{TOPRIGHTDRAWINGCORNER.X - 30, TOPRIGHTDRAWINGCORNER.Y + 8 + ASME_Y14_35_WIDTH180->getNumRev() * (ASME_Y14_35_WIDTH180->getNumLinesRev() * 3.5 + 2)}, 0.35);

    // Lines
    for(unsigned int i = 0; i < ASME_Y14_35_WIDTH180->getNumRev(); i++)
    {
        drawLine(Coordinate{TOPRIGHTDRAWINGCORNER.X, TOPRIGHTDRAWINGCORNER.Y + 8 + (ASME_Y14_35_WIDTH180->getNumLinesRev() * 3.5 + 2) * i}, Coordinate{TOPRIGHTDRAWINGCORNER.X - 180, TOPRIGHTDRAWINGCORNER.Y + 8 + (ASME_Y14_35_WIDTH180->getNumLinesRev() * 3.5 + 2) * i}, 0.35);
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 172.5, TOPRIGHTDRAWINGCORNER.Y + 9.5 + (ASME_Y14_35_WIDTH180->getNumLinesRev() * 3.5 + 2) * i}, REVHISTORYFIELDS["opt1"].Value, TITELBLOCKFIELDS["opt1"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 155, TOPRIGHTDRAWINGCORNER.Y + 9.5 + (ASME_Y14_35_WIDTH180->getNumLinesRev() * 3.5 + 2) * i}, REVHISTORYFIELDS["opt2"].Value, TITELBLOCKFIELDS["opt2"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 97.5, TOPRIGHTDRAWINGCORNER.Y + 9.5 + (ASME_Y14_35_WIDTH180->getNumLinesRev() * 3.5 + 2) * i}, REVHISTORYFIELDS["opt3"].Value, TITELBLOCKFIELDS["opt3"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 40, TOPRIGHTDRAWINGCORNER.Y + 9.5 + (ASME_Y14_35_WIDTH180->getNumLinesRev() * 3.5 + 2) * i}, REVHISTORYFIELDS["opt4"].Value, TITELBLOCKFIELDS["opt4"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{TOPRIGHTDRAWINGCORNER.X - 15, TOPRIGHTDRAWINGCORNER.Y + 9.5 + (ASME_Y14_35_WIDTH180->getNumLinesRev() * 3.5 + 2) * i}, REVHISTORYFIELDS["opt5"].Value, TITELBLOCKFIELDS["opt5"].Name, 2.5, TextHeightAnchor::Top, TextWidthAnchor::Center, 0.25, true, i);
    }
}

void TemplateGen::drawFoldLines(double depth)
{
    switch (SHEETSTYLE)
    {
    case SheetStyle::ISO5457_ISO7200:
        if(FOLDLINETARGET.sizeString == "A4P with border" && SHEETSIZE.height >= 297 && SHEETSIZE.width >= 210)
        {
            double len = 0; // length of the blocck
            int num = 0; // number of blocks
            do
            {
                num++;
                len = (SHEETSIZE.width - 210) / num;
            }while(len > 190 || num % 2 != 0);

            for(int i = 1; i <= num; i++)
            {
                drawVerFoldLine(20 + len * i, depth);
            }

            // Horizontal
            double indexHeight = SHEETSIZE.height - 297;
            while(indexHeight > 0)
            {
                drawHorFoldLine(indexHeight, depth);
                indexHeight -= 297;
            }

        }else if(FOLDLINETARGET.sizeString == "200mmX290mm with border" && SHEETSIZE.height >= 290 && SHEETSIZE.width >= 200)
        {
            double len = 0; // length of the blocck
            int num = 0; // number of blocks
            do
            {
                num++;
                len = (SHEETSIZE.width - 210) / num;
            }while(len > 180 || num % 2 != 0);

            drawVerFoldLine(SHEETSIZE.width - 10, depth);

            for(int i = 1; i <= num; i++)
            {
                drawVerFoldLine(20 + len * i, depth);
            }

            // Horizontal
            double indexHeight = SHEETSIZE.height - 290;
            while(indexHeight > 0)
            {
                drawHorFoldLine(indexHeight, depth);
                indexHeight -= 290;
            }

        }
        break;

    case SheetStyle::BLANK:
        break;
    }
}

void TemplateGen::drawSmallPartsList()
{
    double fildHeight = (2.5 * 1.5) * SMALLPARTSLISTSOPTIONS->getNumLinesPerField() + 3;
    double listHeight = 8 + (fildHeight) * SMALLPARTSLISTSOPTIONS->getNumParts();
    double bottom = TOPLEFTTITELBLOCKCORNER.Y + listHeight;
    Coordinate topLeft = TOPLEFTTITELBLOCKCORNER;
    drawRect(topLeft, Coordinate{TOPRIGHTDRAWINGCORNER.X, bottom}, 0.7);
    double width = TOPRIGHTDRAWINGCORNER.X - TOPLEFTTITELBLOCKCORNER.X;
    drawLine(Coordinate{topLeft.X + width * (double(1)/18), topLeft.Y}, Coordinate{topLeft.X + width * (double(1)/18), bottom}, 0.35);
    drawLine(Coordinate{topLeft.X + width * (double(5)/36), topLeft.Y}, Coordinate{topLeft.X + width * (double(5)/36), bottom}, 0.35);
    drawLine(Coordinate{topLeft.X + width * (double(7)/36), topLeft.Y}, Coordinate{topLeft.X + width * (double(7)/36), bottom}, 0.35);
    drawLine(Coordinate{topLeft.X + width * (double(21)/36), topLeft.Y}, Coordinate{topLeft.X + width * (double(21)/36), bottom}, 0.35);
    for(unsigned int i = 1; i <= SMALLPARTSLISTSOPTIONS->getNumParts(); i++)
    {
        QStringList opt1Val;
        QStringList opt2Val;
        QStringList opt3Val;
        QStringList opt4Val;
        QStringList opt5Val;
        for(unsigned int j = 0; j < SMALLPARTSLISTSOPTIONS->getNumLinesPerField(); j++)
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
    drawText(Coordinate{topLeft.X + (width * (double(1)/18)) / 2, bottom - 6}, SMALLPARTSLISTFIELDS["opt1"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{topLeft.X + width * (double(1)/18) + (width * (double(3)/36)) / 2, bottom - 6}, SMALLPARTSLISTFIELDS["opt2"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{topLeft.X + width * (double(5)/36) + (width * (double(2)/36)) / 2, bottom - 6}, SMALLPARTSLISTFIELDS["opt3"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{topLeft.X + width * (double(7)/36) + (width * (double(14)/36)) / 2, bottom - 6}, SMALLPARTSLISTFIELDS["opt4"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{topLeft.X + width * (double(21)/36) + (width * (double(15)/36)) / 2, bottom - 6}, SMALLPARTSLISTFIELDS["opt5"].Label, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);

    drawLine(Coordinate{topLeft.X, topLeft.Y + (fildHeight * SMALLPARTSLISTSOPTIONS->getNumParts()) + 4}, Coordinate{TOPRIGHTDRAWINGCORNER.X, topLeft.Y + (fildHeight * SMALLPARTSLISTSOPTIONS->getNumParts()) + 4}, 0.35);

    drawText(Coordinate{topLeft.X + (width * (double(1)/18)) / 2, bottom - 2}, "1", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{topLeft.X + width * (double(1)/18) + (width * (double(3)/36)) / 2, bottom - 2}, "2", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{topLeft.X + width * (double(5)/36) + (width * (double(2)/36)) / 2, bottom - 2}, "3", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{topLeft.X + width * (double(7)/36) + (width * (double(14)/36)) / 2, bottom - 2}, "4", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{topLeft.X + width * (double(21)/36) + (width * (double(15)/36)) / 2, bottom - 2}, "5", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
}

void TemplateGen::drawFullSheetPartsList()
{
    double width = TOPRIGHTFULLPARTLIST.X - TOPLEFTFULLPARTLIST.X;
    double left = TOPLEFTFULLPARTLIST.X;
    double right = TOPRIGHTFULLPARTLIST.X;
    double top = TOPRIGHTFULLPARTLIST.Y;
    double bottom = BOTTOMRIGHTFULLPARTLIST.Y;
    double fieldHeight = (2.5 * 1.5) * FULLSHEETPARTLISTOPIONS->getNumLinesPerField() + 3;
    //Boarder
    drawRect(TOPLEFTFULLPARTLIST, BOTTOMRIGHTFULLPARTLIST, 0.7);
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
    //drawLine(Coordinate{left, bottom}, Coordinate{right, bottom}, 0.7);
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
        for(unsigned int j = 0; j < FULLSHEETPARTLISTOPIONS->getNumLinesPerField(); j++)
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

void TemplateGen::drawFullSheetPartsListCSVKiCAD()
{
    if(PARTINDEX == 0)
    {
        BOMKicad = readBOMKiCAD(FULLSHEETPARTLISTOPIONS->getBOMDIR());
    }
//    double width = TOPRIGHTDRAWINGCORNER.X - TOPLEFTDRAWINGCORNER.X;
//    double left = TOPLEFTDRAWINGCORNER.X;
//    double right = TOPRIGHTDRAWINGCORNER.X;
//    double top = TOPRIGHTDRAWINGCORNER.Y;
//    double bottom = TOPLEFTTITELBLOCKCORNER.Y;


    double width = TOPRIGHTFULLPARTLIST.X - TOPLEFTFULLPARTLIST.X;
    double left = TOPLEFTFULLPARTLIST.X;
    double right = TOPRIGHTFULLPARTLIST.X;
    double top = TOPRIGHTFULLPARTLIST.Y;
    double bottom = BOTTOMRIGHTFULLPARTLIST.Y;
    //Boarder
    drawRect(TOPLEFTFULLPARTLIST, BOTTOMRIGHTFULLPARTLIST, 0.7);

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
    drawText(Coordinate{left + (width * (2/double(36))) / 2, top + 6}, "Pos.", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{left + width * (2/double(36)) + (width * (3/double(36))) / 2, top + 6}, "Ref.", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{left + width * (5/double(36)) + (width * (2/double(36))) / 2, top + 6}, "Qty.", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{left + width * (7/double(36)) + (width * (14/double(36))) / 2, top + 6}, "Name", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{left + width * (21/double(36)) + (width * (8/double(36))) / 2, top + 6}, "Value", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawText(Coordinate{left + width * (29/double(36)) + (width * (7/double(36))) / 2, top + 6}, "Description", "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
    drawLine(Coordinate{left, top + 8}, Coordinate{right, top + 8}, 0.7);
    drawLine(Coordinate{left, bottom}, Coordinate{right, bottom}, 0.7);
    top += 8;
    // Part list
    double indexTop = top;
    int i = PARTINDEX;
    QStringList opt1Val;
    QStringList opt2Val;
    QStringList opt3Val;
    QStringList opt4Val;
    QStringList opt5Val;
    QStringList opt6Val;
    QString line = BOMKicad.first();
    int lines = splitBOMlineKiCAD(line, opt1Val, opt2Val, opt3Val, opt4Val, opt5Val, opt6Val);
    double fieldHeight = (2.5 * 1.5) * lines + 3;
    while(indexTop + fieldHeight <= bottom && BOMKicad.size() > 0)
    {
        i++;
        line = BOMKicad.first();
        BOMKicad.pop_front();
        lines = splitBOMlineKiCAD(line, opt1Val, opt2Val, opt3Val, opt4Val, opt5Val, opt6Val);
        fieldHeight = (2.5 * 1.5) * lines + 3;

        drawText(Coordinate{left + (width * (2/double(36))) / 2, indexTop + fieldHeight/2}, QString::number(i), FULLSHEETPARTSLISTFIELDS["opt1"].Name, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true);
        drawText(Coordinate{left + width * (2/double(36)) + (width * (3/double(36))) / 2, indexTop + fieldHeight/2}, opt2Val, FULLSHEETPARTSLISTFIELDS["opt2"].Name, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{left + width * (5/double(36)) + (width * (2/double(36))) / 2, indexTop + fieldHeight/2}, opt3Val, FULLSHEETPARTSLISTFIELDS["opt3"].Name, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{left + width * (7/double(36)) + (width * (14/double(36))) / 2, indexTop + fieldHeight/2}, opt4Val, FULLSHEETPARTSLISTFIELDS["opt4"].Name, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{left + width * (21/double(36)) + (width * (8/double(36))) / 2, indexTop + fieldHeight/2}, opt5Val, FULLSHEETPARTSLISTFIELDS["opt5"].Name, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawText(Coordinate{left + width * (29/double(36)) + (width * (7/double(36))) / 2 - 2, indexTop + fieldHeight/2}, opt6Val, FULLSHEETPARTSLISTFIELDS["opt6"].Name, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
        drawLine(Coordinate{left, indexTop}, Coordinate{right, indexTop}, 0.35);
        indexTop +=fieldHeight;
    }
    drawLine(Coordinate{left, indexTop}, Coordinate{right, indexTop}, 0.35);
    PARTINDEX = i;


    if(BOMKicad.size() > 0 && newSheet())
    {
        SHEETINDEX++;
        draw();
    }
}

void TemplateGen::drawFullSheetPartsListCSVStd()
{
    if(PARTINDEX == 0)
    {
        BOMStd = readBOMStd(FULLSHEETPARTLISTOPIONS->getBOMDIR());
    }
//    double left = TOPLEFTDRAWINGCORNER.X;
    double widthOffset = 0;
//    double right = TOPRIGHTDRAWINGCORNER.X;
//    double top = TOPRIGHTDRAWINGCORNER.Y;
//    double bottom = TOPLEFTTITELBLOCKCORNER.Y;
    double fieldHeight = (2.5 * 1.5) * 1 + 3;


    double width = TOPRIGHTFULLPARTLIST.X - TOPLEFTFULLPARTLIST.X;
    double left = TOPLEFTFULLPARTLIST.X;
    double right = TOPRIGHTFULLPARTLIST.X;
    double top = TOPRIGHTFULLPARTLIST.Y;
    double bottom = BOTTOMRIGHTFULLPARTLIST.Y;
    //Boarder
    drawRect(TOPLEFTFULLPARTLIST, BOTTOMRIGHTFULLPARTLIST, 0.7);

    // Vertival
    foreach (BOMColumn c, BOMStd)
    {
        widthOffset += c.Width;
        drawLine(Coordinate{left + widthOffset, top}, Coordinate{left + widthOffset, bottom}, 0.35);
    }
    widthOffset = 0;

    // Head
    int j = 1;
    foreach (BOMColumn c, BOMStd)
    {
        drawText(Coordinate{left + widthOffset + c.Width/2, top + 2}, QString::number(j), "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
        widthOffset += c.Width;
        j++;
    }
    widthOffset = 0;
    top += 4;
    drawLine(Coordinate{left, top}, Coordinate{right, top}, 0.35);
    foreach (BOMColumn c, BOMStd)
    {
        drawText(Coordinate{left + widthOffset + c.Width/2, top + 2}, c.Title, "", 1.8, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.18, false);
        widthOffset += c.Width;
    }
    widthOffset = 0;
    drawLine(Coordinate{left, top + 4}, Coordinate{right, top + 4}, 0.7);
    drawLine(Coordinate{left, bottom}, Coordinate{right, bottom}, 0.7);
    top += 4;
    // Part list
    double indexTop = top;
    int i = PARTINDEX;

    while(indexTop + fieldHeight <= bottom && BOMStd.first().Values.size() > 0)
    {
        i++;
        // Get Field Height
        int lines = 0;
        foreach (BOMColumn c, BOMStd)
        {
            int l = splitBOMValStd(c.Values.first(), c.Width - 2).length();
            if(l > lines)
            {
                lines = l;
            }
        }
        fieldHeight = (2.5 * 1.5) * lines + 3;
        //Write Values
        for(int c = 0; c < BOMStd.size() ; c++)
        {
            drawText(Coordinate{left + widthOffset + BOMStd[c].Width/2, indexTop + fieldHeight/2}, splitBOMValStd(BOMStd[c].Values.first(), BOMStd[c].Width - 2), FULLSHEETPARTSLISTFIELDS["opt2"].Name, 2.5, TextHeightAnchor::Middle, TextWidthAnchor::Center, 0.25, true, i);
            widthOffset += BOMStd[c].Width;
            BOMStd[c].Values.pop_front();

        }
        widthOffset = 0;
        indexTop +=fieldHeight;
        drawLine(Coordinate{left, indexTop}, Coordinate{right, indexTop}, 0.35);
    }
    PARTINDEX = i;

    if(BOMStd.first().Values.size() > 0 && newSheet())
    {
        SHEETINDEX++;
        draw();
    }
}

int TemplateGen::fullSheetPartsListNumSheetsKiCAD()
{
    int partindex = 0;
    int sheetindex = 0;
    bool stillCounting = true;
    QList<QString> bom = readBOMKiCAD(FULLSHEETPARTLISTOPIONS->getBOMDIR());

    do
    {
        double top = TOPRIGHTDRAWINGCORNER.Y;
        double bottom = TOPLEFTTITELBLOCKCORNER.Y;
        top += 8;
        double indexTop = top;
        int i = partindex;
        QStringList opt1Val;
        QStringList opt2Val;
        QStringList opt3Val;
        QStringList opt4Val;
        QStringList opt5Val;
        QStringList opt6Val;
        QString line = bom.first();
        int lines = splitBOMlineKiCAD(line, opt1Val, opt2Val, opt3Val, opt4Val, opt5Val, opt6Val);
        double fieldHeight = (2.5 * 1.5) * lines + 3;
        while(indexTop + fieldHeight <= bottom && bom.size() > 0)
        {
            i++;
            line = bom.first();
            bom.pop_front();
            lines = splitBOMlineKiCAD(line, opt1Val, opt2Val, opt3Val, opt4Val, opt5Val, opt6Val);
            fieldHeight = (2.5 * 1.5) * lines + 3;

            indexTop +=fieldHeight;
        }
        partindex = i;


        if(bom.size() > 0)
        {
            sheetindex++;
        }else
        {
            sheetindex++;
            stillCounting = false;
        }
    }while(stillCounting);
    return sheetindex;
}

QString TemplateGen::getSheetFieldKey()
{
    QList<QString> keys = TITELBLOCKFIELDS.keys();
    QList<TitelblockField> field = TITELBLOCKFIELDS.values();
    for(int i = 0; i < keys.size(); i++)
    {
        if(field[i].Label == "Sheet" || field[i].Label == "Seite")
        {
            return keys[i];
        }
    }
    return "opt1";
}

void TemplateGen::drawISO5457_ISO7200()
{
    if(ISO7200OPTIONS->getTrimmingMarks())
    {
        drawTrimmingMarksISO5457();
    }
    drawDrawingBorderISO5457();

    drawTitelblockISO7200();

//    drawLine(TOPLEFTDRAWINGCORNER, BOTTOMRIGHTDRAWINGCORNER, .6);
//    drawLine(TOPRIGHTDRAWINGCORNER, BOTTOMLEFTDRAWINGCORNER, .6);

//    drawLine(TOPLEFTTITELBLOCKCORNER, TOPLEFTDRAWINGCORNER, 0.8);
//    drawLine(BOTTOMLEFTREVHISTORY, TOPLEFTDRAWINGCORNER, 0.8);

//    drawLine(TOPLEFTFULLPARTLIST, BOTTOMRIGHTFULLPARTLIST, .6);
//    drawLine(TOPRIGHTFULLPARTLIST, BOTTOMLEFTFULLPARTLIST, .6);
}

void TemplateGen::drawBlank()
{
    //TRIMMINGMARKS = false;
//    ISO7200OPTIONS->setTrimmingMarks(false);
//    REVHISTORY = false;
//    FOLDLINES = false;
//    SMALLPARTSLIST = false;
//    FULLSHEETPARTSLIST = false;
//    FULLSHEETPARTLISTOPIONS->getImporCSV() = false;
//    LOGO = false;
//    DESCRIPTION = false;
}

void TemplateGen::drawProjectionMethod(Coordinate at, ProjectionMethodType what)
{
    const double unit = double(10)/24;
    QList<Coordinate> listA{
        Coordinate{-30 * unit, 2 * unit},
        Coordinate{-30 * unit, 22 * unit},
        Coordinate{-50 * unit, 16 * unit},
        Coordinate{-50 * unit, 8 * unit},
    };
    QList<Coordinate> listB{
        Coordinate{-7 * unit, 2 * unit},
        Coordinate{-7 * unit, 22 * unit},
        Coordinate{-27 * unit, 16 * unit},
        Coordinate{-27 * unit, 8 * unit},
    };
    switch (what) {
    case ProjectionMethodType::None:
        break;
    case ProjectionMethodType::FirstAngle:
        drawCircle(Coordinate{17 * -unit + at.X, 12 * unit + at.Y}, 5 * unit, .35);
        drawCircle(Coordinate{17 * -unit + at.X, 12 * unit + at.Y}, 10 * unit, .35);

        drawPoly(at, listA, .35, false);

        drawSlimDotLine(Coordinate{-52 * unit + at.X, 12 * unit + at.Y}, Coordinate{5 * -unit + at.X, 12 * unit + at.Y}, .18);
        drawSlimDotLine(Coordinate{-17 * unit + at.X, 0 * unit + at.Y}, Coordinate{17 * -unit + at.X, 24 * unit + at.Y}, .18);
        break;
    case ProjectionMethodType::ThirdAngle:
        drawPoly(at, listB, .35, false);

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
        if(NODRAW)
        {
            return;
        }
        qint64 foldlinesDepth = 0;
        switch (SHEETSTYLE)
        {
        case SheetStyle::ISO5457_ISO7200:
            drawISO5457_ISO7200();
            foldlinesDepth = 5;
            break;
        case SheetStyle::BLANK:
            drawBlank();
            foldlinesDepth = 0;
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

        if(FULLSHEETPARTSLIST && !FULLSHEETPARTLISTOPIONS->getImporCSV())
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


        if(FULLSHEETPARTSLIST && FULLSHEETPARTLISTOPIONS->getImporCSV() && FULLSHEETPARTLISTOPIONS->getBOMStyle() == BOMStyles::Standard)// needs to be last
        {
            drawFullSheetPartsListCSVStd();
        }else if(FULLSHEETPARTSLIST && FULLSHEETPARTLISTOPIONS->getImporCSV() && FULLSHEETPARTLISTOPIONS->getBOMStyle() == BOMStyles::KiCAD)// needs to be last
        {
            drawFullSheetPartsListCSVKiCAD();
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

const SheetSize &TemplateGen::getSHEETSIZE() const
{
    return SHEETSIZE;
}

void TemplateGen::setSHEETSIZE(const SheetSize &newSHEETSIZE)
{
    finisheD.sheetsizeE = true;
    SHEETSIZE = newSHEETSIZE;
}

SheetStyle TemplateGen::getSHEETSTYLE() const
{
    return SHEETSTYLE;
}

void TemplateGen::setSHEETSTYLE(SheetStyle newSHEETSTYLE)
{
    finisheD.sheetstylE = true;
    SHEETSTYLE = newSHEETSTYLE;
}

qint64 TemplateGen::getNUMOPTLINES() const
{
    return ISO7200OPTIONS->getNumOptLins();
}

void TemplateGen::setNUMOPTLINES(qint64 newNUMOPTLINES)
{
    //NUMOPTLINES = NUMOPTLINES;
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

const SheetSize &TemplateGen::getFOLDLINETARGET() const
{
    return FOLDLINETARGET;
}

void TemplateGen::setFOLDLINETARGET(const SheetSize &newFOLDLINETARGET)
{
    FOLDLINETARGET = newFOLDLINETARGET;
    finisheD.foldlinestargeT = true;
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

const QMap<QString, TitelblockField> &TemplateGen::getFULLSHEETPARTSLISTFIELDS() const
{
    return FULLSHEETPARTSLISTFIELDS;
}

void TemplateGen::setFULLSHEETPARTSLISTFIELDS(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS)
{
    FULLSHEETPARTSLISTFIELDS = newFULLSHEETPARTSLISTFIELDS;
    finisheD.fullsheetpartlistfieldS = true;
}
