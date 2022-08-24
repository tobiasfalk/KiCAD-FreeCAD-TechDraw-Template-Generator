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

    const QMap<QString, TitelblockField> &getFULLSHEETPARTSLISTFIELDS_FREECAD() const;
    void setFULLSHEETPARTSLISTFIELDS_FREECAD(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_FREECAD);

    const QMap<QString, TitelblockField> &getFULLSHEETPARTSLISTFIELDS_KICAD5() const;
    void setFULLSHEETPARTSLISTFIELDS_KICAD5(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_KICAD5);

    const QMap<QString, TitelblockField> &getFULLSHEETPARTSLISTFIELDS_KICAD6() const;
    void setFULLSHEETPARTSLISTFIELDS_KICAD6(const QMap<QString, TitelblockField> &newFULLSHEETPARTSLISTFIELDS_KICAD6);

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

    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_FREECAD;
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_FREECAD_ORG;

    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_KICAD5;
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_KICAD5_ORG;

    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_KICAD6;
    QMap<QString, TitelblockField> FULLSHEETPARTSLISTFIELDS_KICAD6_ORG;


    void loadStdOptions();
    void loadButtonText();
};

#endif // FULLSHEETSPARTLISTOPTIONS_H
