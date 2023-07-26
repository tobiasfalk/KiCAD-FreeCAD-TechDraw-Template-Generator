#ifndef ISO5457DIALOG_H
#define ISO5457DIALOG_H

#include <QDialog>

#include "iso5457options.h"

namespace Ui {
class ISO5457Dialog;
}

class ISO5457Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit ISO5457Dialog(QWidget *parent = nullptr);
    explicit ISO5457Dialog(std::shared_ptr<ISO5457Options> newISO5457OPTIONS, QWidget *parent = nullptr);
    ~ISO5457Dialog();

    std::shared_ptr<ISO5457Options> getISO5457OPTIONS() const;
    void setISO5457OPTIONS(const std::shared_ptr<ISO5457Options> &newISO5457OPTIONS);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_trimmingMarksCheckBox_stateChanged(int arg1);

private:
    Ui::ISO5457Dialog *ui;

    std::shared_ptr<ISO5457Options> ISO5457OPTIONS;
};

#endif // ISO5457DIALOG_H
