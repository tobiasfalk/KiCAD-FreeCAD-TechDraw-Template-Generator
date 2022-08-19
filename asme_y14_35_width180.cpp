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

const QMap<QString, TitelblockField> &ASME_Y14_35_Width180::getREVHISTORYFIELDS() const
{
    return REVHISTORYFIELDS;
}

void ASME_Y14_35_Width180::setREVHISTORYFIELDS(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS)
{
    REVHISTORYFIELDS = newREVHISTORYFIELDS;
    REVHISTORYFIELDS_ORG = newREVHISTORYFIELDS;
    loadButtonText();
}

void ASME_Y14_35_Width180::resetToOrigin()
{
    REVHISTORYFIELDS = REVHISTORYFIELDS_ORG;
}

void ASME_Y14_35_Width180::on_buttonBox_rejected()
{
    REVHISTORYFIELDS = REVHISTORYFIELDS_ORG;
}

void ASME_Y14_35_Width180::loadStdOptions()
{
    //                      name                     lable                              KiCAD 5 Value                                                                   KiCAD 6 Value                                                   FreeCAD Name            FreeCAD Value
    REVHISTORYFIELDS.insert("head",  TitelblockField{"Revision History",                QStringList{"-"},                                                               QStringList{"-"},                                               "Revision History",     QStringList{".", ".", "."}});
    REVHISTORYFIELDS.insert("opt1",  TitelblockField{"Zone",                            QStringList{"Z&{N} A", "Z&{N} B", "Z&{N} C"},                                   QStringList{"${zone&{N}A}", "${zone&{N}B}", "${zone&{N}C}"},    "Z&{N}",                QStringList{".", ".", "."}});
    REVHISTORYFIELDS.insert("opt2",  TitelblockField{"Rev.",                            QStringList{"R&{N} A", "R&{N} B", "R&{N} C"},                                   QStringList{"${rev&{N}A}", "${rev&{N}B}", "${rev&{N}C}"},       "R&{N}",                QStringList{".", ".", "."}});
    REVHISTORYFIELDS.insert("opt3",  TitelblockField{"Description",                     QStringList{"Description &{N} A", "Description &{N} B", "Description &{N} C"},  QStringList{"${desc&{N}A}", "${desc&{N}B}", "${desc&{N}C}"},    "Description &{N}",     QStringList{".", ".", "."}});
    REVHISTORYFIELDS.insert("opt4",  TitelblockField{"Date",                            QStringList{"D&{N} A", "D&{N} B", "D&{N} C"},                                   QStringList{"${d&{N}A}", "${d&{N}B}", "${d&{N}C}"},             "D&{N}",                QStringList{".", ".", "."}});
    REVHISTORYFIELDS.insert("opt5",  TitelblockField{"Created by",                      QStringList{"C by &{N} A", "C by &{N} B", "C by &{ C"},                         QStringList{"${cBy&{N}A}", "${cBy&{N}B}", "${cBy&{N}C}"},       "C by &{N}",            QStringList{".", ".", "."}});
}

void ASME_Y14_35_Width180::loadButtonText()
{
    ui->headPushButton->setText("Head: "  + REVHISTORYFIELDS["head"].Label);
    ui->opt1PushButton->setText("Option 1: "  + REVHISTORYFIELDS["opt1"].Label);
    ui->opt2PushButton->setText("Option 2: "  + REVHISTORYFIELDS["opt2"].Label);
    ui->opt3PushButton->setText("Option 3: "  + REVHISTORYFIELDS["opt3"].Label);
    ui->opt4PushButton->setText("Option 4: "  + REVHISTORYFIELDS["opt4"].Label);
    ui->opt5PushButton->setText("Option 5: "  + REVHISTORYFIELDS["opt5"].Label);
}


void ASME_Y14_35_Width180::on_headPushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD(REVHISTORYFIELDS["head"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        REVHISTORYFIELDS["head"] = changeWindow.getFIELD();
    }
    loadButtonText();
}


void ASME_Y14_35_Width180::on_opt1PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD(REVHISTORYFIELDS["opt1"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        REVHISTORYFIELDS["opt1"] = changeWindow.getFIELD();
    }
    loadButtonText();
}


void ASME_Y14_35_Width180::on_opt2PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD(REVHISTORYFIELDS["opt2"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        REVHISTORYFIELDS["opt2"] = changeWindow.getFIELD();
    }
    loadButtonText();
}


void ASME_Y14_35_Width180::on_opt3PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD(REVHISTORYFIELDS["opt3"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        REVHISTORYFIELDS["opt3"] = changeWindow.getFIELD();
    }
    loadButtonText();
}


void ASME_Y14_35_Width180::on_opt4PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD(REVHISTORYFIELDS["opt4"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        REVHISTORYFIELDS["opt4"] = changeWindow.getFIELD();
    }
    loadButtonText();
}


void ASME_Y14_35_Width180::on_opt5PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD(REVHISTORYFIELDS["opt5"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        REVHISTORYFIELDS["opt5"] = changeWindow.getFIELD();
    }
    loadButtonText();
}

