#include "iso7200adialog.h"
#include "ui_iso7200adialog.h"

ISO7200ADialog::ISO7200ADialog(QWidget *parent) : QDialog(parent), m_ui(new Ui::ISO7200ADialog)
{
    m_ui->setupUi(this);
    setTitleBlock(std::make_shared<ISO7200A>());
}

ISO7200ADialog::~ISO7200ADialog()
{
    delete m_ui;
}

std::shared_ptr<ISO7200A> ISO7200ADialog::titleBlock() const
{
    return m_titleBlock;
}

void ISO7200ADialog::setTitleBlock(const std::shared_ptr<ISO7200A> &newTitleBlock)
{
    m_titleBlock = newTitleBlock;

    m_ui->languageComboBox->clear();
    m_ui->fieldComboBox->clear();

    // initLanguge Combobox
    foreach (QString lan, m_titleBlock->languages()) {
        m_ui->languageComboBox->addItem(lan);
    }
    m_titleBlock->setLanguage(m_ui->languageComboBox->currentText());

    // init Field ComboBox
    foreach (QString key, m_titleBlock->currentLanguage().keys()) {
        m_ui->fieldComboBox->addItem(key);
    }
}

void ISO7200ADialog::initLanguages() { }

void ISO7200ADialog::on_fieldComboBox_currentTextChanged(const QString &arg1)
{
    m_ui->lableLineEdit->setText(m_titleBlock->currentLanguage()[arg1].lable);
    m_ui->textLineEdit->setText(m_titleBlock->currentLanguage()[arg1].text);
    m_ui->isEditableCheckBox->setChecked(m_titleBlock->currentLanguage()[arg1].isEditable);
}

void ISO7200ADialog::on_lableLineEdit_textEdited(const QString &arg1)
{
    // std::shared_ptr<QMap<QString, QMap<QString, ISO7200ATextStruct>>> tmp1 =
    //         m_titleBlock->languageTexts();
    // QMap<QString, ISO7200ATextStruct> tmp2 = tmp1->value(m_ui->languageComboBox->currentText());
    // tmp2[m_ui->fieldComboBox->currentText()].lable = arg1;
    // tmp1->remove(m_ui->languageComboBox->currentText());
    // tmp1->insert(m_ui->languageComboBox->currentText(), tmp2);
    // m_titleBlock->updateCurrentLanguage();
    // qDebug() << "L1: " <<
    // m_titleBlock->currentLanguage()[m_ui->fieldComboBox->currentText()].lable;
}

void ISO7200ADialog::on_lableLineEdit_textChanged(const QString &arg1)
{
    std::shared_ptr<QMap<QString, QMap<QString, ISO7200ATextStruct>>> tmp1 =
            m_titleBlock->languageTexts();
    QMap<QString, ISO7200ATextStruct> tmp2 = tmp1->value(m_ui->languageComboBox->currentText());
    tmp2[m_ui->fieldComboBox->currentText()].lable = arg1;
    tmp1->remove(m_ui->languageComboBox->currentText());
    tmp1->insert(m_ui->languageComboBox->currentText(), tmp2);
    m_titleBlock->updateCurrentLanguage();
    qDebug() << "Lable: "
             << m_titleBlock->currentLanguage()[m_ui->fieldComboBox->currentText()].lable;
}

void ISO7200ADialog::on_textLineEdit_textEdited(const QString &arg1)
{
    std::shared_ptr<QMap<QString, QMap<QString, ISO7200ATextStruct>>> tmp1 =
            m_titleBlock->languageTexts();
    QMap<QString, ISO7200ATextStruct> tmp2 = tmp1->value(m_ui->languageComboBox->currentText());
    tmp2[m_ui->fieldComboBox->currentText()].text = arg1;
    tmp1->remove(m_ui->languageComboBox->currentText());
    tmp1->insert(m_ui->languageComboBox->currentText(), tmp2);
    m_titleBlock->updateCurrentLanguage();
    qDebug() << "Text: "
             << m_titleBlock->currentLanguage()[m_ui->fieldComboBox->currentText()].lable;
}

void ISO7200ADialog::on_isEditableCheckBox_clicked(bool checked)
{
    std::shared_ptr<QMap<QString, QMap<QString, ISO7200ATextStruct>>> tmp1 =
            m_titleBlock->languageTexts();
    QMap<QString, ISO7200ATextStruct> tmp2 = tmp1->value(m_ui->languageComboBox->currentText());
    tmp2[m_ui->fieldComboBox->currentText()].isEditable = checked;
    tmp1->remove(m_ui->languageComboBox->currentText());
    tmp1->insert(m_ui->languageComboBox->currentText(), tmp2);
    m_titleBlock->updateCurrentLanguage();
    qDebug() << "Editable: "
             << m_titleBlock->currentLanguage()[m_ui->fieldComboBox->currentText()].lable;
}

void ISO7200ADialog::on_languageComboBox_currentTextChanged(const QString &arg1)
{
    m_titleBlock->setLanguage(arg1);
    on_fieldComboBox_currentTextChanged(m_ui->fieldComboBox->currentText());
}
