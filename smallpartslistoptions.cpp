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

const QMap<QString, TitelblockField> &SmallPartsListOptions::getSMALLPARTSLISTFIELDS_FREECAD() const
{
    return SMALLPARTSLISTFIELDS_FREECAD;
}

void SmallPartsListOptions::setSMALLPARTSLISTFIELDS_FREECAD(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS_FREECAD)
{
    SMALLPARTSLISTFIELDS_FREECAD = newSMALLPARTSLISTFIELDS_FREECAD;
    SMALLPARTSLISTFIELDS_FREECAD_ORG = newSMALLPARTSLISTFIELDS_FREECAD;
}

const QMap<QString, TitelblockField> &SmallPartsListOptions::getSMALLPARTSLISTFIELDS_KICAD5() const
{
    return SMALLPARTSLISTFIELDS_KICAD5;
}

void SmallPartsListOptions::setSMALLPARTSLISTFIELDS_KICAD5(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS_KICAD5)
{
    SMALLPARTSLISTFIELDS_KICAD5 = newSMALLPARTSLISTFIELDS_KICAD5;
    SMALLPARTSLISTFIELDS_KICAD5_ORG = newSMALLPARTSLISTFIELDS_KICAD5;
}

const QMap<QString, TitelblockField> &SmallPartsListOptions::getSMALLPARTSLISTFIELDS_KICAD6() const
{
    return SMALLPARTSLISTFIELDS_KICAD6;
}

void SmallPartsListOptions::setSMALLPARTSLISTFIELDS_KICAD6(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS_KICAD6)
{
    SMALLPARTSLISTFIELDS_KICAD6 = newSMALLPARTSLISTFIELDS_KICAD6;
    SMALLPARTSLISTFIELDS_KICAD6_ORG = newSMALLPARTSLISTFIELDS_KICAD6;
}

void SmallPartsListOptions::loadStdOptions()
{
    // KICAD 5
    //                           key                    label                                     Value             name
    SMALLPARTSLISTFIELDS_KICAD5.insert("opt1", TitelblockField{"Pos.",                QStringList{"p"},             "Pos."});
    SMALLPARTSLISTFIELDS_KICAD5.insert("opt2", TitelblockField{"Qty.",                QStringList{"q"},             "Qty."});
    SMALLPARTSLISTFIELDS_KICAD5.insert("opt3", TitelblockField{"Unit",                QStringList{"u"},             "Unit"});
    SMALLPARTSLISTFIELDS_KICAD5.insert("opt4", TitelblockField{"Titel",               QStringList{"titel/name"},    "Titel"});
    SMALLPARTSLISTFIELDS_KICAD5.insert("opt5", TitelblockField{"Doc. number",         QStringList{"doc number"},    "Doc. number"});

    // KICAD 6
    //                           key                    label                                     Value                               name
    SMALLPARTSLISTFIELDS_KICAD6.insert("opt1", TitelblockField{"Pos.",                       QStringList{"${p&{N}&{L}}"},                    "Pos."});
    SMALLPARTSLISTFIELDS_KICAD6.insert("opt2", TitelblockField{"Qty.",                       QStringList{"${q&{N}&{L}}"},                    "Qty."});
    SMALLPARTSLISTFIELDS_KICAD6.insert("opt3", TitelblockField{"Unit",                       QStringList{"${u&{N}&{L}}"},                    "Unit"});
    SMALLPARTSLISTFIELDS_KICAD6.insert("opt4", TitelblockField{"Titel",                      QStringList{"${titel/name&{N}&{L}}"},           "Titel"});
    SMALLPARTSLISTFIELDS_KICAD6.insert("opt5", TitelblockField{"Doc. number",                QStringList{"${docNumber&{N}&{L}}"},            "Doc. number"});

    // FREECAD
    //                           key                    label                              Value             name
    SMALLPARTSLISTFIELDS_FREECAD.insert("opt1", TitelblockField{"Pos.",                QStringList{"."},            "Pos."});
    SMALLPARTSLISTFIELDS_FREECAD.insert("opt2", TitelblockField{"Qty.",                QStringList{"."},            "Qty."});
    SMALLPARTSLISTFIELDS_FREECAD.insert("opt3", TitelblockField{"Unit",                QStringList{"."},            "Unit"});
    SMALLPARTSLISTFIELDS_FREECAD.insert("opt4", TitelblockField{"Titel",               QStringList{"."},            "Titel"});
    SMALLPARTSLISTFIELDS_FREECAD.insert("opt5", TitelblockField{"Doc. number",         QStringList{"."},            "Doc. number"});
}

void SmallPartsListOptions::loadButtonText()
{
    ui->opt1PushButton->setText(SMALLPARTSLISTFIELDS_FREECAD["opt1"].Label);
    ui->opt2PushButton->setText(SMALLPARTSLISTFIELDS_FREECAD["opt2"].Label);
    ui->opt3PushButton->setText(SMALLPARTSLISTFIELDS_FREECAD["opt3"].Label);
    ui->opt4PushButton->setText(SMALLPARTSLISTFIELDS_FREECAD["opt4"].Label);
    ui->opt5PushButton->setText(SMALLPARTSLISTFIELDS_FREECAD["opt5"].Label);
}

void SmallPartsListOptions::on_buttonBox_rejected()
{
    SMALLPARTSLISTFIELDS_FREECAD = SMALLPARTSLISTFIELDS_FREECAD_ORG;
    SMALLPARTSLISTFIELDS_KICAD5 = SMALLPARTSLISTFIELDS_KICAD5_ORG;
    SMALLPARTSLISTFIELDS_KICAD6 = SMALLPARTSLISTFIELDS_KICAD6_ORG;
}


void SmallPartsListOptions::on_opt1PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(SMALLPARTSLISTFIELDS_FREECAD["opt1"]);
    changeWindow.setFIELD_KICAD5(SMALLPARTSLISTFIELDS_KICAD5["opt1"]);
    changeWindow.setFIELD_KICAD6(SMALLPARTSLISTFIELDS_KICAD6["opt1"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        SMALLPARTSLISTFIELDS_FREECAD["opt1"] = changeWindow.getFIELD_FREECAD();
        SMALLPARTSLISTFIELDS_KICAD5["opt1"] = changeWindow.getFIELD_KICAD5();
        SMALLPARTSLISTFIELDS_KICAD6["opt1"] = changeWindow.getFIELD_KICAD6();
    }
    loadButtonText();
}


void SmallPartsListOptions::on_opt2PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(SMALLPARTSLISTFIELDS_FREECAD["opt2"]);
    changeWindow.setFIELD_KICAD5(SMALLPARTSLISTFIELDS_KICAD5["opt2"]);
    changeWindow.setFIELD_KICAD6(SMALLPARTSLISTFIELDS_KICAD6["opt2"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        SMALLPARTSLISTFIELDS_FREECAD["opt2"] = changeWindow.getFIELD_FREECAD();
        SMALLPARTSLISTFIELDS_KICAD5["opt2"] = changeWindow.getFIELD_KICAD5();
        SMALLPARTSLISTFIELDS_KICAD6["opt2"] = changeWindow.getFIELD_KICAD6();
    }
    loadButtonText();
}


void SmallPartsListOptions::on_opt3PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(SMALLPARTSLISTFIELDS_FREECAD["opt3"]);
    changeWindow.setFIELD_KICAD5(SMALLPARTSLISTFIELDS_KICAD5["opt3"]);
    changeWindow.setFIELD_KICAD6(SMALLPARTSLISTFIELDS_KICAD6["opt3"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        SMALLPARTSLISTFIELDS_FREECAD["opt3"] = changeWindow.getFIELD_FREECAD();
        SMALLPARTSLISTFIELDS_KICAD5["opt3"] = changeWindow.getFIELD_KICAD5();
        SMALLPARTSLISTFIELDS_KICAD6["opt3"] = changeWindow.getFIELD_KICAD6();
    }
    loadButtonText();
}


void SmallPartsListOptions::on_opt4PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(SMALLPARTSLISTFIELDS_FREECAD["opt4"]);
    changeWindow.setFIELD_KICAD5(SMALLPARTSLISTFIELDS_KICAD5["opt4"]);
    changeWindow.setFIELD_KICAD6(SMALLPARTSLISTFIELDS_KICAD6["opt4"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        SMALLPARTSLISTFIELDS_FREECAD["opt4"] = changeWindow.getFIELD_FREECAD();
        SMALLPARTSLISTFIELDS_KICAD5["opt4"] = changeWindow.getFIELD_KICAD5();
        SMALLPARTSLISTFIELDS_KICAD6["opt4"] = changeWindow.getFIELD_KICAD6();
    }
    loadButtonText();
}


void SmallPartsListOptions::on_opt5PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(SMALLPARTSLISTFIELDS_FREECAD["opt5"]);
    changeWindow.setFIELD_KICAD5(SMALLPARTSLISTFIELDS_KICAD5["opt5"]);
    changeWindow.setFIELD_KICAD6(SMALLPARTSLISTFIELDS_KICAD6["opt5"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        SMALLPARTSLISTFIELDS_FREECAD["opt5"] = changeWindow.getFIELD_FREECAD();
        SMALLPARTSLISTFIELDS_KICAD5["opt5"] = changeWindow.getFIELD_KICAD5();
        SMALLPARTSLISTFIELDS_KICAD6["opt5"] = changeWindow.getFIELD_KICAD6();
    }
    loadButtonText();
}

