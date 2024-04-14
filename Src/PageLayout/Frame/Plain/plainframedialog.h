#ifndef PLAINFRAMEDIALOG_H
#define PLAINFRAMEDIALOG_H

#include <QDialog>
#include "Plain/plainframe.h"

namespace Ui {
class PlainFrameDialog;
}

class PlainFrameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlainFrameDialog(QWidget *parent = nullptr);
    ~PlainFrameDialog();

    std::shared_ptr<PlainFrame> getFrame();

private:
    Ui::PlainFrameDialog *m_ui;
};

#endif // PLAINFRAMEDIALOG_H
