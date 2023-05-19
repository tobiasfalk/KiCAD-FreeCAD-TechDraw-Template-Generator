#include "asme_y14_35_width180dialog.h"
#include "ui_asme_y14_35_width180dialog.h"

ASME_Y14_35_Width180Dialog::ASME_Y14_35_Width180Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ASME_Y14_35_Width180Dialog)
{
    ui->setupUi(this);
}

ASME_Y14_35_Width180Dialog::ASME_Y14_35_Width180Dialog(std::shared_ptr<ASME_Y14_35_Width180Options> newASME_Y14_35_WIDTH180OPTIONS, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ASME_Y14_35_Width180Dialog)
{
    ui->setupUi(this);
    setASME_Y14_35_WIDTH180OPTIONS(newASME_Y14_35_WIDTH180OPTIONS);
}

ASME_Y14_35_Width180Dialog::~ASME_Y14_35_Width180Dialog()
{
    delete ui;
}

void ASME_Y14_35_Width180Dialog::on_buttonBox_rejected()
{
}

void ASME_Y14_35_Width180Dialog::loadButtonText()
{
    ui->headPushButton->setText("Head: "  + ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_FREECAD()["head"].Label);
    ui->revOpt1PushButton->setText("Option 1: "  + ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_FREECAD()["opt1"].Label);
    ui->revOpt2PushButton->setText("Option 2: "  + ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_FREECAD()["opt2"].Label);
    ui->revOpt3PushButton->setText("Option 3: "  + ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_FREECAD()["opt3"].Label);
    ui->revOpt4PushButton->setText("Option 4: "  + ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_FREECAD()["opt4"].Label);
    ui->revOpt5PushButton->setText("Option 5: "  + ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_FREECAD()["opt5"].Label);
    ui->numRevSpinBox->setValue(ASME_Y14_35_WIDTH180OPTIONS->getNumRev());
    ui->numLinesRevSpinBox->setValue(ASME_Y14_35_WIDTH180OPTIONS->getNumLinesRev());
}

void ASME_Y14_35_Width180Dialog::loadPreview()
{
    PREVIEW = std::shared_ptr<Preview>(new Preview());
    PREVIEW->setMinimumWidth(400);
    PREVIEW->setStyleSheet("background-color: rgb(255,255,255)");

    // Preview
    SheetSize sheetSize = SheetSize{"ASME_Y14_35_WIDTH180", 180, 8 + ASME_Y14_35_WIDTH180OPTIONS->getNumRev() * (ASME_Y14_35_WIDTH180OPTIONS->getNumLinesRev() * (2.5 * 1.5) + 2)};
    QString sheetName = "ASME_Y14_35_WIDTH180";
    SheetStyle sheetStyle = SheetStyle::BLANK;
    QMap<QString, TitelblockField> titelblockFields = ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF();
    qint64 numOptLines = ISO7200OPTIONS->getNumOptLins();// ui->OptLinesSpinBox->value();
    QMap<QString, TitelblockField> revHistoryFields = ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_PDF();
    bool revHistory = true;
    bool foldLines = false;
    SheetSize foldLinesTaget = SheetSize{"ISO7200", 210, 250};
    bool smallPartsList = false;
    QMap<QString, TitelblockField> smallPartsListFileds = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_PDF();
    bool fullSheetPartsList = false;
    QMap<QString, TitelblockField> fullSheetPartsListFields = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_PDF();
    bool logo = false;
    QString logoDir = "";

    QDir dir;
    dir.mkdir(QDir::currentPath() + "/tmp");
    //TemplateGenKiCAD_5 KiCAD5(this);
    PREVIEW->setDIR(QDir::currentPath() + "/tmp");
    PREVIEW->setSHEETSIZE(sheetSize);
    PREVIEW->setSHEETNAME(sheetName);
    PREVIEW->setSHEETSTYLE(sheetStyle);
    PREVIEW->setNUMOPTLINES(numOptLines);
    PREVIEW->setTITELBLOCKFIELDS(titelblockFields);
    PREVIEW->setREVHISTORY(revHistory);
    PREVIEW->setREVHISTORYSTYLE(RevHistoryStyle::ASME_Y14_35_Width180);
    PREVIEW->setREVHISTORYFIELDS(revHistoryFields);
    PREVIEW->setFOLDLINES(foldLines);
    PREVIEW->setFOLDLINETARGET(foldLinesTaget);
    PREVIEW->setSMALLPARTSLIST(smallPartsList);
    PREVIEW->setSMALLPARTSLISTFIELDS(smallPartsListFileds);
    PREVIEW->setFULLSHEETPARTSLIST(fullSheetPartsList);
    PREVIEW->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFields);
    PREVIEW->setLOGO(logo);
    PREVIEW->setLOGODIR(logoDir);

    PREVIEW->setISO7200OPTIONS(ISO7200OPTIONS);
    PREVIEW->setASME_Y14_35_WIDTH180OPTIONS(ASME_Y14_35_WIDTH180OPTIONS);
    PREVIEW->setFULLSHEETPARTLISTOPIONS(FULLSHEETPARTLISTOPIONS);
    PREVIEW->setSMALLPARTSLISTSOPTIONS(SMALLPARTSLISTSOPTIONS);


    ui->gridLayout_2->addWidget(PREVIEW.get());
}

void ASME_Y14_35_Width180Dialog::updatePreview()
{
    if(DIALOGRUNNING){
        // Preview
        SheetSize sheetSize = SheetSize{"ISO7200", 180, 8 + ASME_Y14_35_WIDTH180OPTIONS->getNumRev() * (ASME_Y14_35_WIDTH180OPTIONS->getNumLinesRev() * (2.5 * 1.5) + 2)};
        QString sheetName = "ISO7200";
        SheetStyle sheetStyle = SheetStyle::BLANK;
        QMap<QString, TitelblockField> titelblockFields = ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF();
        qint64 numOptLines = ISO7200OPTIONS->getNumOptLins();// ui->OptLinesSpinBox->value();
        QMap<QString, TitelblockField> revHistoryFields = ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_PDF();
        bool revHistory = true;
        bool foldLines = false;
        SheetSize foldLinesTaget = SheetSize{"ISO7200", 210, 250};
        bool smallPartsList = false;
        QMap<QString, TitelblockField> smallPartsListFileds = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_PDF();
        bool fullSheetPartsList = false;
        QMap<QString, TitelblockField> fullSheetPartsListFields = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_PDF();
        bool logo = false;
        QString logoDir = "";

        QDir dir;
        dir.mkdir(QDir::currentPath() + "/tmp");
        //TemplateGenKiCAD_5 KiCAD5(this);
        PREVIEW->setDIR(QDir::currentPath() + "/tmp");
        PREVIEW->setSHEETSIZE(sheetSize);
        PREVIEW->setSHEETNAME(sheetName);
        PREVIEW->setSHEETSTYLE(sheetStyle);
        PREVIEW->setNUMOPTLINES(numOptLines);
        PREVIEW->setTITELBLOCKFIELDS(titelblockFields);
        PREVIEW->setREVHISTORY(revHistory);
        PREVIEW->setREVHISTORYSTYLE(RevHistoryStyle::ASME_Y14_35_Width180);
        PREVIEW->setREVHISTORYFIELDS(revHistoryFields);
        PREVIEW->setFOLDLINES(foldLines);
        PREVIEW->setFOLDLINETARGET(foldLinesTaget);
        PREVIEW->setSMALLPARTSLIST(smallPartsList);
        PREVIEW->setSMALLPARTSLISTFIELDS(smallPartsListFileds);
        PREVIEW->setFULLSHEETPARTSLIST(fullSheetPartsList);
        PREVIEW->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFields);
        PREVIEW->setLOGO(logo);
        PREVIEW->setLOGODIR(logoDir);
        PREVIEW->setMinimumWidth(this->size().width()/2);

        PREVIEW->setISO7200OPTIONS(ISO7200OPTIONS);
        PREVIEW->setASME_Y14_35_WIDTH180OPTIONS(ASME_Y14_35_WIDTH180OPTIONS);
        PREVIEW->setFULLSHEETPARTLISTOPIONS(FULLSHEETPARTLISTOPIONS);
        PREVIEW->setSMALLPARTSLISTSOPTIONS(SMALLPARTSLISTSOPTIONS);
        PREVIEW->update();
    }
}

void ASME_Y14_35_Width180Dialog::on_headPushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_FREECAD()["head"]);
    changeWindow.setFIELD_KICAD5(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_KICAD5()["head"]);
    changeWindow.setFIELD_KICAD6(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_KICAD6()["head"]);
    changeWindow.setFIELD_PDF(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_PDF()["head"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_FREECAD("head", changeWindow.getFIELD_FREECAD());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_KICAD5("head", changeWindow.getFIELD_KICAD5());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_KICAD6("head", changeWindow.getFIELD_KICAD6());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_PDF("head", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}


void ASME_Y14_35_Width180Dialog::on_revOpt1PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_FREECAD()["opt1"]);
    changeWindow.setFIELD_KICAD5(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_KICAD5()["opt1"]);
    changeWindow.setFIELD_KICAD6(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_KICAD6()["opt1"]);
    changeWindow.setFIELD_PDF(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_PDF()["opt1"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_FREECAD("opt1", changeWindow.getFIELD_FREECAD());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_KICAD5("opt1", changeWindow.getFIELD_KICAD5());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_KICAD6("opt1", changeWindow.getFIELD_KICAD6());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_PDF("opt1", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}


void ASME_Y14_35_Width180Dialog::on_revOpt2PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_FREECAD()["opt2"]);
    changeWindow.setFIELD_KICAD5(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_KICAD5()["opt2"]);
    changeWindow.setFIELD_KICAD6(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_KICAD6()["opt2"]);
    changeWindow.setFIELD_PDF(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_PDF()["opt2"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_FREECAD("opt2", changeWindow.getFIELD_FREECAD());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_KICAD5("opt2", changeWindow.getFIELD_KICAD5());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_KICAD6("opt2", changeWindow.getFIELD_KICAD6());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_PDF("opt2", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}


void ASME_Y14_35_Width180Dialog::on_revOpt3PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_FREECAD()["opt3"]);
    changeWindow.setFIELD_KICAD5(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_KICAD5()["opt3"]);
    changeWindow.setFIELD_KICAD6(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_KICAD6()["opt3"]);
    changeWindow.setFIELD_PDF(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_PDF()["opt3"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_FREECAD("opt3", changeWindow.getFIELD_FREECAD());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_KICAD5("opt3", changeWindow.getFIELD_KICAD5());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_KICAD6("opt3", changeWindow.getFIELD_KICAD6());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_PDF("opt3", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}


void ASME_Y14_35_Width180Dialog::on_revOpt4PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_FREECAD()["opt4"]);
    changeWindow.setFIELD_KICAD5(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_KICAD5()["opt4"]);
    changeWindow.setFIELD_KICAD6(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_KICAD6()["opt4"]);
    changeWindow.setFIELD_PDF(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_PDF()["opt4"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_FREECAD("opt4", changeWindow.getFIELD_FREECAD());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_KICAD5("opt4", changeWindow.getFIELD_KICAD5());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_KICAD6("opt4", changeWindow.getFIELD_KICAD6());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_PDF("opt4", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}


void ASME_Y14_35_Width180Dialog::on_revOpt5PushButton_clicked()
{
    ChangeTitelblockField changeWindow;
    changeWindow.setFIELD_FREECAD(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_FREECAD()["opt5"]);
    changeWindow.setFIELD_KICAD5(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_KICAD5()["opt5"]);
    changeWindow.setFIELD_KICAD6(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_KICAD6()["opt5"]);
    changeWindow.setFIELD_PDF(ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_PDF()["opt5"]);
    changeWindow.setModal(true);
    changeWindow.exec();
    if(changeWindow.result())
    {
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_FREECAD("opt5", changeWindow.getFIELD_FREECAD());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_KICAD5("opt5", changeWindow.getFIELD_KICAD5());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_KICAD6("opt5", changeWindow.getFIELD_KICAD6());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELD_PDF("opt5", changeWindow.getFIELD_PDF());
    }
    loadButtonText();
    updatePreview();
}


void ASME_Y14_35_Width180Dialog::on_buttonBox_accepted()
{

}

std::shared_ptr<ASME_Y14_35_Width180Options> ASME_Y14_35_Width180Dialog::getASME_Y14_35_WIDTH180OPTIONS() const
{
    return ASME_Y14_35_WIDTH180OPTIONS;
}

void ASME_Y14_35_Width180Dialog::setASME_Y14_35_WIDTH180OPTIONS(const std::shared_ptr<ASME_Y14_35_Width180Options> &newASME_Y14_35_WIDTH180OPTIONS)
{
    ASME_Y14_35_WIDTH180OPTIONS = newASME_Y14_35_WIDTH180OPTIONS;
    DIALOGRUNNING = true;
    loadButtonText();
    loadPreview();
}


void ASME_Y14_35_Width180Dialog::on_numRevSpinBox_valueChanged(int arg1)
{
    ASME_Y14_35_WIDTH180OPTIONS->setNumRev(arg1);
    updatePreview();
}


void ASME_Y14_35_Width180Dialog::on_numLinesRevSpinBox_valueChanged(int arg1)
{
    ASME_Y14_35_WIDTH180OPTIONS->setNumLinesRev(arg1);
    updatePreview();
}

void ASME_Y14_35_Width180Dialog::resizeEvent(QResizeEvent *)
{
    updatePreview();
}

