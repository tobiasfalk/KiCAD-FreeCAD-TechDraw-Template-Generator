#include "plaintitleblockdialog.h"
#include "ui_plaintitleblockdialog.h"

PlainTitleBlockDialog::PlainTitleBlockDialog(QWidget *parent)
    : QDialog(parent), m_ui(new Ui::PlainTitleBlockDialog)
{
    m_ui->setupUi(this);
    m_titleBlock = std::make_shared<PlainTitleBlock>();
}

PlainTitleBlockDialog::~PlainTitleBlockDialog()
{
    delete m_ui;
}

const std::shared_ptr<PlainTitleBlock> &PlainTitleBlockDialog::titleBlock() const
{
    m_titleBlock->setHeight(m_ui->heigthDoubleSpinBox->value());
    m_titleBlock->setWidth(m_ui->widthDoubleSpinBox->value());
    return m_titleBlock;
}

void PlainTitleBlockDialog::setTitleBlock(const std::shared_ptr<PlainTitleBlock> &newTitleBlock)
{
    m_ui->heigthDoubleSpinBox->setValue(newTitleBlock->height());
    m_ui->widthDoubleSpinBox->setValue(newTitleBlock->width());
    m_titleBlock = newTitleBlock;
}
