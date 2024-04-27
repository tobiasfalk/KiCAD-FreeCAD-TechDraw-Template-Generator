#include "iso5457framedialog.h"
#include "ui_iso5457framedialog.h"

ISO5457FrameDialog::ISO5457FrameDialog(QWidget *parent)
    : QDialog(parent), m_ui(new Ui::ISO5457FrameDialog)
{
    m_ui->setupUi(this);
    m_frame = std::make_shared<ISO5457Frame>();
}

ISO5457FrameDialog::~ISO5457FrameDialog()
{
    delete m_ui;
}

std::shared_ptr<ISO5457Frame> ISO5457FrameDialog::frame() const
{
    qDebug() << "A";
    m_frame->setShowPageSize(m_ui->pageSizeCheckBox->isChecked());
    qDebug() << "B" << m_frame->showPageSize();
    m_frame->setShowTrimmingMarks(m_ui->trimmingCheckBox->isChecked());
    qDebug() << "C" << m_frame->showTrimmingMarks();
    return m_frame;
}

void ISO5457FrameDialog::setFrame(const std::shared_ptr<ISO5457Frame> &newFrame)
{
    m_frame = newFrame;
    m_ui->pageSizeCheckBox->setChecked(m_frame->showPageSize());
    m_ui->trimmingCheckBox->setChecked(m_frame->showTrimmingMarks());
}
