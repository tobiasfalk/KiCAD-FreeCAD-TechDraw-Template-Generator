#include "templateoptions.h"

QStringList NumToABC(qint64 num)
{
    QStringList ret;
    num--;
    QList<QString> abc = {"A", "B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    QList<qint64> abcNum = {0};
    for(int i = 0; i < num; i++)
    {
        abcNum[0]++;
        for(int n = 0; n < abcNum.length(); n++)
        {
            if(abcNum[n] == 24 && n == abcNum.length() - 1)
            {
                abcNum[n] = 0;
                abcNum.append(0);
            }
            else if(abcNum[n] == 24 && n != abcNum.length())
            {
                abcNum[n] = 0;
                abcNum[n+1]++;
            }
        }
    }

    foreach(qint64 i, abcNum)
    {
        ret.prepend(abc[i]);
    }
    return ret;
}

bool allFinisheD(FinisheD finisheD)
{
    if(!finisheD.diR)
    {
        return false;
    }
    else if(!finisheD.pagesizeE)
    {
        return false;
    }
    else if(!finisheD.sheetnamE)
    {
        return false;
    }
    else if(!finisheD.pagestylE)
    {
        return false;
    }
    else if(!finisheD.numoptlineS)
    {
        return false;
    }
    else if(!finisheD.titelblockfieldS)
    {
        return false;
    }
    else if(!finisheD.trimmingmarkS)
    {
        return false;
    }
    else if(!finisheD.revhistorY)
    {
        return false;
    }
    else if(!finisheD.revhistorystylE)
    {
        return false;
    }
    else if(!finisheD.numrevhistorY)
    {
        return false;
    }
    else if(!finisheD.revhistoryfieldS)
    {
        return false;
    }
    else if(!finisheD.foldlineS)
    {
        return false;
    }
    else if(!finisheD.foldlinestargeT)
    {
        return false;
    }
    else if(!finisheD.smallpartslisT)
    {
        return false;
    }
    else if(!finisheD.numpartssmallpartslisT)
    {
        return false;
    }
    else if(!finisheD.numlinessmallpartslisT)
    {
        return false;
    }
    else if(!finisheD.smallpartslistfieldS)
    {
        return false;
    }
    else if(!finisheD.fullsheetpartslisT)
    {
        return false;
    }
    else if(!finisheD.numlinesfullsheetpartslisT)
    {
        return false;
    }
    else if(!finisheD.fullsheetpartlistfieldS)
    {
        return false;
    }
    else if(!finisheD.numsheetsfullsheetpartslisT)
    {
        return false;
    }
    else if(!finisheD.logO)
    {
        return false;
    }
    else if(!finisheD.logodiR)
    {
        return false;
    }
    return true;
}

void printFinisheD(FinisheD finisheD)
{
    qDebug() << "diR: " << finisheD.diR;
    qDebug() << "pagesizeE: " << finisheD.pagesizeE;
    qDebug() << "sheetnamE: " << finisheD.sheetnamE;
    qDebug() << "numoptlineS: " << finisheD.numoptlineS;
    qDebug() << "numrevhistorY: " << finisheD.numrevhistorY;
    qDebug() << "pagestylE: " << finisheD.pagestylE;
    qDebug() << "revhistorY: " << finisheD.revhistorY;
    qDebug() << "revhistoryfieldS: " << finisheD.revhistoryfieldS;
    qDebug() << "revhistorystylE: " << finisheD.revhistorystylE;
    qDebug() << "titelblockfieldS: " << finisheD.titelblockfieldS;
    qDebug() << "trimmingmarkS: " << finisheD.trimmingmarkS;
    qDebug() << "foldlineS: " << finisheD.foldlineS;
    qDebug() << "foldlinestargeT: " << finisheD.foldlinestargeT;
    qDebug() << "smallpartslisT: " << finisheD.smallpartslisT;
    qDebug() << "numpartssmallpartslisT: " << finisheD.numpartssmallpartslisT;
    qDebug() << "numlinessmallpartslisT: " << finisheD.numlinessmallpartslisT;
    qDebug() << "smallpartslistfieldS: " << finisheD.smallpartslistfieldS;
    qDebug() << "fullsheetpartslist: " << finisheD.fullsheetpartslisT;
    qDebug() << "numlinesfullsheetpartslisT: " << finisheD.numlinesfullsheetpartslisT;
    qDebug() << "fullsheetpartlistfieldS: " << finisheD.fullsheetpartlistfieldS;
    qDebug() << "numsheetsfullsheetpartslisT: " << finisheD.numsheetsfullsheetpartslisT;
    qDebug() << "logO: " << finisheD.logO;
    qDebug() << "logodiR: " << finisheD.logodiR;
}
