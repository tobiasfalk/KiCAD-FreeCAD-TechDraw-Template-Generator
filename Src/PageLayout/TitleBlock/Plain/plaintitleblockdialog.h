#ifndef PLAINTITLEBLOCKDIALOG_H
#define PLAINTITLEBLOCKDIALOG_H

#include <QDialog>

#include "PageLayout/TitleBlock/Plain/plaintitleblock.h"

namespace Ui {
class PlainTitleBlockDialog;
}

class PlainTitleBlockDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlainTitleBlockDialog(QWidget *parent = nullptr);
    ~PlainTitleBlockDialog();

    std::shared_ptr<PlainTitleBlock> titleBlock() const;
    void setTitleBlock(const std::shared_ptr<PlainTitleBlock> &newTitleBlock);

private:
    Ui::PlainTitleBlockDialog *m_ui;

    std::shared_ptr<PlainTitleBlock> m_titleBlock;
};

#endif // PLAINTITLEBLOCKDIALOG_H
