#ifndef PLAINTITLEBLOCKDIALOG_H
#define PLAINTITLEBLOCKDIALOG_H

#include <QDialog>

#include "PageLayout/TitleBlock/Plain/plaintitleblock.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class PlainTitleBlockDialog;
}
QT_END_NAMESPACE

///
/// \brief The PlainTitleBlockDialog class creates a dialog for setting all the parameters of the
/// PlainTitleBlock
///
class PlainTitleBlockDialog : public QDialog
{
    Q_OBJECT

public:
    ///
    /// \brief PlainTitleBlockDialog is the base constructor
    /// \param parent is the Qt parent pointer
    ///
    explicit PlainTitleBlockDialog(QWidget *parent = nullptr);
    ~PlainTitleBlockDialog();

    ///
    /// \brief titleBlock returns the title-block with the set parameters
    /// \return the title-block
    ///
    std::shared_ptr<PlainTitleBlock> titleBlock() const;
    ///
    /// \brief setTitleBlock sets the parameters to those of the title-block
    /// \param newTitleBlock
    ///
    void setTitleBlock(const std::shared_ptr<PlainTitleBlock> &newTitleBlock);

private:
    ///
    /// \brief m_ui the Qt Ui object
    ///
    Ui::PlainTitleBlockDialog *m_ui;

    ///
    /// \brief m_titleBlock the used title-block
    ///
    std::shared_ptr<PlainTitleBlock> m_titleBlock;
};

#endif // PLAINTITLEBLOCKDIALOG_H
