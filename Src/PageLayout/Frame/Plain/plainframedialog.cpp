#include "plainframedialog.h"
#include "ui_plainframedialog.h"

PlainFrameDialog::PlainFrameDialog(QWidget *parent)
    : QDialog(parent), m_ui(new Ui::PlainFrameDialog)
{
    m_ui->setupUi(this);
    m_frame = std::make_shared<PlainFrame>();
}

PlainFrameDialog::~PlainFrameDialog()
{
    delete m_ui;
}

void PlainFrameDialog::setFrame(std::shared_ptr<PlainFrame> newFrame)
{
    m_ui->LineWidthDoubleSpinBox->setValue(newFrame->lineWidth());
    m_ui->BottomDoubleSpinBox->setValue(newFrame->indentBottom());
    m_ui->TopDoubleSpinBox->setValue(newFrame->indentTop());
    m_ui->LeftDoubleSpinBox->setValue(newFrame->indentLeft());
    m_ui->RigthDoubleSpinBox->setValue(newFrame->indentRigth());
    m_frame = newFrame;
}

std::shared_ptr<PlainFrame> PlainFrameDialog::getFrame()
{
    m_frame->setLineWidth(m_ui->LineWidthDoubleSpinBox->value());
    m_frame->setIndentBottom(m_ui->BottomDoubleSpinBox->value());
    m_frame->setIndentTop(m_ui->TopDoubleSpinBox->value());
    m_frame->setIndentLeft(m_ui->LeftDoubleSpinBox->value());
    m_frame->setIndentRigth(m_ui->RigthDoubleSpinBox->value());

    return m_frame;
}

void PlainFrameDialog::on_LineWidthDoubleSpinBox_editingFinished()
{
    m_frame->setLineWidth(m_ui->LineWidthDoubleSpinBox->value());
    m_frame->setIndentBottom(m_ui->BottomDoubleSpinBox->value());
    m_frame->setIndentTop(m_ui->TopDoubleSpinBox->value());
    m_frame->setIndentLeft(m_ui->LeftDoubleSpinBox->value());
    m_frame->setIndentRigth(m_ui->RigthDoubleSpinBox->value());
}

void PlainFrameDialog::on_TopDoubleSpinBox_editingFinished()
{
    m_frame->setLineWidth(m_ui->LineWidthDoubleSpinBox->value());
    m_frame->setIndentBottom(m_ui->BottomDoubleSpinBox->value());
    m_frame->setIndentTop(m_ui->TopDoubleSpinBox->value());
    m_frame->setIndentLeft(m_ui->LeftDoubleSpinBox->value());
    m_frame->setIndentRigth(m_ui->RigthDoubleSpinBox->value());
}

void PlainFrameDialog::on_RigthDoubleSpinBox_editingFinished()
{
    m_frame->setLineWidth(m_ui->LineWidthDoubleSpinBox->value());
    m_frame->setIndentBottom(m_ui->BottomDoubleSpinBox->value());
    m_frame->setIndentTop(m_ui->TopDoubleSpinBox->value());
    m_frame->setIndentLeft(m_ui->LeftDoubleSpinBox->value());
    m_frame->setIndentRigth(m_ui->RigthDoubleSpinBox->value());
}

void PlainFrameDialog::on_LeftDoubleSpinBox_editingFinished()
{
    m_frame->setLineWidth(m_ui->LineWidthDoubleSpinBox->value());
    m_frame->setIndentBottom(m_ui->BottomDoubleSpinBox->value());
    m_frame->setIndentTop(m_ui->TopDoubleSpinBox->value());
    m_frame->setIndentLeft(m_ui->LeftDoubleSpinBox->value());
    m_frame->setIndentRigth(m_ui->RigthDoubleSpinBox->value());
}

void PlainFrameDialog::on_BottomDoubleSpinBox_editingFinished()
{
    m_frame->setLineWidth(m_ui->LineWidthDoubleSpinBox->value());
    m_frame->setIndentBottom(m_ui->BottomDoubleSpinBox->value());
    m_frame->setIndentTop(m_ui->TopDoubleSpinBox->value());
    m_frame->setIndentLeft(m_ui->LeftDoubleSpinBox->value());
    m_frame->setIndentRigth(m_ui->RigthDoubleSpinBox->value());
}
