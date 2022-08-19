#ifndef FULLSHEETSPARTLISTOPTIONS_H
#define FULLSHEETSPARTLISTOPTIONS_H

#include <QDialog>

#include "templateoptions.h"
#include "changetitelblockfield.h"

namespace Ui {
class FullSheetsPartListOptions;
}

class FullSheetsPartListOptions : public QDialog
{
    Q_OBJECT

public:
    explicit FullSheetsPartListOptions(QWidget *parent = nullptr);
    ~FullSheetsPartListOptions();

    const QMap<QString, TitelblockField> &getFULLSHEETPARTSLISTFIELDS() const;
    void setFULLSHEETPARTSLISTFIELDS(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS);
    void resetToOrigin();

private slots:
    void on_opt1PushButton_clicked();

    void on_opt2PushButton_clicked();

    void on_opt3PushButton_clicked();

    void on_opt4PushButton_clicked();

    void on_opt5PushButton_clicked();

    void on_opt6PushButton_clicked();

private:
    Ui::FullSheetsPartListOptions *ui;

    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS;
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_ORG;


    void loadStdOptions();
    void loadButtonText();
};

#endif // FULLSHEETSPARTLISTOPTIONS_H
