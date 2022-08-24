#include "changetitelblockfield.h"
#include "ui_changetitelblockfield.h"

const TitelblockField &ChangeTitelblockField::getFIELD_FREECAD()
{
    FIELD_FREECAD.Label = ui->lableLineEdit->text();
    FIELD_FREECAD.Name = ui->freeCADnameLineEdit->text();
    FIELD_FREECAD.Value = stringToStringList(ui->freeCADTextEdit->toPlainText());
    return FIELD_FREECAD;
}

void ChangeTitelblockField::setFIELD_FREECAD(const TitelblockField &newFIELD_FREECAD)
{
    FIELD_FREECAD = newFIELD_FREECAD;
    FIELD_FREECAD_ORG = FIELD_FREECAD;
    ui->lableLineEdit->setText(FIELD_FREECAD.Label);
    ui->freeCADnameLineEdit->setText(FIELD_FREECAD.Name);
    ui->freeCADTextEdit->setPlainText(stringListToString(FIELD_FREECAD.Value));
}

const TitelblockField &ChangeTitelblockField::getFIELD_KICAD5()
{
    FIELD_KICAD5.Label = ui->lableLineEdit->text();
    FIELD_KICAD5.Value = stringToStringList(ui->kiCAD5PlainTextEdit->toPlainText());
    return FIELD_KICAD5;
}

void ChangeTitelblockField::setFIELD_KICAD5(const TitelblockField &newFIELD_KICAD5)
{
    FIELD_KICAD5 = newFIELD_KICAD5;
    FIELD_KICAD5_ORG = newFIELD_KICAD5;
    ui->kiCAD5PlainTextEdit->setPlainText(stringListToString(FIELD_KICAD5.Value));
}

const TitelblockField &ChangeTitelblockField::getFIELD_KICAD6()
{
    FIELD_KICAD6.Label = ui->lableLineEdit->text();
    FIELD_KICAD6.Value = stringToStringList(ui->kiCAD6PlainTextEdit->toPlainText());
    return FIELD_KICAD6;
}

void ChangeTitelblockField::setFIELD_KICAD6(const TitelblockField &newFIELD_KICAD6)
{
    FIELD_KICAD6 = newFIELD_KICAD6;
    FIELD_KICAD5_ORG = newFIELD_KICAD6;
    ui->kiCAD6PlainTextEdit->setPlainText(stringListToString(FIELD_KICAD6.Value));
}

QString ChangeTitelblockField::stringListToString(QStringList list)
{
    QString ret = list[0];
    list.removeFirst();
    foreach(QString str, list)
    {
        ret += "\n" + str;
    }
    return ret;
}

QStringList ChangeTitelblockField::stringToStringList(QString str)
{
    return str.split('\n');
}

ChangeTitelblockField::ChangeTitelblockField(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeTitelblockField)
{
    ui->setupUi(this);
}

ChangeTitelblockField::~ChangeTitelblockField()
{
    delete ui;
}

void ChangeTitelblockField::on_buttonBox_rejected()
{
    FIELD_FREECAD = FIELD_FREECAD_ORG;
}

