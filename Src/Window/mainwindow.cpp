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

void MainWindow::initSheetTitleblocks()
{
    ui->SheetTitleblockComboBox->addItem("ISO7200"); // SheetTitleblock::ISO7200
    ui->SheetTitleblockComboBox->addItem("Blank"); // SheetTitleblock::BLANK
}

void MainWindow::initSheetFrames()
{
    ui->SheetFrameComboBox->addItem("ISO5457"); // SheetStyle::ISO5457_ISO7200
    ui->SheetFrameComboBox->addItem("Blank"); // SheetStyle::BLANK
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

SheetTitleblock MainWindow::getSheetTitleblock()
{
    if(ui->SheetTitleblockComboBox->currentText() == "ISO7200")
    {
        return SheetTitleblock::ISO7200;
    }else if(ui->SheetTitleblockComboBox->currentText() == "Blank")
    {
        return SheetTitleblock::BLANK;
    }

    return SheetTitleblock::ISO7200;
}

SheetFrame MainWindow::getSheetFrame()
{
    if(ui->SheetFrameComboBox->currentText() == "ISO5457")
    {
        return SheetFrame::ISO5457;
    }else if(ui->SheetFrameComboBox->currentText() == "Blank")
    {
        return SheetFrame::BLANK;
    }

    return SheetFrame::ISO5457;
}

SheetSize MainWindow::getSheetSize(QString sizeString, double width, double height)
{
    SheetSize tmp;
    if(sizeString == "User defined")
    {
        tmp.sizeString = ui->NameLineEdit->text();
        tmp.height = ui->sheetHeightDoubleSpinBox->value();
        tmp.width = ui->sheetWidthDoubleSpinBox->value();
    }
    else
    {
        tmp.sizeString = "User defined";
        tmp.height = height;
        tmp.width = width;
        foreach(SheetSize sheet, SHEETSIZES)
        {
            if(sheet.sizeString == sizeString)
            {
                sheet.sizeString = sheet.sizeString;
                tmp = sheet;
            }
        }
    }
    if(ui->portraitCheckBox->isChecked()){
        SheetSize tmpA = tmp;
        tmp.width = tmpA.height;
        tmp.height = tmpA.width;
    }
    return tmp;
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
    PREVIEW->setMinimumWidth(ui->centralwidget->size().width() - 800);
    QWidget::resizeEvent(event);
}

bool MainWindow::drawTemplate(QString dir, std::shared_ptr<TemplateGen> templatPtr, QMap<QString, TitelblockField> titelblockFields, QMap<QString, TitelblockField> revHistoryFields, QMap<QString, TitelblockField> smallPartsListFileds, QMap<QString, TitelblockField> fullSheetPartsListFields)
{
    SheetSize sheetSize = getSheetSize(ui->SheetSizeComboBox->currentText());
    QString sheetName = ui->NameLineEdit->text();;
    SheetTitleblock sheetTitleblock= getSheetTitleblock();
    SheetFrame sheetFrame = getSheetFrame();
    qint64 numOptLines = ISO7200OPTIONS->getNumOptLins();// ui->OptLinesSpinBox->value();
    bool revHistory = ui->RevHistoryCheckBox->isChecked();
    bool foldLines = ui->foldLinesCheckBox->isChecked();
    SheetSize foldLinesTaget = getFoldLinesTarget(ui->foldingLinesComboBox->currentText());
    bool smallPartsList = ui->SmallPartsListCheckBox->isChecked();
    bool fullSheetPartsList = ui->FullPartsListCheckBox->isChecked();
    bool logo = ui->logoCheckBox->isChecked();
    QString logoDir = LOGODIR;

    templatPtr->setDIR(dir);
    templatPtr->setSHEETSIZE(sheetSize);
    templatPtr->setSHEETNAME(sheetName);
    templatPtr->setSHEETTITLEBLOCK(sheetTitleblock);
    templatPtr->setSHEETFRAME(sheetFrame);
    templatPtr->setNUMOPTLINES(numOptLines);
    templatPtr->setTITELBLOCKFIELDS(titelblockFields);
    templatPtr->setREVHISTORY(revHistory);
    templatPtr->setREVHISTORYSTYLE(getRevHistoryStyle());
    templatPtr->setREVHISTORYFIELDS(revHistoryFields);
    templatPtr->setFOLDLINES(foldLines);
    templatPtr->setFOLDLINETARGET(foldLinesTaget);
    templatPtr->setSMALLPARTSLIST(smallPartsList);
    templatPtr->setSMALLPARTSLISTFIELDS(smallPartsListFileds);
    templatPtr->setFULLSHEETPARTSLIST(fullSheetPartsList);
    templatPtr->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFields);
    templatPtr->setLOGO(logo);
    templatPtr->setLOGODIR(logoDir);

    templatPtr->setISO7200OPTIONS(ISO7200OPTIONS);
    templatPtr->setISO5457OPTIONS(ISO5457OPTIONS);
    templatPtr->setASME_Y14_35_WIDTH180OPTIONS(ASME_Y14_35_WIDTH180OPTIONS);
    templatPtr->setFULLSHEETPARTLISTOPIONS(FULLSHEETPARTLISTOPIONS);
    templatPtr->setSMALLPARTSLISTSOPTIONS(SMALLPARTSLISTSOPTIONS);
    templatPtr->draw();
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("./lib/icon.png"));
    initSheetSizes();
    initSheetTitleblocks();
    initSheetFrames();
    initRevHistoryStyles();
    initFoldLinesTarget();
//    initBOMStyles();

    PREVIEW = std::shared_ptr<Preview>(new Preview());
    PREVIEW->setMinimumWidth(900);
    PREVIEW->setStyleSheet("background-color: rgb(255,255,255)");

    QDir dir;
    dir.mkdir(QDir::currentPath() + "/tmp");

    // Preview
    SheetSize sheetSize = getSheetSize(ui->SheetSizeComboBox->currentText());
    QString sheetName = ui->NameLineEdit->text();
    SheetTitleblock sheetTitleblock = getSheetTitleblock();
    SheetFrame sheetFrame = getSheetFrame();
    QMap<QString, TitelblockField> titelblockFields = ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF();
    qint64 numOptLines = ISO7200OPTIONS->getNumOptLins();// ui->OptLinesSpinBox->value();
    QMap<QString, TitelblockField> revHistoryFields = ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_PDF();
    bool revHistory = ui->RevHistoryCheckBox->isChecked();
    bool foldLines = ui->foldLinesCheckBox->isChecked();
    SheetSize foldLinesTaget = getFoldLinesTarget(ui->foldingLinesComboBox->currentText());
    bool smallPartsList = ui->SmallPartsListCheckBox->isChecked();
    QMap<QString, TitelblockField> smallPartsListFileds = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_PDF();
    bool fullSheetPartsList = ui->FullPartsListCheckBox->isChecked();
    QMap<QString, TitelblockField> fullSheetPartsListFields = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_PDF();
    bool logo = ui->logoCheckBox->isChecked();
    QString logoDir = LOGODIR;

    //TemplateGenKiCAD_5 KiCAD5(this);
    PREVIEW->setDIR(QDir::currentPath() + "/tmp");
    PREVIEW->setSHEETSIZE(sheetSize);
    PREVIEW->setSHEETNAME(sheetName);
    PREVIEW->setSHEETTITLEBLOCK(sheetTitleblock);
    PREVIEW->setSHEETFRAME(sheetFrame);
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
    PREVIEW->setISO5457OPTIONS(ISO5457OPTIONS);
    PREVIEW->setASME_Y14_35_WIDTH180OPTIONS(ASME_Y14_35_WIDTH180OPTIONS);
    PREVIEW->setFULLSHEETPARTLISTOPIONS(FULLSHEETPARTLISTOPIONS);
    PREVIEW->setSMALLPARTSLISTSOPTIONS(SMALLPARTSLISTSOPTIONS);

    PREVIEW->setSheetBorder(ui->preViewSheetBordercheckBox->isChecked());


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
        qDebug() << "KiCAD5";
        // KiCAD 5
        SheetSize sheetSize = getSheetSize(ui->SheetSizeComboBox->currentText());
        QString sheetName = ui->NameLineEdit->text();;
        SheetTitleblock sheetTitleblock= getSheetTitleblock();
        SheetFrame sheetFrame = getSheetFrame();
        QMap<QString, TitelblockField> titelblockFieldsKiCAD5 = ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5();
        qint64 numOptLines = ISO7200OPTIONS->getNumOptLins();// ui->OptLinesSpinBox->value();
        QMap<QString, TitelblockField> revHistoryFieldsKiCAD5 = ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_KICAD5();
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

        drawTemplate(dir, KiCAD5, titelblockFieldsKiCAD5, revHistoryFieldsKiCAD5, smallPartsListFiledsKiCAD5, fullSheetPartsListFieldsKiCAD5);

        qDebug() << "KiCAD6";
        // KiCAD 6
        QMap<QString, TitelblockField> titelblockFieldsKiCAD6 = ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6();
        QMap<QString, TitelblockField> revHistoryFieldsKiCAD6 = ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_KICAD6();
        QMap<QString, TitelblockField> smallPartsListFiledsKiCAD6 = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_KICAD6();
        QMap<QString, TitelblockField> fullSheetPartsListFieldsKiCAD6 = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_KICAD6();


        std::shared_ptr<TemplateGenKiCAD_6> KiCAD6(new TemplateGenKiCAD_6(this));

        drawTemplate(dir, KiCAD6, titelblockFieldsKiCAD6, revHistoryFieldsKiCAD6, smallPartsListFiledsKiCAD6, fullSheetPartsListFieldsKiCAD6);

        qDebug() << "KiCAD7";
        // KiCAD 7
        QMap<QString, TitelblockField> titelblockFieldsKiCAD7 = ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6();
        QMap<QString, TitelblockField> revHistoryFieldsKiCAD7 = ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_KICAD6();
        QMap<QString, TitelblockField> smallPartsListFiledsKiCAD7 = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_KICAD6();
        QMap<QString, TitelblockField> fullSheetPartsListFieldsKiCAD7 = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_KICAD6();

        std::shared_ptr<TemplateGenKiCAD_7> KiCAD7(new TemplateGenKiCAD_7(this));

        drawTemplate(dir, KiCAD7, titelblockFieldsKiCAD7, revHistoryFieldsKiCAD7, smallPartsListFiledsKiCAD7, fullSheetPartsListFieldsKiCAD7);

        qDebug() << "FreeCAD";
        // FreeCAD
        QMap<QString, TitelblockField> titelblockFieldsFreeCAD = ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD();
        QMap<QString, TitelblockField> revHistoryFieldsFreeCAD = ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_FREECAD();
        QMap<QString, TitelblockField> smallPartsListFiledsFreeCAD = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_FREECAD();
        QMap<QString, TitelblockField> fullSheetPartsListFieldsFreeCAD = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_FREECAD();

        std::shared_ptr<TemplateGenFreeCAD> FreeCAD(new TemplateGenFreeCAD(this));

        drawTemplate(dir, FreeCAD, titelblockFieldsFreeCAD, revHistoryFieldsFreeCAD, smallPartsListFiledsFreeCAD, fullSheetPartsListFieldsFreeCAD);

        qDebug() << "PDF";
        // PDF
        QMap<QString, TitelblockField> titelblockFieldsPDF = ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF();
        QMap<QString, TitelblockField> revHistoryFieldsPDF = ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_PDF();
        QMap<QString, TitelblockField> smallPartsListFiledsPDF = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_PDF();
        QMap<QString, TitelblockField> fullSheetPartsListFieldsPDF = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_PDF();

        std::shared_ptr<TemplateGenPDF> PDF(new TemplateGenPDF(this));

        drawTemplate(dir, PDF, titelblockFieldsPDF, revHistoryFieldsPDF, smallPartsListFiledsPDF, fullSheetPartsListFieldsPDF);

        qDebug() << "SVG";
        // SVG(uses PDF Options)

        std::shared_ptr<TemplateGenSVG> SVG(new TemplateGenSVG(this));

        drawTemplate(dir, SVG, titelblockFieldsPDF, revHistoryFieldsPDF, smallPartsListFiledsPDF, fullSheetPartsListFieldsPDF);

        qDebug() << "Eagle";
        // Eagle
        // Uses the FreeCAD Setings
        std::shared_ptr<TemplateGenEagle> Eagle(new TemplateGenEagle(this));

        drawTemplate(dir, Eagle, titelblockFieldsFreeCAD, revHistoryFieldsFreeCAD, smallPartsListFiledsFreeCAD, fullSheetPartsListFieldsFreeCAD);
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
    if(ui->SheetTitleblockComboBox->currentText() == "ISO7200")
    {
        std::unique_ptr<ISO7200Dialog> ISO7200DIALOG(new ISO7200Dialog(ISO7200OPTIONS, this));
        ISO7200DIALOG->setModal(true);
        ISO7200DIALOG->exec();
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
        std::unique_ptr<ASME_Y14_35_Width180Dialog> ASME_Y14_35_WIDTH180DIALOG(new ASME_Y14_35_Width180Dialog(ASME_Y14_35_WIDTH180OPTIONS, this));
        ASME_Y14_35_WIDTH180DIALOG->setModal(true);
        ASME_Y14_35_WIDTH180DIALOG->exec();
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
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELDS_KICAD5(file.getREVHISTORYFIELDS_KICAD5());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELDS_KICAD6(file.getREVHISTORYFIELDS_KICAD6());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELDS_FREECAD(file.getREVHISTORYFIELDS_FREECAD());
        ASME_Y14_35_WIDTH180OPTIONS->setREVHISTORYFIELDS_PDF(file.getREVHISTORYFIELDS_PDF());
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
        //SheetStyle sheetStyle = getSheetStyle();
        QMap<QString, TitelblockField> titelblockFields_KICAD5 = ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5();
        QMap<QString, TitelblockField> titelblockFields_KICAD6 = ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6();
        QMap<QString, TitelblockField> titelblockFields_FREECAD = ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD();
        QMap<QString, TitelblockField> titelblockFields_PDF = ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF();
        qint64 numOptLines = ISO7200OPTIONS->getNumOptLins();// ui->OptLinesSpinBox->value();
        qint64 numRevHistory = ASME_Y14_35_WIDTH180OPTIONS->getNumRev();
        QMap<QString, TitelblockField> revHistoryFields_KICAD5 = ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_KICAD5();
        QMap<QString, TitelblockField> revHistoryFields_KICAD6 = ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_KICAD6();
        QMap<QString, TitelblockField> revHistoryFields_FREECAD = ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_FREECAD();
        QMap<QString, TitelblockField> revHistoryFields_PDF = ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_PDF();
        bool trimmingMarks = ISO5457OPTIONS->getTrimmingMarks();//ui->trimmingMarksCheckBox->isChecked();
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
        //file.setSHEETSTYLE(sheetStyle);
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
    QMap<QString, TitelblockField> titelblockFields = ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF();
    QMap<QString, TitelblockField> revHistoryFields = ASME_Y14_35_WIDTH180OPTIONS->getREVHISTORYFIELDS_PDF();
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
    PREVIEW->setSHEETTITLEBLOCK(getSheetTitleblock());
    PREVIEW->setSHEETFRAME(getSheetFrame());

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

    PREVIEW->setISO7200OPTIONS(ISO7200OPTIONS);
    PREVIEW->setISO5457OPTIONS(ISO5457OPTIONS);
    PREVIEW->setASME_Y14_35_WIDTH180OPTIONS(ASME_Y14_35_WIDTH180OPTIONS);
    PREVIEW->setFULLSHEETPARTLISTOPIONS(FULLSHEETPARTLISTOPIONS);
    PREVIEW->setSMALLPARTSLISTSOPTIONS(SMALLPARTSLISTSOPTIONS);

    PREVIEW->setSheetBorder(ui->preViewSheetBordercheckBox->isChecked());

    PREVIEW->update();
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


void MainWindow::on_RevHistoryCheckBox_stateChanged(int arg1)
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


void MainWindow::on_spaceComboBox_currentIndexChanged(int index)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_portraitCheckBox_stateChanged(int arg1)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_preViewSheetBordercheckBox_stateChanged(int arg1)
{
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_sheetFramePushButton_clicked()
{
    if(ui->SheetFrameComboBox->currentText() == "ISO5457")
    {
        std::unique_ptr<ISO5457Dialog> ISO5457DIALOG(new ISO5457Dialog(ISO5457OPTIONS, this));
        ISO5457DIALOG->setModal(true);
        ISO5457DIALOG->exec();
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

