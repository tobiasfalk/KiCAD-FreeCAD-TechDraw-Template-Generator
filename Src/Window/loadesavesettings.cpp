#include "loadesavesettings.h"

#include <QtXml>
#include <QTextStream>

const SheetSize &LoadeSaveSettings::getSHEETSIZE() const
{
    return SHEETSIZE;
}

void LoadeSaveSettings::setSHEETSIZE(const SheetSize &newSHEETSIZE)
{
    SHEETSIZE = newSHEETSIZE;
    finisheD.sheetsizeE = true;
}

SheetStyle LoadeSaveSettings::getSHEETSTYLE() const
{
    return SHEETSTYLE;
}

void LoadeSaveSettings::setSHEETSTYLE(SheetStyle newSHEETSTYLE)
{
    SHEETSTYLE = newSHEETSTYLE;
    finisheD.sheetstylE = true;
}

const QMap<QString, TitelblockField> &LoadeSaveSettings::getTITELBLOCKFIELDS_FREECAD() const
{
    return TITELBLOCKFIELDS_FREECAD;
}

void LoadeSaveSettings::setTITELBLOCKFIELDS_FREECAD(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_FREECAD)
{
    TITELBLOCKFIELDS_FREECAD = newTITELBLOCKFIELDS_FREECAD;
    finisheD.titelblockfieldS = true;
}

const QMap<QString, TitelblockField> &LoadeSaveSettings::getTITELBLOCKFIELDS_KICAD5() const
{
    return TITELBLOCKFIELDS_KICAD5;
}

void LoadeSaveSettings::setTITELBLOCKFIELDS_KICAD5(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_KICAD5)
{
    TITELBLOCKFIELDS_KICAD5 = newTITELBLOCKFIELDS_KICAD5;
    finisheD.titelblockfieldS = true;
}

const QMap<QString, TitelblockField> &LoadeSaveSettings::getTITELBLOCKFIELDS_KICAD6() const
{
    return TITELBLOCKFIELDS_KICAD5;
}

void LoadeSaveSettings::setTITELBLOCKFIELDS_KICAD6(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_KICAD6)
{
    TITELBLOCKFIELDS_KICAD6 = newTITELBLOCKFIELDS_KICAD6;
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

const SheetSize &LoadeSaveSettings::getFOLDLINESTARGET() const
{
    return FOLDLINESTARGET;
}

void LoadeSaveSettings::setFOLDLINESTARGET(const SheetSize &newFOLDLINESTARGET)
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

const QMap<QString, TitelblockField> &LoadeSaveSettings::getSMALLPARTSLISTFIELDS_FREECAD() const
{
    return SMALLPARTSLISTFIELDS_FREECAD;
}

void LoadeSaveSettings::setSMALLPARTSLISTFIELDS_FREECAD(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS_FREECAD)
{
    SMALLPARTSLISTFIELDS_FREECAD = newSMALLPARTSLISTFIELDS_FREECAD;
    finisheD.smallpartslistfieldS = true;
}

const QMap<QString, TitelblockField> &LoadeSaveSettings::getSMALLPARTSLISTFIELDS_KICAD5() const
{
    return SMALLPARTSLISTFIELDS_KICAD5;
}

void LoadeSaveSettings::setSMALLPARTSLISTFIELDS_KICAD5(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS_KICAD5)
{
    SMALLPARTSLISTFIELDS_KICAD5 = newSMALLPARTSLISTFIELDS_KICAD5;
    finisheD.smallpartslistfieldS = true;
}

const QMap<QString, TitelblockField> &LoadeSaveSettings::getSMALLPARTSLISTFIELDS_KICAD6() const
{
    return SMALLPARTSLISTFIELDS_KICAD6;
}

void LoadeSaveSettings::setSMALLPARTSLISTFIELDS_KICAD6(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS_KICAD6)
{
    SMALLPARTSLISTFIELDS_KICAD6 = newSMALLPARTSLISTFIELDS_KICAD6;
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

const QMap<QString, TitelblockField> &LoadeSaveSettings::getREVHISTORYFIELDS_FREECAD() const
{
    return REVHISTORYFIELDS_FREECAD;
}

void LoadeSaveSettings::setREVHISTORYFIELDS_FREECAD(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_FREECAD)
{
    REVHISTORYFIELDS_FREECAD = newREVHISTORYFIELDS_FREECAD;
    finisheD.revhistoryfieldS = true;
}

const QMap<QString, TitelblockField> &LoadeSaveSettings::getREVHISTORYFIELDS_KICAD5() const
{
    return REVHISTORYFIELDS_KICAD5;
}

void LoadeSaveSettings::setREVHISTORYFIELDS_KICAD5(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_KICAD5)
{
    REVHISTORYFIELDS_KICAD5 = newREVHISTORYFIELDS_KICAD5;
    finisheD.revhistoryfieldS = true;
}

const QMap<QString, TitelblockField> &LoadeSaveSettings::getREVHISTORYFIELDS_KICAD6() const
{
    return REVHISTORYFIELDS_KICAD6;
}

void LoadeSaveSettings::setREVHISTORYFIELDS_KICAD6(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_KICAD6)
{
    REVHISTORYFIELDS_KICAD6 = newREVHISTORYFIELDS_KICAD6;
    finisheD.revhistoryfieldS = true;
}

const QMap<QString, TitelblockField> &LoadeSaveSettings::getFULLSHEETPARTSLISTFIELDS_FREECAD() const
{
    return FULLSHEETPARTSLISTFIELDS_FREECAD;
}

void LoadeSaveSettings::setFULLSHEETPARTSLISTFIELDS_FREECAD(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_FREECAD)
{
    FULLSHEETPARTSLISTFIELDS_FREECAD = newFULLSHEETPARTSLISTFIELDS_FREECAD;
    finisheD.fullsheetpartlistfieldS = true;
}

const QMap<QString, TitelblockField> &LoadeSaveSettings::getFULLSHEETPARTSLISTFIELDS_KICAD5() const
{
    return FULLSHEETPARTSLISTFIELDS_KICAD5;
}

void LoadeSaveSettings::setFULLSHEETPARTSLISTFIELDS_KICAD5(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_KICAD5)
{
    FULLSHEETPARTSLISTFIELDS_KICAD5 = newFULLSHEETPARTSLISTFIELDS_KICAD5;
    finisheD.fullsheetpartlistfieldS = true;
}

const QMap<QString, TitelblockField> &LoadeSaveSettings::getFULLSHEETPARTSLISTFIELDS_KICAD6() const
{
    return FULLSHEETPARTSLISTFIELDS_KICAD6;
}

void LoadeSaveSettings::setFULLSHEETPARTSLISTFIELDS_KICAD6(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_KICAD6)
{
    FULLSHEETPARTSLISTFIELDS_KICAD6 = newFULLSHEETPARTSLISTFIELDS_KICAD6;
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

const QMap<QString, TitelblockField> &LoadeSaveSettings::getTITELBLOCKFIELDS_PDF() const
{
    return TITELBLOCKFIELDS_PDF;
}

void LoadeSaveSettings::setTITELBLOCKFIELDS_PDF(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_PDF)
{
    TITELBLOCKFIELDS_PDF = newTITELBLOCKFIELDS_PDF;
}

const QMap<QString, TitelblockField> &LoadeSaveSettings::getREVHISTORYFIELDS_PDF() const
{
    return REVHISTORYFIELDS_PDF;
}

void LoadeSaveSettings::setREVHISTORYFIELDS_PDF(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_PDF)
{
    REVHISTORYFIELDS_PDF = newREVHISTORYFIELDS_PDF;
}

const QMap<QString, TitelblockField> &LoadeSaveSettings::getSMALLPARTSLISTFIELDS_PDF() const
{
    return SMALLPARTSLISTFIELDS_PDF;
}

void LoadeSaveSettings::setSMALLPARTSLISTFIELDS_PDF(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS_PDF)
{
    SMALLPARTSLISTFIELDS_PDF = newSMALLPARTSLISTFIELDS_PDF;
}

const QMap<QString, TitelblockField> &LoadeSaveSettings::getFULLSHEETPARTSLISTFIELDS_PDF() const
{
    return FULLSHEETPARTSLISTFIELDS_PDF;
}

void LoadeSaveSettings::setFULLSHEETPARTSLISTFIELDS_PDF(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_PDF)
{
    FULLSHEETPARTSLISTFIELDS_PDF = newFULLSHEETPARTSLISTFIELDS_PDF;
}

QString LoadeSaveSettings::getSheetStyleString()
{
    QString ret = "";
    switch (SHEETSTYLE)
    {
    case SheetStyle::ISO5457_ISO7200:
        ret = "ISO5457_ISO7200";
        break;
    case SheetStyle::BLANK:
        break;
    }
    return ret;
}

SheetStyle LoadeSaveSettings::toSheetStyle(QString style)
{
    if(style == "ISO5457_ISO7200")
    {
        return SheetStyle::ISO5457_ISO7200;
    }
    return SheetStyle::ISO5457_ISO7200;
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

QString LoadeSaveSettings::setProjectionMethod(ProjectionMethodType methode)
{
    switch (methode) {
    case ProjectionMethodType::None:
        return "none";
        break;
    case ProjectionMethodType::FirstAngle:
        return "firstAngle";
        break;
    case ProjectionMethodType::ThirdAngle:
        return "thirdAngle";
        break;
    default:
        return "none";
        break;
    }
}

ProjectionMethodType LoadeSaveSettings::getProjectionMethod(QString methode)
{
    if(methode == "none")
    {
        return ProjectionMethodType::None;
    }else if(methode == "firstAngle")
    {
        return ProjectionMethodType::FirstAngle;
    }else if(methode == "thirdAngle")
    {
        return ProjectionMethodType::ThirdAngle;
    }
    return ProjectionMethodType::None;
}

LoadeSaveSettings::LoadeSaveSettings(QObject *parent) : QObject(parent)
{

}

void LoadeSaveSettings::saveSettings(QString dir)
{
    QFile xmlFile(dir);
    if (!xmlFile.open(QFile::WriteOnly | QFile::Text ))
    {
        qWarning() << "Already opened or there is another issue";
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
    foreach (const QString &str, TITELBLOCKFIELDS_FREECAD.keys())
    {
        QDomElement field = document.createElement("Opt");
        field.setAttribute("key", str);
        field.setAttribute("label", TITELBLOCKFIELDS_FREECAD.value(str).Label);
        field.setAttribute("valKiCAD5", stringListToString(TITELBLOCKFIELDS_KICAD5.value(str).Value));
        field.setAttribute("valKiCAD6", stringListToString(TITELBLOCKFIELDS_KICAD6.value(str).Value));
        field.setAttribute("nameFreeCAD", TITELBLOCKFIELDS_FREECAD.value(str).Name);
        field.setAttribute("valFreeCAD", stringListToString(TITELBLOCKFIELDS_FREECAD.value(str).Value));
        field.setAttribute("valPDF", stringListToString(TITELBLOCKFIELDS_PDF.value(str).Value));
        field.setAttribute("projectionMethod", setProjectionMethod(TITELBLOCKFIELDS_FREECAD.value(str).ProjectionMethod));
        settings.appendChild(field);
    }
    root.appendChild(settings);

    settings = document.createElement("RevHistory");
    settings.setAttribute("name", "RevHistory");
    settings.setAttribute("revHistory", REVHISTORY);
    settings.setAttribute("style", getRevHistoryStyleString());
    settings.setAttribute("num", NUMREVHISTORY);
    foreach (const QString &str, REVHISTORYFIELDS_FREECAD.keys())
    {
        QDomElement field = document.createElement("Opt");
        field.setAttribute("key", str);
        field.setAttribute("label", REVHISTORYFIELDS_FREECAD.value(str).Label);
        field.setAttribute("valKiCAD5", stringListToString(REVHISTORYFIELDS_KICAD5.value(str).Value));
        field.setAttribute("valKiCAD6", stringListToString(REVHISTORYFIELDS_KICAD6.value(str).Value));
        field.setAttribute("nameFreeCAD", REVHISTORYFIELDS_FREECAD.value(str).Name);
        field.setAttribute("valFreeCAD", stringListToString(REVHISTORYFIELDS_FREECAD.value(str).Value));
        field.setAttribute("valPDF", stringListToString(REVHISTORYFIELDS_PDF.value(str).Value));
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
    foreach (const QString &str, SMALLPARTSLISTFIELDS_FREECAD.keys())
    {
        QDomElement field = document.createElement("Opt");
        field.setAttribute("key", str);
        field.setAttribute("label", SMALLPARTSLISTFIELDS_FREECAD.value(str).Label);
        field.setAttribute("valKiCAD5", stringListToString(SMALLPARTSLISTFIELDS_KICAD5.value(str).Value));
        field.setAttribute("valKiCAD6", stringListToString(SMALLPARTSLISTFIELDS_KICAD6.value(str).Value));
        field.setAttribute("nameFreeCAD", SMALLPARTSLISTFIELDS_FREECAD.value(str).Name);
        field.setAttribute("valFreeCAD", stringListToString(SMALLPARTSLISTFIELDS_FREECAD.value(str).Value));
        field.setAttribute("valPDF", stringListToString(SMALLPARTSLISTFIELDS_PDF.value(str).Value));
        settings.appendChild(field);
    }
    root.appendChild(settings);

    settings = document.createElement("FullSheetPartsList");
    settings.setAttribute("name", "FullSheetPartsList");
    settings.setAttribute("fullSheetPartsList", FULLSHEETPARTSLIST);
    settings.setAttribute("numLines", NUMLINESFULLSHEETPARTSLIST);
    foreach (const QString &str, FULLSHEETPARTSLISTFIELDS_FREECAD.keys())
    {
        QDomElement field = document.createElement("Opt");
        field.setAttribute("key", str);
        field.setAttribute("label", FULLSHEETPARTSLISTFIELDS_FREECAD.value(str).Label);
        field.setAttribute("valKiCAD5", stringListToString(FULLSHEETPARTSLISTFIELDS_KICAD5.value(str).Value));
        field.setAttribute("valKiCAD6", stringListToString(FULLSHEETPARTSLISTFIELDS_KICAD6.value(str).Value));
        field.setAttribute("nameFreeCAD", FULLSHEETPARTSLISTFIELDS_FREECAD.value(str).Name);
        field.setAttribute("valFreeCAD", stringListToString(FULLSHEETPARTSLISTFIELDS_FREECAD.value(str).Value));
        field.setAttribute("valPDF", stringListToString(FULLSHEETPARTSLISTFIELDS_PDF.value(str).Value));
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
        qWarning() << "Cannot read file" << file.errorString();
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
                    TITELBLOCKFIELDS_FREECAD[option.attribute("key")].Label = option.attribute("label");
                    TITELBLOCKFIELDS_KICAD5[option.attribute("key")].Label = option.attribute("label");
                    TITELBLOCKFIELDS_KICAD6[option.attribute("key")].Label = option.attribute("label");
                    TITELBLOCKFIELDS_PDF[option.attribute("key")].Label = option.attribute("label");
                    TITELBLOCKFIELDS_KICAD5[option.attribute("key")].Value = option.attribute("valKiCAD5").split("&{n}");
                    TITELBLOCKFIELDS_KICAD6[option.attribute("key")].Value = option.attribute("valKiCAD6").split("&{n}");
                    TITELBLOCKFIELDS_FREECAD[option.attribute("key")].Name = option.attribute("nameFreeCAD");
                    TITELBLOCKFIELDS_KICAD5[option.attribute("key")].Name = option.attribute("nameFreeCAD");
                    TITELBLOCKFIELDS_KICAD6[option.attribute("key")].Name = option.attribute("nameFreeCAD");
                    TITELBLOCKFIELDS_FREECAD[option.attribute("key")].Value = option.attribute("valFreeCAD").split("&{n}");
                    if(!option.attribute("valPDF").isNull())
                    {
                        TITELBLOCKFIELDS_PDF[option.attribute("key")].Value = option.attribute("valPDF").split("&{n}");
                    }
                    if(!option.attribute("projectionMethod").isNull())
                    {
                        TITELBLOCKFIELDS_PDF[option.attribute("key")].ProjectionMethod = getProjectionMethod(option.attribute("projectionMethod"));
                    }
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
                    REVHISTORYFIELDS_FREECAD[option.attribute("key")].Label = option.attribute("label");
                    REVHISTORYFIELDS_KICAD5[option.attribute("key")].Label = option.attribute("label");
                    REVHISTORYFIELDS_KICAD6[option.attribute("key")].Label = option.attribute("label");
                    REVHISTORYFIELDS_PDF[option.attribute("key")].Label = option.attribute("label");
                    REVHISTORYFIELDS_KICAD5[option.attribute("key")].Value = option.attribute("valKiCAD5").split("&{n}");
                    REVHISTORYFIELDS_KICAD6[option.attribute("key")].Value = option.attribute("valKiCAD6").split("&{n}");
                    REVHISTORYFIELDS_FREECAD[option.attribute("key")].Name = option.attribute("nameFreeCAD");
                    REVHISTORYFIELDS_KICAD5[option.attribute("key")].Name = option.attribute("nameFreeCAD");
                    REVHISTORYFIELDS_KICAD6[option.attribute("key")].Name = option.attribute("nameFreeCAD");
                    REVHISTORYFIELDS_FREECAD[option.attribute("key")].Value = option.attribute("valFreeCAD").split("&{n}");
                    if(!option.attribute("valPDF").isNull())
                    {
                        REVHISTORYFIELDS_PDF[option.attribute("key")].Value = option.attribute("valPDF").split("&{n}");
                    }
                    option = option.nextSibling().toElement();
                }
            }
        }
        else if(component.tagName() == "Foldlines")
        {
            FOLDLINES = component.attribute("foldlines").toInt();
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
                    SMALLPARTSLISTFIELDS_FREECAD[option.attribute("key")].Label = option.attribute("label");
                    SMALLPARTSLISTFIELDS_KICAD5[option.attribute("key")].Label = option.attribute("label");
                    SMALLPARTSLISTFIELDS_KICAD6[option.attribute("key")].Label = option.attribute("label");
                    SMALLPARTSLISTFIELDS_PDF[option.attribute("key")].Label = option.attribute("label");
                    SMALLPARTSLISTFIELDS_KICAD5[option.attribute("key")].Value = option.attribute("valKiCAD5").split("&{n}");
                    SMALLPARTSLISTFIELDS_KICAD6[option.attribute("key")].Value = option.attribute("valKiCAD6").split("&{n}");
                    SMALLPARTSLISTFIELDS_FREECAD[option.attribute("key")].Name = option.attribute("nameFreeCAD");
                    SMALLPARTSLISTFIELDS_KICAD5[option.attribute("key")].Name = option.attribute("nameFreeCAD");
                    SMALLPARTSLISTFIELDS_KICAD6[option.attribute("key")].Name = option.attribute("nameFreeCAD");
                    SMALLPARTSLISTFIELDS_FREECAD[option.attribute("key")].Value = option.attribute("valFreeCAD").split("&{n}");
                    if(!option.attribute("valPDF").isNull())
                    {
                        SMALLPARTSLISTFIELDS_PDF[option.attribute("key")].Value = option.attribute("valPDF").split("&{n}");
                    }
                    option = option.nextSibling().toElement();
                }
            }
        }
        else if(component.tagName() == "FullSheetPartsList")
        {
            FULLSHEETPARTSLIST = component.attribute("fullSheetPartsList").toInt();
            NUMLINESFULLSHEETPARTSLIST = component.attribute("numLines").toInt();
            QDomElement option = component.firstChild().toElement();

            while(!option.isNull())
            {
                option.nextSibling().toElement();
                if(option.tagName() == "Opt")
                {
                    FULLSHEETPARTSLISTFIELDS_FREECAD[option.attribute("key")].Label = option.attribute("label");
                    FULLSHEETPARTSLISTFIELDS_KICAD5[option.attribute("key")].Label = option.attribute("label");
                    FULLSHEETPARTSLISTFIELDS_KICAD6[option.attribute("key")].Label = option.attribute("label");
                    FULLSHEETPARTSLISTFIELDS_PDF[option.attribute("key")].Label = option.attribute("label");
                    FULLSHEETPARTSLISTFIELDS_KICAD5[option.attribute("key")].Value = option.attribute("valKiCAD5").split("&{n}");
                    FULLSHEETPARTSLISTFIELDS_KICAD6[option.attribute("key")].Value = option.attribute("valKiCAD6").split("&{n}");
                    FULLSHEETPARTSLISTFIELDS_FREECAD[option.attribute("key")].Name = option.attribute("nameFreeCAD");
                    FULLSHEETPARTSLISTFIELDS_KICAD5[option.attribute("key")].Name = option.attribute("nameFreeCAD");
                    FULLSHEETPARTSLISTFIELDS_KICAD6[option.attribute("key")].Name = option.attribute("nameFreeCAD");
                    FULLSHEETPARTSLISTFIELDS_FREECAD[option.attribute("key")].Value = option.attribute("valFreeCAD").split("&{n}");
                    if(!option.attribute("valPDF").isNull())
                    {
                        FULLSHEETPARTSLISTFIELDS_PDF[option.attribute("key")].Value = option.attribute("valPDF").split("&{n}");
                    }
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
