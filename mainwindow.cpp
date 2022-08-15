#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "loadesavesettings.h"

#include "templategenkicad_5.h"
#include "templategenkicad_6.h"
#include "templategenkicad_7.h"

void MainWindow::initPageSizes()
{
    foreach(PageSize sheet, PAGESIZES)
    {
        ui->SheetSizeComboBox->addItem(sheet.sizeString);
    }
}

void MainWindow::initPageStyles()
{
    ui->SheetStyleComboBox->addItem("ISO5457 ISO7200"); // PageStyle::ISO5457_ISO7200
}

void MainWindow::initRevHistoryStyles()
{
    ui->revHistoryStyleComboBox->addItem("ASME Y14.35 Width: 180");// RevHistoryStyle::ASME_Y14_35_Width180
}

void MainWindow::initFoldLinesTarget()
{
    foreach(PageSize sheet, FOLDLINESTARGET)
    {
        ui->foldingLinesComboBox->addItem(sheet.sizeString);
    }
}

PageStyle MainWindow::getPageStyle()
{
    if(ui->SheetStyleComboBox->currentText() == "ISO5457 ISO7200")
    {
        return PageStyle::ISO5457_ISO7200;
    }

    return PageStyle::ISO5457_ISO7200;
}

PageSize MainWindow::getPageSize(QString sizeString, double width, double height)
{
    if(sizeString == "User defined")
    {
        PageSize tmp;
        tmp.sizeString = ui->NameLineEdit->text();
        tmp.height = ui->sheetHeightDoubleSpinBox->value();
        tmp.width = ui->sheetWidthDoubleSpinBox->value();
        return tmp;
    }
    else
    {
        foreach(PageSize page, PAGESIZES)
        {
            if(page.sizeString == sizeString)
            {
                page.sizeString = page.sizeString;
                return page;
            }
        }
        PageSize tmp;
        tmp.sizeString = "User defined";
        tmp.height = height;
        tmp.width = width;
        return tmp;
    }
}

PageSize MainWindow::getFoldLinesTarget(QString sizeString)
{
    foreach(PageSize page, FOLDLINESTARGET)
    {
        if(page.sizeString == sizeString)
        {
            return page;
        }
    }
    return FOLDLINESTARGET[0];
}

RevHistoryStyle MainWindow::getRevHistoryStyle()
{
    if(ui->revHistoryStyleComboBox->currentText() == "ASME Y14.35 Width: 180")
    {
        return RevHistoryStyle::ASME_Y14_35_Width180;
    }

    return RevHistoryStyle::ASME_Y14_35_Width180;
}

QString MainWindow::getRevHistoryStyleString(RevHistoryStyle style)
{
    QString ret = "";
    switch (style)
    {
    case RevHistoryStyle::ASME_Y14_35_Width180:
        ret = "ASME Y14.35 Width: 180";
        break;
    }
    return ret;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initPageSizes();
    initPageStyles();
    initRevHistoryStyles();
    initFoldLinesTarget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_GeneratePushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 LASTDIR,
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    PageSize sheetSize = getPageSize(ui->SheetSizeComboBox->currentText());
    QString sheetName = ui->NameLineEdit->text();
    PageStyle sheetStyle = getPageStyle();
    QMap<QString, TitelblockField> titelblockFields = ISO7200OPTIONS->getTITELBLOCKFIELDS();
    qint64 numOptLines = ui->OptLinesSpinBox->value();
    qint64 numRevHistory = ui->numRevSpinBox->value();
    QMap<QString, TitelblockField> revHistoryFields = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS();
    bool trimmingMarks = ui->trimmingMarksCheckBox->isChecked();
    bool revHistory = ui->RevHistoryCheckBox->isChecked();
    bool foldLines = ui->foldLinesCheckBox->isChecked();
    PageSize foldLinesTaget = getFoldLinesTarget(ui->foldingLinesComboBox->currentText());
    bool smallPartsList = ui->SmallPartsListCheckBox->isChecked();
    quint64 numLinesSmallPartsList = ui->SmallPartsListNumLinesPerFieldSpinBox->value();
    quint64 numPartsSmallPartsList = ui->SmallPartsListNumPartsSpinBox->value();
    QMap<QString, TitelblockField> smallPartsListFileds = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS();
    bool fullSheetPartsList = ui->FullPartsListCheckBox->isChecked();
    quint64 numLinesFullSheetPartsList = ui->FullPartsListNumLinesPerFieldSpinBox->value();
    quint64 numSheetsFullSheetPartsList = ui->FullPartsListNumLinesPerFieldSpinBox->value();
    QMap<QString, TitelblockField> fullSheetPartsListFields = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS();
    bool logo = ui->logoCheckBox->isChecked();
    QString logoDir = LOGODIR;

    // KiCAD 5
    {
        TemplateGenKiCAD_5 KiCAD(this);
        KiCAD.setDIR(dir);
        KiCAD.setPAGESIZE(sheetSize);
        KiCAD.setSHEETNAME(sheetName);
        KiCAD.setPAGESTYLE(sheetStyle);
        KiCAD.setNUMOPTLINES(numOptLines);
        KiCAD.setTITELBLOCKFIELDS(titelblockFields);
        KiCAD.setTRIMMINGMARKS(trimmingMarks);
        KiCAD.setREVHISTORY(revHistory);
        KiCAD.setREVHISTORYSTYLE(getRevHistoryStyle());
        KiCAD.setNUMREVHISTORY(numRevHistory);
        KiCAD.setREVHISTORYFIELDS(revHistoryFields);
        KiCAD.setFOLDLINES(foldLines);
        KiCAD.setFOLDLINETARGET(foldLinesTaget);
        KiCAD.setSMALLPARTSLIST(smallPartsList);
        KiCAD.setNUMLINESMALLPARTSLIST(numLinesSmallPartsList);
        KiCAD.setNUMPARTSSMALLPARTSLIST(numPartsSmallPartsList);
        KiCAD.setSMALLPARTSLISTFIELDS(smallPartsListFileds);
        KiCAD.setFULLSHEETPARTSLIST(fullSheetPartsList);
        KiCAD.setNUMLINESFULLSHEETPARTSLIST(numLinesFullSheetPartsList);
        KiCAD.setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFields);
        KiCAD.setLOGO(logo);
        KiCAD.setLOGODIR(logoDir);
        KiCAD.draw();
    }

    // KiCAD 6
    {
        TemplateGenKiCAD_6 KiCAD(this);
        KiCAD.setDIR(dir);
        KiCAD.setPAGESIZE(sheetSize);
        KiCAD.setSHEETNAME(sheetName);
        KiCAD.setPAGESTYLE(sheetStyle);
        KiCAD.setNUMOPTLINES(numOptLines);
        KiCAD.setTITELBLOCKFIELDS(titelblockFields);
        KiCAD.setTRIMMINGMARKS(trimmingMarks);
        KiCAD.setREVHISTORY(revHistory);
        KiCAD.setREVHISTORYSTYLE(getRevHistoryStyle());
        KiCAD.setNUMREVHISTORY(numRevHistory);
        KiCAD.setREVHISTORYFIELDS(revHistoryFields);
        KiCAD.setFOLDLINES(foldLines);
        KiCAD.setFOLDLINETARGET(foldLinesTaget);
        KiCAD.setSMALLPARTSLIST(smallPartsList);
        KiCAD.setNUMLINESMALLPARTSLIST(numLinesSmallPartsList);
        KiCAD.setNUMPARTSSMALLPARTSLIST(numPartsSmallPartsList);
        KiCAD.setSMALLPARTSLISTFIELDS(smallPartsListFileds);
        KiCAD.setFULLSHEETPARTSLIST(fullSheetPartsList);
        KiCAD.setNUMLINESFULLSHEETPARTSLIST(numLinesFullSheetPartsList);
        KiCAD.setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFields);
        KiCAD.setLOGO(logo);
        KiCAD.setLOGODIR(logoDir);
        KiCAD.draw();
    }

    // KiCAD 7
    {
        TemplateGenKiCAD_7 KiCAD(this);
        KiCAD.setDIR(dir);
        KiCAD.setPAGESIZE(sheetSize);
        KiCAD.setSHEETNAME(sheetName);
        KiCAD.setPAGESTYLE(sheetStyle);
        KiCAD.setNUMOPTLINES(numOptLines);
        KiCAD.setTITELBLOCKFIELDS(titelblockFields);
        KiCAD.setTRIMMINGMARKS(trimmingMarks);
        KiCAD.setREVHISTORY(revHistory);
        KiCAD.setREVHISTORYSTYLE(getRevHistoryStyle());
        KiCAD.setNUMREVHISTORY(numRevHistory);
        KiCAD.setREVHISTORYFIELDS(revHistoryFields);
        KiCAD.setFOLDLINES(foldLines);
        KiCAD.setFOLDLINETARGET(foldLinesTaget);
        KiCAD.setSMALLPARTSLIST(smallPartsList);
        KiCAD.setNUMLINESMALLPARTSLIST(numLinesSmallPartsList);
        KiCAD.setNUMPARTSSMALLPARTSLIST(numPartsSmallPartsList);
        KiCAD.setSMALLPARTSLISTFIELDS(smallPartsListFileds);
        KiCAD.setFULLSHEETPARTSLIST(fullSheetPartsList);
        KiCAD.setNUMLINESFULLSHEETPARTSLIST(numLinesFullSheetPartsList);
        KiCAD.setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFields);
        KiCAD.setLOGO(logo);
        KiCAD.setLOGODIR(logoDir);
        KiCAD.draw();
    }
}

void MainWindow::on_SheetSizeComboBox_currentTextChanged(const QString &arg1)
{
    PageSize sheetSize = getPageSize(arg1);
    ui->sheetHeightDoubleSpinBox->setValue(sheetSize.height);
    ui->sheetWidthDoubleSpinBox->setValue(sheetSize.width);

    if(arg1 == "User defined")
    {
        ui->NameLineEdit->setEnabled(true);
        ui->sheetHeightDoubleSpinBox->setEnabled(true);
        ui->sheetWidthDoubleSpinBox->setEnabled(true);
    }
    else
    {
        ui->NameLineEdit->setEnabled(false);
        ui->sheetHeightDoubleSpinBox->setEnabled(false);
        ui->sheetWidthDoubleSpinBox->setEnabled(false);
    }

    if(arg1 == "A4P" || arg1 == "A4L")
    {
        ui->foldLinesCheckBox->setChecked(false);
    }
}

void MainWindow::on_sheetTitelblockFieldsPushButton_clicked()
{
    if(ui->SheetStyleComboBox->currentText() == "ISO5457 ISO7200")
    {
        ISO7200OPTIONS->setModal(true);
        ISO7200OPTIONS->exec();
    }
    else
    {
        qDebug() << "None";
    }
}

void MainWindow::on_revHistoryStylePushButton_clicked()
{
    if(ui->revHistoryStyleComboBox->currentText() == "ASME Y14.35 Width: 180")
    {
        ASME_Y14_35_WIDTH180->setModal(true);
        ASME_Y14_35_WIDTH180->exec();
    }
    else
    {
        qDebug() << "None";
    }
}

void MainWindow::on_FullPartsListCheckBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->FullPartsListNumLinesPerFieldLabel->setEnabled(true);
        ui->FullPartsListNumLinesPerFieldSpinBox->setEnabled(true);
        ui->FullPartsListNumSheetsLabel->setEnabled(true);
        ui->FullPartsListNumSheetsSpinBox->setEnabled(true);
        ui->SmallPartsListCheckBox->setEnabled(false);
    }
    else
    {
        ui->FullPartsListNumLinesPerFieldLabel->setEnabled(false);
        ui->FullPartsListNumLinesPerFieldSpinBox->setEnabled(false);
        ui->FullPartsListNumSheetsLabel->setEnabled(false);
        ui->FullPartsListNumSheetsSpinBox->setEnabled(false);
        ui->SmallPartsListCheckBox->setEnabled(true);
    }
}

void MainWindow::on_SmallPartsListCheckBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->SmallPartsListNumLinesPerFieldLabel->setEnabled(true);
        ui->SmallPartsListNumLinesPerFieldSpinBox->setEnabled(true);
        ui->SmallPartsListNumPartsLabel->setEnabled(true);
        ui->SmallPartsListNumPartsSpinBox->setEnabled(true);
        ui->FullPartsListCheckBox->setEnabled(false);
    }
    else
    {
        ui->SmallPartsListNumLinesPerFieldLabel->setEnabled(false);
        ui->SmallPartsListNumLinesPerFieldSpinBox->setEnabled(false);
        ui->SmallPartsListNumPartsLabel->setEnabled(false);
        ui->SmallPartsListNumPartsSpinBox->setEnabled(false);
        ui->FullPartsListCheckBox->setEnabled(true);
    }
}

void MainWindow::on_pushButton_clicked()
{
    SMALLPARTSLISTSOPTIONS->setModal(true);
    SMALLPARTSLISTSOPTIONS->exec();
}

void MainWindow::on_editFullPartsListPushButton_clicked()
{
    FULLSHEETPARTLISTOPIONS->setModal(true);
    FULLSHEETPARTLISTOPIONS->exec();
}

void MainWindow::on_loadFielsPushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Load File",
                                LASTDIR + "setting.xml",
                                "Xml (*.xml)");
    LoadeSaveSettings file(this);
    file.loadSettings(fileName);
    ui->SheetSizeComboBox->setCurrentText(file.getSHEETSIZE().sizeString);
    ISO7200OPTIONS->setTITELBLOCKFIELDS(file.getTITELBLOCKFIELDS());
    ui->RevHistoryCheckBox->setChecked(file.getREVHISTORY());
    ui->revHistoryStyleComboBox->setCurrentText(getRevHistoryStyleString(file.getREVHISTORYSTYLE()));
    ASME_Y14_35_WIDTH180->setREVHISTORYFIELDS(file.getREVHISTORYFIELDS());
    ui->foldLinesCheckBox->setChecked(file.getFOLDLINES());
    ui->foldingLinesComboBox->setCurrentText(file.getFOLDLINESTARGET().sizeString);
    ui->SmallPartsListCheckBox->setChecked(file.getSMALLPARTSLIST());
    SMALLPARTSLISTSOPTIONS->setSMALLPARTSLISTFIELDS(file.getSMALLPARTSLISTFIELDS());
    ui->SmallPartsListNumLinesPerFieldSpinBox->setValue(file.getNUMLINESSMALLPARTSLIST());
    ui->SmallPartsListNumPartsSpinBox->setValue(file.getNUMPARTSSMALLPARTSLIST());
    ui->FullPartsListCheckBox->setChecked(file.getFULLSHEETPARTSLIST());
    FULLSHEETPARTLISTOPIONS->setFULLSHEETPARTSLISTFIELDS(file.getFULLSHEETPARTSLISTFIELDS());
    ui->FullPartsListNumLinesPerFieldSpinBox->setValue(file.getNUMLINESFULLSHEETPARTSLIST());
    ui->FullPartsListNumSheetsSpinBox->setValue(file.getNUMSHEETSFULLSHEETPARTSLIST());
    ui->logoCheckBox->setChecked(file.getLOGO());
    LOGODIR = file.getLOGODIR();
}


void MainWindow::on_saveFieldsPushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Load File",
                                LASTDIR + "setting.xml",
                                "Xml (*.xml)");
    PageSize sheetSize = getPageSize(ui->SheetSizeComboBox->currentText());
    QString sheetName = ui->NameLineEdit->text();
    PageStyle sheetStyle = getPageStyle();
    QMap<QString, TitelblockField> titelblockFields = ISO7200OPTIONS->getTITELBLOCKFIELDS();
    qint64 numOptLines = ui->OptLinesSpinBox->value();
    qint64 numRevHistory = ui->numRevSpinBox->value();
    QMap<QString, TitelblockField> revHistoryFields = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS();
    bool trimmingMarks = ui->trimmingMarksCheckBox->isChecked();
    bool revHistory = ui->RevHistoryCheckBox->isChecked();
    bool foldLines = ui->foldLinesCheckBox->isChecked();
    PageSize foldLinesTaget = getFoldLinesTarget(ui->foldingLinesComboBox->currentText());
    bool smallPartsList = ui->SmallPartsListCheckBox->isChecked();
    quint64 numLinesSmallPartsList = ui->SmallPartsListNumLinesPerFieldSpinBox->value();
    quint64 numPartsSmallPartsList = ui->SmallPartsListNumPartsSpinBox->value();
    QMap<QString, TitelblockField> smallPartsListFileds = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS();
    bool fullSheetPartsList = ui->FullPartsListCheckBox->isChecked();
    quint64 numLinesFullSheetPartsList = ui->FullPartsListNumLinesPerFieldSpinBox->value();
    quint64 numSheetsFullSheetPartsList = ui->FullPartsListNumLinesPerFieldSpinBox->value();
    QMap<QString, TitelblockField> fullSheetPartsListFields = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS();
    bool logo = ui->logoCheckBox->isChecked();
    QString logoDir = LOGODIR;

    LoadeSaveSettings file(this);
    file.setSHEETSIZE(sheetSize);
    file.setSHEETNAME(sheetName);
    file.setSHEETSTYLE(sheetStyle);
    file.setNUMOPTLINES(numOptLines);
    file.setTITELBLOCKFIELDS(titelblockFields);
    file.setTRIMMINGMARKS(trimmingMarks);
    file.setREVHISTORY(revHistory);
    file.setREVHISTORYSTYLE(getRevHistoryStyle());
    file.setNUMREVHISTORY(numRevHistory);
    file.setREVHISTORYFIELDS(revHistoryFields);
    file.setFOLDLINES(foldLines);
    file.setFOLDLINESTARGET(foldLinesTaget);
    file.setSMALLPARTSLIST(smallPartsList);
    file.setNUMLINESSMALLPARTSLIST(numLinesSmallPartsList);
    file.setNUMPARTSSMALLPARTSLIST(numPartsSmallPartsList);
    file.setSMALLPARTSLISTFIELDS(smallPartsListFileds);
    file.setFULLSHEETPARTSLIST(fullSheetPartsList);
    file.setNUMLINESFULLSHEETPARTSLIST(numLinesFullSheetPartsList);
    file.setNUMSHEETSFULLSHEETPARTSLIST(numSheetsFullSheetPartsList);
    file.setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFields);
    file.setLOGO(logo);
    file.setLOGODIR(logoDir);
    file.saveSettings(fileName);
}

void MainWindow::on_logoPushButton_clicked()
{
    ui->logoCheckBox->setChecked(true);
    QString dir = QFileDialog::getOpenFileName(this, "Open File",
                                               "/home",
                                               "Logos (*.svg);;All files (*.*)");
    LOGODIR = dir;
}


