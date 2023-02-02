#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <memory>
#include <utility>

#include <QMainWindow>
#include <QFileDialog>

#include "templateoptions.h"
#include "iso7200options.h"
#include "asme_y14_35_width180.h"
#include "smallpartslistoptions.h"
#include "fullsheetspartlistoptions.h"

#include "templategenkicad_5.h"
#include "templategenkicad_6.h"
#include "templategenkicad_7.h"
#include "templategenfreecad.h"
#include "templategenpdf.h"
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

//    void on_selectCSVBOMpushButton_clicked();

    void on_previewPushButton_clicked();

    void on_sheetWidthDoubleSpinBox_valueChanged(double arg1);

    void on_sheetHeightDoubleSpinBox_valueChanged(double arg1);

    void on_NameLineEdit_textEdited(const QString &arg1);

    void on_SheetStyleComboBox_currentIndexChanged(int index);

    void on_trimmingMarksCheckBox_stateChanged(int arg1);

    void on_OptLinesSpinBox_valueChanged(int arg1);

    void on_DescriptionCheckBox_stateChanged(int arg1);

    void on_DescriptionSpinBox_valueChanged(int arg1);

    void on_RevHistoryCheckBox_stateChanged(int arg1);

    void on_numRevSpinBox_valueChanged(int arg1);

    void on_revHistoryStyleComboBox_currentIndexChanged(int index);

    void on_foldLinesCheckBox_stateChanged(int arg1);

    void on_foldingLinesComboBox_currentIndexChanged(int index);

    void on_FullPartsListNumLinesPerFieldSpinBox_valueChanged(int arg1);

    void on_insertBomCheckBox_stateChanged(int arg1);

    void on_csvBOMComboBox_currentIndexChanged(int index);

    void on_SmallPartsListNumLinesPerFieldSpinBox_valueChanged(int arg1);

    void on_SmallPartsListNumPartsSpinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    ///
    /// \brief SHEETSIZES is a list of all the sheetsize(sheetsizes)
    ///
    // Sizes in mm                                            Designation               width  height
    QList<SheetSize> SHEETSIZES = QList<SheetSize>   { SheetSize{"User defined",            400,   250},
                                                    SheetSize{"4A0",                     2378,  1682},
                                                    SheetSize{"2A0",                     1682,  1189},
                                                    SheetSize{"A0",                      1189,  841},
                                                    SheetSize{"A1",                      841,   594},
                                                    SheetSize{"A2",                      594,   420},
                                                    SheetSize{"A3",                      420,   297},
                                                    SheetSize{"A4L",                     297,   210},
                                                    SheetSize{"A4P",                     210,   297},
                                                    SheetSize{"B0",                      1414,  1000},
                                                    SheetSize{"B1",                      1000,  707},
                                                    SheetSize{"B2",                      707,   500},
                                                    SheetSize{"B3",                      500,   353},
                                                    SheetSize{"B4",                      353,   250},
                                                    SheetSize{"B5",                      250,   176},
                                                    SheetSize{"ANSI Y14.1 AL (Letter)",  279,   216},
                                                    SheetSize{"ANSI Y14.1 AP (Letter)",  216,   279},
                                                    SheetSize{"ANSI Y14.1 B",            432,   279},
                                                    SheetSize{"ANSI Y14.1 C",            559,   432},
                                                    SheetSize{"ANSI Y14.1 D",            864,   559},
                                                    SheetSize{"ANSI Y14.1 E",            1118,  864},
                                                    SheetSize{"ANSI Y14.1 F",            1016,  711},
                                                    SheetSize{"Legal",                   356,   216},
                                                    SheetSize{"Tabloid (Ledger)",        432,   279},
                                                    SheetSize{"Arch AL",                 305,   229},
                                                    SheetSize{"Arch AP",                 229,   305},
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
    QList<SheetSize> FOLDLINESTARGET = QList<SheetSize>   { SheetSize{"A4P with border",         210,   297},
                                                          SheetSize{"200mmX290mm with border",             200,     290},};

    std::shared_ptr<ISO7200Options> ISO7200OPTIONS =  std::shared_ptr<ISO7200Options>(new ISO7200Options(this));
    std::shared_ptr<ASME_Y14_35_Width180> ASME_Y14_35_WIDTH180 = std::shared_ptr<ASME_Y14_35_Width180>(new ASME_Y14_35_Width180(this));
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
