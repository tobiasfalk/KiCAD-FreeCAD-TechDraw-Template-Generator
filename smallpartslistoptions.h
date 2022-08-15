#ifndef SMALLPARTSLISTOPTIONS_H
#define SMALLPARTSLISTOPTIONS_H

#include <QDialog>

#include "templateoptions.h"
#include "changetitelblockfield.h"

namespace Ui {
class SmallPartsListOptions;
}

class SmallPartsListOptions : public QDialog
{
    Q_OBJECT

public:
    explicit SmallPartsListOptions(QWidget *parent = nullptr);
    ~SmallPartsListOptions();

    const QMap<QString, TitelblockField> &getSMALLPARTSLISTFIELDS() const;
    void setSMALLPARTSLISTFIELDS(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS);

private slots:
    void on_buttonBox_rejected();

    void on_opt1PushButton_clicked();

    void on_opt2PushButton_clicked();

    void on_opt3PushButton_clicked();

    void on_opt4PushButton_clicked();

    void on_opt5PushButton_clicked();

private:
    Ui::SmallPartsListOptions *ui;

    QMap<QString, TitelblockField> SMALLPARTSLISTFIELDS;
    QMap<QString, TitelblockField> SMALLPARTSLISTFIELDS_ORG;


    void loadStdOptions();
    void loadButtonText();
};

#endif // SMALLPARTSLISTOPTIONS_H
