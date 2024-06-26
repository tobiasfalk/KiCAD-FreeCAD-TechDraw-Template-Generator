#ifndef ISO7200ADIALOG_H
#define ISO7200ADIALOG_H

#include <QDialog>
#include "PageLayout/TitleBlock/ISO7200A/iso7200a.h"

namespace Ui {
class ISO7200ADialog;
}

class ISO7200ADialog : public QDialog
{
    Q_OBJECT

public:
    explicit ISO7200ADialog(QWidget *parent = nullptr);
    ~ISO7200ADialog();

    std::shared_ptr<ISO7200A> titleBlock() const;
    void setTitleBlock(const std::shared_ptr<ISO7200A> &newTitleBlock);

private slots:
    void on_fieldComboBox_currentTextChanged(const QString &arg1);

    void on_lableLineEdit_textEdited(const QString &arg1);

    void on_lableLineEdit_textChanged(const QString &arg1);

    void on_textLineEdit_textEdited(const QString &arg1);

    void on_isEditableCheckBox_clicked(bool checked);

    void on_languageComboBox_currentTextChanged(const QString &arg1);

    void on_LogoPathPushButton_clicked();

    void on_LogoPathLineEdit_textEdited(const QString &arg1);

private:
    Ui::ISO7200ADialog *m_ui;

    ///
    /// \brief m_titleBlock the used title-block
    ///
    std::shared_ptr<ISO7200A> m_titleBlock;

    void initLanguages();
};

#endif // ISO7200ADIALOG_H
