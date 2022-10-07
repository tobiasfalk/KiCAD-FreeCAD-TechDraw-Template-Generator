#ifndef CHANGETITELBLOCKFIELD_H
#define CHANGETITELBLOCKFIELD_H

#include <QDialog>
#include <QString>

#include "templateoptions.h"

namespace Ui {
class ChangeTitelblockField;
}

///
/// \brief The ChangeTitelblockField class changes a field(titelblockfield).
///
class ChangeTitelblockField : public QDialog
{
    Q_OBJECT

private:
    Ui::ChangeTitelblockField *ui;

    ///
    /// \brief FIELD_FREECAD The Field for the FreeCAD version of the Template
    ///
    TitelblockField FIELD_FREECAD;
    ///
    /// \brief FIELD_FREECAD_ORG The origonal Field for the FreeCAD version of the Template, used when presed reset or reset is caled
    ///
    TitelblockField FIELD_FREECAD_ORG;
    ///
    /// \brief FIELD_KICAD5 The Field for the KiCAD 5 version of the Template
    ///
    TitelblockField FIELD_KICAD5;
    ///
    /// \brief FIELD_KICAD5_ORG The origonal Field for the KiCAD 5 version of the Template, used when presed reset or reset is caled
    ///
    TitelblockField FIELD_KICAD5_ORG;
    ///
    /// \brief FIELD_KICAD6 The Field for the KiCAD 6 version of the Template
    ///
    TitelblockField FIELD_KICAD6;
    ///
    /// \brief FIELD_KICAD6_ORG The origonal Field for the KiCAD 6 version of the Template, used when presed reset or reset is caled
    ///
    TitelblockField FIELD_KICAD6_ORG;
    ///
    /// \brief FIELD_PDF The Field for the PDF and Eagle version of the Template
    ///
    TitelblockField FIELD_PDF;
    ///
    /// \brief FIELD_PDF_ORG The origonal Field for the PDF and Eagle version of the Template, used when presed reset or reset is caled
    ///
    TitelblockField FIELD_PDF_ORG;

    ///
    /// \brief stringListToString makes a StringList to a string and places a ${N} betwen the List elements
    /// \param list the list to process
    /// \return the relustig String
    ///
    QString stringListToString(QStringList list);
    ///
    /// \brief stringToStringList splits the String in to a Stringlist at ${N}
    /// \param str the string to process
    /// \return the resulting List
    ///
    QStringList stringToStringList(QString str);

    ///
    /// \brief setProjectionMethod sets the Projektion Methode combobox to the given value
    /// \param methode
    ///
    void setProjectionMethod(ProjectionMethodType methode);
    ///
    /// \brief getProjectionMethod returns the value of the Projektion Methode combobox
    /// \return
    ///
    ProjectionMethodType getProjectionMethod();

public:
    ///
    /// \brief ChangeTitelblockField the standart constructor
    /// \param parent
    ///
    explicit ChangeTitelblockField(QWidget *parent = nullptr);
    ///
    /// \brief ~ChangeTitelblockField the deconstructor
    ///
    ~ChangeTitelblockField();

    ///
    /// \brief getFIELD_FREECAD is the geter methoed for FIELD_FREECAD
    /// \return the FreeCAD field
    ///
    const TitelblockField &getFIELD_FREECAD();
    ///
    /// \brief setFIELD_FREECAD is the setter methoed for FIELD_FREECAD
    /// \param newFIELD_FREECAD the FreeCAD field
    ///
    void setFIELD_FREECAD(const TitelblockField &newFIELD_FREECAD);

    ///
    /// \brief getFIELD_KICAD5 is the geter methoed for FIELD_KICAD5
    /// \return the KiCAD 5 field
    ///
    const TitelblockField &getFIELD_KICAD5();
    ///
    /// \brief setFIELD_KICAD5 is the setter methoed for FIELD_KICAD5
    /// \param newFIELD_KICAD5 the KiCAD 5 field
    ///
    void setFIELD_KICAD5(const TitelblockField &newFIELD_KICAD5);

    ///
    /// \brief getFIELD_KICAD6 is the geter methoed for FIELD_KICAD6
    /// \return the KiCAD 6 field
    ///
    const TitelblockField &getFIELD_KICAD6();
    ///
    /// \brief setFIELD_KICAD6 is the setter methoed for FIELD_KICAD6
    /// \param newFIELD_KICAD6 the KiCAD 6 field
    ///
    void setFIELD_KICAD6(const TitelblockField &newFIELD_KICAD6);

    ///
    /// \brief getFIELD_PDF is the geter methoed for FIELD_KICAD6
    /// \return
    ///
    const TitelblockField &getFIELD_PDF();
    ///
    /// \brief setFIELD_PDF
    /// \param newFIELD_PDF
    ///
    void setFIELD_PDF(const TitelblockField &newFIELD_PDF);

private slots:
    ///
    /// \brief on_buttonBox_rejected resets all fields
    ///
    void on_buttonBox_rejected();
};

#endif // CHANGETITELBLOCKFIELD_H
