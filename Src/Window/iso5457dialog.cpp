#include "iso5457dialog.h"
#include "ui_iso5457dialog.h"

ISO5457Dialog::ISO5457Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ISO5457Dialog)
{
    ui->setupUi(this);
}

ISO5457Dialog::ISO5457Dialog(std::shared_ptr<ISO5457Options> newISO5457OPTIONS, QWidget *parent) :
    ISO5457Dialog(parent)
{
    setISO5457OPTIONS(newISO5457OPTIONS);
    ui->trimmingMarksCheckBox->setChecked(ISO5457OPTIONS->getTrimmingMarks());
    //ui->setupUi(this);
}

ISO5457Dialog::~ISO5457Dialog()
{
    delete ui;
}

std::shared_ptr<ISO5457Options> ISO5457Dialog::getISO5457OPTIONS() const
{
    return ISO5457OPTIONS;
}

void ISO5457Dialog::setISO5457OPTIONS(const std::shared_ptr<ISO5457Options> &newISO5457OPTIONS)
{
    ISO5457OPTIONS = newISO5457OPTIONS;
}


void ISO5457Dialog::on_buttonBox_accepted()
{
    ISO5457OPTIONS->setTrimmingMarks(ui->trimmingMarksCheckBox->isChecked());
}


void ISO5457Dialog::on_buttonBox_rejected()
{
}


void ISO5457Dialog::on_trimmingMarksCheckBox_stateChanged(int arg1)
{
}

