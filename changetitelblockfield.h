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

    TitelblockField FIELD;
    TitelblockField FIELD_ORG;

    QString stringListToString(QStringList list);
    QStringList stringToStringList(QString str);

public:
    explicit ChangeTitelblockField(QWidget *parent = nullptr);
    ~ChangeTitelblockField();
    const TitelblockField &getFIELD();
    void setFIELD(const TitelblockField &newFIELD);
private slots:
    void on_buttonBox_rejected();
};

#endif // CHANGETITELBLOCKFIELD_H
