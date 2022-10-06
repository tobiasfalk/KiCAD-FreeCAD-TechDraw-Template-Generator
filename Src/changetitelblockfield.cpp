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
    setProjectionMethod(FIELD_FREECAD.ProjectionMethod);
}

const TitelblockField &ChangeTitelblockField::getFIELD_KICAD5()
{
    FIELD_KICAD5.Label = ui->lableLineEdit->text();
    FIELD_KICAD5.Value = stringToStringList(ui->kiCAD5PlainTextEdit->toPlainText());
    FIELD_KICAD5.ProjectionMethod = getProjectionMethod();
    return FIELD_KICAD5;
}

void ChangeTitelblockField::setFIELD_KICAD5(const TitelblockField &newFIELD_KICAD5)
{
    FIELD_KICAD5 = newFIELD_KICAD5;
    FIELD_KICAD5_ORG = newFIELD_KICAD5;
    ui->kiCAD5PlainTextEdit->setPlainText(stringListToString(FIELD_KICAD5.Value));
    setProjectionMethod(FIELD_KICAD5.ProjectionMethod);
}

const TitelblockField &ChangeTitelblockField::getFIELD_KICAD6()
{
    FIELD_KICAD6.Label = ui->lableLineEdit->text();
    FIELD_KICAD6.Value = stringToStringList(ui->kiCAD6PlainTextEdit->toPlainText());
    FIELD_FREECAD.ProjectionMethod = getProjectionMethod();
    return FIELD_KICAD6;
}

void ChangeTitelblockField::setFIELD_KICAD6(const TitelblockField &newFIELD_KICAD6)
{
    FIELD_KICAD6 = newFIELD_KICAD6;
    FIELD_KICAD5_ORG = newFIELD_KICAD6;
    ui->kiCAD6PlainTextEdit->setPlainText(stringListToString(FIELD_KICAD6.Value));
    setProjectionMethod(FIELD_KICAD6.ProjectionMethod);
}

const TitelblockField &ChangeTitelblockField::getFIELD_PDF()
{
    FIELD_PDF.Label = ui->lableLineEdit->text();
    FIELD_PDF.Value = stringToStringList(ui->pdfTextEdit->toPlainText());
    FIELD_PDF.ProjectionMethod = getProjectionMethod();
    return FIELD_PDF;
}

void ChangeTitelblockField::setFIELD_PDF(const TitelblockField &newFIELD_PDF)
{
    FIELD_PDF = newFIELD_PDF;
    FIELD_PDF_ORG = newFIELD_PDF;
    ui->pdfTextEdit->setPlainText(stringListToString(FIELD_PDF.Value));
    setProjectionMethod(FIELD_PDF.ProjectionMethod);
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

void ChangeTitelblockField::setProjectionMethod(ProjectionMethodType methode)
{
    switch (methode) {
    case ProjectionMethodType::None:
        ui->projectionMethodComboBox->setCurrentText("None");
        break;
    case ProjectionMethodType::FirstAngle:
        ui->projectionMethodComboBox->setCurrentText("First Angle");
        break;
    case ProjectionMethodType::ThirdAngle:
        ui->projectionMethodComboBox->setCurrentText("Third Angle");
        break;
    default:
        ui->projectionMethodComboBox->setCurrentText("None");
        break;
    }
}

ProjectionMethodType ChangeTitelblockField::getProjectionMethod()
{
    if(ui->projectionMethodComboBox->currentText() == "None")
    {
        return ProjectionMethodType::None;
    }else if(ui->projectionMethodComboBox->currentText() == "First Angle")
    {
        return ProjectionMethodType::FirstAngle;
    }else if(ui->projectionMethodComboBox->currentText() == "Third Angle")
    {
        return ProjectionMethodType::ThirdAngle;
    }
    return ProjectionMethodType::None;
}

ChangeTitelblockField::ChangeTitelblockField(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeTitelblockField)
{
    ui->setupUi(this);
    ui->projectionMethodComboBox->addItem("None");
    ui->projectionMethodComboBox->addItem("First Angle");
    ui->projectionMethodComboBox->addItem("Third Angle");
}

ChangeTitelblockField::~ChangeTitelblockField()
{
    delete ui;
}

void ChangeTitelblockField::on_buttonBox_rejected()
{
    FIELD_FREECAD = FIELD_FREECAD_ORG;
}

