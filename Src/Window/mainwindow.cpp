#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "PageLayout/Frame/pageframe.h"
#include "PageLayout/pagestyle.h"
#include "Threads/universaldrawthread.h"
#include "PageLayout/Frame/Plain/plainframedialog.h"
#include "PageLayout/TitleBlock/Plain/plaintitleblock.h"
#include "PageLayout/TitleBlock/Plain/plaintitleblockdialog.h"
#include "PageLayout/Frame/ISO5457/iso5457frame.h"
#include "UniversalDraw/universaldraw.h"
#include <cstdlib>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    m_preView = std::make_shared<PreView>();
    m_pageStyle = std::make_shared<PageStyle>();
    m_frame = std::make_shared<PageFrame>();
    m_titleblock = std::make_shared<TitleBlock>();
    updatePreView();

    m_ui->PreViewGridLayout->addWidget(m_preView.get());

    initPageSizes();
    initFrames();
    initTitleBlocks();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::on_GeneratePushButton_clicked()
{
    PageStyle pageStyle;

    pageStyle.setFrame(m_frame);
    pageStyle.setTitleblocke(m_titleblock);

    pageStyle.setPageSize(getPageSizeFromName(m_ui->PageSizeComboBox->currentText()),
                          getOrientationFromUi());

    // qDebug() << pageStyle;

    QString path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), m_lastPath,
                                                     QFileDialog::ShowDirsOnly
                                                             | QFileDialog::DontResolveSymlinks);
    if (path.isEmpty()) {
        return;
    }

    m_lastPath = path;

    UniversalDrawThread *thread = new UniversalDrawThread(
            m_lastPath + "/" + m_ui->fileNameLineEdit->text(), pageStyle, getDrawingFormates());

    connect(thread, &UniversalDrawThread::resultReady, this, &MainWindow::handleResults);

    thread->start();
}

void MainWindow::handleResults(UniversalDrawThread *thread)
{
    // qDebug() << thread->fileName();
    delete thread;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_preView->setMinimumWidth(m_ui->centralwidget->size().width() - 800);
    QWidget::resizeEvent(event);
}

void MainWindow::updatePreView()
{
    m_pageStyle->setPageSize(getPageSizeFromName(m_ui->PageSizeComboBox->currentText()),
                             getOrientationFromUi());
    m_pageStyle->setFrame(m_frame);
    m_pageStyle->setTitleblocke(m_titleblock);
    m_preView->setPageStyle(m_pageStyle);
    m_preView->update();
}

void MainWindow::updateFrame(QString framStr)
{
    m_pageStyle->setPageSize(getPageSizeFromName(m_ui->PageSizeComboBox->currentText()),
                             getOrientationFromUi());
    if (framStr == "None") {
        m_frame = std::make_shared<PageFrame>();
    } else if (framStr == "Plain Frame") {
        m_frame = std::make_shared<PlainFrame>();
    } else if (framStr == "ISO5457") {
        std::shared_ptr<ISO5457Frame> tmp = std::make_shared<ISO5457Frame>();
        tmp->decideBottomAndTopCenteringLine(
                m_titleblock->titleBlockArea().width(), m_titleblock->titleBlockArea().height(),
                m_pageStyle->getLayout().fullRect(QPageLayout::Millimeter));
        m_frame = tmp;
    }
    updatePreView();
}

void MainWindow::updateFrame()
{
    updateFrame(m_ui->FrameComboBox->currentText());
}

void MainWindow::initPageSizes()
{
    foreach (QPageSize page, m_pagesizes) {
        m_ui->PageSizeComboBox->addItem(page.name());
    }
    m_ui->PageWidthDoubleSpinBox->setValue(m_pagesizes[0].size(QPageSize::Millimeter).width());
    m_ui->PageHeigthDoubleSpinBox->setValue(m_pagesizes[0].size(QPageSize::Millimeter).height());
}

void MainWindow::initFrames()
{
    foreach (QString frameStr, m_frames) {
        m_ui->FrameComboBox->addItem(frameStr);
    }
}

void MainWindow::initTitleBlocks()
{
    foreach (QString titleBlockStr, m_titleBlocks) {
        m_ui->TitleBlockComboBox->addItem(titleBlockStr);
    }
}

QPageSize MainWindow::getPageSizeFromName(QString name)
{
    foreach (QPageSize page, m_pagesizes) {
        if (name == page.name()) {
            return page;
        }
    }
    return QPageSize{ QSizeF{ 420, 297 }, QPageSize::Millimeter, "A3", QPageSize::ExactMatch };
}

QPageLayout::Orientation MainWindow::getOrientationFromUi()
{
    if (m_ui->PortraitCheckBox->isChecked()) {
        return QPageLayout::Orientation::Portrait;
    } else {
        return QPageLayout::Orientation::Landscape;
    }
}

QList<DrawingFormate> MainWindow::getDrawingFormates()
{
    QList<DrawingFormate> ret;

    if (m_ui->FreeCADsvgCheckBox->isChecked()) {
        ret.append(DrawingFormate::FreeCADSvg);
    }

    if (m_ui->KiCAD8CheckBox->isChecked()) {
        ret.append(DrawingFormate::KiCAD8);
    }

    if (m_ui->QtPdfCheckBox->isChecked()) {
        ret.append(DrawingFormate::PdfQtPaint);
    }

    if (m_ui->QtSvgCheckBox->isChecked()) {
        ret.append(DrawingFormate::SvgQtPaint);
    }

    if (m_ui->SvgCheckBox->isChecked()) {
        ret.append(DrawingFormate::Svg);
    }

    return ret;
}

void MainWindow::on_PageSizeComboBox_currentTextChanged(const QString &name)
{
    QPageSize page = getPageSizeFromName(name);
    m_ui->PageWidthDoubleSpinBox->setValue(page.size(QPageSize::Millimeter).width());
    m_ui->PageHeigthDoubleSpinBox->setValue(page.size(QPageSize::Millimeter).height());
    m_ui->NameLineEdit->setText(page.name());
    m_ui->fileNameLineEdit->setText(page.name().replace(" ", "_") + "_template");
    if (name == "User defined") {
        m_ui->PageWidthDoubleSpinBox->setEnabled(true);
        m_ui->PageHeigthDoubleSpinBox->setEnabled(true);
        m_ui->NameLineEdit->setEnabled(true);
    } else {
        m_ui->PageWidthDoubleSpinBox->setEnabled(false);
        m_ui->PageHeigthDoubleSpinBox->setEnabled(false);
        m_ui->NameLineEdit->setEnabled(false);
    }

    updateFrame();
    updatePreView();
}

void MainWindow::on_PageWidthDoubleSpinBox_valueChanged(double width)
{
    m_pagesizes[0] =
            QPageSize{ QSizeF{ width, m_ui->PageHeigthDoubleSpinBox->value() },
                       QPageSize::Millimeter, m_ui->NameLineEdit->text(), QPageSize::ExactMatch };
}

void MainWindow::on_PageHeigthDoubleSpinBox_valueChanged(double height)
{
    m_pagesizes[0] =
            QPageSize{ QSizeF{ m_ui->PageWidthDoubleSpinBox->value(), height },
                       QPageSize::Millimeter, m_ui->NameLineEdit->text(), QPageSize::ExactMatch };
}

void MainWindow::on_NameLineEdit_editingFinished()
{
    m_pagesizes[0] =
            QPageSize{ QSizeF{ m_ui->PageWidthDoubleSpinBox->value(),
                               m_ui->PageHeigthDoubleSpinBox->value() },
                       QPageSize::Millimeter, m_ui->NameLineEdit->text(), QPageSize::ExactMatch };
}

void MainWindow::on_framePushButton_clicked()
{
    if (m_frame->type() == "Plain Frame") {
        PlainFrameDialog frameDialog;

        // frameDialog.setFrame(m_frame);

        // frameDialog.show();
        frameDialog.setModal(true);
        frameDialog.exec();

        m_frame = frameDialog.frame();
    }
    updateFrame();
    updatePreView();
}

void MainWindow::on_FrameComboBox_currentTextChanged(const QString &arg1)
{
    updateFrame(arg1);
}

void MainWindow::on_TitleBlockComboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "None") {
        m_titleblock = std::make_shared<TitleBlock>();
    } else if (arg1 == "Plain TitleBlock") {
        m_titleblock = std::make_shared<PlainTitleBlock>();
    }
    updateFrame();
    updatePreView();
}

void MainWindow::on_TitleBlockPushButton_clicked()
{
    if (m_titleblock->type() == "Plain TitleBlock") {
        PlainTitleBlockDialog dialog;

        dialog.setModal(true);
        dialog.exec();

        m_titleblock = dialog.titleBlock();
    }
    updateFrame();
    updatePreView();
}
