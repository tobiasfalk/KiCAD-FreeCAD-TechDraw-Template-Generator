#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "PageLayout/Frame/pageframe.h"
#include "PageLayout/pagestyle.h"
#include "Threads/universaldrawthread.h"
#include "PageLayout/Frame/Plain/plainframedialog.h"
#include "PageLayout/TitleBlock/Plain/plaintitleblock.h"
#include "PageLayout/TitleBlock/Plain/plaintitleblockdialog.h"
#include "PageLayout/TitleBlock/ISO7200A/iso7200a.h"
#include "PageLayout/TitleBlock/ISO7200B/iso7200b.h"
#include "PageLayout/Frame/ISO5457/iso5457frame.h"
#include "UniversalDraw/universaldraw.h"
#include <cstdlib>

UTGMainWindow::UTGMainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::UTGMainWindow)
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
    initTitleBlockLanguages();
}

UTGMainWindow::~UTGMainWindow()
{
    delete m_ui;
}

void UTGMainWindow::on_GeneratePushButton_clicked()
{
    PageStyle pageStyle;

    pageStyle.setFrame(m_frame);
    pageStyle.setTitleblocke(m_titleblock);

    pageStyle.setPageSize(getPageSizeFromName(m_ui->PageSizeComboBox->currentText()),
                          getOrientationFromUi());

    QString path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), m_lastPath,
                                                     QFileDialog::ShowDirsOnly
                                                             | QFileDialog::DontResolveSymlinks);
    if (path.isEmpty()) {
        return;
    }

    m_lastPath = path;

    UniversalDrawThread *thread = new UniversalDrawThread(
            m_lastPath + "/" + m_ui->fileNameLineEdit->text(), pageStyle, getDrawingFormates());

    connect(thread, &UniversalDrawThread::resultReady, this, &UTGMainWindow::handleResults);

    thread->start();
}

void UTGMainWindow::handleResults(UniversalDrawThread *thread)
{
    delete thread;
}

void UTGMainWindow::resizeEvent(QResizeEvent *event)
{
    m_preView->setMinimumWidth(m_ui->centralwidget->size().width() - 800);
    QWidget::resizeEvent(event);
}

void UTGMainWindow::updatePreView()
{
    m_pageStyle->setPageSize(getPageSizeFromName(m_ui->PageSizeComboBox->currentText()),
                             getOrientationFromUi());
    m_pageStyle->setFrame(m_frame);
    m_pageStyle->setTitleblocke(m_titleblock);
    m_preView->setPageStyle(m_pageStyle);
    m_preView->update();
}

void UTGMainWindow::updateFrame(QString framStr)
{
    m_pageStyle->setPageSize(getPageSizeFromName(m_ui->PageSizeComboBox->currentText()),
                             getOrientationFromUi());
    bool indent = m_frame->noDrawingAreaIndent();
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
    m_frame->setNoDrawingAreaIndent(indent);
    updatePreView();
}

void UTGMainWindow::updateFrame()
{
    updateFrame(m_ui->FrameComboBox->currentText());
}

void UTGMainWindow::initPageSizes()
{
    foreach (QPageSize page, m_pagesizes) {
        m_ui->PageSizeComboBox->addItem(page.name());
    }
    m_ui->PageWidthDoubleSpinBox->setValue(m_pagesizes[0].size(QPageSize::Millimeter).width());
    m_ui->PageHeigthDoubleSpinBox->setValue(m_pagesizes[0].size(QPageSize::Millimeter).height());
}

void UTGMainWindow::initFrames()
{
    foreach (QString frameStr, m_frames) {
        m_ui->FrameComboBox->addItem(frameStr);
    }
}

void UTGMainWindow::initTitleBlocks()
{
    foreach (QString titleBlockStr, m_titleBlocks) {
        m_ui->TitleBlockComboBox->addItem(titleBlockStr);
    }
}

void UTGMainWindow::initTitleBlockLanguages()
{
    m_ui->TitleBlLanguageComboBox->clear();
    QList<QString> langs = m_titleblock->languages();
    foreach (QString lan, langs) {
        m_ui->TitleBlLanguageComboBox->addItem(lan);
    }
}

QPageSize UTGMainWindow::getPageSizeFromName(QString name)
{
    foreach (QPageSize page, m_pagesizes) {
        if (name == page.name()) {
            return page;
        }
    }
    return QPageSize{ QSizeF{ 420, 297 }, QPageSize::Millimeter, "A3", QPageSize::ExactMatch };
}

QPageLayout::Orientation UTGMainWindow::getOrientationFromUi()
{
    if (m_ui->PortraitCheckBox->isChecked()) {
        return QPageLayout::Orientation::Portrait;
    } else {
        return QPageLayout::Orientation::Landscape;
    }
}

QList<DrawingFormate> UTGMainWindow::getDrawingFormates()
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

void UTGMainWindow::on_PageSizeComboBox_currentTextChanged(const QString &name)
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

void UTGMainWindow::on_PageWidthDoubleSpinBox_valueChanged(double width)
{
    m_pagesizes[0] =
            QPageSize{ QSizeF{ width, m_ui->PageHeigthDoubleSpinBox->value() },
                       QPageSize::Millimeter, m_ui->NameLineEdit->text(), QPageSize::ExactMatch };

    updateFrame();
    updatePreView();
}

void UTGMainWindow::on_PageHeigthDoubleSpinBox_valueChanged(double height)
{
    m_pagesizes[0] =
            QPageSize{ QSizeF{ m_ui->PageWidthDoubleSpinBox->value(), height },
                       QPageSize::Millimeter, m_ui->NameLineEdit->text(), QPageSize::ExactMatch };

    updateFrame();
    updatePreView();
}

void UTGMainWindow::on_NameLineEdit_editingFinished()
{
    m_pagesizes[0] =
            QPageSize{ QSizeF{ m_ui->PageWidthDoubleSpinBox->value(),
                               m_ui->PageHeigthDoubleSpinBox->value() },
                       QPageSize::Millimeter, m_ui->NameLineEdit->text(), QPageSize::ExactMatch };
}

void UTGMainWindow::on_framePushButton_clicked()
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

void UTGMainWindow::on_FrameComboBox_currentTextChanged(const QString &arg1)
{
    updateFrame(arg1);
}

void UTGMainWindow::on_TitleBlockComboBox_currentTextChanged(const QString &arg1)
{
    m_frame->setNoDrawingAreaIndent(false);
    if (arg1 == "None") {
        m_titleblock = std::make_shared<TitleBlock>();
    } else if (arg1 == "Plain TitleBlock") {
        m_titleblock = std::make_shared<PlainTitleBlock>();
    } else if (arg1 == "ISO7200 Style A") {
        m_titleblock = std::make_shared<ISO7200A>();
    } else if (arg1 == "ISO7200 Style B") {
        m_titleblock = std::make_shared<ISO7200B>();
    }
    updateFrame();
    updatePreView();
    initTitleBlockLanguages();
}

void UTGMainWindow::on_TitleBlockPushButton_clicked()
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

void UTGMainWindow::on_TitleBlLanguageComboBox_currentTextChanged(const QString &arg1)
{
    m_titleblock->setLanguage(arg1);
    updatePreView();
}
