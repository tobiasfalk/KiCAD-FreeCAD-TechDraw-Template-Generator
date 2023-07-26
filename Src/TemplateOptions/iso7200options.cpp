#include "iso7200options.h"

void ISO7200Options::loadStdOptions()
{
    // FreeCAD
    //                      key                     label                                       Value                                       Name
    TITELBLOCKFIELDS_FREECAD.insert("opt1",  TitelblockField{"Option 1",                        QStringList{"."},                           "Option 1", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt2",  TitelblockField{"Option 2",                        QStringList{"."},                           "Option 2", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt3",  TitelblockField{"Option 3",                        QStringList{"."},                           "Option 3", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt4",  TitelblockField{"Surface treatment",               QStringList{"."},                           "Surface treatment", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt5",  TitelblockField{"Weight",                          QStringList{"."},                           "Weight", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt6",  TitelblockField{"Standard",                        QStringList{"."},                           "Standard", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt7",  TitelblockField{"Raw dimensions",                  QStringList{"."},                           "Raw dimensions", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt8",  TitelblockField{"Projection",                      QStringList{"."},                           "Projection", ProjectionMethodType::ThirdAngle});
    TITELBLOCKFIELDS_FREECAD.insert("opt9",  TitelblockField{"Scale",                           QStringList{"${SCALE}"},                    "Scale", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt10", TitelblockField{"Created by",                      QStringList{"${createdBy}"},                "Created by", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt11", TitelblockField{"Valid from to",                   QStringList{"."},                           "Valid from to", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt12", TitelblockField{"Document state",                  QStringList{"."},                           "Document state", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt13", TitelblockField{"Approved by",                     QStringList{"."},                           "Approved by", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt14", TitelblockField{"Project",                         QStringList{"${project}"},                  "Project", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt15", TitelblockField{"Document type",                   QStringList{"."},                           "Document type", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt16", TitelblockField{"Legal owner",                     QStringList{"${companyLeagalOwnerA}",
                                                                                                            "${companyLeagalOwnerB}",
                                                                                                            "${companyLeagalOwnerC}"},      "Legal owner", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt17", TitelblockField{"Title, Supplementary title",      QStringList{"${TITLE}",  ".", "."},         "Title, Supplementary title", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt18", TitelblockField{"Document number",                 QStringList{"."},                           "Document number", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt19", TitelblockField{"Rev.",                            QStringList{"."},                           "Rev.", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt20", TitelblockField{"Date of issue",                   QStringList{"."},                           "Date of issue", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt21", TitelblockField{"Lang.",                           QStringList{"EN"},                          "Lang.", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt22", TitelblockField{"Sheet",                           QStringList{"${#}/${##}"},                           "Sheet", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD.insert("opt23", TitelblockField{"Description",                     QStringList{"."},                           "Description", ProjectionMethodType::None});
    TITELBLOCKFIELDS_FREECAD_ORG = TITELBLOCKFIELDS_FREECAD;

    // KiCAD 5
    //                      key                     label                                      Value                                        Name
    TITELBLOCKFIELDS_KICAD5.insert("opt1",  TitelblockField{"Option 1",                        QStringList{"Option 1 Value"},               "Option 1", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt2",  TitelblockField{"Option 2",                        QStringList{"Option 2 Value"},               "Option 2", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt3",  TitelblockField{"Option 3",                        QStringList{"Option 2 Value"},               "Option 3", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt4",  TitelblockField{"Surface treatment",               QStringList{"Surface treatment Value"},      "Surface treatment", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt5",  TitelblockField{"Weight",                          QStringList{"Weight Value"},                 "Weight", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt6",  TitelblockField{"Standard",                        QStringList{"Standard Value"},               "Standard", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt7",  TitelblockField{"Raw dimensions",                  QStringList{"Raw dimensions Value"},         "Raw dimensions", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt8",  TitelblockField{"Projection",                      QStringList{""},                             "Projection", ProjectionMethodType::ThirdAngle});
    TITELBLOCKFIELDS_KICAD5.insert("opt9",  TitelblockField{"Scale",                           QStringList{"Scale Value"},                  "Scale", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt10", TitelblockField{"Created by",                      QStringList{"%C0"},                          "Created by", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt11", TitelblockField{"Valid from to",                   QStringList{"%D to -"},                      "Valid from to", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt12", TitelblockField{"Document state",                  QStringList{"-"},                            "Document state", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt13", TitelblockField{"Approved by",                     QStringList{"%C1"},                          "Approved by", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt14", TitelblockField{"Project",                         QStringList{"%C2"},                          "Project", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt15", TitelblockField{"Document type",                   QStringList{"%C3"},                          "Document type", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt16", TitelblockField{"Legal owner",                     QStringList{"%Y"},                           "Legal owner", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt17", TitelblockField{"Title, Supplementary title",      QStringList{"%T"},                           "Title, Supplementary title", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt18", TitelblockField{"Document number",                 QStringList{"%F"},                           "Document number", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt19", TitelblockField{"Rev.",                            QStringList{"%R"},                           "Rev.", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt20", TitelblockField{"Date of issue",                   QStringList{"%D"},                           "Date of issue", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt21", TitelblockField{"Lang.",                           QStringList{"EN"},                           "Lang.", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt22", TitelblockField{"Sheet",                           QStringList{"%S/%N"},                        "Sheet", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5.insert("opt23", TitelblockField{"Description",                     QStringList{"Description"},                  "Description", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD5_ORG = TITELBLOCKFIELDS_KICAD5;

    // KiCAD 6
    //                      key                     label                                      Value                                        Name
    TITELBLOCKFIELDS_KICAD6.insert("opt1",  TitelblockField{"Option 1",                        QStringList{"${opt1Val}"},                  "Option 1", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt2",  TitelblockField{"Option 2",                        QStringList{"${opt2Val}"},                  "Option 2", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt3",  TitelblockField{"Option 3",                        QStringList{"${opt3Val}"},                  "Option 3", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt4",  TitelblockField{"Surface treatment",               QStringList{"${surfaceTreatmentValue}"},    "Surface treatment", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt5",  TitelblockField{"Weight",                          QStringList{"${weightValue}"},              "Weight", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt6",  TitelblockField{"Standard",                        QStringList{"${standardValue}"},            "Standard", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt7",  TitelblockField{"Raw dimensions",                  QStringList{"${rawDimValue}"},              "Raw dimensions", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt8",  TitelblockField{"Projection",                      QStringList{""},                            "Projection", ProjectionMethodType::ThirdAngle});
    TITELBLOCKFIELDS_KICAD6.insert("opt9",  TitelblockField{"Scale",                           QStringList{"${scaleVal}"},                 "Scale", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt10", TitelblockField{"Created by",                      QStringList{"${createdBy}"},                "Created by", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt11", TitelblockField{"Valid from to",                   QStringList{"${validFromTo}"},              "Valid from to", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt12", TitelblockField{"Document state",                  QStringList{"${docState}"},                 "Document state", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt13", TitelblockField{"Approved by",                     QStringList{"${approvedBy}"},               "Approved by", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt14", TitelblockField{"Project",                         QStringList{"${project}"},                  "Project", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt15", TitelblockField{"Document type",                   QStringList{"${docType}"},                  "Document type", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt16", TitelblockField{"Legal owner",                     QStringList{"${COMPANY}"},                  "Legal owner", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt17", TitelblockField{"Title, Supplementary title",      QStringList{"${TITLE}"},                    "Title, Supplementary title", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt18", TitelblockField{"Document number",                 QStringList{"${docNumber}"},                "Document number", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt19", TitelblockField{"Rev.",                            QStringList{"${REVISION}"},                 "Rev.", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt20", TitelblockField{"Date of issue",                   QStringList{"${ISSUE_DATE}"},               "Date of issue", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt21", TitelblockField{"Lang.",                           QStringList{"${lang}"},                     "Lang.", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt22", TitelblockField{"Sheet",                           QStringList{"${#}/${##}"},                  "Sheet", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6.insert("opt23", TitelblockField{"Description",                     QStringList{"${description_&{N}}"},         "Description", ProjectionMethodType::None});
    TITELBLOCKFIELDS_KICAD6_ORG = TITELBLOCKFIELDS_KICAD6;

    // PDF
    //                      key                     label                                       Value                                       Name
    TITELBLOCKFIELDS_PDF.insert("opt1",  TitelblockField{"Option 1",                        QStringList{""},                           "Option 1", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt2",  TitelblockField{"Option 2",                        QStringList{""},                           "Option 2", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt3",  TitelblockField{"Option 3",                        QStringList{""},                           "Option 3", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt4",  TitelblockField{"Surface treatment",               QStringList{""},                           "Surface treatment", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt5",  TitelblockField{"Weight",                          QStringList{""},                           "Weight", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt6",  TitelblockField{"Standard",                        QStringList{""},                           "Standard", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt7",  TitelblockField{"Raw dimensions",                  QStringList{""},                           "Raw dimensions", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt8",  TitelblockField{"Projection",                      QStringList{""},                           "Projection", ProjectionMethodType::ThirdAngle});
    TITELBLOCKFIELDS_PDF.insert("opt9",  TitelblockField{"Scale",                           QStringList{""},                           "Scale", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt10", TitelblockField{"Created by",                      QStringList{""},                           "Created by", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt11", TitelblockField{"Valid from to",                   QStringList{""},                           "Valid from to", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt12", TitelblockField{"Document state",                  QStringList{""},                           "Document state", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt13", TitelblockField{"Approved by",                     QStringList{""},                           "Approved by", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt14", TitelblockField{"Project",                         QStringList{""},                           "Project", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt15", TitelblockField{"Document type",                   QStringList{""},                           "Document type", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt16", TitelblockField{"Legal owner",                     QStringList{""},                           "Legal owner", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt17", TitelblockField{"Title, Supplementary title",      QStringList{""},                           "Title, Supplementary title", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt18", TitelblockField{"Document number",                 QStringList{""},                           "Document number", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt19", TitelblockField{"Rev.",                            QStringList{""},                           "Rev.", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt20", TitelblockField{"Date of issue",                   QStringList{""},                           "Date of issue", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt21", TitelblockField{"Lang.",                           QStringList{"EN"},                         "Lang.", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt22", TitelblockField{"Sheet",                           QStringList{""},                           "Sheet", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF.insert("opt23", TitelblockField{"Description",                     QStringList{""},                           "Description", ProjectionMethodType::None});
    TITELBLOCKFIELDS_PDF_ORG = TITELBLOCKFIELDS_PDF;
}

bool ISO7200Options::getDescField()
{
    return descField;
}

void ISO7200Options::setDescField(bool newDescField)
{
    descField = newDescField;
}

unsigned int ISO7200Options::getNumDescLines()
{
    if(getDescField()){
        return numDescLines;
    }
    return 0;
}

void ISO7200Options::setNumDescLines(unsigned int newNumDescLines)
{
    numDescLines = newNumDescLines;
}

unsigned int ISO7200Options::getNumOptLins()
{
    return numOptLins;
}

void ISO7200Options::setNumOptLins(unsigned int newNumOptLins)
{
    if(newNumOptLins > 3){
        newNumOptLins = 3;
    }
    numOptLins = newNumOptLins;
}

ISO7200Options::ISO7200Options(QObject *parent) :
    QObject(parent)
{
    loadStdOptions();

    setNumDescLines(1);
    setNumOptLins(0);
}

ISO7200Options::~ISO7200Options()
{
}

void ISO7200Options::resetToStd()
{
    TITELBLOCKFIELDS_FREECAD = TITELBLOCKFIELDS_FREECAD_ORG;
    TITELBLOCKFIELDS_KICAD5 = TITELBLOCKFIELDS_KICAD5_ORG;
    TITELBLOCKFIELDS_KICAD6 = TITELBLOCKFIELDS_KICAD6_ORG;
    TITELBLOCKFIELDS_PDF = TITELBLOCKFIELDS_PDF_ORG;
}

const QMap<QString, TitelblockField> &ISO7200Options::getTITELBLOCKFIELDS_FREECAD() const
{
    return TITELBLOCKFIELDS_FREECAD;
}

const QMap<QString, TitelblockField> &ISO7200Options::getTITELBLOCKFIELDS_PDF() const
{
    return TITELBLOCKFIELDS_PDF;
}

void ISO7200Options::setTITELBLOCKFIELDS_PDF(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_PDF)
{
    TITELBLOCKFIELDS_PDF = newTITELBLOCKFIELDS_PDF;
}

void ISO7200Options::setTITELBLOCKFIELD_PDF(QString key, TitelblockField field)
{
    TITELBLOCKFIELDS_PDF[key] = field;
}

const QMap<QString, TitelblockField> &ISO7200Options::getTITELBLOCKFIELDS_KICAD6() const
{
    return TITELBLOCKFIELDS_KICAD6;
}

void ISO7200Options::setTITELBLOCKFIELDS_KICAD6(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_KICAD6)
{
    TITELBLOCKFIELDS_KICAD6 = newTITELBLOCKFIELDS_KICAD6;
}

void ISO7200Options::setTITELBLOCKFIELD_KICAD6(QString key, TitelblockField field)
{
    TITELBLOCKFIELDS_KICAD6[key] = field;
}

const QMap<QString, TitelblockField> &ISO7200Options::getTITELBLOCKFIELDS_KICAD5() const
{
    return TITELBLOCKFIELDS_KICAD5;
}

void ISO7200Options::setTITELBLOCKFIELDS_KICAD5(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_KICAD5)
{
    TITELBLOCKFIELDS_KICAD5 = newTITELBLOCKFIELDS_KICAD5;
}

void ISO7200Options::setTITELBLOCKFIELD_KICAD5(QString key, TitelblockField field)
{
    TITELBLOCKFIELDS_KICAD5[key] = field;
}

void ISO7200Options::setTITELBLOCKFIELDS_FREECAD(const QMap<QString, TitelblockField> &newTITELBLOCKFIELDS_FREECAD)
{
    TITELBLOCKFIELDS_FREECAD = newTITELBLOCKFIELDS_FREECAD;
}

void ISO7200Options::setTITELBLOCKFIELD_FREECAD(QString key, TitelblockField field)
{
    TITELBLOCKFIELDS_FREECAD[key] = field;
}


