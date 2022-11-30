#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "loadesavesettings.h"

#include "kicad_symbol_scaler_ui.h"

void MainWindow::initPageSizes()
{
    foreach(PageSize sheet, PAGESIZES)
    {
        ui->SheetSizeComboBox->addItem(sheet.sizeString);
    }
    ui->sheetWidthDoubleSpinBox->setValue(PAGESIZES[0].width);
    ui->sheetHeightDoubleSpinBox->setValue(PAGESIZES[0].height);
}

void MainWindow::initPageStyles()
{
    ui->SheetStyleComboBox->addItem("ISO5457 ISO7200"); // PageStyle::ISO5457_ISO7200
    ui->SheetStyleComboBox->addItem("Blank"); // PageStyle::BLANK
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

void MainWindow::initBOMStyles()
{
    ui->csvBOMComboBox->addItem("KiCAD bom_csv_grouped_by_value_with_fp");
    ui->csvBOMComboBox->addItem("Standart as in CSV");
    ui->csvBOMComboBox->setCurrentText("Standart as in CSV");
}

PageStyle MainWindow::getPageStyle()
{
    if(ui->SheetStyleComboBox->currentText() == "ISO5457 ISO7200")
    {
        return PageStyle::ISO5457_ISO7200;
    }else if(ui->SheetStyleComboBox->currentText() == "Blank")
    {
        return PageStyle::BLANK;
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

BOMStyles MainWindow::getBOMStyle()
{
    if(ui->csvBOMComboBox->currentText() == "KiCAD bom_csv_grouped_by_value_with_fp")
    {
        return BOMStyles::KiCAD;
    }else if(ui->csvBOMComboBox->currentText() == "Standart as in CSV")
    {
        return BOMStyles::Standard;
    }
    return BOMStyles::Standard;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    PREVIEW->setMinimumWidth(ui->centralwidget->size().width() - 600);
    QWidget::resizeEvent(event);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initPageSizes();
    initPageStyles();
    initRevHistoryStyles();
    initFoldLinesTarget();
    initBOMStyles();

    PREVIEW = std::shared_ptr<Preview>(new Preview());
    PREVIEW->setMinimumWidth(900);
    PREVIEW->setStyleSheet("background-color: rgb(255,255,255)");

    // Preview
    PageSize sheetSize = getPageSize(ui->SheetSizeComboBox->currentText());
    QString sheetName = ui->NameLineEdit->text();
    PageStyle sheetStyle = getPageStyle();
    QMap<QString, TitelblockField> titelblockFields = ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF();
    qint64 numOptLines = ui->OptLinesSpinBox->value();
    qint64 numRevHistory = ui->numRevSpinBox->value();
    QMap<QString, TitelblockField> revHistoryFields = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_PDF();
    bool trimmingMarks = ui->trimmingMarksCheckBox->isChecked();
    bool revHistory = ui->RevHistoryCheckBox->isChecked();
    bool foldLines = ui->foldLinesCheckBox->isChecked();
    PageSize foldLinesTaget = getFoldLinesTarget(ui->foldingLinesComboBox->currentText());
    bool smallPartsList = ui->SmallPartsListCheckBox->isChecked();
    quint64 numLinesSmallPartsList = ui->SmallPartsListNumLinesPerFieldSpinBox->value();
    quint64 numPartsSmallPartsList = ui->SmallPartsListNumPartsSpinBox->value();
    QMap<QString, TitelblockField> smallPartsListFileds = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_PDF();
    bool fullSheetPartsList = ui->FullPartsListCheckBox->isChecked();
    quint64 numLinesFullSheetPartsList = ui->FullPartsListNumLinesPerFieldSpinBox->value();
    bool fullSheetPartsListCSV = ui->insertBomCheckBox->isChecked();
    QMap<QString, TitelblockField> fullSheetPartsListFields = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_PDF();
    bool logo = ui->logoCheckBox->isChecked();
    QString logoDir = LOGODIR;
    bool description = ui->DescriptionCheckBox->isChecked();
    quint64 descriptionNumLines = ui->DescriptionSpinBox->value();

    QDir dir;
    dir.mkdir(QDir::currentPath() + "/tmp");
    //TemplateGenKiCAD_5 KiCAD5(this);
    PREVIEW->setDIR(QDir::currentPath() + "/tmp");
    PREVIEW->setPAGESIZE(sheetSize);
    PREVIEW->setSHEETNAME(sheetName);
    PREVIEW->setPAGESTYLE(sheetStyle);
    PREVIEW->setNUMOPTLINES(numOptLines);
    PREVIEW->setTITELBLOCKFIELDS(titelblockFields);
    PREVIEW->setTRIMMINGMARKS(trimmingMarks);
    PREVIEW->setREVHISTORY(revHistory);
    PREVIEW->setREVHISTORYSTYLE(getRevHistoryStyle());
    PREVIEW->setNUMREVHISTORY(numRevHistory);
    PREVIEW->setREVHISTORYFIELDS(revHistoryFields);
    PREVIEW->setFOLDLINES(foldLines);
    PREVIEW->setFOLDLINETARGET(foldLinesTaget);
    PREVIEW->setSMALLPARTSLIST(smallPartsList);
    PREVIEW->setNUMLINESMALLPARTSLIST(numLinesSmallPartsList);
    PREVIEW->setNUMPARTSSMALLPARTSLIST(numPartsSmallPartsList);
    PREVIEW->setSMALLPARTSLISTFIELDS(smallPartsListFileds);
    PREVIEW->setFULLSHEETPARTSLIST(fullSheetPartsList);
    PREVIEW->setFULLSHEETPARTSLISTCSV(fullSheetPartsListCSV);
    PREVIEW->setFULLSHEETPARTLISTCSVSTYLE(getBOMStyle());
    PREVIEW->setFULLSHEETPARTSLISTCSVFILE(BOMDIR);
    PREVIEW->setNUMLINESFULLSHEETPARTSLIST(numLinesFullSheetPartsList);
    PREVIEW->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFields);
    PREVIEW->setLOGO(logo);
    PREVIEW->setLOGODIR(logoDir);
    PREVIEW->setDESCRIPTION(description);
    PREVIEW->setDESCRIPTIONNUMLINES(descriptionNumLines);

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
        PageSize sheetSize = getPageSize(ui->SheetSizeComboBox->currentText());
        QString sheetName = ui->NameLineEdit->text();
        PageStyle sheetStyle = getPageStyle();
        QMap<QString, TitelblockField> titelblockFieldsKiCAD5 = ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5();
        qint64 numOptLines = ui->OptLinesSpinBox->value();
        qint64 numRevHistory = ui->numRevSpinBox->value();
        QMap<QString, TitelblockField> revHistoryFieldsKiCAD5 = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_KICAD5();
        bool trimmingMarks = ui->trimmingMarksCheckBox->isChecked();
        bool revHistory = ui->RevHistoryCheckBox->isChecked();
        bool foldLines = ui->foldLinesCheckBox->isChecked();
        PageSize foldLinesTaget = getFoldLinesTarget(ui->foldingLinesComboBox->currentText());
        bool smallPartsList = ui->SmallPartsListCheckBox->isChecked();
        quint64 numLinesSmallPartsList = ui->SmallPartsListNumLinesPerFieldSpinBox->value();
        quint64 numPartsSmallPartsList = ui->SmallPartsListNumPartsSpinBox->value();
        QMap<QString, TitelblockField> smallPartsListFiledsKiCAD5 = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_KICAD5();
        bool fullSheetPartsList = ui->FullPartsListCheckBox->isChecked();
        quint64 numLinesFullSheetPartsList = ui->FullPartsListNumLinesPerFieldSpinBox->value();
        bool fullSheetPartsListCSV = ui->insertBomCheckBox->isChecked();
        QMap<QString, TitelblockField> fullSheetPartsListFieldsKiCAD5 = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_KICAD5();
        bool logo = ui->logoCheckBox->isChecked();
        QString logoDir = LOGODIR;
        bool description = ui->DescriptionCheckBox->isChecked();
        quint64 descriptionNumLines = ui->DescriptionSpinBox->value();

        std::unique_ptr<TemplateGenKiCAD_5> KiCAD5(new TemplateGenKiCAD_5 (this));
        KiCAD5->setDIR(dir);
        KiCAD5->setPAGESIZE(sheetSize);
        KiCAD5->setSHEETNAME(sheetName);
        KiCAD5->setPAGESTYLE(sheetStyle);
        KiCAD5->setNUMOPTLINES(numOptLines);
        KiCAD5->setTITELBLOCKFIELDS(titelblockFieldsKiCAD5);
        KiCAD5->setTRIMMINGMARKS(trimmingMarks);
        KiCAD5->setREVHISTORY(revHistory);
        KiCAD5->setREVHISTORYSTYLE(getRevHistoryStyle());
        KiCAD5->setNUMREVHISTORY(numRevHistory);
        KiCAD5->setREVHISTORYFIELDS(revHistoryFieldsKiCAD5);
        KiCAD5->setFOLDLINES(foldLines);
        KiCAD5->setFOLDLINETARGET(foldLinesTaget);
        KiCAD5->setSMALLPARTSLIST(smallPartsList);
        KiCAD5->setNUMLINESMALLPARTSLIST(numLinesSmallPartsList);
        KiCAD5->setNUMPARTSSMALLPARTSLIST(numPartsSmallPartsList);
        KiCAD5->setSMALLPARTSLISTFIELDS(smallPartsListFiledsKiCAD5);
        KiCAD5->setFULLSHEETPARTSLIST(fullSheetPartsList);
        KiCAD5->setFULLSHEETPARTSLISTCSV(fullSheetPartsListCSV);
        KiCAD5->setFULLSHEETPARTLISTCSVSTYLE(getBOMStyle());
        KiCAD5->setFULLSHEETPARTSLISTCSVFILE(BOMDIR);
        KiCAD5->setNUMLINESFULLSHEETPARTSLIST(numLinesFullSheetPartsList);
        KiCAD5->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFieldsKiCAD5);
        KiCAD5->setLOGO(logo);
        KiCAD5->setLOGODIR(logoDir);
        KiCAD5->setDESCRIPTION(description);
        KiCAD5->setDESCRIPTIONNUMLINES(descriptionNumLines);
        KiCAD5->draw();

        // KiCAD 6
        QMap<QString, TitelblockField> titelblockFieldsKiCAD6 = ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6();
        QMap<QString, TitelblockField> revHistoryFieldsKiCAD6 = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_KICAD6();
        QMap<QString, TitelblockField> smallPartsListFiledsKiCAD6 = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_KICAD6();
        QMap<QString, TitelblockField> fullSheetPartsListFieldsKiCAD6 = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_KICAD6();


        std::unique_ptr<TemplateGenKiCAD_6> KiCAD6(new TemplateGenKiCAD_6(this));
        KiCAD6->setDIR(dir);
        KiCAD6->setPAGESIZE(sheetSize);
        KiCAD6->setSHEETNAME(sheetName);
        KiCAD6->setPAGESTYLE(sheetStyle);
        KiCAD6->setNUMOPTLINES(numOptLines);
        KiCAD6->setTITELBLOCKFIELDS(titelblockFieldsKiCAD6);
        KiCAD6->setTRIMMINGMARKS(trimmingMarks);
        KiCAD6->setREVHISTORY(revHistory);
        KiCAD6->setREVHISTORYSTYLE(getRevHistoryStyle());
        KiCAD6->setNUMREVHISTORY(numRevHistory);
        KiCAD6->setREVHISTORYFIELDS(revHistoryFieldsKiCAD6);
        KiCAD6->setFOLDLINES(foldLines);
        KiCAD6->setFOLDLINETARGET(foldLinesTaget);
        KiCAD6->setSMALLPARTSLIST(smallPartsList);
        KiCAD6->setNUMLINESMALLPARTSLIST(numLinesSmallPartsList);
        KiCAD6->setNUMPARTSSMALLPARTSLIST(numPartsSmallPartsList);
        KiCAD6->setSMALLPARTSLISTFIELDS(smallPartsListFiledsKiCAD6);
        KiCAD6->setFULLSHEETPARTSLIST(fullSheetPartsList);
        KiCAD6->setFULLSHEETPARTSLISTCSV(fullSheetPartsListCSV);
        KiCAD6->setFULLSHEETPARTLISTCSVSTYLE(getBOMStyle());
        KiCAD6->setFULLSHEETPARTSLISTCSVFILE(BOMDIR);
        KiCAD6->setNUMLINESFULLSHEETPARTSLIST(numLinesFullSheetPartsList);
        KiCAD6->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFieldsKiCAD6);
        KiCAD6->setLOGO(logo);
        KiCAD6->setLOGODIR(logoDir);
        KiCAD6->setDESCRIPTION(description);
        KiCAD6->setDESCRIPTIONNUMLINES(descriptionNumLines);
        KiCAD6->draw();

        // KiCAD 7
        QMap<QString, TitelblockField> titelblockFieldsKiCAD7 = ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6();
        QMap<QString, TitelblockField> revHistoryFieldsKiCAD7 = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_KICAD6();
        QMap<QString, TitelblockField> smallPartsListFiledsKiCAD7 = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_KICAD6();
        QMap<QString, TitelblockField> fullSheetPartsListFieldsKiCAD7 = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_KICAD6();

        std::unique_ptr<TemplateGenKiCAD_7> KiCAD7(new TemplateGenKiCAD_7(this));
        KiCAD7->setDIR(dir);
        KiCAD7->setPAGESIZE(sheetSize);
        KiCAD7->setSHEETNAME(sheetName);
        KiCAD7->setPAGESTYLE(sheetStyle);
        KiCAD7->setNUMOPTLINES(numOptLines);
        KiCAD7->setTITELBLOCKFIELDS(titelblockFieldsKiCAD7);
        KiCAD7->setTRIMMINGMARKS(trimmingMarks);
        KiCAD7->setREVHISTORY(revHistory);
        KiCAD7->setREVHISTORYSTYLE(getRevHistoryStyle());
        KiCAD7->setNUMREVHISTORY(numRevHistory);
        KiCAD7->setREVHISTORYFIELDS(revHistoryFieldsKiCAD7);
        KiCAD7->setFOLDLINES(foldLines);
        KiCAD7->setFOLDLINETARGET(foldLinesTaget);
        KiCAD7->setSMALLPARTSLIST(smallPartsList);
        KiCAD7->setNUMLINESMALLPARTSLIST(numLinesSmallPartsList);
        KiCAD7->setNUMPARTSSMALLPARTSLIST(numPartsSmallPartsList);
        KiCAD7->setSMALLPARTSLISTFIELDS(smallPartsListFiledsKiCAD7);
        KiCAD7->setFULLSHEETPARTSLIST(fullSheetPartsList);
        KiCAD7->setFULLSHEETPARTSLISTCSV(fullSheetPartsListCSV);
        KiCAD7->setFULLSHEETPARTLISTCSVSTYLE(getBOMStyle());
        KiCAD7->setFULLSHEETPARTSLISTCSVFILE(BOMDIR);
        KiCAD7->setNUMLINESFULLSHEETPARTSLIST(numLinesFullSheetPartsList);
        KiCAD7->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFieldsKiCAD7);
        KiCAD7->setLOGO(logo);
        KiCAD7->setLOGODIR(logoDir);
        KiCAD7->setDESCRIPTION(description);
        KiCAD7->setDESCRIPTIONNUMLINES(descriptionNumLines);
        KiCAD7->draw();

        // FreeCAD
        QMap<QString, TitelblockField> titelblockFieldsFreeCAD = ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD();
        QMap<QString, TitelblockField> revHistoryFieldsFreeCAD = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_FREECAD();
        QMap<QString, TitelblockField> smallPartsListFiledsFreeCAD = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_FREECAD();
        QMap<QString, TitelblockField> fullSheetPartsListFieldsFreeCAD = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_FREECAD();

        std::unique_ptr<TemplateGenFreeCAD> FreeCAD(new TemplateGenFreeCAD(this));
        FreeCAD->setDIR(dir);
        FreeCAD->setPAGESIZE(sheetSize);
        FreeCAD->setSHEETNAME(sheetName);
        FreeCAD->setPAGESTYLE(sheetStyle);
        FreeCAD->setNUMOPTLINES(numOptLines);
        FreeCAD->setTITELBLOCKFIELDS(titelblockFieldsFreeCAD);
        FreeCAD->setTRIMMINGMARKS(trimmingMarks);
        FreeCAD->setREVHISTORY(revHistory);
        FreeCAD->setREVHISTORYSTYLE(getRevHistoryStyle());
        FreeCAD->setNUMREVHISTORY(numRevHistory);
        FreeCAD->setREVHISTORYFIELDS(revHistoryFieldsFreeCAD);
        FreeCAD->setFOLDLINES(foldLines);
        FreeCAD->setFOLDLINETARGET(foldLinesTaget);
        FreeCAD->setSMALLPARTSLIST(smallPartsList);
        FreeCAD->setNUMLINESMALLPARTSLIST(numLinesSmallPartsList);
        FreeCAD->setNUMPARTSSMALLPARTSLIST(numPartsSmallPartsList);
        FreeCAD->setSMALLPARTSLISTFIELDS(smallPartsListFiledsFreeCAD);
        FreeCAD->setFULLSHEETPARTSLIST(fullSheetPartsList);
        FreeCAD->setFULLSHEETPARTSLISTCSV(fullSheetPartsListCSV);
        FreeCAD->setFULLSHEETPARTLISTCSVSTYLE(getBOMStyle());
        FreeCAD->setFULLSHEETPARTSLISTCSVFILE(BOMDIR);
        FreeCAD->setNUMLINESFULLSHEETPARTSLIST(numLinesFullSheetPartsList);
        FreeCAD->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFieldsFreeCAD);
        FreeCAD->setLOGO(logo);
        FreeCAD->setLOGODIR(logoDir);
        FreeCAD->setDESCRIPTION(description);
        FreeCAD->setDESCRIPTIONNUMLINES(descriptionNumLines);
        FreeCAD->draw();

        // PDF
        QMap<QString, TitelblockField> titelblockFieldsPDF = ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF();
        QMap<QString, TitelblockField> revHistoryFieldsPDF = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_PDF();
        QMap<QString, TitelblockField> smallPartsListFiledsPDF = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_PDF();
        QMap<QString, TitelblockField> fullSheetPartsListFieldsPDF = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_PDF();

        std::unique_ptr<TemplateGenPDF> PDF(new TemplateGenPDF(this));
        PDF->setDIR(dir);
        PDF->setPAGESIZE(sheetSize);
        PDF->setSHEETNAME(sheetName);
        PDF->setPAGESTYLE(sheetStyle);
        PDF->setNUMOPTLINES(numOptLines);
        PDF->setTITELBLOCKFIELDS(titelblockFieldsPDF);
        PDF->setTRIMMINGMARKS(trimmingMarks);
        PDF->setREVHISTORY(revHistory);
        PDF->setREVHISTORYSTYLE(getRevHistoryStyle());
        PDF->setNUMREVHISTORY(numRevHistory);
        PDF->setREVHISTORYFIELDS(revHistoryFieldsPDF);
        PDF->setFOLDLINES(foldLines);
        PDF->setFOLDLINETARGET(foldLinesTaget);
        PDF->setSMALLPARTSLIST(smallPartsList);
        PDF->setNUMLINESMALLPARTSLIST(numLinesSmallPartsList);
        PDF->setNUMPARTSSMALLPARTSLIST(numPartsSmallPartsList);
        PDF->setSMALLPARTSLISTFIELDS(smallPartsListFiledsPDF);
        PDF->setFULLSHEETPARTSLIST(fullSheetPartsList);
        PDF->setFULLSHEETPARTSLISTCSV(fullSheetPartsListCSV);
        PDF->setFULLSHEETPARTLISTCSVSTYLE(getBOMStyle());
        PDF->setFULLSHEETPARTSLISTCSVFILE(BOMDIR);
        PDF->setNUMLINESFULLSHEETPARTSLIST(numLinesFullSheetPartsList);
        PDF->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFieldsPDF);
        PDF->setLOGO(logo);
        PDF->setLOGODIR(logoDir);
        PDF->setDESCRIPTION(description);
        PDF->setDESCRIPTIONNUMLINES(descriptionNumLines);
        PDF->draw();

        // Eagle
        // Uses the PDF Setings
        std::unique_ptr<TemplateGenEagle> Eagle(new TemplateGenEagle(this));
        Eagle->setDIR(dir);
        Eagle->setPAGESIZE(sheetSize);
        Eagle->setSHEETNAME(sheetName);
        Eagle->setPAGESTYLE(sheetStyle);
        Eagle->setNUMOPTLINES(numOptLines);
        Eagle->setTITELBLOCKFIELDS(titelblockFieldsPDF);
        Eagle->setTRIMMINGMARKS(trimmingMarks);
        Eagle->setREVHISTORY(revHistory);
        Eagle->setREVHISTORYSTYLE(getRevHistoryStyle());
        Eagle->setNUMREVHISTORY(numRevHistory);
        Eagle->setREVHISTORYFIELDS(revHistoryFieldsPDF);
        Eagle->setFOLDLINES(foldLines);
        Eagle->setFOLDLINETARGET(foldLinesTaget);
        Eagle->setSMALLPARTSLIST(smallPartsList);
        Eagle->setNUMLINESMALLPARTSLIST(numLinesSmallPartsList);
        Eagle->setNUMPARTSSMALLPARTSLIST(numPartsSmallPartsList);
        Eagle->setSMALLPARTSLISTFIELDS(smallPartsListFiledsPDF);
        Eagle->setFULLSHEETPARTSLIST(fullSheetPartsList);
        Eagle->setFULLSHEETPARTSLISTCSV(fullSheetPartsListCSV);
        Eagle->setFULLSHEETPARTLISTCSVSTYLE(getBOMStyle());
        Eagle->setFULLSHEETPARTSLISTCSVFILE(BOMDIR);
        Eagle->setNUMLINESFULLSHEETPARTSLIST(numLinesFullSheetPartsList);
        Eagle->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFieldsPDF);
        Eagle->setLOGO(logo);
        Eagle->setLOGODIR(logoDir);
        Eagle->setDESCRIPTION(description);
        Eagle->setDESCRIPTIONNUMLINES(descriptionNumLines);
        Eagle->draw();
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
        ui->FullPartsListNumLinesPerFieldLabel->setEnabled(true);
        ui->FullPartsListNumLinesPerFieldSpinBox->setEnabled(true);
        ui->selectCSVBOMpushButton->setEnabled(true);
        ui->insertBomCheckBox->setEnabled(true);
        ui->csvBOMComboBox->setEnabled(true);
        ui->SmallPartsListCheckBox->setEnabled(false);
    }
    else
    {
        ui->FullPartsListNumLinesPerFieldLabel->setEnabled(false);
        ui->FullPartsListNumLinesPerFieldSpinBox->setEnabled(false);
        ui->selectCSVBOMpushButton->setEnabled(false);
        ui->insertBomCheckBox->setEnabled(false);
        ui->csvBOMComboBox->setEnabled(false);
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
        ui->SmallPartsListNumLinesPerFieldSpinBox->setValue(file.getNUMLINESSMALLPARTSLIST());
        ui->SmallPartsListNumPartsSpinBox->setValue(file.getNUMPARTSSMALLPARTSLIST());
        ui->FullPartsListCheckBox->setChecked(file.getFULLSHEETPARTSLIST());
        FULLSHEETPARTLISTOPIONS->setFULLSHEETPARTSLISTFIELDS_KICAD5(file.getFULLSHEETPARTSLISTFIELDS_KICAD5());
        FULLSHEETPARTLISTOPIONS->setFULLSHEETPARTSLISTFIELDS_KICAD6(file.getFULLSHEETPARTSLISTFIELDS_KICAD6());
        FULLSHEETPARTLISTOPIONS->setFULLSHEETPARTSLISTFIELDS_FREECAD(file.getFULLSHEETPARTSLISTFIELDS_FREECAD());
        FULLSHEETPARTLISTOPIONS->setFULLSHEETPARTSLISTFIELDS_PDF(file.getFULLSHEETPARTSLISTFIELDS_PDF());
        ui->FullPartsListNumLinesPerFieldSpinBox->setValue(file.getNUMLINESFULLSHEETPARTSLIST());
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
        PageSize sheetSize = getPageSize(ui->SheetSizeComboBox->currentText());
        QString sheetName = ui->NameLineEdit->text();
        PageStyle sheetStyle = getPageStyle();
        QMap<QString, TitelblockField> titelblockFields_KICAD5 = ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD5();
        QMap<QString, TitelblockField> titelblockFields_KICAD6 = ISO7200OPTIONS->getTITELBLOCKFIELDS_KICAD6();
        QMap<QString, TitelblockField> titelblockFields_FREECAD = ISO7200OPTIONS->getTITELBLOCKFIELDS_FREECAD();
        QMap<QString, TitelblockField> titelblockFields_PDF = ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF();
        qint64 numOptLines = ui->OptLinesSpinBox->value();
        qint64 numRevHistory = ui->numRevSpinBox->value();
        QMap<QString, TitelblockField> revHistoryFields_KICAD5 = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_KICAD5();
        QMap<QString, TitelblockField> revHistoryFields_KICAD6 = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_KICAD6();
        QMap<QString, TitelblockField> revHistoryFields_FREECAD = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_FREECAD();
        QMap<QString, TitelblockField> revHistoryFields_PDF = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_PDF();
        bool trimmingMarks = ui->trimmingMarksCheckBox->isChecked();
        bool revHistory = ui->RevHistoryCheckBox->isChecked();
        bool foldLines = ui->foldLinesCheckBox->isChecked();
        PageSize foldLinesTaget = getFoldLinesTarget(ui->foldingLinesComboBox->currentText());
        bool smallPartsList = ui->SmallPartsListCheckBox->isChecked();
        quint64 numLinesSmallPartsList = ui->SmallPartsListNumLinesPerFieldSpinBox->value();
        quint64 numPartsSmallPartsList = ui->SmallPartsListNumPartsSpinBox->value();
        QMap<QString, TitelblockField> smallPartsListFileds_KICAD5 = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_KICAD5();
        QMap<QString, TitelblockField> smallPartsListFileds_KICAD6 = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_KICAD6();
        QMap<QString, TitelblockField> smallPartsListFileds_FREECAD = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_FREECAD();
        QMap<QString, TitelblockField> smallPartsListFileds_PDF = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_PDF();
        bool fullSheetPartsList = ui->FullPartsListCheckBox->isChecked();
        quint64 numLinesFullSheetPartsList = ui->FullPartsListNumLinesPerFieldSpinBox->value();
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


void MainWindow::on_selectCSVBOMpushButton_clicked()
{
    ui->insertBomCheckBox->setChecked(true);
    QString dir = QFileDialog::getOpenFileName(this, "Open File",
                                               "/home",
                                               "BOMs (*.csv);;All files (*.*)");
    if(dir.size() > 0)
    {
        BOMDIR = dir;
    }
    if(WINDOWRUNNING)
    {
        on_previewPushButton_clicked();
    }
}


void MainWindow::on_previewPushButton_clicked()
{
    PageSize sheetSize = getPageSize(ui->SheetSizeComboBox->currentText());
    QString sheetName = ui->NameLineEdit->text();
    PageStyle sheetStyle = getPageStyle();
    QMap<QString, TitelblockField> titelblockFields = ISO7200OPTIONS->getTITELBLOCKFIELDS_PDF();
    qint64 numOptLines = ui->OptLinesSpinBox->value();
    qint64 numRevHistory = ui->numRevSpinBox->value();
    QMap<QString, TitelblockField> revHistoryFields = ASME_Y14_35_WIDTH180->getREVHISTORYFIELDS_PDF();
    bool trimmingMarks = ui->trimmingMarksCheckBox->isChecked();
    bool revHistory = ui->RevHistoryCheckBox->isChecked();
    bool foldLines = ui->foldLinesCheckBox->isChecked();
    PageSize foldLinesTaget = getFoldLinesTarget(ui->foldingLinesComboBox->currentText());
    bool smallPartsList = ui->SmallPartsListCheckBox->isChecked();
    quint64 numLinesSmallPartsList = ui->SmallPartsListNumLinesPerFieldSpinBox->value();
    quint64 numPartsSmallPartsList = ui->SmallPartsListNumPartsSpinBox->value();
    QMap<QString, TitelblockField> smallPartsListFileds = SMALLPARTSLISTSOPTIONS->getSMALLPARTSLISTFIELDS_PDF();
    bool fullSheetPartsList = ui->FullPartsListCheckBox->isChecked();
    quint64 numLinesFullSheetPartsList = ui->FullPartsListNumLinesPerFieldSpinBox->value();
    bool fullSheetPartsListCSV = ui->insertBomCheckBox->isChecked();
    QMap<QString, TitelblockField> fullSheetPartsListFields = FULLSHEETPARTLISTOPIONS->getFULLSHEETPARTSLISTFIELDS_PDF();
    bool logo = ui->logoCheckBox->isChecked();
    QString logoDir = LOGODIR;
    bool description = ui->DescriptionCheckBox->isChecked();
    quint64 descriptionNumLines = ui->DescriptionSpinBox->value();

    PREVIEW->setDIR(QDir::currentPath() + "/tmp");
    PREVIEW->setPAGESIZE(sheetSize);
    PREVIEW->setSHEETNAME(sheetName);
    PREVIEW->setPAGESTYLE(sheetStyle);
    PREVIEW->setNUMOPTLINES(numOptLines);
    PREVIEW->setTITELBLOCKFIELDS(titelblockFields);
    PREVIEW->setTRIMMINGMARKS(trimmingMarks);
    PREVIEW->setREVHISTORY(revHistory);
    PREVIEW->setREVHISTORYSTYLE(getRevHistoryStyle());
    PREVIEW->setNUMREVHISTORY(numRevHistory);
    PREVIEW->setREVHISTORYFIELDS(revHistoryFields);
    PREVIEW->setFOLDLINES(foldLines);
    PREVIEW->setFOLDLINETARGET(foldLinesTaget);
    PREVIEW->setSMALLPARTSLIST(smallPartsList);
    PREVIEW->setNUMLINESMALLPARTSLIST(numLinesSmallPartsList);
    PREVIEW->setNUMPARTSSMALLPARTSLIST(numPartsSmallPartsList);
    PREVIEW->setSMALLPARTSLISTFIELDS(smallPartsListFileds);
    PREVIEW->setFULLSHEETPARTSLIST(fullSheetPartsList);
    PREVIEW->setFULLSHEETPARTSLISTCSV(fullSheetPartsListCSV);
    PREVIEW->setFULLSHEETPARTLISTCSVSTYLE(getBOMStyle());
    PREVIEW->setFULLSHEETPARTSLISTCSVFILE(BOMDIR);
    PREVIEW->setNUMLINESFULLSHEETPARTSLIST(numLinesFullSheetPartsList);
    PREVIEW->setFULLSHEETPARTSLISTFIELDS(fullSheetPartsListFields);
    PREVIEW->setLOGO(logo);
    PREVIEW->setLOGODIR(logoDir);
    PREVIEW->setDESCRIPTION(description);
    PREVIEW->setDESCRIPTIONNUMLINES(descriptionNumLines);
    PREVIEW->setMinimumWidth(ui->centralwidget->size().width() - 600);
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

