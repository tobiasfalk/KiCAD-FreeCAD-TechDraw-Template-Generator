#ifndef CHANGETITELBLOCKFIELD_H
#define CHANGETITELBLOCKFIELD_H

#include <QDialog>
#include <QString>

#include "templateoptions.h"

namespace Ui {
class ChangeTitelblockField;
}

class ChangeTitelblockField : public QDialog
{
    Q_OBJECT

private:
    Ui::ChangeTitelblockField *ui;

    TitelblockField FIELD_FREECAD;
    TitelblockField FIELD_FREECAD_ORG;
    TitelblockField FIELD_KICAD5;
    TitelblockField FIELD_KICAD5_ORG;
    TitelblockField FIELD_KICAD6;
    TitelblockField FIELD_KICAD6_ORG;

    QString stringListToString(QStringList list);
    QStringList stringToStringList(QString str);

public:
    explicit ChangeTitelblockField(QWidget *parent = nullptr);
    ~ChangeTitelblockField();

    const TitelblockField &getFIELD_FREECAD();
    void setFIELD_FREECAD(const TitelblockField &newFIELD_FREECAD);

    const TitelblockField &getFIELD_KICAD5();
    void setFIELD_KICAD5(const TitelblockField &newFIELD_KICAD5);

    const TitelblockField &getFIELD_KICAD6();
    void setFIELD_KICAD6(const TitelblockField &newFIELD_KICAD6);

private slots:
    void on_buttonBox_rejected();
};

#endif // CHANGETITELBLOCKFIELD_H
