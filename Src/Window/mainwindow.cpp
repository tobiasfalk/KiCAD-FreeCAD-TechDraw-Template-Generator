#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Plain/plainframe.h"
#include "pageframe.h"
#include "pagestyle.h"
#include "Plain/plainframe.h"
#include "universaldrawthread.h"
#include "Plain/plainframedialog.h"
#include "universaldraw.h"
#include <cstdlib>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    qDebug() << "Nope";

    m_preView = std::make_shared<PreView>();
    qDebug() << "Nope A";
    m_pageStyle = std::make_shared<PageStyle>();
    qDebug() << "Nope B";
    m_pageStyle->setPageSize(
            QPageSize{ QSizeF{ 210, 297 }, QPageSize::Millimeter, "A4", QPageSize::ExactMatch },
            QPageLayout::Orientation::Landscape);
    m_frame = std::make_shared<PlainFrame>();
    m_pageStyle->setFrame(m_frame);

    qDebug() << "Nope C";
    m_preView->setPageStyle(m_pageStyle);
    qDebug() << "Nope D";

    m_ui->PreViewGridLayout->addWidget(m_preView.get());
    qDebug() << "Nope E";

    initPageSizes();
    qDebug() << "Nope F";
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::on_GeneratePushButton_clicked()
{
    PageStyle pageStyle;

    PlainFrameDialog frameDialog;

    frameDialog.show();

    std::shared_ptr<PageFrame> frame = frameDialog.getFrame();

    pageStyle.setFrame(frame);

    pageStyle.setPageSize(getPageSizeFromName(m_ui->PageSizeComboBox->currentText()),
                          getOrientationFromUi());

    // qDebug() << pageStyle;

    m_lastPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), m_lastPath,
                                                   QFileDialog::ShowDirsOnly
                                                           | QFileDialog::DontResolveSymlinks);

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

void MainWindow::initPageSizes()
{
    foreach (QPageSize page, m_pagesizes) {
        m_ui->PageSizeComboBox->addItem(page.name());
    }
    m_ui->PageWidthDoubleSpinBox->setValue(m_pagesizes[0].size(QPageSize::Millimeter).width());
    m_ui->PageHeigthDoubleSpinBox->setValue(m_pagesizes[0].size(QPageSize::Millimeter).height());
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

void MainWindow::on_pushButton_clicked()
{
    PlainFrameDialog frameDialog;

    frameDialog.show();
}
