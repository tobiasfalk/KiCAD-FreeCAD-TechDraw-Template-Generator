#include "asme_y14_35_width180options.h"

ASME_Y14_35_Width180Options::ASME_Y14_35_Width180Options(QObject *parent) :
    QObject(parent)
{
    loadStdOptions();
}

ASME_Y14_35_Width180Options::~ASME_Y14_35_Width180Options()
{
}

const QMap<QString, TitelblockField> &ASME_Y14_35_Width180Options::getREVHISTORYFIELDS_FREECAD() const
{
    return REVHISTORYFIELDS_FREECAD;
}

void ASME_Y14_35_Width180Options::setREVHISTORYFIELDS_FREECAD(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_FREECAD)
{
    REVHISTORYFIELDS_FREECAD = newREVHISTORYFIELDS_FREECAD;
}

void ASME_Y14_35_Width180Options::setREVHISTORYFIELD_FREECAD(QString key, const TitelblockField &newREVHISTORYFIELDS_FREECAD)
{
    REVHISTORYFIELDS_FREECAD[key] = newREVHISTORYFIELDS_FREECAD;
}

void ASME_Y14_35_Width180Options::resetToStd()
{
    REVHISTORYFIELDS_FREECAD = REVHISTORYFIELDS_ORG_FREECAD;
    REVHISTORYFIELDS_KICAD5 = REVHISTORYFIELDS_ORG_KICAD5;
    REVHISTORYFIELDS_KICAD6 = REVHISTORYFIELDS_ORG_KICAD6;
    REVHISTORYFIELDS_PDF = REVHISTORYFIELDS_ORG_PDF;
}

void ASME_Y14_35_Width180Options::loadStdOptions()
{
    //FreeCAD
    //                              key                      label                                  Value            Name
    REVHISTORYFIELDS_FREECAD.insert("head",  TitelblockField{"Revision History",        QStringList{".", ".", "."}, "Revision History", ProjectionMethodType::None});
    REVHISTORYFIELDS_FREECAD.insert("opt1",  TitelblockField{"Zone",                    QStringList{".", ".", "."}, "Z&{N}", ProjectionMethodType::None});
    REVHISTORYFIELDS_FREECAD.insert("opt2",  TitelblockField{"Rev.",                    QStringList{".", ".", "."}, "R&{N}", ProjectionMethodType::None});
    REVHISTORYFIELDS_FREECAD.insert("opt3",  TitelblockField{"Description",             QStringList{".", ".", "."}, "Description &{N}", ProjectionMethodType::None});
    REVHISTORYFIELDS_FREECAD.insert("opt4",  TitelblockField{"Date",                    QStringList{".", ".", "."}, "D&{N}", ProjectionMethodType::None});
    REVHISTORYFIELDS_FREECAD.insert("opt5",  TitelblockField{"Created by",              QStringList{".", ".", "."}, "C by &{N}", ProjectionMethodType::None});


    //KiCAD 5
    //                              key                      label                                  Value                                                               Name
    REVHISTORYFIELDS_KICAD5.insert("head",  TitelblockField{"Revision History",         QStringList{"-"},                                                               "Revision History", ProjectionMethodType::None});
    REVHISTORYFIELDS_KICAD5.insert("opt1",  TitelblockField{"Zone",                     QStringList{"Z&{N} A", "Z&{N} B", "Z&{N} C"},                                   "Z&{N}", ProjectionMethodType::None});
    REVHISTORYFIELDS_KICAD5.insert("opt2",  TitelblockField{"Rev.",                     QStringList{"R&{N} A", "R&{N} B", "R&{N} C"},                                   "R&{N}", ProjectionMethodType::None});
    REVHISTORYFIELDS_KICAD5.insert("opt3",  TitelblockField{"Description",              QStringList{"Description &{N} A", "Description &{N} B", "Description &{N} C"},  "Description &{N}", ProjectionMethodType::None});
    REVHISTORYFIELDS_KICAD5.insert("opt4",  TitelblockField{"Date",                     QStringList{"D&{N} A", "D&{N} B", "D&{N} C"},                                   "D&{N}", ProjectionMethodType::None});
    REVHISTORYFIELDS_KICAD5.insert("opt5",  TitelblockField{"Created by",               QStringList{"C by &{N} A", "C by &{N} B", "C by &{ C"},                         "C by &{N}", ProjectionMethodType::None});


    //KiCAD 6
    //                              key                      label                                  Value                                                               Name
    REVHISTORYFIELDS_KICAD6.insert("head",  TitelblockField{"Revision History",                QStringList{"-"},                                               "Revision History", ProjectionMethodType::None});
    REVHISTORYFIELDS_KICAD6.insert("opt1",  TitelblockField{"Zone",                            QStringList{"${zone&{N}A}", "${zone&{N}B}", "${zone&{N}C}"},    "Z&{N}", ProjectionMethodType::None});
    REVHISTORYFIELDS_KICAD6.insert("opt2",  TitelblockField{"Rev.",                            QStringList{"${rev&{N}A}", "${rev&{N}B}", "${rev&{N}C}"},       "R&{N}", ProjectionMethodType::None});
    REVHISTORYFIELDS_KICAD6.insert("opt3",  TitelblockField{"Description",                     QStringList{"${desc&{N}A}", "${desc&{N}B}", "${desc&{N}C}"},    "Description &{N}", ProjectionMethodType::None});
    REVHISTORYFIELDS_KICAD6.insert("opt4",  TitelblockField{"Date",                            QStringList{"${d&{N}A}", "${d&{N}B}", "${d&{N}C}"},             "D&{N}", ProjectionMethodType::None});
    REVHISTORYFIELDS_KICAD6.insert("opt5",  TitelblockField{"Created by",                      QStringList{"${cBy&{N}A}", "${cBy&{N}B}", "${cBy&{N}C}"},       "C by &{N}", ProjectionMethodType::None});

    //PDF
    //                              key                      label                                  Value            Name
    REVHISTORYFIELDS_PDF.insert("head",  TitelblockField{"Revision History",        QStringList{""}, "Revision History", ProjectionMethodType::None});
    REVHISTORYFIELDS_PDF.insert("opt1",  TitelblockField{"Zone",                    QStringList{""}, "Z&{N}", ProjectionMethodType::None});
    REVHISTORYFIELDS_PDF.insert("opt2",  TitelblockField{"Rev.",                    QStringList{""}, "R&{N}", ProjectionMethodType::None});
    REVHISTORYFIELDS_PDF.insert("opt3",  TitelblockField{"Description",             QStringList{""}, "Description &{N}", ProjectionMethodType::None});
    REVHISTORYFIELDS_PDF.insert("opt4",  TitelblockField{"Date",                    QStringList{""}, "D&{N}", ProjectionMethodType::None});
    REVHISTORYFIELDS_PDF.insert("opt5",  TitelblockField{"Created by",              QStringList{""}, "C by &{N}", ProjectionMethodType::None});
}

unsigned int ASME_Y14_35_Width180Options::getNumLinesRev()
{
    return numLinesRev;
}

void ASME_Y14_35_Width180Options::setNumLinesRev(unsigned int newNumLinesRev)
{
    numLinesRev = newNumLinesRev;
}

const QMap<QString, TitelblockField> &ASME_Y14_35_Width180Options::getREVHISTORYFIELDS_PDF() const
{
    return REVHISTORYFIELDS_PDF;
}

void ASME_Y14_35_Width180Options::setREVHISTORYFIELDS_PDF(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_PDF)
{
    REVHISTORYFIELDS_PDF = newREVHISTORYFIELDS_PDF;
}

void ASME_Y14_35_Width180Options::setREVHISTORYFIELD_PDF(QString key, const TitelblockField &newREVHISTORYFIELDS_PDF)
{
    REVHISTORYFIELDS_PDF[key] = newREVHISTORYFIELDS_PDF;
}

unsigned int ASME_Y14_35_Width180Options::getNumRev()
{
    return numRev;
}

void ASME_Y14_35_Width180Options::setNumRev(unsigned int newNumRev)
{
    numRev = newNumRev;
}

const QMap<QString, TitelblockField> &ASME_Y14_35_Width180Options::getREVHISTORYFIELDS_KICAD6() const
{
    return REVHISTORYFIELDS_KICAD6;
}

void ASME_Y14_35_Width180Options::setREVHISTORYFIELDS_KICAD6(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_KICAD6)
{
    REVHISTORYFIELDS_KICAD6 = newREVHISTORYFIELDS_KICAD6;
}

void ASME_Y14_35_Width180Options::setREVHISTORYFIELD_KICAD6(QString key, const TitelblockField &newREVHISTORYFIELDS_KICAD6)
{
    REVHISTORYFIELDS_KICAD6[key] = newREVHISTORYFIELDS_KICAD6;
}

const QMap<QString, TitelblockField> &ASME_Y14_35_Width180Options::getREVHISTORYFIELDS_KICAD5() const
{
    return REVHISTORYFIELDS_KICAD5;
}

void ASME_Y14_35_Width180Options::setREVHISTORYFIELDS_KICAD5(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_KICAD5)
{
    REVHISTORYFIELDS_KICAD5 = newREVHISTORYFIELDS_KICAD5;
}

void ASME_Y14_35_Width180Options::setREVHISTORYFIELD_KICAD5(QString key, const TitelblockField &newREVHISTORYFIELDS_KICAD5)
{
    REVHISTORYFIELDS_KICAD5[key] = newREVHISTORYFIELDS_KICAD5;
}

