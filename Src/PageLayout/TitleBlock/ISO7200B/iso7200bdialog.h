#ifndef ISO7200BDIALOG_H
#define ISO7200BDIALOG_H

#include <QDialog>
#include "PageLayout/TitleBlock/ISO7200B/iso7200b.h"

namespace Ui {
class ISO7200BDialog;
}

class ISO7200BDialog : public QDialog
{
    Q_OBJECT

public:
    ///
    /// \brief ISO7200BDialog the base constructor
    /// \param parent the Qt parent pointer
    ///
    explicit ISO7200BDialog(QWidget *parent = nullptr);
    ~ISO7200BDialog();

    ///
    /// \brief titleBlock returns the currently edited title block
    /// \return the title block
    ///
    const std::shared_ptr<ISO7200B> &titleBlock() const;
    ///
    /// \brief setTitleBlock sets the title block to edit
    /// \param newTitleBlock
    ///
    void setTitleBlock(const std::shared_ptr<ISO7200B> &newTitleBlock);

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
    Ui::ISO7200BDialog *m_ui;

    ///
    /// \brief m_titleBlock the used title-block
    ///
    std::shared_ptr<ISO7200B> m_titleBlock;

    ///
    /// \brief initLanguages initializes the language combo box
    ///
    void initLanguages();
};

#endif // ISO7200BDIALOG_H
