#include "asme_y14_35_width180.h"
#include "ui_asme_y14_35_width180.h"

ASME_Y14_35_Width180::ASME_Y14_35_Width180(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ASME_Y14_35_Width180)
{
    ui->setupUi(this);
    loadStdOptions();
    loadButtonText();
}

ASME_Y14_35_Width180::~ASME_Y14_35_Width180()
{
    delete ui;
}

const QMap<QString, TitelblockField> &ASME_Y14_35_Width180::getREVHISTORYFIELDS_FREECAD() const
{
    return REVHISTORYFIELDS_FREECAD;
}

void ASME_Y14_35_Width180::setREVHISTORYFIELDS_FREECAD(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_FREECAD)
{
    REVHISTORYFIELDS_FREECAD = newREVHISTORYFIELDS_FREECAD;
    REVHISTORYFIELDS_ORG_FREECAD = newREVHISTORYFIELDS_FREECAD;
    loadButtonText();
}

void ASME_Y14_35_Width180::resetToOrigin()
{
    REVHISTORYFIELDS_FREECAD = REVHISTORYFIELDS_ORG_FREECAD;
    REVHISTORYFIELDS_KICAD5 = REVHISTORYFIELDS_ORG_KICAD5;
    REVHISTORYFIELDS_KICAD6 = REVHISTORYFIELDS_ORG_KICAD6;
    REVHISTORYFIELDS_PDF = REVHISTORYFIELDS_ORG_PDF;
}

void ASME_Y14_35_Width180::on_buttonBox_rejected()
{
    resetToOrigin();
}

void ASME_Y14_35_Width180::loadStdOptions()
{
    //FreeCAD
    //                              key                      label                                  Value            Name
    REVHISTORYFIELDS_FREECAD.insert("head",  TitelblockField{"Revision History",        QStringList{".", ".", "."}, "Revision History"});
    REVHISTORYFIELDS_FREECAD.insert("opt1",  TitelblockField{"Zone",                    QStringList{".", ".", "."}, "Z&{N}"});
    REVHISTORYFIELDS_FREECAD.insert("opt2",  TitelblockField{"Rev.",                    QStringList{".", ".", "."}, "R&{N}"});
    REVHISTORYFIELDS_FREECAD.insert("opt3",  TitelblockField{"Description",             QStringList{".", ".", "."}, "Description &{N}"});
    REVHISTORYFIELDS_FREECAD.insert("opt4",  TitelblockField{"Date",                    QStringList{".", ".", "."}, "D&{N}"});
    REVHISTORYFIELDS_FREECAD.insert("opt5",  TitelblockField{"Created by",              QStringList{".", ".", "."}, "C by &{N}"});


    //KiCAD 5
    //                              key                      label                                  Value                                                               Name
    REVHISTORYFIELDS_KICAD5.insert("head",  TitelblockField{"Revision History",         QStringList{"-"},                                                               "Revision History"});
    REVHISTORYFIELDS_KICAD5.insert("opt1",  TitelblockField{"Zone",                     QStringList{"Z&{N} A", "Z&{N} B", "Z&{N} C"},                                   "Z&{N}"});
    REVHISTORYFIELDS_KICAD5.insert("opt2",  TitelblockField{"Rev.",                     QStringList{"R&{N} A", "R&{N} B", "R&{N} C"},                                   "R&{N}"});
    REVHISTORYFIELDS_KICAD5.insert("opt3",  TitelblockField{"Description",              QStringList{"Description &{N} A", "Description &{N} B", "Description &{N} C"},  "Description &{N}"});
    REVHISTORYFIELDS_KICAD5.insert("opt4",  TitelblockField{"Date",                     QStringList{"D&{N} A", "D&{N} B", "D&{N} C"},                                   "D&{N}"});
    REVHISTORYFIELDS_KICAD5.insert("opt5",  TitelblockField{"Created by",               QStringList{"C by &{N} A", "C by &{N} B", "C by &{ C"},                         "C by &{N}"});


    //KiCAD 6
    //                              key                      label                                  Value                                                               Name
    REVHISTORYFIELDS_KICAD6.insert("head",  TitelblockField{"Revision History",                QStringList{"-"},                                               "Revision History"});
    REVHISTORYFIELDS_KICAD6.insert("opt1",  TitelblockField{"Zone",                            QStringList{"${zone&{N}A}", "${zone&{N}B}", "${zone&{N}C}"},    "Z&{N}"});
    REVHISTORYFIELDS_KICAD6.insert("opt2",  TitelblockField{"Rev.",                            QStringList{"${rev&{N}A}", "${rev&{N}B}", "${rev&{N}C}"},       "R&{N}"});
    REVHISTORYFIELDS_KICAD6.insert("opt3",  TitelblockField{"Description",                     QStringList{"${desc&{N}A}", "${desc&{N}B}", "${desc&{N}C}"},    "Description &{N}"});
    REVHISTORYFIELDS_KICAD6.insert("opt4",  TitelblockField{"Date",                            QStringList{"${d&{N}A}", "${d&{N}B}", "${d&{N}C}"},             "D&{N}"});
    REVHISTORYFIELDS_KICAD6.insert("opt5",  TitelblockField{"Created by",                      QStringList{"${cBy&{N}A}", "${cBy&{N}B}", "${cBy&{N}C}"},       "C by &{N}"});

    //PDF
    //                              key                      label                                  Value            Name
    REVHISTORYFIELDS_PDF.insert("head",  TitelblockField{"Revision History",        QStringList{""}, "Revision History"});
    REVHISTORYFIELDS_PDF.insert("opt1",  TitelblockField{"Zone",                    QStringList{""}, "Z&{N}"});
    REVHISTORYFIELDS_PDF.insert("opt2",  TitelblockField{"Rev.",                    QStringList{""}, "R&{N}"});
    REVHISTORYFIELDS_PDF.insert("opt3",  TitelblockField{"Description",             QStringList{""}, "Description &{N}"});
    REVHISTORYFIELDS_PDF.insert("opt4",  TitelblockField{"Date",                    QStringList{""}, "D&{N}"});
    REVHISTORYFIELDS_PDF.insert("opt5",  TitelblockField{"Created by",              QStringList{""}, "C by &{N}"});
}

void ASME_Y14_35_Width180::loadButtonText()
{
    ui->headPushButton->setText("Head: "  + REVHISTORYFIELDS_FREECAD["head"].Label);
    ui->opt1PushButton->setText("Option 1: "  + REVHISTORYFIELDS_FREECAD["opt1"].Label);
    ui->opt2PushButton->setText("Option 2: "  + REVHISTORYFIELDS_FREECAD["opt2"].Label);
    ui->opt3PushButton->setText("Option 3: "  + REVHISTORYFIELDS_FREECAD["opt3"].Label);
    ui->opt4PushButton->setText("Option 4: "  + REVHISTORYFIELDS_FREECAD["opt4"].Label);
    ui->opt5PushButton->setText("Option 5: "  + REVHISTORYFIELDS_FREECAD["opt5"].Label);
}


void ASME_Y14_35_Width180::on_headPushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(REVHISTORYFIELDS_FREECAD["head"]);
    changeWindow.setFIELD_KICAD5(REVHISTORYFIELDS_KICAD5["head"]);
    changeWindow.setFIELD_KICAD6(REVHISTORYFIELDS_KICAD6["head"]);
    changeWindow.setFIELD_PDF(REVHISTORYFIELDS_PDF["head"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        REVHISTORYFIELDS_FREECAD["head"] = changeWindow.getFIELD_FREECAD();
        REVHISTORYFIELDS_KICAD5["head"] = changeWindow.getFIELD_KICAD5();
        REVHISTORYFIELDS_KICAD6["head"] = changeWindow.getFIELD_KICAD6();
        REVHISTORYFIELDS_PDF["head"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}


void ASME_Y14_35_Width180::on_opt1PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(REVHISTORYFIELDS_FREECAD["opt1"]);
    changeWindow.setFIELD_KICAD5(REVHISTORYFIELDS_KICAD5["opt1"]);
    changeWindow.setFIELD_KICAD6(REVHISTORYFIELDS_KICAD6["opt1"]);
    changeWindow.setFIELD_PDF(REVHISTORYFIELDS_PDF["opt1"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        REVHISTORYFIELDS_FREECAD["opt1"] = changeWindow.getFIELD_FREECAD();
        REVHISTORYFIELDS_KICAD5["opt1"] = changeWindow.getFIELD_KICAD5();
        REVHISTORYFIELDS_KICAD6["opt1"] = changeWindow.getFIELD_KICAD6();
        REVHISTORYFIELDS_PDF["opt1"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}


void ASME_Y14_35_Width180::on_opt2PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(REVHISTORYFIELDS_FREECAD["opt2"]);
    changeWindow.setFIELD_KICAD5(REVHISTORYFIELDS_KICAD5["opt2"]);
    changeWindow.setFIELD_KICAD6(REVHISTORYFIELDS_KICAD6["opt2"]);
    changeWindow.setFIELD_PDF(REVHISTORYFIELDS_PDF["opt2"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        REVHISTORYFIELDS_FREECAD["opt2"] = changeWindow.getFIELD_FREECAD();
        REVHISTORYFIELDS_KICAD5["opt2"] = changeWindow.getFIELD_KICAD5();
        REVHISTORYFIELDS_KICAD6["opt2"] = changeWindow.getFIELD_KICAD6();
        REVHISTORYFIELDS_PDF["opt2"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}


void ASME_Y14_35_Width180::on_opt3PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(REVHISTORYFIELDS_FREECAD["opt3"]);
    changeWindow.setFIELD_KICAD5(REVHISTORYFIELDS_KICAD5["opt3"]);
    changeWindow.setFIELD_KICAD6(REVHISTORYFIELDS_KICAD6["opt3"]);
    changeWindow.setFIELD_PDF(REVHISTORYFIELDS_PDF["opt3"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        REVHISTORYFIELDS_FREECAD["opt3"] = changeWindow.getFIELD_FREECAD();
        REVHISTORYFIELDS_KICAD5["opt3"] = changeWindow.getFIELD_KICAD5();
        REVHISTORYFIELDS_KICAD6["opt3"] = changeWindow.getFIELD_KICAD6();
        REVHISTORYFIELDS_PDF["opt3"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}


void ASME_Y14_35_Width180::on_opt4PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(REVHISTORYFIELDS_FREECAD["opt4"]);
    changeWindow.setFIELD_KICAD5(REVHISTORYFIELDS_KICAD5["opt4"]);
    changeWindow.setFIELD_KICAD6(REVHISTORYFIELDS_KICAD6["opt4"]);
    changeWindow.setFIELD_PDF(REVHISTORYFIELDS_PDF["opt4"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        REVHISTORYFIELDS_FREECAD["opt4"] = changeWindow.getFIELD_FREECAD();
        REVHISTORYFIELDS_KICAD5["opt4"] = changeWindow.getFIELD_KICAD5();
        REVHISTORYFIELDS_KICAD6["opt4"] = changeWindow.getFIELD_KICAD6();
        REVHISTORYFIELDS_PDF["opt4"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}


void ASME_Y14_35_Width180::on_opt5PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(REVHISTORYFIELDS_FREECAD["opt5"]);
    changeWindow.setFIELD_KICAD5(REVHISTORYFIELDS_KICAD5["opt5"]);
    changeWindow.setFIELD_KICAD6(REVHISTORYFIELDS_KICAD6["opt5"]);
    changeWindow.setFIELD_PDF(REVHISTORYFIELDS_PDF["opt5"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        REVHISTORYFIELDS_FREECAD["opt5"] = changeWindow.getFIELD_FREECAD();
        REVHISTORYFIELDS_KICAD5["opt5"] = changeWindow.getFIELD_KICAD5();
        REVHISTORYFIELDS_KICAD6["opt5"] = changeWindow.getFIELD_KICAD6();
        REVHISTORYFIELDS_PDF["opt5"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

const QMap<QString, TitelblockField> &ASME_Y14_35_Width180::getREVHISTORYFIELDS_PDF() const
{
    return REVHISTORYFIELDS_PDF;
}

void ASME_Y14_35_Width180::setREVHISTORYFIELDS_PDF(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_PDF)
{
    REVHISTORYFIELDS_PDF = newREVHISTORYFIELDS_PDF;
    REVHISTORYFIELDS_ORG_PDF = newREVHISTORYFIELDS_PDF;
}

const QMap<QString, TitelblockField> &ASME_Y14_35_Width180::getREVHISTORYFIELDS_KICAD6() const
{
    return REVHISTORYFIELDS_KICAD6;
}

void ASME_Y14_35_Width180::setREVHISTORYFIELDS_KICAD6(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_KICAD6)
{
    REVHISTORYFIELDS_KICAD6 = newREVHISTORYFIELDS_KICAD6;
    REVHISTORYFIELDS_ORG_KICAD6 = newREVHISTORYFIELDS_KICAD6;
    loadButtonText();
}

const QMap<QString, TitelblockField> &ASME_Y14_35_Width180::getREVHISTORYFIELDS_KICAD5() const
{
    return REVHISTORYFIELDS_KICAD5;
}

void ASME_Y14_35_Width180::setREVHISTORYFIELDS_KICAD5(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_KICAD5)
{
    REVHISTORYFIELDS_KICAD5 = newREVHISTORYFIELDS_KICAD5;
    REVHISTORYFIELDS_ORG_KICAD5 = newREVHISTORYFIELDS_KICAD5;
    loadButtonText();
}

