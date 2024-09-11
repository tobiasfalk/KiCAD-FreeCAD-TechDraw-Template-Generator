#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "PageLayout/Frame/pageframe.h"
#include "PageLayout/pagestyle.h"
#include "Threads/universaldrawthread.h"
#include "PageLayout/Frame/Plain/plainframedialog.h"
#include "PageLayout/TitleBlock/Plain/plaintitleblock.h"
#include "PageLayout/TitleBlock/Plain/plaintitleblockdialog.h"
#include "PageLayout/TitleBlock/ISO7200A/iso7200a.h"
#include "PageLayout/TitleBlock/ISO7200A/iso7200adialog.h"
#include "PageLayout/TitleBlock/ISO7200B/iso7200b.h"
#include "PageLayout/TitleBlock/ISO7200B/iso7200bdialog.h"
#include "PageLayout/Frame/ISO5457/iso5457frame.h"
#include "PageLayout/Frame/ISO5457/iso5457framedialog.h"
#include "PageLayout/FoldingLines/foldinglines.h"
#include "PageLayout/FoldingLines/DIN824ALike/din824alike.h"
#include "PageLayout/FoldingLines/DIN824CLike/din824clike.h"
#include "UniversalDraw/universaldraw.h"
#include <cstdlib>

UTGMainWindow::UTGMainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::UTGMainWindow)
{
    m_ui->setupUi(this);

    m_preView = std::make_shared<PreView>();
    m_pageStyle = std::make_shared<PageStyle>();
    m_frame = std::make_shared<PageFrame>();
    m_titleblock = std::make_shared<TitleBlock>();
    m_foldingLines = std::make_shared<FoldingLines>();
    updatePreView();

    m_ui->PreViewGridLayout->addWidget(m_preView.get());

    initPageSizes();
    initFrames();
    initTitleBlocks();
    initTitleBlockLanguages();
    initFoldingLineAlgs();
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
    pageStyle.setFoldingLines(m_foldingLines);

    pageStyle.setPageSize(getPageSizeFromName(m_ui->PageSizeComboBox->currentText()),
                          getOrientationFromUi());

    pageStyle.setShowEditable(m_ui->ShowEditTextCheckBox->isChecked());
    pageStyle.setFont(m_ui->FontLineEdit->text());

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
    // std::shared_ptr<FoldingLines> fold = std::make_shared<FoldingLines>();
    m_pageStyle->setFoldingLines(m_foldingLines);
    m_pageStyle->setFont(m_ui->FontLineEdit->text());
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
    } else

            if (framStr == "Plain Frame" && m_frame->type() == "Plain Frame") {
        auto shared_base = std::shared_ptr<PageFrame>{ std::move(m_frame) };
        std::shared_ptr<PlainFrame> tmp = std::static_pointer_cast<PlainFrame>(shared_base);
        m_frame = tmp;
    } else if (framStr == "Plain Frame" && m_frame->type() != "Plain Frame") {
        m_frame = std::make_shared<PlainFrame>();
    } else

            if (framStr == "ISO5457" && m_frame->type() == "ISO5457") {
        auto shared_base = std::shared_ptr<PageFrame>{ std::move(m_frame) };
        std::shared_ptr<ISO5457Frame> tmp = std::static_pointer_cast<ISO5457Frame>(
                shared_base); // std::make_shared<ISO5457Frame>();
        tmp->decideBottomAndTopCenteringLine(
                m_titleblock->titleBlockArea().width(), m_titleblock->titleBlockArea().height(),
                m_pageStyle->getLayout().fullRect(QPageLayout::Millimeter));
        m_frame = tmp;
    } else if (framStr == "ISO5457" && m_frame->type() != "ISO5457") {
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

void UTGMainWindow::updateFoldingLines(QString foldStr)
{
    if (foldStr == "None") {
        m_foldingLines = std::make_shared<FoldingLines>();
    } else if (foldStr == "DIN 824 A Like") {
        double depth = m_foldingLines->depth();
        m_foldingLines = std::make_shared<DIN824ALike>();
        m_foldingLines->setDepth(depth);
    } else if (foldStr == "DIN 824 C Like") {
        double depth = m_foldingLines->depth();
        m_foldingLines = std::make_shared<DIN824CLike>();
        m_foldingLines->setDepth(depth);
    }
    m_foldingLines->setToWhat(
            QPageLayout{ getPageSizeFromName(m_ui->FoldingLinesTagetComboBox->currentText()),
                         getFoldOrientationFromUi(), QMargins{ 0, 0, 0, 0 } });
    updatePreView();
}

void UTGMainWindow::updateFoldingLines()
{
    updateFoldingLines(m_ui->FoldingLineComboBox->currentText());
}

QList<QString> UTGMainWindow::sortedPageNames(QMap<QString, QPageSize> pageMap)
{
    QList<QString> ret;
    ret.append("User defined");
    QList<QPageSize> values = pageMap.values();
    QStringList names;
    int nmsSize = names.size();
    foreach (QPageSize page, values) {
        if (page.name() != "") {
            names.append(page.name());
        }
    }
    QStringList aSeries = names.filter(QRegularExpression{ "^[0-9]*A[0-9]" });
    // aSeries.append(names.filter(QRegularExpression{ "^A[0-9]" }));
    // aSeries.append(names.filter(QRegularExpression{ "[0-9]*^A[0-9]*\\+" }));
    // aSeries.append(names.filter(QRegularExpression{ "^A[0-9]*\\+" }));
    ret.append(aSeries);
    QStringList bSeries = names.filter(QRegularExpression{ "^[0-9]*B[0-9]" });
    // bSeries.append(names.filter(QRegularExpression{ "^B[0-9]" }));
    // bSeries.append(names.filter(QRegularExpression{ "[0-9]*^B[0-9]*\\+" }));
    // bSeries.append(names.filter(QRegularExpression{ "^B[0-9]*\\+" }));
    ret.append(bSeries);
    QStringList cSeries = names.filter(QRegularExpression{ "^[0-9]*C[0-9]" });
    // cSeries.append(names.filter(QRegularExpression{ "^C[0-9]" }));
    // cSeries.append(names.filter(QRegularExpression{ "[0-9]*^C[0-9]*\\+" }));
    // cSeries.append(names.filter(QRegularExpression{ "^C[0-9]*\\+" }));
    ret.append(cSeries);
    QStringList dSeries = names.filter(QRegularExpression{ "^[0-9]*D[0-9]" });
    // dSeries.append(names.filter(QRegularExpression{ "^D[0-9]" }));
    // dSeries.append(names.filter(QRegularExpression{ "[0-9]*^D[0-9]*\\+" }));
    // cSeries.append(names.filter(QRegularExpression{ "^D[0-9]*\\+" }));
    ret.append(dSeries);

    QStringList jbSeries = names.filter(QRegularExpression{ "^JB[0-9]" });
    ret.append(jbSeries);

    QStringList sisdSeries = names.filter(QRegularExpression{ "^SIS D[0-9]" });
    ret.append(sisdSeries);
    QStringList siseSeries = names.filter(QRegularExpression{ "^SIS E[0-9]" });
    ret.append(siseSeries);
    QStringList sisfSeries = names.filter(QRegularExpression{ "^SIS F[0-9]" });
    ret.append(sisfSeries);
    QStringList sisgSeries = names.filter(QRegularExpression{ "^SIS G[0-9]" });
    ret.append(sisgSeries);

    QStringList custom = names.filter(QRegularExpression{ "^([0-9]*mm)X([0-9]*mm)" });
    ret.append(custom);

    QStringList norRealASeries = names.filter(QRegularExpression{ "^Not real [0-9]*A[0-9]" });
    ret.append(norRealASeries);

    QStringList ansi = names.filter(QRegularExpression{ "^ANSI Y14.1 [ABCDEF]" });
    ret.append(ansi);
    QStringList arch = names.filter(QRegularExpression{ "^Arch [ABCDEF]" });
    ret.append(arch);
    ret.append("Letter");
    ret.append("Legal");
    ret.append("Tabloid");
    ret.append("Ledger");

    if (ret.size() != nmsSize) {
        foreach (QString nm, names) {
            if (!ret.contains(nm)) {
                ret.append(nm);
                qWarning() << "Not Sorted Paper Sizes: " << nm;
            }
        }
    }

    return ret;
}

void UTGMainWindow::initPageSizes()
{
    // sortedPageNames(m_pagesizes);
    // QList<QPageSize> values = m_pagesizes.values();
    // QStringList names;
    // foreach (QPageSize page, values) {
    //     if (page.name() != "") {
    //         names.append(page.name());
    //     }
    // }
    // names.sort();
    QList<QString> names = sortedPageNames(m_pagesizes);
    m_ui->PageSizeComboBox->clear();
    m_ui->FoldingLinesTagetComboBox->clear();
    foreach (QString nm, names) {
        m_ui->PageSizeComboBox->addItem(nm);
        m_ui->FoldingLinesTagetComboBox->addItem(nm);
    }
    m_ui->PageSizeComboBox->setCurrentText("User defined");
    m_ui->FoldingLinesTagetComboBox->setCurrentText("A4");
    m_ui->PageWidthDoubleSpinBox->setValue(
            m_pagesizes["User defined"].size(QPageSize::Millimeter).width());
    m_ui->PageHeigthDoubleSpinBox->setValue(
            m_pagesizes["User defined"].size(QPageSize::Millimeter).height());
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

void UTGMainWindow::initFoldingLineAlgs()
{
    m_ui->FoldingLineComboBox->clear();
    foreach (QString alg, m_foldingLineAlgs) {
        m_ui->FoldingLineComboBox->addItem(alg);
    }
}

QPageSize UTGMainWindow::getPageSizeFromName(QString name)
{
    // foreach (QPageSize page, m_pagesizes) {
    //     qDebug() << "Page Test: " << name << "==" << page << " => " << (name == page.name());
    //     if (name == page.name()) {
    //         qDebug() << "Page Found: " << page;
    //         return page;
    //     }
    // }
    // return QPageSize{ QSizeF{ 420, 297 }, QPageSize::Millimeter, "Error", QPageSize::ExactMatch
    // };
    return m_pagesizes[name];
}

QPageLayout::Orientation UTGMainWindow::getOrientationFromUi()
{
    if (m_ui->PortraitCheckBox->isChecked()) {
        return QPageLayout::Orientation::Portrait;
    } else {
        return QPageLayout::Orientation::Landscape;
    }
}

QPageLayout::Orientation UTGMainWindow::getFoldOrientationFromUi()
{
    if (m_ui->FoldingKinesTargetPortraitCheckBox->isChecked()) {
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

    if (m_ui->HtmlCheckBox->isChecked()) {
        ret.append(DrawingFormate::Html);
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
    updateFoldingLines();
    updatePreView();
}

void UTGMainWindow::on_PageWidthDoubleSpinBox_valueChanged(double width)
{
    m_pagesizes["User defined"] =
            QPageSize{ QSizeF{ width, m_ui->PageHeigthDoubleSpinBox->value() },
                       QPageSize::Millimeter, m_ui->NameLineEdit->text(), QPageSize::ExactMatch };

    updateFrame();
    updateFoldingLines();
    updatePreView();
}

void UTGMainWindow::on_PageHeigthDoubleSpinBox_valueChanged(double height)
{
    m_pagesizes["User defined"] =
            QPageSize{ QSizeF{ m_ui->PageWidthDoubleSpinBox->value(), height },
                       QPageSize::Millimeter, m_ui->NameLineEdit->text(), QPageSize::ExactMatch };

    updateFrame();
    updateFoldingLines();
    updatePreView();
}

void UTGMainWindow::on_NameLineEdit_editingFinished()
{
    m_pagesizes[0] =
            QPageSize{ QSizeF{ m_ui->PageWidthDoubleSpinBox->value(),
                               m_ui->PageHeigthDoubleSpinBox->value() },
                       QPageSize::Millimeter, m_ui->NameLineEdit->text(), QPageSize::ExactMatch };
    updatePreView();
}

void UTGMainWindow::on_framePushButton_clicked()
{
    if (m_frame->type() == "Plain Frame") {
        PlainFrameDialog frameDialog;

        auto shared_base = std::shared_ptr<PageFrame>{ std::move(m_frame) };
        std::shared_ptr<PlainFrame> tmp = std::static_pointer_cast<PlainFrame>(shared_base);

        frameDialog.setFrame(tmp);

        // frameDialog.setFrame(m_frame);

        // frameDialog.show();
        frameDialog.setModal(true);
        frameDialog.exec();

        m_frame = frameDialog.frame();
    } else if (m_frame->type() == "ISO5457") {
        ISO5457FrameDialog dialog;

        auto shared_base = std::shared_ptr<PageFrame>{ std::move(m_frame) };
        std::shared_ptr<ISO5457Frame> tmp = std::static_pointer_cast<ISO5457Frame>(shared_base);

        dialog.setFrame(tmp);

        dialog.setModal(true);
        dialog.exec();

        m_frame = dialog.frame();
    }
    updateFrame();
    updateFoldingLines();
    updatePreView();
}

void UTGMainWindow::on_FrameComboBox_currentTextChanged(const QString &arg1)
{
    updateFrame(arg1);
    updatePreView();
}

void UTGMainWindow::on_TitleBlockComboBox_currentTextChanged(const QString &arg1)
{
    m_frame->setNoDrawingAreaIndent(false);
    if (arg1 == "None") {
        m_titleblock = std::make_shared<TitleBlock>();
    } else if (arg1 == "Plain TitleBlock") {
        m_titleblock = std::make_shared<PlainTitleBlock>();
    } else if (arg1 == "ISO7200 Style A") {
        if (m_titleblock->type() == "ISO7200 Style A") {

            auto shared_base = std::shared_ptr<TitleBlock>{ std::move(m_titleblock) };
            std::shared_ptr<ISO7200A> tmp = std::static_pointer_cast<ISO7200A>(shared_base);

            m_titleblock = tmp;
        } else {
            m_titleblock = std::make_shared<ISO7200A>();
        }
    } else if (arg1 == "ISO7200 Style B") {
        m_titleblock = std::make_shared<ISO7200B>();
    }
    updateFrame();
    initTitleBlockLanguages();
    updateFoldingLines();
    updatePreView();
}

void UTGMainWindow::on_TitleBlockPushButton_clicked()
{
    if (m_titleblock->type() == "Plain TitleBlock") {
        PlainTitleBlockDialog dialog;

        dialog.setModal(true);
        dialog.exec();

        m_titleblock = dialog.titleBlock();
    } else if (m_titleblock->type() == "ISO7200 Style A") {
        ISO7200ADialog dialog;

        auto shared_base = std::shared_ptr<TitleBlock>{ std::move(m_titleblock) };
        std::shared_ptr<ISO7200A> tmp = std::static_pointer_cast<ISO7200A>(shared_base);

        dialog.setTitleBlock(tmp);

        dialog.setModal(true);
        dialog.exec();

        m_titleblock = tmp; // dialog.titleBlock();
        m_ui->TitleBlLanguageComboBox->setCurrentText(m_titleblock->language());
    } else if (m_titleblock->type() == "ISO7200 Style B") {
        ISO7200BDialog dialog;

        auto shared_base = std::shared_ptr<TitleBlock>{ std::move(m_titleblock) };
        std::shared_ptr<ISO7200B> tmp = std::static_pointer_cast<ISO7200B>(shared_base);

        dialog.setTitleBlock(tmp);

        dialog.setModal(true);
        dialog.exec();

        m_titleblock = tmp; // dialog.titleBlock();
        m_ui->TitleBlLanguageComboBox->setCurrentText(m_titleblock->language());
    }
    updateFrame();
    updateFoldingLines();
    updatePreView();
}

void UTGMainWindow::on_TitleBlLanguageComboBox_currentTextChanged(const QString &arg1)
{
    m_titleblock->setLanguage(arg1);
    updatePreView();
}

void UTGMainWindow::on_FoldingLineComboBox_currentTextChanged(const QString &arg1)
{
    updateFoldingLines(arg1);
    updatePreView();
}

void UTGMainWindow::on_FoldingLinesTagetComboBox_currentTextChanged(const QString &arg1)
{
    updateFoldingLines();
    updatePreView();
}

void UTGMainWindow::on_PortraitCheckBox_stateChanged(int arg1)
{
    updateFrame();
    updateFoldingLines();
    updatePreView();
}

void UTGMainWindow::on_FoldingKinesTargetPortraitCheckBox_stateChanged(int arg1)
{
    updateFrame();
    updateFoldingLines();
    updatePreView();
}

void UTGMainWindow::on_updatePushButton_clicked()
{
    updateFrame();
    updateFoldingLines();
    updatePreView();
}

void UTGMainWindow::on_FoldingLineDepthDoubleSpinBox_editingFinished()
{
    m_foldingLines->setDepth(m_ui->FoldingLineDepthDoubleSpinBox->value());
    updateFrame();
    updateFoldingLines();
    updatePreView();
}

void UTGMainWindow::on_FoldingLineDepthDoubleSpinBox_valueChanged(double arg1)
{
    m_foldingLines->setDepth(arg1);
    updateFrame();
    updateFoldingLines();
    updatePreView();
}

void UTGMainWindow::on_FontLineEdit_textChanged(const QString &arg1)
{
    updateFrame();
    updateFoldingLines();
    updatePreView();
}
