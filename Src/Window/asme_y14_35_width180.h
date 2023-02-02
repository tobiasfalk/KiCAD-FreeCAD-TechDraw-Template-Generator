#ifndef ASME_Y14_35_WIDTH180_H
#define ASME_Y14_35_WIDTH180_H

#include <QDialog>

#include "templateoptions.h"
#include "changetitelblockfield.h"

namespace Ui {
class ASME_Y14_35_Width180;
}

///
/// \brief The ASME_Y14_35_Width180 classcontains all options for the ASME Y14.35 Revision history style, whit this class it is alsow posible to change them with a window.
///
class ASME_Y14_35_Width180 : public QDialog
{
    Q_OBJECT

public:
    ///
    /// \brief ASME_Y14_35_Width180 constructor
    /// \param parent is the Qt Parent parameter
    ///
    explicit ASME_Y14_35_Width180(QWidget *parent = nullptr);
    ///
    /// \brief ASME_Y14_35_Width180 deconstructor
    ///
    ~ASME_Y14_35_Width180();

    ///
    /// \brief getREVHISTORYFIELDS_FREECAD returns the RevHistory fields for the FreeCAD Template
    /// \return RevHistory fields for the FreeCAD Template
    ///
    const QMap<QString, TitelblockField> &getREVHISTORYFIELDS_FREECAD() const;
    ///
    /// \brief setREVHISTORYFIELDS_FREECAD sets the RevHistory fields for the FreeCAD Template
    /// \param newREVHISTORYFIELDS_FREECAD the RevHistory fields for the FreeCAD Template
    ///
    void setREVHISTORYFIELDS_FREECAD(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_FREECAD);
    ///
    /// \brief resetToOrigin resets all parameter to the original set parameter(thos of the standart or that where set)
    ///
    void resetToOrigin();

    ///
    /// \brief getREVHISTORYFIELDS_KICAD5 returns the RevHistory fields for the KiCAD 5 Template
    /// \return the RevHistory fields for the KiCAD 5 Template
    ///
    const QMap<QString, TitelblockField> &getREVHISTORYFIELDS_KICAD5() const;
    ///
    /// \brief setREVHISTORYFIELDS_KICAD5 sets the RevHistory fields for the KiCAD 5 Template
    /// \param newREVHISTORYFIELDS_KICAD5 the RevHistory fields for the KiCAD 5 Template
    ///
    void setREVHISTORYFIELDS_KICAD5(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_KICAD5);

    ///
    /// \brief getREVHISTORYFIELDS_KICAD6 returns the RevHistory fields for the KiCAD 6 Template
    /// \return the RevHistory fields for the KiCAD 6 Template
    ///
    const QMap<QString, TitelblockField> &getREVHISTORYFIELDS_KICAD6() const;
    ///
    /// \brief setREVHISTORYFIELDS_KICAD6 sets the RevHistory fields for the KiCAD 6 Template
    /// \param newREVHISTORYFIELDS_KICAD6 the RevHistory fields for the KiCAD 6 Template
    ///
    void setREVHISTORYFIELDS_KICAD6(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_KICAD6);

    ///
    /// \brief getREVHISTORYFIELDS_PDF returns the RevHistory fields for the PDF Template
    /// \return the RevHistory fields for the PDF Template
    ///
    const QMap<QString, TitelblockField> &getREVHISTORYFIELDS_PDF() const;
    ///
    /// \brief setREVHISTORYFIELDS_PDF sets the RevHistory fields for the PDF Template
    /// \param newREVHISTORYFIELDS_PDF the RevHistory fields for the PDF Template
    ///
    void setREVHISTORYFIELDS_PDF(const QMap<QString, TitelblockField> &newREVHISTORYFIELDS_PDF);

    ///
    /// \brief getNumRev returns the number of revisions
    /// \return
    ///
    unsigned int getNumRev();
    ///
    /// \brief setNumRev sets the number of revisions
    /// \param newNumRev
    ///
    void setNumRev(unsigned int newNumRev);

private slots:
    ///
    /// \brief on_buttonBox_rejected is the event when the reject button is clicked
    ///
    void on_buttonBox_rejected();

    ///
    /// \brief on_headPushButton_clicked is the event when the head option buttion is clicked
    ///
    void on_headPushButton_clicked();

    ///
    /// \brief on_opt1PushButton_clicked is the event when the option 1 buttion is clicked
    ///
    void on_opt1PushButton_clicked();

    ///
    /// \brief on_opt2PushButton_clicked is the event when the option 2 buttion is clicked
    ///
    void on_opt2PushButton_clicked();

    ///
    /// \brief on_opt3PushButton_clicked is the event when the option 3 buttion is clicked
    ///
    void on_opt3PushButton_clicked();

    ///
    /// \brief on_opt4PushButton_clicked is the event when the option 4 buttion is clicked
    ///
    void on_opt4PushButton_clicked();

    ///
    /// \brief on_opt5PushButton_clicked is the event when the option 5 buttion is clicked
    ///
    void on_opt5PushButton_clicked();

private:
    ///
    /// \brief ui is the pointer fo the qt UI
    ///
    Ui::ASME_Y14_35_Width180 *ui;

    ///
    /// \brief REVHISTORYFIELDS_FREECAD is the map with all the FreeCAD fields
    ///
    QMap<QString, TitelblockField> REVHISTORYFIELDS_FREECAD;
    ///
    /// \brief REVHISTORYFIELDS_ORG_FREECAD is the map with all the origonal FreeCAD fields
    ///
    QMap<QString, TitelblockField> REVHISTORYFIELDS_ORG_FREECAD;
    ///
    /// \brief REVHISTORYFIELDS_KICAD5 is the map with all the KiCAD 5 fields
    ///
    QMap<QString, TitelblockField> REVHISTORYFIELDS_KICAD5;
    ///
    /// \brief REVHISTORYFIELDS_ORG_KICAD5 is the map with all the origonal KiCAD 5 fields
    ///
    QMap<QString, TitelblockField> REVHISTORYFIELDS_ORG_KICAD5;
    ///
    /// \brief REVHISTORYFIELDS_KICAD6 is the map with all the KiCAD 6 fields
    ///
    QMap<QString, TitelblockField> REVHISTORYFIELDS_KICAD6;
    ///
    /// \brief REVHISTORYFIELDS_ORG_KICAD6 is the map with all the origonal KiCAD 6 fields
    ///
    QMap<QString, TitelblockField> REVHISTORYFIELDS_ORG_KICAD6;
    ///
    /// \brief REVHISTORYFIELDS_PDF is the map with all the PDF fields
    ///
    QMap<QString, TitelblockField> REVHISTORYFIELDS_PDF;
    ///
    /// \brief REVHISTORYFIELDS_ORG_PDF is the map with all the origonal PDF fields
    ///
    QMap<QString, TitelblockField> REVHISTORYFIELDS_ORG_PDF;


    ///
    /// \brief loadStdOptions loads the standart values for the fields
    ///
    void loadStdOptions();
    ///
    /// \brief loadButtonText loads the lable as text to display
    ///
    void loadButtonText();

    ///
    /// \brief numRev is the number of revisions
    ///
    unsigned int numRev = 1;
};

#endif // ASME_Y14_35_WIDTH180_H
