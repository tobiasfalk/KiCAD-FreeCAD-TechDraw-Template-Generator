#ifndef ASME_Y14_35_WIDTH180_H
#define ASME_Y14_35_WIDTH180_H

#include <QDialog>

#include "templateoptions.h"
#include "changetitelblockfield.h"

namespace Ui {
class ASME_Y14_35_Width180;
}

class ASME_Y14_35_Width180 : public QDialog
{
    Q_OBJECT

public:
    explicit ASME_Y14_35_Width180(QWidget *parent = nullptr);
    ~ASME_Y14_35_Width180();

    const QMap<QString, TitelblockField> &getREVHISTORYFIELDS_FREECAD() const;
    void setREVHISTORYFIELDS_FREECAD(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_FREECAD);
    void resetToOrigin();

    const QMap<QString, TitelblockField> &getREVHISTORYFIELDS_KICAD5() const;
    void setREVHISTORYFIELDS_KICAD5(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_KICAD5);

    const QMap<QString, TitelblockField> &getREVHISTORYFIELDS_KICAD6() const;
    void setREVHISTORYFIELDS_KICAD6(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_KICAD6);

private slots:
    void on_buttonBox_rejected();

    void on_headPushButton_clicked();

    void on_opt1PushButton_clicked();

    void on_opt2PushButton_clicked();

    void on_opt3PushButton_clicked();

    void on_opt4PushButton_clicked();

    void on_opt5PushButton_clicked();

private:
    Ui::ASME_Y14_35_Width180 *ui;

    QMap<QString, TitelblockField> REVHISTORYFIELDS_FREECAD;
    QMap<QString, TitelblockField> REVHISTORYFIELDS_ORG_FREECAD;
    QMap<QString, TitelblockField> REVHISTORYFIELDS_KICAD5;
    QMap<QString, TitelblockField> REVHISTORYFIELDS_ORG_KICAD5;
    QMap<QString, TitelblockField> REVHISTORYFIELDS_KICAD6;
    QMap<QString, TitelblockField> REVHISTORYFIELDS_ORG_KICAD6;


    void loadStdOptions();
    void loadButtonText();
};

#endif // ASME_Y14_35_WIDTH180_H
