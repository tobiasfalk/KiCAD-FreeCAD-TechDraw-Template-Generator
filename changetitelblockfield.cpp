#include "changetitelblockfield.h"
#include "ui_changetitelblockfield.h"

const TitelblockField &ChangeTitelblockField::getFIELD()
{
    FIELD.Label = ui->lableLineEdit->text();
    FIELD.ValueKiCAD5 = stringToStringList(ui->kiCAD5PlainTextEdit->toPlainText());
    FIELD.ValueKiCAD6 = stringToStringList(ui->kiCAD6PlainTextEdit->toPlainText());
    return FIELD;
}

void ChangeTitelblockField::setFIELD(const TitelblockField &newFIELD)
{
    FIELD = newFIELD;
    FIELD_ORG = FIELD;
    ui->lableLineEdit->setText(FIELD.Label);
    ui->kiCAD5PlainTextEdit->setPlainText(stringListToString(FIELD.ValueKiCAD5));
    ui->kiCAD6PlainTextEdit->setPlainText(stringListToString(FIELD.ValueKiCAD6));
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
    FIELD = FIELD_ORG;
}

