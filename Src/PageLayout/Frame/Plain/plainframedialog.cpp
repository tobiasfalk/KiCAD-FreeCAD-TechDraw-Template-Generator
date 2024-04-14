#include "plainframedialog.h"
#include "ui_plainframedialog.h"

PlainFrameDialog::PlainFrameDialog(QWidget *parent)
    : QDialog(parent), m_ui(new Ui::PlainFrameDialog)
{
    m_ui->setupUi(this);
}

PlainFrameDialog::~PlainFrameDialog()
{
    delete m_ui;
}

std::shared_ptr<PlainFrame> PlainFrameDialog::getFrame()
{
    std::shared_ptr<PlainFrame> ret = std::make_shared<PlainFrame>();

    ret->setLineWidth(m_ui->LineWidthDoubleSpinBox->value());
    ret->setIndentBottom(m_ui->BottomDoubleSpinBox->value());
    ret->setIndentTop(m_ui->TopDoubleSpinBox->value());
    ret->setIndentLeft(m_ui->LeftDoubleSpinBox->value());
    ret->setIndentRigth(m_ui->RigthDoubleSpinBox->value());

    return ret;
}
