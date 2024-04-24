#ifndef PLAINFRAMEDIALOG_H
#define PLAINFRAMEDIALOG_H

#include <QDialog>
#include "PageLayout/Frame/Plain/plainframe.h"

namespace Ui {
class PlainFrameDialog;
}

class PlainFrameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlainFrameDialog(QWidget *parent = nullptr);
    ~PlainFrameDialog();

    void setFrame(std::shared_ptr<PlainFrame> newFrame);
    std::shared_ptr<PlainFrame> getFrame();

private slots:
    void on_LineWidthDoubleSpinBox_editingFinished();

    void on_TopDoubleSpinBox_editingFinished();

    void on_RigthDoubleSpinBox_editingFinished();

    void on_LeftDoubleSpinBox_editingFinished();

    void on_BottomDoubleSpinBox_editingFinished();

private:
    Ui::PlainFrameDialog *m_ui;
    std::shared_ptr<PlainFrame> m_frame;
};

#endif // PLAINFRAMEDIALOG_H
