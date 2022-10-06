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

    const QMap<QString, TitelblockField> &getSMALLPARTSLISTFIELDS_FREECAD() const;
    void setSMALLPARTSLISTFIELDS_FREECAD(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS_FREECAD);

    const QMap<QString, TitelblockField> &getSMALLPARTSLISTFIELDS_KICAD5() const;
    void setSMALLPARTSLISTFIELDS_KICAD5(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS_KICAD5);

    const QMap<QString, TitelblockField> &getSMALLPARTSLISTFIELDS_KICAD6() const;
    void setSMALLPARTSLISTFIELDS_KICAD6(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS_KICAD6);

    const QMap<QString, TitelblockField> &getSMALLPARTSLISTFIELDS_PDF() const;
    void setSMALLPARTSLISTFIELDS_PDF(const QMap<QString, TitelblockField> &newSMALLPARTSLISTFIELDS_PDF);

private slots:
    void on_buttonBox_rejected();

    void on_opt1PushButton_clicked();

    void on_opt2PushButton_clicked();

    void on_opt3PushButton_clicked();

    void on_opt4PushButton_clicked();

    void on_opt5PushButton_clicked();

private:
    Ui::SmallPartsListOptions *ui;

    QMap<QString, TitelblockField> SMALLPARTSLISTFIELDS_FREECAD;
    QMap<QString, TitelblockField> SMALLPARTSLISTFIELDS_FREECAD_ORG;

    QMap<QString, TitelblockField> SMALLPARTSLISTFIELDS_KICAD5;
    QMap<QString, TitelblockField> SMALLPARTSLISTFIELDS_KICAD5_ORG;

    QMap<QString, TitelblockField> SMALLPARTSLISTFIELDS_KICAD6;
    QMap<QString, TitelblockField> SMALLPARTSLISTFIELDS_KICAD6_ORG;

    QMap<QString, TitelblockField> SMALLPARTSLISTFIELDS_PDF;
    QMap<QString, TitelblockField> SMALLPARTSLISTFIELDS_PDF_ORG;


    void loadStdOptions();
    void loadButtonText();
};

#endif // SMALLPARTSLISTOPTIONS_H
