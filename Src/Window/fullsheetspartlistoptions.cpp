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

const QMap<QString, TitelblockField> &FullSheetsPartListOptions::getFULLSHEETPARTSLISTFIELDS_FREECAD() const
{
    return FULLSHEETPARTSLISTFIELDS_FREECAD;
}

void FullSheetsPartListOptions::setFULLSHEETPARTSLISTFIELDS_FREECAD(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_FREECAD)
{
    FULLSHEETPARTSLISTFIELDS_FREECAD = newFULLSHEETPARTSLISTFIELDS_FREECAD;
    FULLSHEETPARTSLISTFIELDS_FREECAD_ORG = newFULLSHEETPARTSLISTFIELDS_FREECAD;
    loadButtonText();
}

const QMap<QString, TitelblockField> &FullSheetsPartListOptions::getFULLSHEETPARTSLISTFIELDS_KICAD5() const
{
    return FULLSHEETPARTSLISTFIELDS_KICAD5;
}

void FullSheetsPartListOptions::setFULLSHEETPARTSLISTFIELDS_KICAD5(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_KICAD5)
{
    FULLSHEETPARTSLISTFIELDS_KICAD5 = newFULLSHEETPARTSLISTFIELDS_KICAD5;
    FULLSHEETPARTSLISTFIELDS_KICAD5_ORG = newFULLSHEETPARTSLISTFIELDS_KICAD5;
    loadButtonText();
}

const QMap<QString, TitelblockField> &FullSheetsPartListOptions::getFULLSHEETPARTSLISTFIELDS_KICAD6() const
{
    return FULLSHEETPARTSLISTFIELDS_KICAD6;
}

void FullSheetsPartListOptions::setFULLSHEETPARTSLISTFIELDS_KICAD6(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_KICAD6)
{
    FULLSHEETPARTSLISTFIELDS_KICAD6 = newFULLSHEETPARTSLISTFIELDS_KICAD6;
    FULLSHEETPARTSLISTFIELDS_KICAD6_ORG = newFULLSHEETPARTSLISTFIELDS_KICAD6;
    loadButtonText();
}

void FullSheetsPartListOptions::resetToOrigin()
{
    FULLSHEETPARTSLISTFIELDS_FREECAD = FULLSHEETPARTSLISTFIELDS_FREECAD_ORG;
}

void FullSheetsPartListOptions::loadStdOptions()
{
    // KiCAD 5
    //                           key                    label                                  Value                        Name
    FULLSHEETPARTSLISTFIELDS_KICAD5.insert("opt1", TitelblockField{"Pos.",                QStringList{"p"},                        "Pos."});
    FULLSHEETPARTSLISTFIELDS_KICAD5.insert("opt2", TitelblockField{"Qty.",                QStringList{"q"},                        "Qty."});
    FULLSHEETPARTSLISTFIELDS_KICAD5.insert("opt3", TitelblockField{"Unit",                QStringList{"u"},                        "Unit"});
    FULLSHEETPARTSLISTFIELDS_KICAD5.insert("opt4", TitelblockField{"Titel",               QStringList{"titel/name"},               "Titel"});
    FULLSHEETPARTSLISTFIELDS_KICAD5.insert("opt5", TitelblockField{"Doc. number",         QStringList{"doc number"},               "Doc. number"});
    FULLSHEETPARTSLISTFIELDS_KICAD5.insert("opt6", TitelblockField{"Comment",             QStringList{"comment"},                  "Comment"});

    // KiCAD 6
    //                           key                    label                                  Value                        Name
    FULLSHEETPARTSLISTFIELDS_KICAD6.insert("opt1", TitelblockField{"Pos.",                QStringList{"${p&{N}&{L}}"},             "Pos."});
    FULLSHEETPARTSLISTFIELDS_KICAD6.insert("opt2", TitelblockField{"Qty.",                QStringList{"${q&{N}&{L}}"},             "Qty."});
    FULLSHEETPARTSLISTFIELDS_KICAD6.insert("opt3", TitelblockField{"Unit",                QStringList{"${u&{N}&{L}}"},             "Unit"});
    FULLSHEETPARTSLISTFIELDS_KICAD6.insert("opt4", TitelblockField{"Titel",               QStringList{"${titel/name&{N}&{L}}"},    "Titel"});
    FULLSHEETPARTSLISTFIELDS_KICAD6.insert("opt5", TitelblockField{"Doc. number",         QStringList{"${docNumber&{N}&{L}}"},     "Doc. number"});
    FULLSHEETPARTSLISTFIELDS_KICAD6.insert("opt6", TitelblockField{"Comment",             QStringList{"${comment&{N}&{L}}"},       "Comment"});

    // FreeCAD
    //                           key                    label                                  Value                        Name
    FULLSHEETPARTSLISTFIELDS_FREECAD.insert("opt1", TitelblockField{"Pos.",                QStringList{":"},                        "Pos."});
    FULLSHEETPARTSLISTFIELDS_FREECAD.insert("opt2", TitelblockField{"Qty.",                QStringList{":"},                        "Qty."});
    FULLSHEETPARTSLISTFIELDS_FREECAD.insert("opt3", TitelblockField{"Unit",                QStringList{":"},                        "Unit"});
    FULLSHEETPARTSLISTFIELDS_FREECAD.insert("opt4", TitelblockField{"Titel",               QStringList{":"},                        "Titel"});
    FULLSHEETPARTSLISTFIELDS_FREECAD.insert("opt5", TitelblockField{"Doc. number",         QStringList{":"},                        "Doc. number"});
    FULLSHEETPARTSLISTFIELDS_FREECAD.insert("opt6", TitelblockField{"Comment",             QStringList{":"},                        "Comment"});

    // PDF
    //                           key                    label                                  Value                        Name
    FULLSHEETPARTSLISTFIELDS_PDF.insert("opt1", TitelblockField{"Pos.",                QStringList{""},                        "Pos."});
    FULLSHEETPARTSLISTFIELDS_PDF.insert("opt2", TitelblockField{"Qty.",                QStringList{""},                        "Qty."});
    FULLSHEETPARTSLISTFIELDS_PDF.insert("opt3", TitelblockField{"Unit",                QStringList{""},                        "Unit"});
    FULLSHEETPARTSLISTFIELDS_PDF.insert("opt4", TitelblockField{"Titel",               QStringList{""},                        "Titel"});
    FULLSHEETPARTSLISTFIELDS_PDF.insert("opt5", TitelblockField{"Doc. number",         QStringList{""},                        "Doc. number"});
    FULLSHEETPARTSLISTFIELDS_PDF.insert("opt6", TitelblockField{"Comment",             QStringList{""},                        "Comment"});
}

void FullSheetsPartListOptions::loadButtonText()
{
    ui->opt1PushButton->setText(FULLSHEETPARTSLISTFIELDS_FREECAD["opt1"].Label);
    ui->opt2PushButton->setText(FULLSHEETPARTSLISTFIELDS_FREECAD["opt2"].Label);
    ui->opt3PushButton->setText(FULLSHEETPARTSLISTFIELDS_FREECAD["opt3"].Label);
    ui->opt4PushButton->setText(FULLSHEETPARTSLISTFIELDS_FREECAD["opt4"].Label);
    ui->opt5PushButton->setText(FULLSHEETPARTSLISTFIELDS_FREECAD["opt5"].Label);
    ui->opt6PushButton->setText(FULLSHEETPARTSLISTFIELDS_FREECAD["opt6"].Label);
}

void FullSheetsPartListOptions::on_opt1PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(FULLSHEETPARTSLISTFIELDS_FREECAD["opt1"]);
    changeWindow.setFIELD_KICAD5(FULLSHEETPARTSLISTFIELDS_KICAD5["opt1"]);
    changeWindow.setFIELD_KICAD6(FULLSHEETPARTSLISTFIELDS_KICAD6["opt1"]);
    changeWindow.setFIELD_PDF(FULLSHEETPARTSLISTFIELDS_PDF["opt1"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        FULLSHEETPARTSLISTFIELDS_FREECAD["opt1"] = changeWindow.getFIELD_FREECAD();
        FULLSHEETPARTSLISTFIELDS_KICAD5["opt1"] = changeWindow.getFIELD_KICAD5();
        FULLSHEETPARTSLISTFIELDS_KICAD6["opt1"] = changeWindow.getFIELD_KICAD6();
        FULLSHEETPARTSLISTFIELDS_PDF["opt1"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}


void FullSheetsPartListOptions::on_opt2PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(FULLSHEETPARTSLISTFIELDS_FREECAD["opt2"]);
    changeWindow.setFIELD_KICAD5(FULLSHEETPARTSLISTFIELDS_KICAD5["opt2"]);
    changeWindow.setFIELD_KICAD6(FULLSHEETPARTSLISTFIELDS_KICAD6["opt2"]);
    changeWindow.setFIELD_PDF(FULLSHEETPARTSLISTFIELDS_PDF["opt2"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        FULLSHEETPARTSLISTFIELDS_FREECAD["opt2"] = changeWindow.getFIELD_FREECAD();
        FULLSHEETPARTSLISTFIELDS_KICAD5["opt2"] = changeWindow.getFIELD_KICAD5();
        FULLSHEETPARTSLISTFIELDS_KICAD6["opt2"] = changeWindow.getFIELD_KICAD6();
        FULLSHEETPARTSLISTFIELDS_PDF["opt2"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}


void FullSheetsPartListOptions::on_opt3PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(FULLSHEETPARTSLISTFIELDS_FREECAD["opt3"]);
    changeWindow.setFIELD_KICAD5(FULLSHEETPARTSLISTFIELDS_KICAD5["opt3"]);
    changeWindow.setFIELD_KICAD6(FULLSHEETPARTSLISTFIELDS_KICAD6["opt3"]);
    changeWindow.setFIELD_PDF(FULLSHEETPARTSLISTFIELDS_PDF["opt3"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        FULLSHEETPARTSLISTFIELDS_FREECAD["opt3"] = changeWindow.getFIELD_FREECAD();
        FULLSHEETPARTSLISTFIELDS_KICAD5["opt3"] = changeWindow.getFIELD_KICAD5();
        FULLSHEETPARTSLISTFIELDS_KICAD6["opt3"] = changeWindow.getFIELD_KICAD6();
        FULLSHEETPARTSLISTFIELDS_PDF["opt3"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}


void FullSheetsPartListOptions::on_opt4PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(FULLSHEETPARTSLISTFIELDS_FREECAD["opt4"]);
    changeWindow.setFIELD_KICAD5(FULLSHEETPARTSLISTFIELDS_KICAD5["opt4"]);
    changeWindow.setFIELD_KICAD6(FULLSHEETPARTSLISTFIELDS_KICAD6["opt4"]);
    changeWindow.setFIELD_PDF(FULLSHEETPARTSLISTFIELDS_PDF["opt4"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        FULLSHEETPARTSLISTFIELDS_FREECAD["opt4"] = changeWindow.getFIELD_FREECAD();
        FULLSHEETPARTSLISTFIELDS_KICAD5["opt4"] = changeWindow.getFIELD_KICAD5();
        FULLSHEETPARTSLISTFIELDS_KICAD6["opt4"] = changeWindow.getFIELD_KICAD6();
        FULLSHEETPARTSLISTFIELDS_PDF["opt4"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}


void FullSheetsPartListOptions::on_opt5PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(FULLSHEETPARTSLISTFIELDS_FREECAD["opt5"]);
    changeWindow.setFIELD_KICAD5(FULLSHEETPARTSLISTFIELDS_KICAD5["opt5"]);
    changeWindow.setFIELD_KICAD6(FULLSHEETPARTSLISTFIELDS_KICAD6["opt5"]);
    changeWindow.setFIELD_PDF(FULLSHEETPARTSLISTFIELDS_PDF["opt5"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        FULLSHEETPARTSLISTFIELDS_FREECAD["opt5"] = changeWindow.getFIELD_FREECAD();
        FULLSHEETPARTSLISTFIELDS_KICAD5["opt5"] = changeWindow.getFIELD_KICAD5();
        FULLSHEETPARTSLISTFIELDS_KICAD6["opt5"] = changeWindow.getFIELD_KICAD6();
        FULLSHEETPARTSLISTFIELDS_PDF["opt5"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

void FullSheetsPartListOptions::on_opt6PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(FULLSHEETPARTSLISTFIELDS_FREECAD["opt6"]);
    changeWindow.setFIELD_KICAD5(FULLSHEETPARTSLISTFIELDS_KICAD5["opt6"]);
    changeWindow.setFIELD_KICAD6(FULLSHEETPARTSLISTFIELDS_KICAD6["opt6"]);
    changeWindow.setFIELD_PDF(FULLSHEETPARTSLISTFIELDS_PDF["opt6"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        FULLSHEETPARTSLISTFIELDS_FREECAD["opt6"] = changeWindow.getFIELD_FREECAD();
        FULLSHEETPARTSLISTFIELDS_KICAD5["opt6"] = changeWindow.getFIELD_KICAD5();
        FULLSHEETPARTSLISTFIELDS_KICAD6["opt6"] = changeWindow.getFIELD_KICAD6();
        FULLSHEETPARTSLISTFIELDS_PDF["opt6"] = changeWindow.getFIELD_PDF();
    }
    loadButtonText();
}

const QMap<QString, TitelblockField> &FullSheetsPartListOptions::getFULLSHEETPARTSLISTFIELDS_PDF() const
{
    return FULLSHEETPARTSLISTFIELDS_PDF;
}

void FullSheetsPartListOptions::setFULLSHEETPARTSLISTFIELDS_PDF(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_PDF)
{
    FULLSHEETPARTSLISTFIELDS_PDF = newFULLSHEETPARTSLISTFIELDS_PDF;
    FULLSHEETPARTSLISTFIELDS_PDF_ORG = newFULLSHEETPARTSLISTFIELDS_PDF;
}

