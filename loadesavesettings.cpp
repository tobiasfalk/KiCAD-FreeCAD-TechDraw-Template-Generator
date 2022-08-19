#include "loadesavesettings.h"

#include <QtXml>
#include <QTextStream>

const PageSize &LoadeSaveSettings::getSHEETSIZE() const
{
    return SHEETSIZE;
}

void LoadeSaveSettings::setSHEETSIZE(const PageSize &newSHEETSIZE)
{
    SHEETSIZE = newSHEETSIZE;
    finisheD.pagesizeE = true;
}

PageStyle LoadeSaveSettings::getSHEETSTYLE() const
{
    return SHEETSTYLE;
}

void LoadeSaveSettings::setSHEETSTYLE(PageStyle newSHEETSTYLE)
{
    SHEETSTYLE = newSHEETSTYLE;
    finisheD.pagestylE = true;
}

const QMap<QString, TitelblockField> &LoadeSaveSettings::getTITELBLOCKFIELDS() const
{
    return TITELBLOCKFIELDS;
}

void LoadeSaveSettings::setTITELBLOCKFIELDS(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS)
{
    TITELBLOCKFIELDS = newTITELBLOCKFIELDS;
    finisheD.titelblockfieldS = true;
}

qint64 LoadeSaveSettings::getNUMOPTLINES() const
{
    return NUMOPTLINES;
}

void LoadeSaveSettings::setNUMOPTLINES(qint64 newNUMOPTLINES)
{
    NUMOPTLINES = newNUMOPTLINES;
    finisheD.numoptlineS = true;
}

qint64 LoadeSaveSettings::getNUMREVHISTORY() const
{
    return NUMREVHISTORY;
}

void LoadeSaveSettings::setNUMREVHISTORY(qint64 newNUMREVHISTORY)
{
    NUMREVHISTORY = newNUMREVHISTORY;
    finisheD.numrevhistorY = true;
}

bool LoadeSaveSettings::getTRIMMINGMARKS() const
{
    return TRIMMINGMARKS;
}

void LoadeSaveSettings::setTRIMMINGMARKS(bool newTRIMMINGMARKS)
{
    TRIMMINGMARKS = newTRIMMINGMARKS;
    finisheD.trimmingmarkS = true;
}

bool LoadeSaveSettings::getREVHISTORY() const
{
    return REVHISTORY;
}

void LoadeSaveSettings::setREVHISTORY(bool newREVHISTORY)
{
    REVHISTORY = newREVHISTORY;
    finisheD.revhistorY = true;
}

bool LoadeSaveSettings::getFOLDLINES() const
{
    return FOLDLINES;
}

void LoadeSaveSettings::setFOLDLINES(bool newFOLDLINES)
{
    FOLDLINES = newFOLDLINES;
    finisheD.foldlineS = true;
}

const PageSize &LoadeSaveSettings::getFOLDLINESTARGET() const
{
    return FOLDLINESTARGET;
}

void LoadeSaveSettings::setFOLDLINESTARGET(const PageSize &newFOLDLINESTARGET)
{
    FOLDLINESTARGET = newFOLDLINESTARGET;
    finisheD.foldlinestargeT = true;
}

bool LoadeSaveSettings::getSMALLPARTSLIST() const
{
    return SMALLPARTSLIST;
}

void LoadeSaveSettings::setSMALLPARTSLIST(bool newSMALLPARTSLIST)
{
    SMALLPARTSLIST = newSMALLPARTSLIST;
    finisheD.smallpartslisT = true;
}

quint64 LoadeSaveSettings::getNUMLINESSMALLPARTSLIST() const
{
    return NUMLINESSMALLPARTSLIST;
}

void LoadeSaveSettings::setNUMLINESSMALLPARTSLIST(quint64 newNUMLINESSMALLPARTSLIST)
{
    NUMLINESSMALLPARTSLIST = newNUMLINESSMALLPARTSLIST;
    finisheD.numlinessmallpartslisT = true;
}

quint64 LoadeSaveSettings::getNUMPARTSSMALLPARTSLIST() const
{
    return NUMPARTSSMALLPARTSLIST;
}

void LoadeSaveSettings::setNUMPARTSSMALLPARTSLIST(quint64 newNUMPARTSSMALLPARTSLIST)
{
    NUMPARTSSMALLPARTSLIST = newNUMPARTSSMALLPARTSLIST;
    finisheD.numpartssmallpartslisT = true;
}

const QMap<QString, TitelblockField> &LoadeSaveSettings::getSMALLPARTSLISTFIELDS() const
{
    return SMALLPARTSLISTFIELDS;
}

void LoadeSaveSettings::setSMALLPARTSLISTFIELDS(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS)
{
    SMALLPARTSLISTFIELDS = newSMALLPARTSLISTFIELDS;
    finisheD.smallpartslistfieldS = true;
}

bool LoadeSaveSettings::getFULLSHEETPARTSLIST() const
{
    return FULLSHEETPARTSLIST;
}

void LoadeSaveSettings::setFULLSHEETPARTSLIST(bool newFULLSHEETPARTSLIST)
{
    FULLSHEETPARTSLIST = newFULLSHEETPARTSLIST;
    finisheD.fullsheetpartslisT = true;
}

quint64 LoadeSaveSettings::getNUMLINESFULLSHEETPARTSLIST() const
{
    return NUMLINESFULLSHEETPARTSLIST;
}

void LoadeSaveSettings::setNUMLINESFULLSHEETPARTSLIST(quint64 newNUMLINESFULLSHEETPARTSLIST)
{
    NUMLINESFULLSHEETPARTSLIST = newNUMLINESFULLSHEETPARTSLIST;
    finisheD.numlinesfullsheetpartslisT = true;
}

quint64 LoadeSaveSettings::getNUMSHEETSFULLSHEETPARTSLIST() const
{
    return NUMSHEETSFULLSHEETPARTSLIST;
}

void LoadeSaveSettings::setNUMSHEETSFULLSHEETPARTSLIST(quint64 newNUMLINESSHEETFULLSHEETPARTSLIST)
{
    NUMSHEETSFULLSHEETPARTSLIST = newNUMLINESSHEETFULLSHEETPARTSLIST;
    finisheD.numsheetsfullsheetpartslisT = true;
}

bool LoadeSaveSettings::getLOGO() const
{
    return LOGO;
}

void LoadeSaveSettings::setLOGO(bool newLOGO)
{
    LOGO = newLOGO;
    finisheD.logO = true;
}

const QString &LoadeSaveSettings::getLOGODIR() const
{
    return LOGODIR;
}

void LoadeSaveSettings::setLOGODIR(const QString &newLOGODIR)
{
    LOGODIR = newLOGODIR;
    finisheD.logodiR = true;
}

RevHistoryStyle LoadeSaveSettings::getREVHISTORYSTYLE() const
{
    return REVHISTORYSTYLE;
}

void LoadeSaveSettings::setREVHISTORYSTYLE(RevHistoryStyle newREVHISTORYSTYLE)
{
    REVHISTORYSTYLE = newREVHISTORYSTYLE;
    finisheD.revhistorystylE = true;
}

const QMap<QString, TitelblockField> &LoadeSaveSettings::getREVHISTORYFIELDS() const
{
    return REVHISTORYFIELDS;
}

void LoadeSaveSettings::setREVHISTORYFIELDS(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS)
{
    REVHISTORYFIELDS = newREVHISTORYFIELDS;
    finisheD.revhistoryfieldS = true;
}

const QMap<QString, TitelblockField> &LoadeSaveSettings::getFULLSHEETPARTSLISTFIELDS() const
{
    return FULLSHEETPARTSLISTFIELDS;
}

void LoadeSaveSettings::setFULLSHEETPARTSLISTFIELDS(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS)
{
    FULLSHEETPARTSLISTFIELDS = newFULLSHEETPARTSLISTFIELDS;
    finisheD.fullsheetpartlistfieldS = true;
}

const QString &LoadeSaveSettings::getSHEETNAME() const
{
    return SHEETNAME;
}

void LoadeSaveSettings::setSHEETNAME(const QString &newSHEETNAME)
{
    SHEETNAME = newSHEETNAME;
    finisheD.sheetnamE = true;
}

QString LoadeSaveSettings::getSheetStyleString()
{
    QString ret = "";
    switch (SHEETSTYLE)
    {
    case PageStyle::ISO5457_ISO7200:
        ret = "ISO5457_ISO7200";
        break;
    }
    return ret;
}

PageStyle LoadeSaveSettings::toSheetStyle(QString style)
{
    if(style == "ISO5457_ISO7200")
    {
        return PageStyle::ISO5457_ISO7200;
    }
    return PageStyle::ISO5457_ISO7200;
}

QString LoadeSaveSettings::getRevHistoryStyleString()
{

    QString ret = "";
    switch (REVHISTORYSTYLE)
    {
    case RevHistoryStyle::ASME_Y14_35_Width180:
        ret = "ASME_Y14_35_Width180";
        break;
    }
    return ret;
}

RevHistoryStyle LoadeSaveSettings::toRevHistoryStyle(QString style)
{
    if(style == "ASME_Y14_35_Width180")
    {
        return RevHistoryStyle::ASME_Y14_35_Width180;
    }
    return RevHistoryStyle::ASME_Y14_35_Width180;
}

QString LoadeSaveSettings::stringListToString(QStringList list)
{
    QString ret = "";
    foreach(QString str, list)
    {
        ret.append(str + "&{n}");
    }
    return ret;
}

LoadeSaveSettings::LoadeSaveSettings(QObject *parent) : QObject(parent)
{

}

void LoadeSaveSettings::saveSettings(QString dir)
{
    QFile xmlFile(dir);
    if (!xmlFile.open(QFile::WriteOnly | QFile::Text ))
    {
        qDebug() << "Already opened or there is another issue";
        xmlFile.close();
    }
    QTextStream xmlContent(&xmlFile);

    QDomDocument document;

    //make the root element
    QDomElement root = document.createElement("SheetSettings");
    //add it to document
    document.appendChild(root);

    QDomElement settings = document.createElement("SheetSize");
    settings.setAttribute("name", "SheetSize");
    settings.setAttribute("sizeString", SHEETSIZE.sizeString);
    settings.setAttribute("height", SHEETSIZE.height);
    settings.setAttribute("width", SHEETSIZE.width);
    settings.setAttribute("sheetName", SHEETNAME);
    root.appendChild(settings);

    settings = document.createElement("SheetStyle");
    settings.setAttribute("name", "SheetStyle");
    settings.setAttribute("style", getSheetStyleString());
    settings.setAttribute("numOptLines", NUMOPTLINES);
    settings.setAttribute("trimmingMarks", TRIMMINGMARKS);
    foreach (const QString &str, TITELBLOCKFIELDS.keys())
    {
        QDomElement field = document.createElement("Opt");
        field.setAttribute("key", str);
        field.setAttribute("label", TITELBLOCKFIELDS.value(str).Label);
        field.setAttribute("valKiCAD5", stringListToString(TITELBLOCKFIELDS.value(str).ValueKiCAD5));
        field.setAttribute("valKiCAD6", stringListToString(TITELBLOCKFIELDS.value(str).ValueKiCAD6));
        field.setAttribute("nameFreeCAD", TITELBLOCKFIELDS.value(str).NameFreeCAD);
        field.setAttribute("valFreeCAD", stringListToString(TITELBLOCKFIELDS.value(str).ValueFreeCAD));
        settings.appendChild(field);
    }
    root.appendChild(settings);

    settings = document.createElement("RevHistory");
    settings.setAttribute("name", "RevHistory");
    settings.setAttribute("revHistory", REVHISTORY);
    settings.setAttribute("style", getRevHistoryStyleString());
    settings.setAttribute("num", NUMREVHISTORY);
    foreach (const QString &str, REVHISTORYFIELDS.keys())
    {
        QDomElement field = document.createElement("Opt");
        field.setAttribute("key", str);
        field.setAttribute("label", REVHISTORYFIELDS.value(str).Label);
        field.setAttribute("valKiCAD5", stringListToString(REVHISTORYFIELDS.value(str).ValueKiCAD5));
        field.setAttribute("valKiCAD6", stringListToString(REVHISTORYFIELDS.value(str).ValueKiCAD6));
        field.setAttribute("nameFreeCAD", REVHISTORYFIELDS.value(str).NameFreeCAD);
        field.setAttribute("valFreeCAD", stringListToString(REVHISTORYFIELDS.value(str).ValueFreeCAD));
        settings.appendChild(field);
    }
    root.appendChild(settings);

    settings = document.createElement("Foldlines");
    settings.setAttribute("name", "Foldlines");
    settings.setAttribute("foldlines", FOLDLINES);
    settings.setAttribute("targetString", FOLDLINESTARGET.sizeString);
    settings.setAttribute("targetHeight", FOLDLINESTARGET.height);
    settings.setAttribute("targetWidth", FOLDLINESTARGET.width);
    root.appendChild(settings);

    settings = document.createElement("SmallPartsList");
    settings.setAttribute("name", "SmallPartsList");
    settings.setAttribute("smallPartsList", SMALLPARTSLIST);
    settings.setAttribute("numLines", NUMLINESSMALLPARTSLIST);
    settings.setAttribute("numParts", NUMPARTSSMALLPARTSLIST);
    foreach (const QString &str, SMALLPARTSLISTFIELDS.keys())
    {
        QDomElement field = document.createElement("Opt");
        field.setAttribute("key", str);
        field.setAttribute("label", SMALLPARTSLISTFIELDS.value(str).Label);
        field.setAttribute("valKiCAD5", stringListToString(SMALLPARTSLISTFIELDS.value(str).ValueKiCAD5));
        field.setAttribute("valKiCAD6", stringListToString(SMALLPARTSLISTFIELDS.value(str).ValueKiCAD6));
        field.setAttribute("nameFreeCAD", SMALLPARTSLISTFIELDS.value(str).NameFreeCAD);
        field.setAttribute("valFreeCAD", stringListToString(SMALLPARTSLISTFIELDS.value(str).ValueFreeCAD));
        settings.appendChild(field);
    }
    root.appendChild(settings);

    settings = document.createElement("FullSheetPartsList");
    settings.setAttribute("name", "FullSheetPartsList");
    settings.setAttribute("fullSheetPartsList", FULLSHEETPARTSLIST);
    settings.setAttribute("numLines", NUMLINESFULLSHEETPARTSLIST);
    settings.setAttribute("numSheets", NUMSHEETSFULLSHEETPARTSLIST);
    foreach (const QString &str, FULLSHEETPARTSLISTFIELDS.keys())
    {
        QDomElement field = document.createElement("Opt");
        field.setAttribute("key", str);
        field.setAttribute("label", FULLSHEETPARTSLISTFIELDS.value(str).Label);
        field.setAttribute("valKiCAD5", stringListToString(FULLSHEETPARTSLISTFIELDS.value(str).ValueKiCAD5));
        field.setAttribute("valKiCAD6", stringListToString(FULLSHEETPARTSLISTFIELDS.value(str).ValueKiCAD6));
        field.setAttribute("nameFreeCAD", FULLSHEETPARTSLISTFIELDS.value(str).NameFreeCAD);
        field.setAttribute("valFreeCAD", stringListToString(FULLSHEETPARTSLISTFIELDS.value(str).ValueFreeCAD));
        settings.appendChild(field);
    }
    root.appendChild(settings);

    settings = document.createElement("Logo");
    settings.setAttribute("name", "Logo");
    settings.setAttribute("logo", LOGO);
    settings.setAttribute("logoDir", LOGODIR);
    root.appendChild(settings);



    xmlContent << document.toString();
}

void LoadeSaveSettings::loadSettings(QString dir)
{
    QFile file(dir);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Cannot read file" << file.errorString();
        exit(0);
    }

    QDomDocument xmlBOM;
    xmlBOM.setContent(&file);
    QDomElement root=xmlBOM.documentElement();

    // Get the first child of the root (Markup COMPONENT is expected)
    QDomElement component=root.firstChild().toElement();

    // Loop while there is a child
    while(!component.isNull())
    {
        if(component.tagName() == "SheetSize")
        {
            SHEETSIZE.sizeString = component.attribute("sizeString");
            SHEETSIZE.width = component.attribute("width").toDouble();
            SHEETSIZE.height = component.attribute("height").toDouble();
        }
        else if(component.tagName() == "SheetStyle")
        {
            SHEETSTYLE = toSheetStyle(component.attribute("style"));
            NUMOPTLINES = component.attribute("numOptLines").toInt();
            TRIMMINGMARKS = component.attribute("trimmingMarks").toInt();
            QDomElement option = component.firstChild().toElement();

            while(!option.isNull())
            {
                option.nextSibling().toElement();
                if(option.tagName() == "Opt")
                {
                    TITELBLOCKFIELDS[option.attribute("key")].Label = option.attribute("label");
                    TITELBLOCKFIELDS[option.attribute("key")].ValueKiCAD5 = option.attribute("valKiCAD5").split("&{n}");
                    TITELBLOCKFIELDS[option.attribute("key")].ValueKiCAD6 = option.attribute("valKiCAD6").split("&{n}");
                    TITELBLOCKFIELDS[option.attribute("key")].NameFreeCAD = option.attribute("nameFreeCAD");
                    TITELBLOCKFIELDS[option.attribute("key")].ValueFreeCAD = option.attribute("valFreeCAD").split("&{n}");
                    option = option.nextSibling().toElement();
                }
            }
        }
        else if(component.tagName() == "RevHistory")
        {
            REVHISTORY = component.attribute("revHistory").toInt();
            NUMREVHISTORY = component.attribute("num").toInt();
            REVHISTORYSTYLE = toRevHistoryStyle(component.attribute("ASME_Y14_35_Width180"));
            QDomElement option = component.firstChild().toElement();

            while(!option.isNull())
            {
                option.nextSibling().toElement();
                if(option.tagName() == "Opt")
                {
                    REVHISTORYFIELDS[option.attribute("key")].Label = option.attribute("label");
                    REVHISTORYFIELDS[option.attribute("key")].ValueKiCAD5 = option.attribute("valKiCAD5").split("&{n}");
                    REVHISTORYFIELDS[option.attribute("key")].ValueKiCAD6 = option.attribute("valKiCAD6").split("&{n}");
                    REVHISTORYFIELDS[option.attribute("key")].NameFreeCAD = option.attribute("nameFreeCAD");
                    REVHISTORYFIELDS[option.attribute("key")].ValueFreeCAD = option.attribute("valFreeCAD").split("&{n}");
                    option = option.nextSibling().toElement();
                }
            }
        }
        else if(component.tagName() == "Foldlines")
        {
            FOLDLINES = component.attribute("Foldlines").toInt();
            FOLDLINESTARGET.sizeString = component.attribute("targetString");
            FOLDLINESTARGET.width = component.attribute("targetWidth").toDouble();
            FOLDLINESTARGET.height = component.attribute("targetHeight").toDouble();
        }
        else if(component.tagName() == "SmallPartsList")
        {
            SMALLPARTSLIST = component.attribute("smallPartsList").toInt();
            NUMPARTSSMALLPARTSLIST = component.attribute("numParts").toInt();
            NUMLINESSMALLPARTSLIST = component.attribute("numLines").toInt();
            QDomElement option = component.firstChild().toElement();

            while(!option.isNull())
            {
                option.nextSibling().toElement();
                if(option.tagName() == "Opt")
                {
                    SMALLPARTSLISTFIELDS[option.attribute("key")].Label = option.attribute("label");
                    SMALLPARTSLISTFIELDS[option.attribute("key")].ValueKiCAD5 = option.attribute("valKiCAD5").split("&{n}");
                    SMALLPARTSLISTFIELDS[option.attribute("key")].ValueKiCAD6 = option.attribute("valKiCAD6").split("&{n}");
                    SMALLPARTSLISTFIELDS[option.attribute("key")].NameFreeCAD = option.attribute("nameFreeCAD");
                    SMALLPARTSLISTFIELDS[option.attribute("key")].ValueFreeCAD = option.attribute("valFreeCAD").split("&{n}");
                    option = option.nextSibling().toElement();
                }
            }
        }
        else if(component.tagName() == "FullSheetPartsList")
        {
            FULLSHEETPARTSLIST = component.attribute("fullSheetPartsList").toInt();
            NUMSHEETSFULLSHEETPARTSLIST = component.attribute("numSheets").toInt();
            NUMLINESFULLSHEETPARTSLIST = component.attribute("numLines").toInt();
            QDomElement option = component.firstChild().toElement();

            while(!option.isNull())
            {
                option.nextSibling().toElement();
                if(option.tagName() == "Opt")
                {
                    FULLSHEETPARTSLISTFIELDS[option.attribute("key")].Label = option.attribute("label");
                    FULLSHEETPARTSLISTFIELDS[option.attribute("key")].ValueKiCAD5 = option.attribute("valKiCAD5").split("&{n}");
                    FULLSHEETPARTSLISTFIELDS[option.attribute("key")].ValueKiCAD6 = option.attribute("valKiCAD6").split("&{n}");
                    FULLSHEETPARTSLISTFIELDS[option.attribute("key")].NameFreeCAD = option.attribute("nameFreeCAD");
                    FULLSHEETPARTSLISTFIELDS[option.attribute("key")].ValueFreeCAD = option.attribute("valFreeCAD").split("&{n}");
                    option = option.nextSibling().toElement();
                }
            }
        }
        else if(component.tagName() == "Logo")
        {
            LOGO = component.attribute("logo").toInt();
            if(component.attribute("logoDir")[0] == '.')
            {
                QString dirTmp = dir;
                dirTmp.truncate(dir.lastIndexOf("/"));
                dirTmp += "/" + component.attribute("logoDir");
                LOGODIR = dirTmp;
            }
            else
            {
                LOGODIR = component.attribute("logoDir");
            }
        }
        component = component.nextSibling().toElement();
    }

}
