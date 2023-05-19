#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <memory>
#include <utility>

#include <QMainWindow>
#include <QFileDialog>

#include "templateoptions.h"
#include "iso7200options.h"
#include "asme_y14_35_width180options.h"
#include "smallpartslistoptions.h"
#include "fullsheetspartlistoptions.h"

#include "iso7200dialog.h"
#include "asme_y14_35_width180dialog.h"

#include "templategenkicad_5.h"
#include "templategenkicad_6.h"
#include "templategenkicad_7.h"
#include "templategenfreecad.h"
#include "templategenpdf.h"
#include "templategensvg.h"
#include "templategeneagle.h"

#include "preview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

///
/// \brief The MainWindow class
///
/// The MainWindow class creates and manages the main Window
///
class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    ///
    /// \brief on_GeneratePushButton_clicked generates all the Templaest
    ///
    void on_GeneratePushButton_clicked();

    void on_SheetSizeComboBox_currentTextChanged(const QString &arg1);

    void on_sheetTitelblockFieldsPushButton_clicked();

    void on_revHistoryStylePushButton_clicked();

    void on_FullPartsListCheckBox_stateChanged(int arg1);

    void on_SmallPartsListCheckBox_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_editFullPartsListPushButton_clicked();

    void on_loadFielsPushButton_clicked();

    void on_logoPushButton_clicked();

    void on_saveFieldsPushButton_clicked();

    void on_pushButton_2_clicked();

    void on_previewPushButton_clicked();

    void on_sheetWidthDoubleSpinBox_valueChanged(double arg1);

    void on_sheetHeightDoubleSpinBox_valueChanged(double arg1);

    void on_NameLineEdit_textEdited(const QString &arg1);

    void on_SheetStyleComboBox_currentIndexChanged(int index);

    void on_RevHistoryCheckBox_stateChanged(int arg1);

    void on_revHistoryStyleComboBox_currentIndexChanged(int index);

    void on_foldLinesCheckBox_stateChanged(int arg1);

    void on_foldingLinesComboBox_currentIndexChanged(int index);

    void on_FullPartsListNumLinesPerFieldSpinBox_valueChanged(int arg1);

    void on_insertBomCheckBox_stateChanged(int arg1);

    void on_csvBOMComboBox_currentIndexChanged(int index);

    void on_SmallPartsListNumLinesPerFieldSpinBox_valueChanged(int arg1);

    void on_SmallPartsListNumPartsSpinBox_valueChanged(int arg1);

    void on_spaceComboBox_currentIndexChanged(int index);

    void on_portraitCheckBox_stateChanged(int arg1);

    void on_preViewSheetBordercheckBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    ///
    /// \brief SHEETSIZES is a list of all the sheetsize(sheetsizes)
    ///
    // Sizes in mm                                            Designation               width  height Referenc from:https://papersizes.io
    QList<SheetSize> SHEETSIZES = QList<SheetSize>   {
                                                    SheetSize{"User defined",            400,   250},

                                                    SheetSize{"4A0",                     2378,  1682},
                                                    SheetSize{"2A0",                     1682,  1189},
                                                    SheetSize{"A0",                      1189,  841},
                                                    SheetSize{"A1",                      841,   594},
                                                    SheetSize{"A2",                      594,   420},
                                                    SheetSize{"A3",                      420,   297},
                                                    SheetSize{"A4",                      297,   210},
                                                    SheetSize{"A5",                      210,   148},
                                                    SheetSize{"A6",                      148,   105},
                                                    SheetSize{"A7",                      105,   74},
                                                    SheetSize{"A8",                      74,    52},
                                                    SheetSize{"A9",                      52,    37},
                                                    SheetSize{"A10",                     37,    26},
                                                    SheetSize{"A11",                     26,    18},
                                                    SheetSize{"A12",                     18,    13},
                                                    SheetSize{"A13",                     13,    9},
                                                    SheetSize{"A0+",                     1292,  914},
                                                    SheetSize{"A1+",                     914,   609},
                                                    SheetSize{"A3+",                     483,   329},

                                                    SheetSize{"B0",                      1414,  1000},
                                                    SheetSize{"B1",                      1000,  707},
                                                    SheetSize{"B2",                      707,   500},
                                                    SheetSize{"B3",                      500,   353},
                                                    SheetSize{"B4",                      353,   250},
                                                    SheetSize{"B5",                      250,   176},
                                                    SheetSize{"B6",                      176,   125},
                                                    SheetSize{"B7",                      125,   88},
                                                    SheetSize{"B8",                      88,    62},
                                                    SheetSize{"B9",                      62,    44},
                                                    SheetSize{"B10",                     44,    31},
                                                    SheetSize{"B11",                     31,    22},
                                                    SheetSize{"B12",                     22,    15},
                                                    SheetSize{"B13",                     15,    11},
                                                    SheetSize{"B0+",                     1580,  1118},
                                                    SheetSize{"B1+",                     1118,  720},
                                                    SheetSize{"B3+",                     720,   520},

                                                    SheetSize{"C0",                      1297,  917},
                                                    SheetSize{"C1",                      917,   648},
                                                    SheetSize{"C2",                      648,   458},
                                                    SheetSize{"C3",                      458,   324},
                                                    SheetSize{"C4",                      324,   229},
                                                    SheetSize{"C5",                      229,   162},
                                                    SheetSize{"C6",                      162,   114},
                                                    SheetSize{"C7",                      114,   81},
                                                    SheetSize{"C8",                      81,    57},
                                                    SheetSize{"C9",                      57,    40},
                                                    SheetSize{"C10",                     40,    28},

                                                    SheetSize{"D0",                      1090,  771},
                                                    SheetSize{"D1",                      771,   545},
                                                    SheetSize{"D2",                      545,   385},
                                                    SheetSize{"D3",                      385,   272},
                                                    SheetSize{"D4",                      272,   192},
                                                    SheetSize{"D5",                      192,   136},
                                                    SheetSize{"D6",                      136,   96},
                                                    SheetSize{"D7",                      96,    68},
                                                    SheetSize{"D8",                      68,    48},

                                                    SheetSize{"JB0",                     1456,  1030},
                                                    SheetSize{"JB1",                     1030,  728},
                                                    SheetSize{"JB2",                     728,   515},
                                                    SheetSize{"JB3",                     515,   364},
                                                    SheetSize{"JB4",                     364,   257},
                                                    SheetSize{"JB5",                     257,   182},
                                                    SheetSize{"JB6",                     182,   128},
                                                    SheetSize{"JB7",                     128,   91},
                                                    SheetSize{"JB8",                     91,    64},
                                                    SheetSize{"JB9",                     64,    45},
                                                    SheetSize{"JB10",                    45,    32},
                                                    SheetSize{"JB11",                    32,    22},
                                                    SheetSize{"JB12",                    22,    16},

                                                    SheetSize{"SIS D0",                  1542,  1091},
                                                    SheetSize{"SIS D1",                  1091,   771},
                                                    SheetSize{"SIS D2",                  771,   545},
                                                    SheetSize{"SIS D3",                  545,   386},
                                                    SheetSize{"SIS D4",                  386,   273},
                                                    SheetSize{"SIS D5",                  273,   193},
                                                    SheetSize{"SIS D6",                  193,   136},
                                                    SheetSize{"SIS D7",                  136,   96},
                                                    SheetSize{"SIS D8",                  96,    68},
                                                    SheetSize{"SIS D9",                  68,    48},
                                                    SheetSize{"SIS D10",                 48,    34},

                                                    SheetSize{"SIS E0",                  1242,  878},
                                                    SheetSize{"SIS E1",                  878,   621},
                                                    SheetSize{"SIS E2",                  621,   439},
                                                    SheetSize{"SIS E3",                  439,   310},
                                                    SheetSize{"SIS E4",                  310,   220},
                                                    SheetSize{"SIS E5",                  220,   155},
                                                    SheetSize{"SIS E6",                  155,   110},
                                                    SheetSize{"SIS E7",                  110,   78},
                                                    SheetSize{"SIS E8",                  78,    55},
                                                    SheetSize{"SIS E9",                  55,    39},
                                                    SheetSize{"SIS E10",                 39,    27},

                                                    SheetSize{"SIS F0",                  1354,  958},
                                                    SheetSize{"SIS F1",                  958,   677},
                                                    SheetSize{"SIS F2",                  677,   479},
                                                    SheetSize{"SIS F3",                  479,   339},
                                                    SheetSize{"SIS F4",                  339,   239},
                                                    SheetSize{"SIS F5",                  239,   169},
                                                    SheetSize{"SIS F6",                  169,   120},
                                                    SheetSize{"SIS F7",                  120,   85},
                                                    SheetSize{"SIS F8",                  85,    60},
                                                    SheetSize{"SIS F9",                  60,    42},
                                                    SheetSize{"SIS F10",                 42,    30},

                                                    SheetSize{"SIS G0",                  1477,  1044},
                                                    SheetSize{"SIS G1",                  1044,   738},
                                                    SheetSize{"SIS G2",                  738,   522},
                                                    SheetSize{"SIS G3",                  522,   369},
                                                    SheetSize{"SIS G4",                  369,   261},
                                                    SheetSize{"SIS G5",                  261,   185},
                                                    SheetSize{"SIS G6",                  185,   131},
                                                    SheetSize{"SIS G7",                  131,   92},
                                                    SheetSize{"SIS G8",                  92,    65},
                                                    SheetSize{"SIS G9",                  65,    46},
                                                    SheetSize{"SIS G10",                 46,    33},

                                                    SheetSize{"290mmX200mm",             290,     200},

                                                    SheetSize{"566mmX400mm",             566,     400},
                                                    SheetSize{"400mmX283mm",             400,     283},
                                                    SheetSize{"283mmX200mm",             283,     200},

                                                    // No actual Formats just for fun and to put the US sizeze even more to the bottom
                                                    SheetSize{"2097152A0(2MA0) Not real", 1722368, 1217536},
                                                    SheetSize{"1048576A0(1MA0) Not real", 1217536, 861184},
                                                    SheetSize{"524288A0(512kA0) Not real", 861184, 608768},
                                                    SheetSize{"262144A0(256kA0) Not real", 608768, 430592},
                                                    SheetSize{"131072A0(128kA0) Not real", 430592, 304384},
                                                    SheetSize{"65536A0(64kA0) Not real", 304384, 215296},
                                                    SheetSize{"32768A0(32kA0) Not real", 215296, 152192},
                                                    SheetSize{"16384A0(16kA0) Not real", 152192, 107648},
                                                    SheetSize{"8192A0(8kA0) Not real",   107648, 76096},
                                                    SheetSize{"4096A0(4kA0) Not real",   76096, 53824},
                                                    SheetSize{"2048A0(2kA0) Not real",   53824, 38048},
                                                    SheetSize{"1024A0(1kA0) Not real",   38048, 26912},
                                                    SheetSize{"512A0 Not real",          26912, 19024},
                                                    SheetSize{"256A0 Not real",          19024, 13456},
                                                    SheetSize{"128A0 Not real",          13456, 9512},
                                                    SheetSize{"64A0 Not real",           9512,  6728},
                                                    SheetSize{"32A0 Not real",           6728,  4756},
                                                    SheetSize{"16A0 Not real",           4756,  3364},
                                                    SheetSize{"8A0 Not real",            3364,  2378},

                                                    SheetSize{"ANSI Y14.1 A (Letter)",   279,   216},
                                                    SheetSize{"ANSI Y14.1 B",            432,   279},
                                                    SheetSize{"ANSI Y14.1 C",            559,   432},
                                                    SheetSize{"ANSI Y14.1 D",            864,   559},
                                                    SheetSize{"ANSI Y14.1 E",            1118,  864},
                                                    SheetSize{"ANSI Y14.1 F",            1016,  711},

                                                    SheetSize{"Legal",                   356,   216},
                                                    SheetSize{"Tabloid (Ledger)",        432,   279},

                                                    SheetSize{"Arch A",                  305,   229},
                                                    SheetSize{"Arch B",                  457,   305},
                                                    SheetSize{"Arch C",                  610,   457},
                                                    SheetSize{"Arch D",                  914,   610},
                                                    SheetSize{"Arch E",                  1219,  914},
                                                    SheetSize{"Arch E1",                 1067,  726},
                                                    SheetSize{"Arch E2",                 965,   660},
                                                    SheetSize{"Arch E3",                 991,   686}};

    ///
    /// \brief FOLDLINESTARGET is a list of sheetsizes(sheetsizes) to withch the foldlines will be created
    ///
    // Sizes in mm                                                  Designation               width  height
    QList<SheetSize> FOLDLINESTARGET = QList<SheetSize>   {
                                                            SheetSize{"A4P with border",         210,   297},
                                                            SheetSize{"200mmX290mm with border", 200,     290},
                                                            SheetSize{"200mmX283mm",             283,     200},};

    std::shared_ptr<ISO7200Options> ISO7200OPTIONS =  std::shared_ptr<ISO7200Options>(new ISO7200Options(this));
    std::shared_ptr<ASME_Y14_35_Width180Options> ASME_Y14_35_WIDTH180OPTIONS = std::shared_ptr<ASME_Y14_35_Width180Options>(new ASME_Y14_35_Width180Options(this));
    std::shared_ptr<FullSheetsPartListOptions> FULLSHEETPARTLISTOPIONS = std::shared_ptr<FullSheetsPartListOptions>(new FullSheetsPartListOptions(this));
    std::shared_ptr<SmallPartsListOptions> SMALLPARTSLISTSOPTIONS = std::shared_ptr<SmallPartsListOptions>(new SmallPartsListOptions(this));

    QString LOGODIR = "&";

    void initSheetSizes();
    void initSheetStyles();
    void initRevHistoryStyles();
    void initFoldLinesTarget();
    void initBOMStyles();

    SheetStyle getSheetStyle();
    SheetSize getSheetSize(QString sizeString, double width = 0, double height = 0);
    SheetSize getFoldLinesTarget(QString sizeString);
    RevHistoryStyle getRevHistoryStyle();
    QString getRevHistoryStyleString(RevHistoryStyle style);
    BOMStyles getBOMStyle();

    QString LASTDIR = "/home/tobias/tmp/";

    std::shared_ptr<Preview> PREVIEW;
    bool WINDOWRUNNING = false;
    void resizeEvent(QResizeEvent *event);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
