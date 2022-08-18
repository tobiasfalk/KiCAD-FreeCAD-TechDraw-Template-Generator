#include "fullsheetspartlistoptions.h"
#include "ui_fullsheetspartlistoptions.h"

FullSheetsPartListOptions::FullSheetsPartListOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FullSheetsPartListOptions)
{
    ui->setupUi(this);
    loadStdOptions();
    loadButtonText();
}

FullSheetsPartListOptions::~FullSheetsPartListOptions()
{
    delete ui;
}

const QMap<QString, TitelblockField> &FullSheetsPartListOptions::getFULLSHEETPARTSLISTFIELDS() const
{
    return FULLSHEETPARTSLISTFIELDS;
}

void FullSheetsPartListOptions::setFULLSHEETPARTSLISTFIELDS(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS)
{
    FULLSHEETPARTSLISTFIELDS = newFULLSHEETPARTSLISTFIELDS;
    FULLSHEETPARTSLISTFIELDS_ORG = newFULLSHEETPARTSLISTFIELDS;
    loadButtonText();
}

void FullSheetsPartListOptions::loadStdOptions()
{
    //                           name                    lable                              KiCAD 5 Value               KiCAD 6 Value                   FreeCAD Name        FreeCAD Value
    FULLSHEETPARTSLISTFIELDS.insert("opt1", TitelblockField{"Pos.",                QStringList{"p"},            QStringList{"${p&{N}&{L}}"},            "Pos.",             QStringList{"."}});
    FULLSHEETPARTSLISTFIELDS.insert("opt2", TitelblockField{"Qty.",                QStringList{"q"},            QStringList{"${q&{N}&{L}}"},            "Qty.",             QStringList{"."}});
    FULLSHEETPARTSLISTFIELDS.insert("opt3", TitelblockField{"Unit",                QStringList{"u"},            QStringList{"${u&{N}&{L}}"},            "Unit",             QStringList{"."}});
    FULLSHEETPARTSLISTFIELDS.insert("opt4", TitelblockField{"Titel",               QStringList{"titel/name"},   QStringList{"${titel/name&{N}&{L}}"},   "Titel",            QStringList{"."}});
    FULLSHEETPARTSLISTFIELDS.insert("opt5", TitelblockField{"Doc. number",         QStringList{"doc number"},   QStringList{"${docNumber&{N}&{L}}"},    "Doc. number",      QStringList{"."}});
    FULLSHEETPARTSLISTFIELDS.insert("opt6", TitelblockField{"Comment",             QStringList{"comment"},      QStringList{"${comment&{N}&{L}}"},      "Comment",          QStringList{"."}});
}

void FullSheetsPartListOptions::loadButtonText()
{
    ui->opt1PushButton->setText(FULLSHEETPARTSLISTFIELDS["opt1"].Label);
    ui->opt2PushButton->setText(FULLSHEETPARTSLISTFIELDS["opt2"].Label);
    ui->opt3PushButton->setText(FULLSHEETPARTSLISTFIELDS["opt3"].Label);
    ui->opt4PushButton->setText(FULLSHEETPARTSLISTFIELDS["opt4"].Label);
    ui->opt5PushButton->setText(FULLSHEETPARTSLISTFIELDS["opt5"].Label);
    ui->opt6PushButton->setText(FULLSHEETPARTSLISTFIELDS["opt6"].Label);
}

void FullSheetsPartListOptions::on_opt1PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD(FULLSHEETPARTSLISTFIELDS["opt1"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    FULLSHEETPARTSLISTFIELDS["opt1"] = changeWindow.getFIELD();
    loadButtonText();
}


void FullSheetsPartListOptions::on_opt2PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD(FULLSHEETPARTSLISTFIELDS["opt2"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    FULLSHEETPARTSLISTFIELDS["opt2"] = changeWindow.getFIELD();
    loadButtonText();
}


void FullSheetsPartListOptions::on_opt3PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD(FULLSHEETPARTSLISTFIELDS["opt3"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    FULLSHEETPARTSLISTFIELDS["opt3"] = changeWindow.getFIELD();
    loadButtonText();
}


void FullSheetsPartListOptions::on_opt4PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD(FULLSHEETPARTSLISTFIELDS["opt4"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    FULLSHEETPARTSLISTFIELDS["opt4"] = changeWindow.getFIELD();
    loadButtonText();
}


void FullSheetsPartListOptions::on_opt5PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD(FULLSHEETPARTSLISTFIELDS["opt5"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    FULLSHEETPARTSLISTFIELDS["opt5"] = changeWindow.getFIELD();
    loadButtonText();
}

void FullSheetsPartListOptions::on_opt6PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD(FULLSHEETPARTSLISTFIELDS["opt6"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    FULLSHEETPARTSLISTFIELDS["opt6"] = changeWindow.getFIELD();
    loadButtonText();
}

