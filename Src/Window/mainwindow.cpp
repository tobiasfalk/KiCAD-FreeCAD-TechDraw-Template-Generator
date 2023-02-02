#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "loadesavesettings.h"

#include "kicad_symbol_scaler_ui.h"

void MainWindow::initSheetSizes()
{
    foreach(SheetSize sheet, SHEETSIZES)
    {
        ui->SheetSizeComboBox->addItem(sheet.sizeString);
    }
    ui->sheetWidthDoubleSpinBox->setValue(SHEETSIZES[0].width);
    ui->sheetHeightDoubleSpinBox->setValue(SHEETSIZES[0].height);
}

void MainWindow::initSheetStyles()
{
    ui->SheetStyleComboBox->addItem("ISO5457 ISO7200"); // SheetStyle::ISO5457_ISO7200
    ui->SheetStyleComboBox->addItem("Blank"); // SheetStyle::BLANK
}

void MainWindow::initRevHistoryStyles()
{
    ui->revHistoryStyleComboBox->addItem("ASME Y14.35 Width: 180");// RevHistoryStyle::ASME_Y14_35_Width180
}

void MainWindow::initFoldLinesTarget()
{
    foreach(SheetSize sheet, FOLDLINESTARGET)
    {
        ui->foldingLinesComboBox->addItem(sheet.sizeString);
    }
}

SheetStyle MainWindow::getSheetStyle()
{
    if(ui->SheetStyleComboBox->currentText() == "ISO5457 ISO7200")
    {
        return SheetStyle::ISO5457_ISO7200;
    }else if(ui->SheetStyleComboBox->currentText() == "Blank")
    {
        return SheetStyle::BLANK;
    }

    return SheetStyle::ISO5457_ISO7200;
}

SheetSize MainWindow::getSheetSize(QString sizeString, double width, double height)
{
    if(sizeString == "User defined")
    {
        SheetSize tmp;
        tmp.sizeString = ui->NameLineEdit->text();
        tmp.height = ui->sheetHeightDoubleSpinBox->value();
        tmp.width = ui->sheetWidthDoubleSpinBox->value();
        return tmp;
    }
    else
    {
        foreach(SheetSize sheet, SHEETSIZES)
        {
            if(sheet.sizeString == sizeString)
            {
                sheet.sizeString = sheet.sizeString;
                return sheet;
            }
        }
        SheetSize tmp;
        tmp.sizeString = "User defined";
        tmp.height = height;
        tmp.width = width;
        return tmp;
    }
}

SheetSize MainWindow::getFoldLinesTarget(QString sizeString)
{
    foreach(SheetSize sheet, FOLDLINESTARGET)
    {
        if(sheet.sizeString == sizeString)
        {
            return sheet;
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

void MainWindow::resizeEvent(QResizeEvent *event)
{
    PREVIEW->setMinimumWidth(ui->centralwidget->size().width() - 600);
    QWidget::resizeEvent(event);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("./lib/icon.png"));
    initSheetSizes();
    initSheetStyles();
    initRevHistoryStyles();
    initFoldLinesTarget();
//    initBOMStyles();

    PREVIEW = std::shared_ptr<Preview>(new Preview());
    PREVIEW->setMinimumWidth(900);
    PREVIEW->setStyleSheet("background-color: rgb(255,255,255)");

    // Preview
    SheetSize sheetSize = getSheetSize(ui->SheetSizeComboBox->currentText());
    QString sheetName = ui->NameLineEdit->text();
    SheetStyle sheetStyle = getSheetStyle();
    QMap<QString, TitelblockField> titelblockFields = ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF();
    qint64 numOptLines = ISO7200OPTIONS->getNumOptLins();// ui->OptLinesSpinBox->value();
    QMap<QString, TitelblockField> revHistoryFields = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_PDF();
    bool revHistory = ui->RevHistoryCheckBox->isChecked();
    bool foldLines = ui->foldLinesCheckBox->isChecked();
    SheetSize foldLinesTaget = getFoldLinesTarget(ui->foldingLinesComboBox->currentText());
    bool smallPartsList = ui->SmallPartsListCheckBox->isChecked();
    QMap<QString, TitelblockField> smallPartsListFileds = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_PDF();
    bool fullSheetPartsList = ui->FullPartsListCheckBox->isChecked();
    QMap<QString, TitelblockField> fullSheetPartsListFields = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_PDF();
    bool logo = ui->logoCheckBox->isChecked();
    QString logoDir = LOGODIR;

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
    PREVIEW->setREVHISTORYSTYLE(getRevHistoryStyle());
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
    PREVIEW->setASME_Y14_35_WIDTH180(ASME_Y14_35_WIDTH180);
    PREVIEW->setFULLSHEETPARTLISTOPIONS(FULLSHEETPARTLISTOPIONS);
    PREVIEW->setSMALLPARTSLISTSOPTIONS(SMALLPARTSLISTSOPTIONS);


    ui->gridLayout_2->addWidget(PREVIEW.get());

    WINDOWRUNNING = true;
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
    if(dir.size() > 0)
    {

        // KiCAD 5
        SheetSize sheetSize = getSheetSize(ui->SheetSizeComboBox->currentText());
        QString sheetName = ui->NameLineEdit->text();
        SheetStyle sheetStyle = getSheetStyle();
        QMap<QString, TitelblockField> titelblockFieldsKiCAD5 = ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5();
        qint64 numOptLines = ISO7200OPTIONS->getNumOptLins();// ui->OptLinesSpinBox->value();
        QMap<QString, TitelblockField> revHistoryFieldsKiCAD5 = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_KICAD5();
        bool revHistory = ui->RevHistoryCheckBox->isChecked();
        bool foldLines = ui->foldLinesCheckBox->isChecked();
        SheetSize foldLinesTaget = getFoldLinesTarget(ui->foldingLinesComboBox->currentText());
        bool smallPartsList = ui->SmallPartsListCheckBox->isChecked();
        QMap<QString, TitelblockField> smallPartsListFiledsKiCAD5 = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_KICAD5();
        bool fullSheetPartsList = ui->FullPartsListCheckBox->isChecked();
        QMap<QString, TitelblockField> fullSheetPartsListFieldsKiCAD5 = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_KICAD5();
        bool logo = ui->logoCheckBox->isChecked();
        QString logoDir = LOGODIR;

        std::shared_ptr<TemplateGenKiCAD_5> KiCAD5(new TemplateGenKiCAD_5 (this));
        KiCAD5->setDIR(dir);
        KiCAD5->setSHEETSIZE(sheetSize);
        KiCAD5->setSHEETNAME(sheetName);
        KiCAD5->setSHEETSTYLE(sheetStyle);
        KiCAD5->setNUMOPTLINES(numOptLines);
        KiCAD5->setTITELBLOCKFIELDS(titelblockFieldsKiCAD5);
        KiCAD5->setREVHISTORY(revHistory);
        KiCAD5->setREVHISTORYSTYLE(getRevHistoryStyle());
        KiCAD5->setREVHISTORYFIELDS(revHistoryFieldsKiCAD5);
        KiCAD5->setFOLDLINES(foldLines);
        KiCAD5->setFOLDLINETARGET(foldLinesTaget);
        KiCAD5->setSMALLPARTSLIST(smallPartsList);
        KiCAD5->setSMALLPARTSLISTFIELDS(smallPartsListFiledsKiCAD5);
        KiCAD5->setFULLSHEETPARTSLIST(fullSheetPartsList);
        KiCAD5->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFieldsKiCAD5);
        KiCAD5->setLOGO(logo);
        KiCAD5->setLOGODIR(logoDir);
        KiCAD5->draw();

        KiCAD5->setISO7200OPTIONS(ISO7200OPTIONS);
        KiCAD5->setASME_Y14_35_WIDTH180(ASME_Y14_35_WIDTH180);
        KiCAD5->setFULLSHEETPARTLISTOPIONS(FULLSHEETPARTLISTOPIONS);
        KiCAD5->setSMALLPARTSLISTSOPTIONS(SMALLPARTSLISTSOPTIONS);

        // KiCAD 6
        QMap<QString, TitelblockField> titelblockFieldsKiCAD6 = ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6();
        QMap<QString, TitelblockField> revHistoryFieldsKiCAD6 = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_KICAD6();
        QMap<QString, TitelblockField> smallPartsListFiledsKiCAD6 = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_KICAD6();
        QMap<QString, TitelblockField> fullSheetPartsListFieldsKiCAD6 = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_KICAD6();


        std::shared_ptr<TemplateGenKiCAD_6> KiCAD6(new TemplateGenKiCAD_6(this));
        KiCAD6->setDIR(dir);
        KiCAD6->setSHEETSIZE(sheetSize);
        KiCAD6->setSHEETNAME(sheetName);
        KiCAD6->setSHEETSTYLE(sheetStyle);
        KiCAD6->setNUMOPTLINES(numOptLines);
        KiCAD6->setTITELBLOCKFIELDS(titelblockFieldsKiCAD6);
        KiCAD6->setREVHISTORY(revHistory);
        KiCAD6->setREVHISTORYSTYLE(getRevHistoryStyle());
        KiCAD6->setREVHISTORYFIELDS(revHistoryFieldsKiCAD6);
        KiCAD6->setFOLDLINES(foldLines);
        KiCAD6->setFOLDLINETARGET(foldLinesTaget);
        KiCAD6->setSMALLPARTSLIST(smallPartsList);
        KiCAD6->setSMALLPARTSLISTFIELDS(smallPartsListFiledsKiCAD6);
        KiCAD6->setFULLSHEETPARTSLIST(fullSheetPartsList);
        KiCAD6->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFieldsKiCAD6);
        KiCAD6->setLOGO(logo);
        KiCAD6->setLOGODIR(logoDir);
        KiCAD6->draw();

        KiCAD6->setISO7200OPTIONS(ISO7200OPTIONS);
        KiCAD6->setASME_Y14_35_WIDTH180(ASME_Y14_35_WIDTH180);
        KiCAD6->setFULLSHEETPARTLISTOPIONS(FULLSHEETPARTLISTOPIONS);
        KiCAD6->setSMALLPARTSLISTSOPTIONS(SMALLPARTSLISTSOPTIONS);

        // KiCAD 7
        QMap<QString, TitelblockField> titelblockFieldsKiCAD7 = ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6();
        QMap<QString, TitelblockField> revHistoryFieldsKiCAD7 = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_KICAD6();
        QMap<QString, TitelblockField> smallPartsListFiledsKiCAD7 = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_KICAD6();
        QMap<QString, TitelblockField> fullSheetPartsListFieldsKiCAD7 = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_KICAD6();

        std::shared_ptr<TemplateGenKiCAD_7> KiCAD7(new TemplateGenKiCAD_7(this));
        KiCAD7->setDIR(dir);
        KiCAD7->setSHEETSIZE(sheetSize);
        KiCAD7->setSHEETNAME(sheetName);
        KiCAD7->setSHEETSTYLE(sheetStyle);
        KiCAD7->setNUMOPTLINES(numOptLines);
        KiCAD7->setTITELBLOCKFIELDS(titelblockFieldsKiCAD7);
        KiCAD7->setREVHISTORY(revHistory);
        KiCAD7->setREVHISTORYSTYLE(getRevHistoryStyle());
        KiCAD7->setREVHISTORYFIELDS(revHistoryFieldsKiCAD7);
        KiCAD7->setFOLDLINES(foldLines);
        KiCAD7->setFOLDLINETARGET(foldLinesTaget);
        KiCAD7->setSMALLPARTSLIST(smallPartsList);
        KiCAD7->setSMALLPARTSLISTFIELDS(smallPartsListFiledsKiCAD7);
        KiCAD7->setFULLSHEETPARTSLIST(fullSheetPartsList);
        KiCAD7->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFieldsKiCAD7);
        KiCAD7->setLOGO(logo);
        KiCAD7->setLOGODIR(logoDir);
        KiCAD7->draw();

        KiCAD7->setISO7200OPTIONS(ISO7200OPTIONS);
        KiCAD7->setASME_Y14_35_WIDTH180(ASME_Y14_35_WIDTH180);
        KiCAD7->setFULLSHEETPARTLISTOPIONS(FULLSHEETPARTLISTOPIONS);
        KiCAD7->setSMALLPARTSLISTSOPTIONS(SMALLPARTSLISTSOPTIONS);

        // FreeCAD
        QMap<QString, TitelblockField> titelblockFieldsFreeCAD = ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD();
        QMap<QString, TitelblockField> revHistoryFieldsFreeCAD = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_FREECAD();
        QMap<QString, TitelblockField> smallPartsListFiledsFreeCAD = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_FREECAD();
        QMap<QString, TitelblockField> fullSheetPartsListFieldsFreeCAD = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_FREECAD();

        std::shared_ptr<TemplateGenFreeCAD> FreeCAD(new TemplateGenFreeCAD(this));
        FreeCAD->setDIR(dir);
        FreeCAD->setSHEETSIZE(sheetSize);
        FreeCAD->setSHEETNAME(sheetName);
        FreeCAD->setSHEETSTYLE(sheetStyle);
        FreeCAD->setNUMOPTLINES(numOptLines);
        FreeCAD->setTITELBLOCKFIELDS(titelblockFieldsFreeCAD);
        FreeCAD->setREVHISTORY(revHistory);
        FreeCAD->setREVHISTORYSTYLE(getRevHistoryStyle());
        FreeCAD->setREVHISTORYFIELDS(revHistoryFieldsFreeCAD);
        FreeCAD->setFOLDLINES(foldLines);
        FreeCAD->setFOLDLINETARGET(foldLinesTaget);
        FreeCAD->setSMALLPARTSLIST(smallPartsList);
        FreeCAD->setSMALLPARTSLISTFIELDS(smallPartsListFiledsFreeCAD);
        FreeCAD->setFULLSHEETPARTSLIST(fullSheetPartsList);
        FreeCAD->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFieldsFreeCAD);
        FreeCAD->setLOGO(logo);
        FreeCAD->setLOGODIR(logoDir);
        FreeCAD->draw();

        FreeCAD->setISO7200OPTIONS(ISO7200OPTIONS);
        FreeCAD->setASME_Y14_35_WIDTH180(ASME_Y14_35_WIDTH180);
        FreeCAD->setFULLSHEETPARTLISTOPIONS(FULLSHEETPARTLISTOPIONS);
        FreeCAD->setSMALLPARTSLISTSOPTIONS(SMALLPARTSLISTSOPTIONS);

        // PDF
        QMap<QString, TitelblockField> titelblockFieldsPDF = ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF();
        QMap<QString, TitelblockField> revHistoryFieldsPDF = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_PDF();
        QMap<QString, TitelblockField> smallPartsListFiledsPDF = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_PDF();
        QMap<QString, TitelblockField> fullSheetPartsListFieldsPDF = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_PDF();

        std::shared_ptr<TemplateGenPDF> PDF(new TemplateGenPDF(this));
        PDF->setDIR(dir);
        PDF->setSHEETSIZE(sheetSize);
        PDF->setSHEETNAME(sheetName);
        PDF->setSHEETSTYLE(sheetStyle);
        PDF->setNUMOPTLINES(numOptLines);
        PDF->setTITELBLOCKFIELDS(titelblockFieldsPDF);
        PDF->setREVHISTORY(revHistory);
        PDF->setREVHISTORYSTYLE(getRevHistoryStyle());
        PDF->setREVHISTORYFIELDS(revHistoryFieldsPDF);
        PDF->setFOLDLINES(foldLines);
        PDF->setFOLDLINETARGET(foldLinesTaget);
        PDF->setSMALLPARTSLIST(smallPartsList);
        PDF->setSMALLPARTSLISTFIELDS(smallPartsListFiledsPDF);
        PDF->setFULLSHEETPARTSLIST(fullSheetPartsList);
        PDF->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFieldsPDF);
        PDF->setLOGO(logo);
        PDF->setLOGODIR(logoDir);
        PDF->draw();

        PDF->setISO7200OPTIONS(ISO7200OPTIONS);
        PDF->setASME_Y14_35_WIDTH180(ASME_Y14_35_WIDTH180);
        PDF->setFULLSHEETPARTLISTOPIONS(FULLSHEETPARTLISTOPIONS);
        PDF->setSMALLPARTSLISTSOPTIONS(SMALLPARTSLISTSOPTIONS);

        // Eagle
        // Uses the FreeCAD Setings
        std::shared_ptr<TemplateGenEagle> Eagle(new TemplateGenEagle(this));
        Eagle->setDIR(dir);
        Eagle->setSHEETSIZE(sheetSize);
        Eagle->setSHEETNAME(sheetName);
        Eagle->setSHEETSTYLE(sheetStyle);
        Eagle->setNUMOPTLINES(numOptLines);
        Eagle->setTITELBLOCKFIELDS(titelblockFieldsFreeCAD);
        Eagle->setREVHISTORY(revHistory);
        Eagle->setREVHISTORYSTYLE(getRevHistoryStyle());
        Eagle->setREVHISTORYFIELDS(revHistoryFieldsFreeCAD);
        Eagle->setFOLDLINES(foldLines);
        Eagle->setFOLDLINETARGET(foldLinesTaget);
        Eagle->setSMALLPARTSLIST(smallPartsList);
        Eagle->setSMALLPARTSLISTFIELDS(smallPartsListFiledsFreeCAD);
        Eagle->setFULLSHEETPARTSLIST(fullSheetPartsList);
        Eagle->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFieldsFreeCAD);
        Eagle->setLOGO(logo);
        Eagle->setLOGODIR(logoDir);
        Eagle->draw();

        Eagle->setISO7200OPTIONS(ISO7200OPTIONS);
        Eagle->setASME_Y14_35_WIDTH180(ASME_Y14_35_WIDTH180);
        Eagle->setFULLSHEETPARTLISTOPIONS(FULLSHEETPARTLISTOPIONS);
        Eagle->setSMALLPARTSLISTSOPTIONS(SMALLPARTSLISTSOPTIONS);
    }
}

void MainWindow::on_SheetSizeComboBox_currentTextChanged(const QString &arg1)
{
    SheetSize sheetSize = getSheetSize(arg1);
    ui->sheetHeightDoubleSpinBox->setValue(sheetSize.height);
    ui->sheetWidthDoubleSpinBox->setValue(sheetSize.width);
    ui->NameLineEdit->setText(sheetSize.sizeString);

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
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
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
        qWarning() << "None";
    }
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
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
        qWarning() << "None";
    }
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}

void MainWindow::on_FullPartsListCheckBox_stateChanged(int arg1)
{
    if(arg1)
    {
//        ui->FullPartsListNumLinesPerFieldLabel->setEnabled(true);
//        ui->FullPartsListNumLinesPerFieldSpinBox->setEnabled(true);
//        ui->selectCSVBOMpushButton->setEnabled(true);
//        ui->insertBomCheckBox->setEnabled(true);
//        ui->csvBOMComboBox->setEnabled(true);
        ui->SmallPartsListCheckBox->setEnabled(false);
    }
    else
    {
//        ui->FullPartsListNumLinesPerFieldLabel->setEnabled(false);
//        ui->FullPartsListNumLinesPerFieldSpinBox->setEnabled(false);
//        ui->selectCSVBOMpushButton->setEnabled(false);
//        ui->insertBomCheckBox->setEnabled(false);
//        ui->csvBOMComboBox->setEnabled(false);
        ui->SmallPartsListCheckBox->setEnabled(true);
    }
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}

void MainWindow::on_SmallPartsListCheckBox_stateChanged(int arg1)
{
    if(arg1)
    {
//        ui->SmallPartsListNumLinesPerFieldLabel->setEnabled(true);
//        ui->SmallPartsListNumLinesPerFieldSpinBox->setEnabled(true);
//        ui->SmallPartsListNumPartsLabel->setEnabled(true);
//        ui->SmallPartsListNumPartsSpinBox->setEnabled(true);
        ui->FullPartsListCheckBox->setEnabled(false);
    }
    else
    {
//        ui->SmallPartsListNumLinesPerFieldLabel->setEnabled(false);
//        ui->SmallPartsListNumLinesPerFieldSpinBox->setEnabled(false);
//        ui->SmallPartsListNumPartsLabel->setEnabled(false);
//        ui->SmallPartsListNumPartsSpinBox->setEnabled(false);
        ui->FullPartsListCheckBox->setEnabled(true);
    }
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}

void MainWindow::on_pushButton_clicked()
{
    SMALLPARTSLISTSOPTIONS->setModal(true);
    SMALLPARTSLISTSOPTIONS->exec();
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}

void MainWindow::on_editFullPartsListPushButton_clicked()
{
    FULLSHEETPARTLISTOPIONS->setModal(true);
    FULLSHEETPARTLISTOPIONS->exec();
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}

void MainWindow::on_loadFielsPushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Load File",
                                LASTDIR + "setting.xml",
                                "Xml (*.xml)");
    if(fileName.size() > 0)
    {
        LoadeSaveSettings file(this);
        file.loadSettings(fileName);
        ui->SheetSizeComboBox->setCurrentText(file.getSHEETSIZE().sizeString);
        ISO7200OPTIONS->setTITELBLOCKFIELDS_KICAD5(file.getTITELBLOCKFIELDS_KICAD5());
        ISO7200OPTIONS->setTITELBLOCKFIELDS_KICAD6(file.getTITELBLOCKFIELDS_KICAD6());
        ISO7200OPTIONS->setTITELBLOCKFIELDS_FREECAD(file.getTITELBLOCKFIELDS_FREECAD());
        ISO7200OPTIONS->setTITELBLOCKFIELDS_PDF(file.getTITELBLOCKFIELDS_PDF());
        ui->RevHistoryCheckBox->setChecked(file.getREVHISTORY());
        ui->revHistoryStyleComboBox->setCurrentText(getRevHistoryStyleString(file.getREVHISTORYSTYLE()));
        ASME_Y14_35_WIDTH180->setREVHISTORYFIELDS_KICAD5(file.getREVHISTORYFIELDS_KICAD5());
        ASME_Y14_35_WIDTH180->setREVHISTORYFIELDS_KICAD6(file.getREVHISTORYFIELDS_KICAD6());
        ASME_Y14_35_WIDTH180->setREVHISTORYFIELDS_FREECAD(file.getREVHISTORYFIELDS_FREECAD());
        ASME_Y14_35_WIDTH180->setREVHISTORYFIELDS_PDF(file.getREVHISTORYFIELDS_PDF());
        ui->foldLinesCheckBox->setChecked(file.getFOLDLINES());
        ui->foldingLinesComboBox->setCurrentText(file.getFOLDLINESTARGET().sizeString);
        ui->SmallPartsListCheckBox->setChecked(file.getSMALLPARTSLIST());
        SMALLPARTSLISTSOPTIONS->setSMALLPARTSLISTFIELDS_KICAD5(file.getSMALLPARTSLISTFIELDS_KICAD5());
        SMALLPARTSLISTSOPTIONS->setSMALLPARTSLISTFIELDS_KICAD6(file.getSMALLPARTSLISTFIELDS_KICAD6());
        SMALLPARTSLISTSOPTIONS->setSMALLPARTSLISTFIELDS_FREECAD(file.getSMALLPARTSLISTFIELDS_FREECAD());
        SMALLPARTSLISTSOPTIONS->setSMALLPARTSLISTFIELDS_PDF(file.getSMALLPARTSLISTFIELDS_PDF());
        SMALLPARTSLISTSOPTIONS->setNumLinesPerField(file.getNUMLINESSMALLPARTSLIST());
        SMALLPARTSLISTSOPTIONS->setNumParts(file.getNUMPARTSSMALLPARTSLIST());
        ui->FullPartsListCheckBox->setChecked(file.getFULLSHEETPARTSLIST());
        FULLSHEETPARTLISTOPIONS->setFULLSHEETPARTSLISTFIELDS_KICAD5(file.getFULLSHEETPARTSLISTFIELDS_KICAD5());
        FULLSHEETPARTLISTOPIONS->setFULLSHEETPARTSLISTFIELDS_KICAD6(file.getFULLSHEETPARTSLISTFIELDS_KICAD6());
        FULLSHEETPARTLISTOPIONS->setFULLSHEETPARTSLISTFIELDS_FREECAD(file.getFULLSHEETPARTSLISTFIELDS_FREECAD());
        FULLSHEETPARTLISTOPIONS->setFULLSHEETPARTSLISTFIELDS_PDF(file.getFULLSHEETPARTSLISTFIELDS_PDF());
        FULLSHEETPARTLISTOPIONS->setNumLinesPerField(file.getNUMLINESFULLSHEETPARTSLIST());
        ui->logoCheckBox->setChecked(file.getLOGO());
        LOGODIR = file.getLOGODIR();
    }
}


void MainWindow::on_saveFieldsPushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Load File",
                                LASTDIR + "setting.xml",
                                "Xml (*.xml)");
    if(fileName.size() > 0)
    {
        SheetSize sheetSize = getSheetSize(ui->SheetSizeComboBox->currentText());
        QString sheetName = ui->NameLineEdit->text();
        SheetStyle sheetStyle = getSheetStyle();
        QMap<QString, TitelblockField> titelblockFields_KICAD5 = ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5();
        QMap<QString, TitelblockField> titelblockFields_KICAD6 = ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6();
        QMap<QString, TitelblockField> titelblockFields_FREECAD = ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD();
        QMap<QString, TitelblockField> titelblockFields_PDF = ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF();
        qint64 numOptLines = ISO7200OPTIONS->getNumOptLins();// ui->OptLinesSpinBox->value();
        qint64 numRevHistory = ASME_Y14_35_WIDTH180->getNumRev();
        QMap<QString, TitelblockField> revHistoryFields_KICAD5 = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_KICAD5();
        QMap<QString, TitelblockField> revHistoryFields_KICAD6 = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_KICAD6();
        QMap<QString, TitelblockField> revHistoryFields_FREECAD = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_FREECAD();
        QMap<QString, TitelblockField> revHistoryFields_PDF = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_PDF();
        bool trimmingMarks = ISO7200OPTIONS->getTrimmingMarks();//ui->trimmingMarksCheckBox->isChecked();
        bool revHistory = ui->RevHistoryCheckBox->isChecked();
        bool foldLines = ui->foldLinesCheckBox->isChecked();
        SheetSize foldLinesTaget = getFoldLinesTarget(ui->foldingLinesComboBox->currentText());
        bool smallPartsList = ui->SmallPartsListCheckBox->isChecked();
        quint64 numLinesSmallPartsList = SMALLPARTSLISTSOPTIONS->getNumLinesPerField();
        quint64 numPartsSmallPartsList = SMALLPARTSLISTSOPTIONS->getNumParts();
        QMap<QString, TitelblockField> smallPartsListFileds_KICAD5 = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_KICAD5();
        QMap<QString, TitelblockField> smallPartsListFileds_KICAD6 = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_KICAD6();
        QMap<QString, TitelblockField> smallPartsListFileds_FREECAD = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_FREECAD();
        QMap<QString, TitelblockField> smallPartsListFileds_PDF = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_PDF();
        bool fullSheetPartsList = ui->FullPartsListCheckBox->isChecked();
        quint64 numLinesFullSheetPartsList = FULLSHEETPARTLISTOPIONS->getNumLinesPerField();
        QMap<QString, TitelblockField> fullSheetPartsListFields_KICAD5 = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_KICAD5();
        QMap<QString, TitelblockField> fullSheetPartsListFields_KICAD6 = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_KICAD6();
        QMap<QString, TitelblockField> fullSheetPartsListFields_FREECAD = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_FREECAD();
        QMap<QString, TitelblockField> fullSheetPartsListFields_PDF = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_PDF();
        bool logo = ui->logoCheckBox->isChecked();
        QString logoDir = LOGODIR;

        LoadeSaveSettings file(this);
        file.setSHEETSIZE(sheetSize);
        file.setSHEETNAME(sheetName);
        file.setSHEETSTYLE(sheetStyle);
        file.setNUMOPTLINES(numOptLines);
        file.setTITELBLOCKFIELDS_KICAD5(titelblockFields_KICAD5);
        file.setTITELBLOCKFIELDS_KICAD6(titelblockFields_KICAD6);
        file.setTITELBLOCKFIELDS_FREECAD(titelblockFields_FREECAD);
        file.setTITELBLOCKFIELDS_PDF(titelblockFields_PDF);
        file.setTRIMMINGMARKS(trimmingMarks);
        file.setREVHISTORY(revHistory);
        file.setREVHISTORYSTYLE(getRevHistoryStyle());
        file.setNUMREVHISTORY(numRevHistory);
        file.setREVHISTORYFIELDS_KICAD5(revHistoryFields_KICAD5);
        file.setREVHISTORYFIELDS_KICAD6(revHistoryFields_KICAD6);
        file.setREVHISTORYFIELDS_FREECAD(revHistoryFields_FREECAD);
        file.setREVHISTORYFIELDS_PDF(revHistoryFields_PDF);
        file.setFOLDLINES(foldLines);
        file.setFOLDLINESTARGET(foldLinesTaget);
        file.setSMALLPARTSLIST(smallPartsList);
        file.setNUMLINESSMALLPARTSLIST(numLinesSmallPartsList);
        file.setNUMPARTSSMALLPARTSLIST(numPartsSmallPartsList);
        file.setSMALLPARTSLISTFIELDS_KICAD5(smallPartsListFileds_KICAD5);
        file.setSMALLPARTSLISTFIELDS_KICAD6(smallPartsListFileds_KICAD6);
        file.setSMALLPARTSLISTFIELDS_FREECAD(smallPartsListFileds_FREECAD);
        file.setSMALLPARTSLISTFIELDS_PDF(smallPartsListFileds_PDF);
        file.setFULLSHEETPARTSLIST(fullSheetPartsList);
        file.setNUMLINESFULLSHEETPARTSLIST(numLinesFullSheetPartsList);
        file.setFULLSHEETPARTSLISTFIELDS_KICAD5(fullSheetPartsListFields_KICAD5);
        file.setFULLSHEETPARTSLISTFIELDS_KICAD6(fullSheetPartsListFields_KICAD6);
        file.setFULLSHEETPARTSLISTFIELDS_FREECAD(fullSheetPartsListFields_FREECAD);
        file.setFULLSHEETPARTSLISTFIELDS_PDF(fullSheetPartsListFields_PDF);
        file.setLOGO(logo);
        file.setLOGODIR(logoDir);
        file.saveSettings(fileName);
    }
}

void MainWindow::on_logoPushButton_clicked()
{
    ui->logoCheckBox->setChecked(true);
    QString dir = QFileDialog::getOpenFileName(this, "Open File",
                                               "/home",
                                               "Logos (*.svg);;All files (*.*)");
    if(dir.size() > 0)
    {
        LOGODIR = dir;
    }
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}



void MainWindow::on_pushButton_2_clicked()
{
    KiCAD_Symbol_Scaler_UI scaler_ui;
    scaler_ui.setModal(true);
    scaler_ui.exec();
}


void MainWindow::on_previewPushButton_clicked()
{
    SheetSize sheetSize = getSheetSize(ui->SheetSizeComboBox->currentText());
    QString sheetName = ui->NameLineEdit->text();
    SheetStyle sheetStyle = getSheetStyle();
    QMap<QString, TitelblockField> titelblockFields = ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF();
    QMap<QString, TitelblockField> revHistoryFields = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_PDF();
    bool revHistory = ui->RevHistoryCheckBox->isChecked();
    bool foldLines = ui->foldLinesCheckBox->isChecked();
    SheetSize foldLinesTaget = getFoldLinesTarget(ui->foldingLinesComboBox->currentText());
    bool smallPartsList = ui->SmallPartsListCheckBox->isChecked();
    QMap<QString, TitelblockField> smallPartsListFileds = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_PDF();
    bool fullSheetPartsList = ui->FullPartsListCheckBox->isChecked();
    QMap<QString, TitelblockField> fullSheetPartsListFields = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_PDF();
    bool logo = ui->logoCheckBox->isChecked();
    QString logoDir = LOGODIR;

    PREVIEW->setDIR(QDir::currentPath() + "/tmp");

    PREVIEW->setSHEETSIZE(sheetSize);
    PREVIEW->setSHEETNAME(sheetName);
    PREVIEW->setSHEETSTYLE(sheetStyle);

    PREVIEW->setTITELBLOCKFIELDS(titelblockFields);
    PREVIEW->setREVHISTORY(revHistory);
    PREVIEW->setREVHISTORYFIELDS(revHistoryFields);
    PREVIEW->setFOLDLINES(foldLines);
    PREVIEW->setFOLDLINETARGET(foldLinesTaget);
    PREVIEW->setSMALLPARTSLIST(smallPartsList);
    PREVIEW->setFULLSHEETPARTSLIST(fullSheetPartsList);
    PREVIEW->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFields);
    PREVIEW->setLOGO(logo);
    PREVIEW->setLOGODIR(logoDir);
    PREVIEW->setMinimumWidth(ui->centralwidget->size().width() - 600);
    PREVIEW->update();

    PREVIEW->setISO7200OPTIONS(ISO7200OPTIONS);
    PREVIEW->setASME_Y14_35_WIDTH180(ASME_Y14_35_WIDTH180);
    PREVIEW->setFULLSHEETPARTLISTOPIONS(FULLSHEETPARTLISTOPIONS);
    PREVIEW->setSMALLPARTSLISTSOPTIONS(SMALLPARTSLISTSOPTIONS);
}


void MainWindow::on_sheetWidthDoubleSpinBox_valueChanged(double arg1)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_sheetHeightDoubleSpinBox_valueChanged(double arg1)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_NameLineEdit_textEdited(const QString &arg1)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_SheetStyleComboBox_currentIndexChanged(int index)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_trimmingMarksCheckBox_stateChanged(int arg1)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_OptLinesSpinBox_valueChanged(int arg1)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_DescriptionCheckBox_stateChanged(int arg1)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_DescriptionSpinBox_valueChanged(int arg1)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_RevHistoryCheckBox_stateChanged(int arg1)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_numRevSpinBox_valueChanged(int arg1)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_revHistoryStyleComboBox_currentIndexChanged(int index)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_foldLinesCheckBox_stateChanged(int arg1)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_foldingLinesComboBox_currentIndexChanged(int index)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_FullPartsListNumLinesPerFieldSpinBox_valueChanged(int arg1)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_insertBomCheckBox_stateChanged(int arg1)
{
//    if(WINDOWRUNNING)
//    {
//        on_previewPushButton_clicked();
//    }
}


void MainWindow::on_csvBOMComboBox_currentIndexChanged(int index)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_SmallPartsListNumLinesPerFieldSpinBox_valueChanged(int arg1)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_SmallPartsListNumPartsSpinBox_valueChanged(int arg1)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}

