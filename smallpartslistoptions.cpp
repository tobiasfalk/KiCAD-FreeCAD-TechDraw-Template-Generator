#include "smallpartslistoptions.h"
#include "ui_smallpartslistoptions.h"

SmallPartsListOptions::SmallPartsListOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SmallPartsListOptions)
{
    ui->setupUi(this);
    loadStdOptions();
    loadButtonText();
}

SmallPartsListOptions::~SmallPartsListOptions()
{
    delete ui;
}

const QMap<QString, TitelblockField> &SmallPartsListOptions::getSMALLPARTSLISTFIELDS() const
{
    return SMALLPARTSLISTFIELDS;
}

void SmallPartsListOptions::setSMALLPARTSLISTFIELDS(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS)
{
    SMALLPARTSLISTFIELDS = newSMALLPARTSLISTFIELDS;
    SMALLPARTSLISTFIELDS_ORG = newSMALLPARTSLISTFIELDS;
}

void SmallPartsListOptions::loadStdOptions()
{
    //                           name                    lable                              KiCAD 5 Value               KiCAD 6 Value
    SMALLPARTSLISTFIELDS.insert("opt1", TitelblockField{"Pos.",                QStringList{"p"},            QStringList{"${p&{N}&{L}}"}});
    SMALLPARTSLISTFIELDS.insert("opt2", TitelblockField{"Qty.",                QStringList{"q"},            QStringList{"${q&{N}&{L}}"}});
    SMALLPARTSLISTFIELDS.insert("opt3", TitelblockField{"Unit",                QStringList{"u"},            QStringList{"${u&{N}&{L}}"}});
    SMALLPARTSLISTFIELDS.insert("opt4", TitelblockField{"Titel",               QStringList{"titel/name"},   QStringList{"${titel/name&{N}&{L}}"}});
    SMALLPARTSLISTFIELDS.insert("opt5", TitelblockField{"Doc. number",         QStringList{"doc number"},   QStringList{"${docNumber&{N}&{L}}"}});
}

void SmallPartsListOptions::loadButtonText()
{
    ui->opt1PushButton->setText(SMALLPARTSLISTFIELDS["opt1"].Label);
    ui->opt2PushButton->setText(SMALLPARTSLISTFIELDS["opt2"].Label);
    ui->opt3PushButton->setText(SMALLPARTSLISTFIELDS["opt3"].Label);
    ui->opt4PushButton->setText(SMALLPARTSLISTFIELDS["opt4"].Label);
    ui->opt5PushButton->setText(SMALLPARTSLISTFIELDS["opt5"].Label);
}

void SmallPartsListOptions::on_buttonBox_rejected()
{
    SMALLPARTSLISTFIELDS = SMALLPARTSLISTFIELDS_ORG;
}


void SmallPartsListOptions::on_opt1PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD(SMALLPARTSLISTFIELDS["opt1"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    SMALLPARTSLISTFIELDS["opt1"] = changeWindow.getFIELD();
    loadButtonText();
}


void SmallPartsListOptions::on_opt2PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD(SMALLPARTSLISTFIELDS["opt2"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    SMALLPARTSLISTFIELDS["opt2"] = changeWindow.getFIELD();
    loadButtonText();
}


void SmallPartsListOptions::on_opt3PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD(SMALLPARTSLISTFIELDS["opt3"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    SMALLPARTSLISTFIELDS["opt3"] = changeWindow.getFIELD();
    loadButtonText();
}


void SmallPartsListOptions::on_opt4PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD(SMALLPARTSLISTFIELDS["opt4"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    SMALLPARTSLISTFIELDS["opt4"] = changeWindow.getFIELD();
    loadButtonText();
}


void SmallPartsListOptions::on_opt5PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD(SMALLPARTSLISTFIELDS["opt5"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    SMALLPARTSLISTFIELDS["opt5"] = changeWindow.getFIELD();
    loadButtonText();
}

