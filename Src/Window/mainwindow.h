#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <memory>
#include <utility>

#include <QFileDialog>
#include <QMainWindow>

// #include "preview.h"
#include "../PreView/preview.h"
// #include "PreView/preview.h"

#include "PageLayout/Frame/pageframe.h"
#include "PageLayout/pagestyle.h"
#include "PageLayout/Frame/Plain/plainframe.h"

#include "Threads/universaldrawthread.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
} // namespace Ui
QT_END_NAMESPACE

///
/// \brief The MainWindow class
///
/// The MainWindow class creates and manages the main Window
///
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ///
    /// \brief MainWindow it is the constructor of this class and initializes this
    /// class
    /// \param parent is the Qt parent object pointer
    ///
    explicit MainWindow(QWidget *parent = nullptr);
    ///
    /// \brief is the de constructor
    ///
    ~MainWindow() override;

private slots:
    void on_GeneratePushButton_clicked();

    void handleResults(UniversalDrawThread *thread);

    void on_PageSizeComboBox_currentTextChanged(const QString &arg1);

    void on_PageWidthDoubleSpinBox_valueChanged(double arg1);

    void on_PageHeigthDoubleSpinBox_valueChanged(double arg1);

    void on_NameLineEdit_editingFinished();

    void on_framePushButton_clicked();

    void on_FrameComboBox_currentTextChanged(const QString &arg1);

    void on_TitleBlockComboBox_currentTextChanged(const QString &arg1);

    void on_TitleBlockPushButton_clicked();

    void on_TitleBlLanguageComboBox_currentTextChanged(const QString &arg1);

private:
    ///
    /// \brief ui is the pointer to the ui and through this all the elements of
    /// the ui are accessed through this
    ///
    Ui::MainWindow *m_ui;

    ///
    /// \brief m_preView is the PreView of the page
    ///
    std::shared_ptr<PreView> m_preView;

    ///
    /// \brief resizeEvent is the event that redraws the preview, it is called when the window sice
    /// changes
    /// \param event
    ///
    void resizeEvent(QResizeEvent *event) override;

    ///
    /// \brief updatePreView redraws the preview
    ///
    void updatePreView();
    void updateFrame(QString framStr);
    void updateFrame();

    ///
    /// \brief m_pagesizes is a list of all the page sizes
    ///
    /// Reference from:https://papersizes.io
    ///
    QList<QPageSize> m_pagesizes = QList<QPageSize>{
        // User defined must be at the top/index 0
        QPageSize{ QSizeF{ 250, 400 }, QPageSize::Millimeter, "User defined",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 1682, 2378 }, QPageSize::Millimeter, "4A0", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 1189, 1682 }, QPageSize::Millimeter, "2A0", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 841, 1189 }, QPageSize::Millimeter, "A0", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 594, 841 }, QPageSize::Millimeter, "A1", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 420, 594 }, QPageSize::Millimeter, "A2", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 297, 420 }, QPageSize::Millimeter, "A3", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 210, 297 }, QPageSize::Millimeter, "A4", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 148, 210 }, QPageSize::Millimeter, "A5", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 105, 148 }, QPageSize::Millimeter, "A6", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 74, 105 }, QPageSize::Millimeter, "A7", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 52, 74 }, QPageSize::Millimeter, "A8", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 37, 52 }, QPageSize::Millimeter, "A9", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 26, 37 }, QPageSize::Millimeter, "A10", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 18, 26 }, QPageSize::Millimeter, "A11", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 13, 18 }, QPageSize::Millimeter, "A12", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 9, 13 }, QPageSize::Millimeter, "A13", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 914, 1292 }, QPageSize::Millimeter, "A0+", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 609, 914 }, QPageSize::Millimeter, "A1+", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 329, 483 }, QPageSize::Millimeter, "A3+", QPageSize::ExactMatch },

        QPageSize{ QSizeF{ 1000, 1414 }, QPageSize::Millimeter, "B0", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 707, 1000 }, QPageSize::Millimeter, "B1", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 500, 707 }, QPageSize::Millimeter, "B2", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 353, 500 }, QPageSize::Millimeter, "B3", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 250, 353 }, QPageSize::Millimeter, "B4", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 176, 250 }, QPageSize::Millimeter, "B5", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 125, 176 }, QPageSize::Millimeter, "B6", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 88, 125 }, QPageSize::Millimeter, "B7", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 62, 88 }, QPageSize::Millimeter, "B8", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 44, 62 }, QPageSize::Millimeter, "B9", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 31, 44 }, QPageSize::Millimeter, "B10", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 22, 31 }, QPageSize::Millimeter, "B11", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 15, 22 }, QPageSize::Millimeter, "B12", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 11, 15 }, QPageSize::Millimeter, "B13", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 1118, 1580 }, QPageSize::Millimeter, "B0+", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 720, 1118 }, QPageSize::Millimeter, "B1+", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 520, 720 }, QPageSize::Millimeter, "B3+", QPageSize::ExactMatch },

        QPageSize{ QSizeF{ 917, 1297 }, QPageSize::Millimeter, "C0", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 648, 917 }, QPageSize::Millimeter, "C1", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 458, 648 }, QPageSize::Millimeter, "C2", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 324, 458 }, QPageSize::Millimeter, "C3", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 229, 324 }, QPageSize::Millimeter, "C4", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 162, 229 }, QPageSize::Millimeter, "C5", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 114, 162 }, QPageSize::Millimeter, "C6", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 81, 114 }, QPageSize::Millimeter, "C7", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 57, 81 }, QPageSize::Millimeter, "C8", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 40, 57 }, QPageSize::Millimeter, "C9", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 28, 40 }, QPageSize::Millimeter, "C10", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 771, 1090 }, QPageSize::Millimeter, "D0", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 545, 771 }, QPageSize::Millimeter, "D1", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 385, 545 }, QPageSize::Millimeter, "D2", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 272, 385 }, QPageSize::Millimeter, "D3", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 192, 272 }, QPageSize::Millimeter, "D4", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 136, 192 }, QPageSize::Millimeter, "D5", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 96, 136 }, QPageSize::Millimeter, "D6", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 68, 96 }, QPageSize::Millimeter, "D7", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 48, 68 }, QPageSize::Millimeter, "D8", QPageSize::ExactMatch },

        QPageSize{ QSizeF{ 1030, 1456 }, QPageSize::Millimeter, "JB0", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 728, 1030 }, QPageSize::Millimeter, "JB1", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 515, 728 }, QPageSize::Millimeter, "JB2", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 364, 515 }, QPageSize::Millimeter, "JB3", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 257, 364 }, QPageSize::Millimeter, "JB4", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 182, 257 }, QPageSize::Millimeter, "JB5", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 128, 182 }, QPageSize::Millimeter, "JB6", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 91, 128 }, QPageSize::Millimeter, "JB7", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 64, 91 }, QPageSize::Millimeter, "JB8", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 45, 64 }, QPageSize::Millimeter, "JB9", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 32, 45 }, QPageSize::Millimeter, "JB10", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 22, 32 }, QPageSize::Millimeter, "JB11", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 16, 22 }, QPageSize::Millimeter, "JB12", QPageSize::ExactMatch },

        QPageSize{ QSizeF{ 1091, 1542 }, QPageSize::Millimeter, "SIS D0", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 771, 1091 }, QPageSize::Millimeter, "SIS D1", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 545, 771 }, QPageSize::Millimeter, "SIS D2", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 386, 545 }, QPageSize::Millimeter, "SIS D3", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 273, 386 }, QPageSize::Millimeter, "SIS D4", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 193, 273 }, QPageSize::Millimeter, "SIS D5", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 136, 193 }, QPageSize::Millimeter, "SIS D6", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 96, 136 }, QPageSize::Millimeter, "SIS D7", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 68, 96 }, QPageSize::Millimeter, "SIS D8", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 48, 68 }, QPageSize::Millimeter, "SIS D9", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 34, 48 }, QPageSize::Millimeter, "SIS D10", QPageSize::ExactMatch },

        QPageSize{ QSizeF{ 878, 1242 }, QPageSize::Millimeter, "SIS E0", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 621, 878 }, QPageSize::Millimeter, "SIS E1", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 439, 621 }, QPageSize::Millimeter, "SIS E2", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 310, 439 }, QPageSize::Millimeter, "SIS E3", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 220, 310 }, QPageSize::Millimeter, "SIS E4", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 155, 220 }, QPageSize::Millimeter, "SIS E5", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 110, 155 }, QPageSize::Millimeter, "SIS E6", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 78, 110 }, QPageSize::Millimeter, "SIS E7", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 55, 78 }, QPageSize::Millimeter, "SIS E8", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 39, 55 }, QPageSize::Millimeter, "SIS E9", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 27, 39 }, QPageSize::Millimeter, "SIS E10", QPageSize::ExactMatch },

        QPageSize{ QSizeF{ 958, 1354 }, QPageSize::Millimeter, "SIS F0", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 677, 958 }, QPageSize::Millimeter, "SIS F1", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 479, 677 }, QPageSize::Millimeter, "SIS F2", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 339, 479 }, QPageSize::Millimeter, "SIS F3", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 239, 339 }, QPageSize::Millimeter, "SIS F4", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 169, 239 }, QPageSize::Millimeter, "SIS F5", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 120, 169 }, QPageSize::Millimeter, "SIS F6", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 85, 120 }, QPageSize::Millimeter, "SIS F7", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 60, 85 }, QPageSize::Millimeter, "SIS F8", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 42, 60 }, QPageSize::Millimeter, "SIS F9", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 30, 42 }, QPageSize::Millimeter, "SIS F10", QPageSize::ExactMatch },

        QPageSize{ QSizeF{ 1044, 1477 }, QPageSize::Millimeter, "SIS G0", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 738, 1044 }, QPageSize::Millimeter, "SIS G1", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 522, 738 }, QPageSize::Millimeter, "SIS G2", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 369, 522 }, QPageSize::Millimeter, "SIS G3", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 261, 369 }, QPageSize::Millimeter, "SIS G4", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 185, 261 }, QPageSize::Millimeter, "SIS G5", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 131, 185 }, QPageSize::Millimeter, "SIS G6", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 92, 131 }, QPageSize::Millimeter, "SIS G7", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 65, 92 }, QPageSize::Millimeter, "SIS G8", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 46, 65 }, QPageSize::Millimeter, "SIS G9", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 33, 46 }, QPageSize::Millimeter, "SIS G10", QPageSize::ExactMatch },

        QPageSize{ QSizeF{ 200, 290 }, QPageSize::Millimeter, "290mmX200mm",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 400, 566 }, QPageSize::Millimeter, "566mmX400mm",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 283, 400 }, QPageSize::Millimeter, "400mmX283mm",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 200, 283 }, QPageSize::Millimeter, "283mmX200mm",
                   QPageSize::ExactMatch },

        // No actual Formats just for fun and to put the US sizes even
        // more to the bottom
        QPageSize{ QSizeF{ 1.21754e+06, 1.72237e+06 }, QPageSize::Millimeter,
                   "2097152A0(2MA0) Not real", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 861184, 1.21754e+06 }, QPageSize::Millimeter, "1048576A0(1MA0) Not real",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 608768, 861184 }, QPageSize::Millimeter, "524288A0(512kA0) Not real",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 430592, 608768 }, QPageSize::Millimeter, "262144A0(256kA0) Not real",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 304384, 430592 }, QPageSize::Millimeter, "131072A0(128kA0) Not real",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 215296, 304384 }, QPageSize::Millimeter, "65536A0(64kA0) Not real",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 152192, 215296 }, QPageSize::Millimeter, "32768A0(32kA0) Not real",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 107648, 152192 }, QPageSize::Millimeter, "16384A0(16kA0) Not real",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 76096, 107648 }, QPageSize::Millimeter, "8192A0(8kA0) Not real",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 53824, 76096 }, QPageSize::Millimeter, "4096A0(4kA0) Not real",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 38048, 53824 }, QPageSize::Millimeter, "2048A0(2kA0) Not real",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 26912, 38048 }, QPageSize::Millimeter, "1024A0(1kA0) Not real",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 19024, 26912 }, QPageSize::Millimeter, "512A0 Not real",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 13456, 19024 }, QPageSize::Millimeter, "256A0 Not real",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 9512, 13456 }, QPageSize::Millimeter, "128A0 Not real",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 6728, 9512 }, QPageSize::Millimeter, "64A0 Not real",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 4756, 6728 }, QPageSize::Millimeter, "32A0 Not real",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 3364, 4756 }, QPageSize::Millimeter, "16A0 Not real",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 2378, 3364 }, QPageSize::Millimeter, "8A0 Not real",

                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 216, 279 }, QPageSize::Millimeter, "ANSI Y14.1 A (Letter)",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 279, 432 }, QPageSize::Millimeter, "ANSI Y14.1 B",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 432, 559 }, QPageSize::Millimeter, "ANSI Y14.1 C",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 559, 864 }, QPageSize::Millimeter, "ANSI Y14.1 D",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 864, 1118 }, QPageSize::Millimeter, "ANSI Y14.1 E",
                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 711, 1016 }, QPageSize::Millimeter, "ANSI Y14.1 F",

                   QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 216, 356 }, QPageSize::Millimeter, "Legal", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 279, 432 }, QPageSize::Millimeter, "Tabloid (Ledger)",
                   QPageSize::ExactMatch },

        QPageSize{ QSizeF{ 229, 305 }, QPageSize::Millimeter, "Arch A", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 305, 457 }, QPageSize::Millimeter, "Arch B", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 457, 610 }, QPageSize::Millimeter, "Arch C", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 610, 914 }, QPageSize::Millimeter, "Arch D", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 914, 1219 }, QPageSize::Millimeter, "Arch E", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 726, 1067 }, QPageSize::Millimeter, "Arch E1", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 660, 965 }, QPageSize::Millimeter, "Arch E2", QPageSize::ExactMatch },
        QPageSize{ QSizeF{ 686, 991 }, QPageSize::Millimeter, "Arch E3", QPageSize::ExactMatch },
    };

    ///
    /// \brief m_frames a list for selection the frame
    ///
    QList<QString> m_frames = QList<QString>{ "None", "Plain Frame", "ISO5457" };

    ///
    /// \brief m_titleBlocks a list for selecting the title-block
    ///
    QList<QString> m_titleBlocks =
            QList<QString>{ "None", "Plain TitleBlock", "ISO7200 Style A", "ISO7200 Style B" };

    ///
    /// \brief initPageSizes initialises the PageSice combobox with m_pagesizes
    ///
    void initPageSizes();
    ///
    /// \brief initFrames initialises the FrameComboBox with m_frames
    ///
    void initFrames();
    ///
    /// \brief initTitleBlocks initialises the TitleBlockComboBox with m_titleBlocks
    ///
    void initTitleBlocks();
    void initTitleBlockLanguages();
    ///
    /// \brief getPageSizeFromName returns the PageSize with a give size string
    /// \param name the size string
    /// \return
    ///
    QPageSize getPageSizeFromName(QString name);
    ///
    /// \brief getOrientationFromUi returns the page orientation depending on the PortraitCheckBox
    /// \return
    ///
    QPageLayout::Orientation getOrientationFromUi();
    ///
    /// \brief getDrawingFormates returns a List with all the Formates that should be created,
    /// depending witch are selected in the ui
    /// \return
    ///
    QList<DrawingFormate> getDrawingFormates();

    ///
    /// \brief m_lastPath saves the last path that was selected on generate
    ///
    QString m_lastPath = "./";

    ///
    /// \brief m_pageStyle is the pageStyle to be drawn
    ///
    std::shared_ptr<PageStyle> m_pageStyle;
    ///
    /// \brief m_frame is the Frame style to be drawn
    ///
    std::shared_ptr<PageFrame> m_frame;
    ///
    /// \brief m_titleblock is the TitleBlock style to be drawn
    ///
    std::shared_ptr<TitleBlock> m_titleblock;
};

#endif // MAINWINDOW_H
