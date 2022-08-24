#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "templateoptions.h"
#include "iso7200options.h"
#include "asme_y14_35_width180.h"
#include "smallpartslistoptions.h"
#include "fullsheetspartlistoptions.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
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

private:
    Ui::MainWindow *ui;
    // Sizes in mm                                            Designation               width  height
    QList<PageSize> PAGESIZES = QList<PageSize>   { PageSize{"User defined",            0,     0},
                                                    PageSize{"4A0",                     2378,  1682},
                                                    PageSize{"2A0",                     1682,  1189},
                                                    PageSize{"A0",                      1189,  841},
                                                    PageSize{"A1",                      841,   594},
                                                    PageSize{"A2",                      594,   420},
                                                    PageSize{"A3",                      420,   297},
                                                    PageSize{"A4L",                     297,   210},
                                                    PageSize{"A4P",                     210,   297},
                                                    PageSize{"B0",                      1414,  1000},
                                                    PageSize{"B1",                      1000,  707},
                                                    PageSize{"B2",                      707,   500},
                                                    PageSize{"B3",                      500,   353},
                                                    PageSize{"B4",                      353,   250},
                                                    PageSize{"B5",                      250,   176},
                                                    PageSize{"ANSI Y14.1 AL (Letter)",  279,   216},
                                                    PageSize{"ANSI Y14.1 AP (Letter)",  216,   279},
                                                    PageSize{"ANSI Y14.1 B",            432,   279},
                                                    PageSize{"ANSI Y14.1 C",            559,   432},
                                                    PageSize{"ANSI Y14.1 D",            864,   559},
                                                    PageSize{"ANSI Y14.1 E",            1118,  864},
                                                    PageSize{"ANSI Y14.1 F",            1016,  711},
                                                    PageSize{"Legal",                   356,   216},
                                                    PageSize{"Tabloid (Ledger)",        432,   279},
                                                    PageSize{"Arch AL",                 305,   229},
                                                    PageSize{"Arch AP",                 229,   305},
                                                    PageSize{"Arch B",                  457,   305},
                                                    PageSize{"Arch C",                  610,   457},
                                                    PageSize{"Arch D",                  914,   610},
                                                    PageSize{"Arch E",                  1219,  914},
                                                    PageSize{"Arch E1",                 1067,  726},
                                                    PageSize{"Arch E2",                 965,   660},
                                                    PageSize{"Arch E3",                 991,   686}};

    // Sizes in mm                                                  Designation               width  height
    QList<PageSize> FOLDLINESTARGET = QList<PageSize>   { PageSize{"A4P with border",         210,   297},
                                                          PageSize{"200mmX290mm with border",             0,     0},};

    ISO7200Options *ISO7200OPTIONS = new ISO7200Options(this);
    ASME_Y14_35_Width180 *ASME_Y14_35_WIDTH180 = new ASME_Y14_35_Width180(this);
    FullSheetsPartListOptions *FULLSHEETPARTLISTOPIONS = new FullSheetsPartListOptions(this);
    SmallPartsListOptions *SMALLPARTSLISTSOPTIONS = new SmallPartsListOptions(this);

    QString LOGODIR = "&";

    void initPageSizes();
    void initPageStyles();
    void initRevHistoryStyles();
    void initFoldLinesTarget();

    PageStyle getPageStyle();
    PageSize getPageSize(QString sizeString, double width = 0, double height = 0);
    PageSize getFoldLinesTarget(QString sizeString);
    RevHistoryStyle getRevHistoryStyle();
    QString getRevHistoryStyleString(RevHistoryStyle style);

    QString LASTDIR = "/home/tobias/tmp/";
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
